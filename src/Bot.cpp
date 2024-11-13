#include "Bot.h"
#include "commands/subcommands/CodeCommand.h"
#include "commands/subcommands/AvatarCommand.h"
#include "commands/subcommands/HelloCommand.h"
#include "commands/subcommands/ChatCommand.h"
#include <spdlog/spdlog.h>
using namespace std;
using namespace dpp;

Bot::Bot(const string& token) : bot(token){

  bot.on_slashcommand([this](const slashcommand_t& event) {
    handle_command(event);
  });
}


void Bot::start(){
  
  bot.on_ready([this](const ready_t& event) {
    if(run_once<struct register_bot_commands>()){
      spdlog::info("Bot está online!");
      register_commands();
    }
  });
  bot.start(st_wait);
}

void Bot::register_commands(){
  // Registra um novo comando e adiciona ao mapeamento
  command_map["hello"] = make_unique<HelloCommand>();
  command_map["codigo"] = make_unique<CodeCommand>();
  command_map["avatar"] = make_unique<AvatarCommand>();
  command_map["chatgpt"] = make_unique<ChatCommand>();

  for(const auto& [name, command] : command_map){
    slashcommand new_command(command->get_name(), command->get_description(), bot.me.id);

    if(name == "avatar"){
      new_command.add_option(
        command_option(co_user, "usúario", "Usuário para ver o avatar", false)
      );
    } else if(name == "chatgpt"){
      new_command.add_option(
        command_option(co_string, "pergunta", "Pergunta para o ChatGPT", true)
      );
    }
    
    bot.global_command_create(new_command, [name](const dpp::confirmation_callback_t& callback) {
            if (callback.is_error()) {
                spdlog::error("Erro ao registrar comando: {}", name);
            } else {
                spdlog::info("Comando registrado com sucesso: {}", name);
            }
    });
  }

}

void Bot::handle_command(const slashcommand_t& event){
  /*
    TODO
    Método para lidar com os comandos
  */
  auto command_name = event.command.get_command_name();

  if(command_map.find(command_name) != command_map.end()){
    command_map[command_name]->execute(event);
  } else {
    event.reply("Comando Desconhecido.");
  }
}