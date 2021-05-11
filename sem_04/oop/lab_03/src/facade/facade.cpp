#include "facade.h"

facade::facade()
{
    _controller_creator = std::shared_ptr<creator>(new controller_creator());
}

void facade::execute_command(const std::shared_ptr<base_command> &command)
{
    command->execute(_controller_creator->get_product());
}
