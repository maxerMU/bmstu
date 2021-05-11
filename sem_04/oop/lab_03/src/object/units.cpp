#include "model_exceptions.h"
#include "units.h"

units::units()
{
}

void units::add_point(const point &_point)
{
    points.push_back(_point);
}

void units::add_edge(const edge &_edge)
{
    if (_edge.get_first() >= points.size() || _edge.get_second() >= points.size())
        throw edge_exception();

    edges.push_back(_edge);
}

std::vector<point> units::get_points()
{
    return points;
}

std::vector<edge> units::get_edges()
{
    return edges;
}

void units::set_center(const point &pos)
{
    center = pos;
}

point units::get_center() const
{
    return center;
}

void units::move(const point &move)
{
    center.move(move);

    for (point &_point : points)
        _point.move(move);
}

void units::scale(const point &scale)
{
    for (point &_point : points)
        _point.scale(center, scale);
}

void units::rotate(const point &rotate)
{
    for (point &_point : points)
        _point.rotate(center, rotate);
}

void units::transform(const point &move, const point &scale, const point &rotate)
{
    this->move(move);
    this->scale(scale);
    this->rotate(rotate);
}
