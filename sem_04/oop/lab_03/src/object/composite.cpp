#include "composite.h"

composite::composite()
{
}

void composite::accept(const std::shared_ptr<visitor> &_visitor) const
{
    _visitor->visit(*this);

    for (auto _obj = this->cbegin(); _obj != this->cend(); ++_obj)
    {
        (*_obj)->accept(_visitor);
    }
}

bool composite::add(const std::shared_ptr<object> _object)
{
    objects.push_back(_object);

    return true;
}

bool composite::remove(size_t index)
{
    objects.erase(objects.begin() + index);

    return true;
}

std::vector<std::shared_ptr<object>>::iterator composite::begin()
{
    return objects.begin();
}

std::vector<std::shared_ptr<object>>::iterator composite::end()
{
    return objects.end();
}

std::vector<std::shared_ptr<object>>::const_iterator composite::cbegin() const
{
    return objects.cbegin();
}

std::vector<std::shared_ptr<object>>::const_iterator composite::cend() const
{
    return objects.cend();
}

std::vector<std::shared_ptr<object>> composite::get_objects() const
{
    return objects;
}

void composite::transform(const point &move, const point &scale, const point &rotate)
{
    for (auto &obj : objects)
    {
        obj->transform(move, scale, rotate);
    }
}
