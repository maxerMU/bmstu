#ifndef ABSTRACT_FACTORY_H
#define ABSTRACT_FACTORY_H

#include <memory>

#include "base_drawer.h"

class abstract_factory
{
public:
    abstract_factory() = default;
    virtual ~abstract_factory() = default;

    virtual std::shared_ptr<base_drawer> create_drawer() = 0;
};

#endif // ABSTRACT_FACTORY_H
