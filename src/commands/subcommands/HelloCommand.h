#ifndef HELLO_COMMAND_H
#define HELLO_COMMAND_H

#include "commands/ICommand.h"
using namespace std;

class HelloCommand : public ICommand {
  public:
    string get_name() const override {
      return "hello";
    }

    string get_description() const override {
      return "Envia uma mensagem de olá";
    }

    void execute(const slashcommand_t& event) const override {
      event.reply("Hello! como posso te ajudar?");
    }
};

#endif