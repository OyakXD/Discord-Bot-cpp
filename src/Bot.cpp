#include "Bot.h"
#include <spdlog/spdlog.h>
using namespace std;
using namespace dpp;

Bot::Bot(const string& token, snowflake log_channel_id) : bot(token), log_channel_id(log_channel_id) {

  bot.on_slashcommand([this](const slashcommand_t& event) {
    handle_command(event);
  });

  logger = make_unique<Logger>(bot, log_channel_id);
  logger->setup_event_handlers();
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
