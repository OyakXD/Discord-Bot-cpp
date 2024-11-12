#ifndef COMMANDREGISTER_H
#define COMMANDREGISTER_H

#include <dpp/dpp.h>
using namespace std;
using namespace dpp;

void add_command(cluster& bot, const slashcommand& command);

#endif