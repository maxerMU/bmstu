#ifndef FACADE_H
#define FACADE_H

#include "controller_creator.h"
#include "commands.h"

class facade
{
public:
    facade();

    void execute_command(const std::shared_ptr<base_command> &command);

private:
    std::shared_ptr<creator> _controller_creator;
};

#endif // FACADE_H
