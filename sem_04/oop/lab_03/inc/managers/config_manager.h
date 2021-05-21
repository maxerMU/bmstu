#ifndef CONFIG_MANAGER_H
#define CONFIG_MANAGER_H

#include "solution.h"
#include "registration.h"

class config_manager
{
public:
    config_manager();

    std::shared_ptr<loader_creator> get_creator(size_t index);

private:
    solution _solution;
    std::shared_ptr<base_registration_maker> reg_maker;
};

class config_manager_creator
{
public:
    std::shared_ptr<config_manager> get_manager();

private:
    void create_manager();

    std::shared_ptr<config_manager> _manager;
};

#endif // CONFIG_MANAGER_H
