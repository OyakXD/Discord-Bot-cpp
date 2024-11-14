#ifndef CHAT_COMMAND_H
#define CHAT_COMMAND_H

#include "commands/ICommand.h"
#include <curl/curl.h>
#include <fstream>
#include <dpp/dpp.h>
#include <sstream>
#include <openai/openai.hpp>
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
      try{
        config_file >> config;
      } catch (const std::exception& e){
        event.reply("Erro ao ler o arquivo de configuração");
        return;
      }

      if(!config.contains("openai_api_key")){
        event.reply("Chave de API não encontrada no arquivo de configuração");
        return;
      }

      string api_key = config["openai_api_key"];
      if(api_key.empty()){
        event.reply("Chave de API está vázia");
        return;
      }

      openai::OpenAI openai_instance(api_key);
      

      try{
        nlohmann::json request_body = {
          {"model", "gpt-3.5-turbo"},
          {"prompt", question},
          {"max_tokens", 100}
        };

        auto response = openai_instance.completion.create(request_body);

        if(response.contains("choices") && response["choices"].is_array() && !response["choices"].empty()){
          string response_text = response["choices"][0]["text"];
          event.reply(dpp::message().set_content(response_text));
        } else {
          event.reply("Erro ao obter resposta do ChatGPT");
        }
      } catch (const std::exception& e){
        string error_message = e.what();

        if(error_message.find("insufficient_quota") != string::npos){
          event.reply("Cota de uso da API atingida. Tente novamente mais tarde.");
        } else {
          event.reply("Erro ao obter resposta do ChatGPT: " + error_message);
        }
      }
    }
};

#endif
