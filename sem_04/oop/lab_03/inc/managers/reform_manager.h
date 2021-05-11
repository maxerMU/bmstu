#ifndef REFORM_MANAGER_H
#define REFORM_MANAGER_H

#include "base_manager.h"
#include "object.h"
#include "point.h"

class reform_manager : public base_manager
{
public:
    reform_manager() = default;

    void reform_object(const std::shared_ptr<object> &obj, const point &move, const point &scale,
                       const point &rotate) const;
};

#endif // REFORM_MANAGER_H
