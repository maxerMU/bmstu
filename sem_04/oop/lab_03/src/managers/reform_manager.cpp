#include "reform_manager.h"

std::shared_ptr<reform_manager> reform_manager_creator::get_manager()
{
    if (_manager == nullptr)
        create_manager();

    return _manager;
}

void reform_manager_creator::create_manager()
{
    static std::shared_ptr<reform_manager> _manager(new reform_manager());
    this->_manager = _manager;
}

void reform_manager::reform_object(const std::shared_ptr<object> &obj, const point &move, const point &scale,
                                   const point &rotate) const
{
    obj->transform(move, scale, rotate);
}
