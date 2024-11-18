#ifndef LOGGER_H
#define LOGGER_H

#include <dpp/dpp.h>
#include <string>
using namespace dpp;

class Logger {
  public:
    Logger(cluster& bot, snowflake log_channel_id);
    void setup_event_handlers();

  private:
    cluster& bot;
    snowflake log_channel_id;

    // Logs de Criação de cargos, atualização e deleção.
    void on_guild_role_create(const guild_role_create_t& event);
    void on_guild_role_update(const guild_role_update_t& event);
    void on_guild_role_delete(const guild_role_delete_t& event);
    // --------------------------------------------------------

    // Logs de Ban, mute e kick
    void on_guild_ban_add(const guild_ban_add_t& event);
    void on_guild_member_remove(const guild_member_remove_t& event);
    void on_voice_state_update(const voice_state_update_t& event);

};

#endif // LOGGER_H