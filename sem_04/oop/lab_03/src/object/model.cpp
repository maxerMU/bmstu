#include "model.h"

model::model()
    :_units(new units)
{
}

model::model(const std::shared_ptr<units> &_units)
    :_units(_units)
{
}

std::shared_ptr<units> model::get_units() const
{
    return _units;
}

void model::accept(const std::shared_ptr<visitor> &_visitor) const
{
    _visitor->visit(*this);
}

void model::transform(const point &move, const point &scale, const point &rotate)
{
    _units->transform(move, scale, rotate);
}
