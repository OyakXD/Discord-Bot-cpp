#ifndef BOT_H
#define BOT_H

#include <dpp/dpp.h>
#include <string>
#include "commands/ICommand.h"
#include <vector>
#include <memory>

using namespace std;
using namespace dpp;

class Bot{
  public:
    Bot(const string& token);
    void start();

  private:
    cluster bot;

    unordered_map<string, unique_ptr<ICommand>> command_map;

    void register_commands();
    void handle_command(const slashcommand_t& event);

};

#endif