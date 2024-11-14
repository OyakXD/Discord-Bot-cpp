#ifndef CLEAR_COMMAND_h
#define CLEAR_COMMAND_h

#include "commands/ICommand.h"
#include <string>
#include <sstream>
using namespace std;

class ClearCommand : public ICommand {
  public:
    string get_name() const override {
      return "clear";
    }

    string get_description() const override {
      return "Limpar mensagens do chat";
    }

    void execute(const slashcommand_t& event) const override {

      int num_messages = 0;
      auto options = event.command.get_command_interaction().options;

      if(!options.empty()){
        num_messages = std::get<int>(options[0].value);  
      } else {
        event.reply("Por favor, insira o número de mensagens a serem apagadas.");
        return;
      }

      if(num_messages <= 0){
        event.reply("O numero de mensagens deve ser maior que zero.");
      }

      dpp::snowflake channel_id = event.command.channel_id;

      event.from->creator->message_get(channel_id, num_messages,
       [event, num_messages, channel_id](const dpp::confirmation_callback_t& callback) mutable {
        if(callback.is_error()){
          event.reply("Erro ao buscar mensagens");
          return;
        }

        auto messages = std::get<dpp::message_map>(callback.value);
        std::vector<dpp::snowflake> message_ids;

        for(const auto& msg : messages) {
          message_ids.push_back(msg.first);
        }

        event.from->creator->message_delete_bulk(message_ids, channel_id, [event](const dpp::confirmation_callback_t& callback) mutable {
          if(callback.is_error()){
            event.reply("Erro ao apagar mensagens");
            return;
          }
            event.reply("Mensagens apagadas com sucesso");
        });
       });
    }
};

#endif