#include "reform_manager.h"

void reform_manager::reform_object(const std::shared_ptr<object> &obj, const point &move, const point &scale,
                                   const point &rotate) const
{
    obj->transform(move, scale, rotate);
}
