#include "logs/Logger.h"
#include <dpp/dpp.h>
#include <string>
using namespace std;

Logger::Logger(dpp::cluster& bot, dpp::snowflake log_channel_id) : bot(bot), log_channel_id(log_channel_id) {}

void Logger::setup_event_handlers(){

  /*

  Eventos de criação, atualização e deleção de cargos
  
  */
  bot.on_guild_role_create([this](const dpp::guild_role_create_t& event){
    on_guild_role_create(event);
  });
  bot.on_guild_role_update([this](const dpp::guild_role_update_t& event){
    on_guild_role_update(event);
  });
  bot.on_guild_role_delete([this](const dpp::guild_role_delete_t& event){
    on_guild_role_delete(event);
  });
  bot.on_guild_ban_add([this](const dpp::guild_ban_add_t& event){
    on_guild_ban_add(event);
  });
  bot.on_guild_member_remove([this](const dpp::guild_member_remove_t& event){
    on_guild_member_remove(event);
  });
  bot.on_voice_state_update([this](const dpp::voice_state_update_t& event){
    on_voice_state_update(event);
  });
}

void Logger::on_guild_role_create(const dpp::guild_role_create_t& event){
    dpp::embed embed = dpp::embed()
    .set_color(dpp::colors::green)
    .set_title("Novo Cargo Criado")
    .add_field("Nome: ", event.created->name);

    bot.message_create(dpp::message(log_channel_id,embed));
}

void Logger::on_guild_role_update(const dpp::guild_role_update_t& event){
    string role_name = event.updated->name;
    string role_id = to_string(event.updated->id);

    dpp::embed embed = dpp::embed()
    .set_color(dpp::colors::sti_blue)
    .set_title("Cargo atualizado!")
    .add_field("Cargo: ", role_name + " (" + role_id + ")", false);

    bot.message_create(dpp::message(log_channel_id,embed));
}

void Logger::on_guild_role_delete(const dpp::guild_role_delete_t& event){
    dpp::embed embed = dpp::embed()
    .set_color(dpp::colors::red)
    .set_title("Cargo deletado")
    .add_field("Nome: ", event.deleted->name);

    bot.message_create(dpp::message(log_channel_id,embed));
}

void Logger::on_guild_ban_add(const dpp::guild_ban_add_t& event){
  string user_name = event.banned.username;
  string user_id = to_string(event.banned.id);

  dpp::embed embed = dpp::embed()
  .set_color(dpp::colors::red)
  .set_title("Usuário Banido")
  .add_field("Usuário", user_name + " (" + user_id + ")", false)
  .set_image("https://www.google.com/url?sa=i&url=https%3A%2F%2Fbr.pinterest.com%2Fpin%2Ffaz-o-l-em-2023--587649451398218720%2F&psig=AOvVaw0bRkoyW49ZqHUQvYo-cLg7&ust=1731976584334000&source=images&cd=vfe&opi=89978449&ved=0CBQQjRxqFwoTCPChhd3R5IkDFQAAAAAdAAAAABAE");

}

void Logger::on_guild_member_remove(const dpp::guild_member_remove_t& event){
  string user_name = event.removed.username;
  string user_id = to_string(event.removed.id);

  dpp::embed embed = dpp::embed()
    .set_color(dpp::colors::orange)
    .set_title("Usúario expulso")
    .add_field("Usuário", user_name + " (" + user_id + ")", false);

    bot.message_create(dpp::message(log_channel_id, embed));
}

void Logger::on_voice_state_update(const dpp::voice_state_update_t& event){
  if(event.state.is_mute() || event.state.is_deaf()) {
    dpp::user* user = dpp::find_user(event.state.user_id);
    if(user){
      string user_name = user->username;
      string user_id = to_string(event.state.user_id);

      dpp::embed embed = dpp::embed()
        .set_color(dpp::colors::yellow)
        .set_title("Usúario Mutado")
        .add_field("Usúario", user_name + " (" + user_id + ") ", false)
        .add_field("Tipo", event.state.is_mute() ? "Mute" : "Deaf", false);

        bot.message_create(dpp::message(log_channel_id, embed));
    }
  }
}