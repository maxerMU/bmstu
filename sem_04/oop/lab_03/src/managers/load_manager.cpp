#include "load_exceptions.h"
#include "load_manager.h"

std::shared_ptr<object> load_manager::load(const std::string &name)
{
    if (_director == nullptr)
        throw no_director_exception();

    return _director->load(name);
}

void load_manager::set_director(const std::shared_ptr<load_director> &_director)
{
    this->_director = _director;
}

std::shared_ptr<load_manager> load_manager_creator::get_manager()
{
    if (_manager == nullptr)
        create_manager();

    return _manager;
}

void load_manager_creator::create_manager()
{
    static std::shared_ptr<load_manager> _manager(new load_manager());
    this->_manager = _manager;
}
