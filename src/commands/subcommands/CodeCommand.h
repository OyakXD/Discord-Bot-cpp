#ifndef CODE_COMMAND_H
#define CODE_COMMAND_H

#include "commands/ICommand.h"
using namespace std;

class CodeCommand : public ICommand {
  public:
    string get_name() const override {
      return "codigo";
    }

    string get_description() const override {
      return "Veja o código fonte do bot";
    }

    void execute(const slashcommand_t& event) const override {
      event.reply("Aqui está, cuidado em! \nhttps://github.com/OyakXD/Discord-Bot-cpp");
    }
};

#endif