#include "config_manager.h"

std::shared_ptr<config_manager> config_manager_creator::get_manager()
{
    if (_manager == nullptr)
        create_manager();

    return _manager;
}

void config_manager_creator::create_manager()
{
    static std::shared_ptr<config_manager> _manager(new config_manager());
    this->_manager = _manager;
}

config_manager::config_manager()
    :reg_maker(std::shared_ptr<base_registration_maker>(new registration_maker()))
{
    reg_maker->make_registration(_solution);
}


std::shared_ptr<loader_creator> config_manager::get_creator(size_t index)
{
    return _solution.get_creator(index);
}
