#include "Bot.h"
#include "commands/CommandRegister.h"
#include "commands/subcommands/HelloCommand.h"
using namespace std;
using namespace dpp;

Bot::Bot(const string& token) : bot(token){

  bot.on_log(utility::cout_logger());
  bot.on_slashcommand([this](const slashcommand_t& event) {
    handle_command(event);
  });
}


void Bot::start(){
  
  bot.on_ready([this](const ready_t& event) {
    if(run_once<struct register_bot_commands>()){
      cout << "Bot está pronto, registrando comandos" << endl;
      register_commands();
    }
  });
  bot.start(st_wait);
}

void Bot::register_commands(){
  // Registra um novo comando e adiciona ao mapeamento
  command_map["hello"] = make_unique<HelloCommand>();
  for(const auto& [name, command] : command_map){
    slashcommand new_command(command->get_name(), command->get_description(), bot.me.id);

    add_command(bot, new_command);
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