#include "model.h"

model::model()
    :_units(new units)
{
}

model::model(const std::shared_ptr<units> &_units)
    :_units(_units)
{
}

void model::add_point(const point &_point)
{
    _units->add_point(_point);
}

void model::add_edge(const edge &_edge)
{
    _units->add_edge(_edge);
}

void model::set_center(const point &pos)
{
    _units->set_center(pos);
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
