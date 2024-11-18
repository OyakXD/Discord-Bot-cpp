#ifndef SOBRE_COMMAND_H
#define SOBRE_COMMAND_H

#include "commands/ICommand.h"
using namespace std;

class SobreCommand : public ICommand {
  public:
    string get_name() const override {
      return "sobre";
    }

    string get_description() const override {
      return "Informações sobre o criador do bot";
    }

    void execute(const slashcommand_t& event) const override {

      string user_name = event.command.usr.username;
      string avatar_url = event.command.usr.get_avatar_url();

      dpp::embed embed = dpp::embed()
        .set_color(dpp::colors::sti_blue)
        .set_title("Kayo - OyakXD")
        .set_description("Olá! Eu sou o Kayo, um bot criado por OyakXD. Meu objetivo é ajudar você a interagir com o Discord de uma maneira mais eficiente e divertida.")
        .set_url("https://github.com/OyakXD")
        .set_thumbnail("https://avatars.githubusercontent.com/u/131064997?v=4")
        .add_field(
          "Necessita de alguma ajuda? \n",
          "Entre em contato comigo no Discord: oyakdev"
        )
        .set_footer(dpp::embed_footer()
          .set_text("Criado por " + user_name)
          .set_icon(avatar_url)
        );

        event.reply(dpp::message().add_embed(embed));
    }
};

#endif