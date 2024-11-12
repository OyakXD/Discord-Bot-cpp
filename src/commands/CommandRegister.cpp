#include "commands/CommandRegister.h"
using namespace std;
using namespace dpp;

void add_command(cluster& bot, const slashcommand& command){
  // Registrador de comandos global
  bot.global_command_create(command);
}