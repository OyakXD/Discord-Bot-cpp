#ifndef AVATAR_COMMAND_h
#define AVATAR_COMMAND_h

#include "commands/ICommand.h"
#include <string>
using namespace std;

class AvatarCommand : public ICommand {
  public:
    string get_name() const override {
      return "avatar";
    }

    string get_description() const override {
      return "Veja sua foto de perfil ou de outro usuário";
    }

    void execute(const slashcommand_t& event) const override {
      snowflake user_id;
      string avatar_url;

      auto user_option = event.command.get_command_interaction().options;

      if(!user_option.empty()){
        user_id = std::get<snowflake>(user_option[0].value);  
      } else {
        user_id = event.command.usr.id;
      }
      auto user = event.from->creator->user_get_sync(user_id);
      avatar_url = user.get_avatar_url();
      event.reply(dpp::message().set_content(avatar_url));
    }
};

#endif