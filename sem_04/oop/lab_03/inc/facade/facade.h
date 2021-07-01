#ifndef FACADE_H
#define FACADE_H

#include "commands.h"

class facade
{
public:
    facade();

    void execute_command(const std::shared_ptr<base_command> &command);
};

#endif // FACADE_H
