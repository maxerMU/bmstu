#include "facade.h"

facade::facade()
{
}

void facade::execute_command(const std::shared_ptr<base_command> &command)
{
    command->execute();
}
