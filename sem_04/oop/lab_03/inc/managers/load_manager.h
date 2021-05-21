#ifndef LOAD_MANAGER_H
#define LOAD_MANAGER_H

#include <memory>
#include <string>

#include "base_manager.h"
#include "load_director.h"
#include "object.h"

class load_manager : public base_manager
{
public:
    load_manager() = default;
    std::shared_ptr<object> load(const std::string &name);
    void set_director(const std::shared_ptr<load_director> &_director);

private:
    std::shared_ptr<load_director> _director;
};

class load_manager_creator
{
public:
    std::shared_ptr<load_manager> get_manager();

private:
    void create_manager();

    std::shared_ptr<load_manager> _manager;
};

#endif // LOAD_MANAGER_H
