#ifndef CHAT_COMMAND_H
#define CHAT_COMMAND_H

#include "commands/ICommand.h"
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <sstream>
using namespace std;

class ChatCommand : public ICommand {
  public:
    string get_name() const override {
      return "chatgpt";
    }

    string get_description() const override {
      return "Faça uma pergunta ao ChatGPT";
    }

    void execute(const slashcommand_t& event) const override {
      string question;
      auto options = event.command.get_command_interaction().options;

      if (!options.empty()) {
        question = std::get<string>(options[0].value);  
      } else {
        event.reply("Por favor, insira uma pergunta.");
        return;
      }

      ifstream config_file("../secretkey.json");
      if (!config_file.is_open()) {
        event.reply("Erro ao abrir o arquivo de configuração");
        return;
      }

      nlohmann::json config;
      try {
        config_file >> config;
      } catch (const std::exception& e) {
        event.reply("Erro ao ler o arquivo de configuração");
        return;
      }

      if (!config.contains("openai_api_key")) {
        event.reply("Chave da API não encontrada no arquivo de configuração");
        return;
      }

      string api_key = config["openai_api_key"];
      CURL* curl;
      CURLcode res;
      std::stringstream response_stream;

      curl_global_init(CURL_GLOBAL_DEFAULT);
      curl = curl_easy_init();

      if (curl) {
        struct curl_slist* headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/json");
        headers = curl_slist_append(headers, ("Authorization: Bearer " + api_key).c_str());

        nlohmann::json json_body = {
          {"prompt", question},
          {"max_tokens", 100}
        };

        curl_easy_setopt(curl, CURLOPT_URL, "https://api.openai.com/v1/engines/davinci/completions");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json_body.dump().c_str());

        // Função para escrever a resposta na string
        auto write_callback = [](void* contents, size_t size, size_t nmemb, void* userp) -> size_t {
                size_t realsize = size * nmemb;
                std::stringstream* response_stream = (std::stringstream*)userp;

                if (response_stream && contents) {
                    response_stream->write((char*)contents, realsize);
                } else {
                    std::cerr << "Erro: Ponteiro nulo no callback de escrita" << std::endl;
                }

                return realsize;
            };

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);    
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_stream);

        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
          event.reply("Erro ao fazer a requisição ao ChatGPT");
        } else {
          try {
            auto jsonData = nlohmann::json::parse(response_stream.str());

            if (jsonData.contains("choices") && jsonData["choices"].is_array() && !jsonData["choices"].empty()) {
              string response = jsonData["choices"][0]["text"];
              event.reply(dpp::message().set_content(response));
            } else {
              event.reply("Não foi possível obter uma resposta do ChatGPT");
            }
          } catch (const nlohmann::json::exception& e) {
            event.reply("Erro ao processar a resposta JSON");
          }
        }

        curl_easy_cleanup(curl);
        curl_slist_free_all(headers);
      } else {
        event.reply("Erro ao inicializar o CURL");
      }
      curl_global_cleanup();
    }
};

#endif
