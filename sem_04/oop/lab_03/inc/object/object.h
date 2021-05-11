#ifndef OBJECT_H
#define OBJECT_H

#include <memory>
#include <stdlib.h>
#include <vector>

#include "visitor.h"
#include "point.h"

class object
{
public:
    object() = default;
    virtual ~object() = default;

    virtual void accept(const std::shared_ptr<visitor> &_visitor) const = 0;

    virtual bool add(const std::shared_ptr<object> _object) {return false;}
    virtual bool remove(size_t index) {return false;}

    virtual std::vector<std::shared_ptr<object>>::iterator begin() {}
    virtual std::vector<std::shared_ptr<object>>::iterator end() {}
    virtual std::vector<std::shared_ptr<object>>::const_iterator cbegin() const {}
    virtual std::vector<std::shared_ptr<object>>::const_iterator cend() const {}

    virtual bool is_composite() const {return false;}

    virtual void transform(const point &move, const point &scale, const point &rotate) = 0;
};

class visible_object : public object
{
public:
    visible_object() = default;
    virtual ~visible_object() = default;

    static bool is_visible() {return true;}
};

class invisible_object : public object
{
public:
    invisible_object() = default;
    virtual ~invisible_object() = default;

    static bool is_visible() {return false;}
};

#endif // OBJECT_H
