#ifndef REGISTRATION_H
#define REGISTRATION_H

#include <map>

#include "loaders.h"
#include "solution.h"

class base_registration_maker
{
public:
    base_registration_maker() = default;
    virtual ~base_registration_maker() = default;
    virtual void make_registration(solution &_solution) = 0;
};

class registration_maker : public base_registration_maker
{
public:
    registration_maker() = default;
    virtual ~registration_maker() = default;
    virtual void make_registration(solution &_solution) override;
};

#endif // REGISTRATION_H
