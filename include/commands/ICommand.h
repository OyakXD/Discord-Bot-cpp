#ifndef ICOMMAND_H
#define ICOMMAND_H

#include <dpp/dpp.h>
#include <string>
using namespace std;
using namespace dpp;

class ICommand {
  public:
    virtual ~ICommand() = default;

    virtual string get_name() const = 0;
    virtual string get_description() const = 0;
    virtual void execute (const slashcommand_t& event) const = 0;
};

#endif