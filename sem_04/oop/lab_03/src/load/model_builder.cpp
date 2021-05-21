#include "model_builder.h"
#include "load_exceptions.h"

model_builder::model_builder()
    :_units(nullptr)
{
}

void model_builder::reset()
{
    _units = std::shared_ptr<units>(new units);
}

bool model_builder::is_build()
{
    return _units != nullptr;
}

std::shared_ptr<model> model_builder::get()
{
    return std::shared_ptr<model>(new model(_units));
}

void model_builder::build_center(const point &_point)
{
    if (!is_build())
        throw build_exception();

    _units->set_center(_point);
}

void model_builder::build_point(const point &_point)
{
    if (!is_build())
        throw build_exception();

    _units->add_point(_point);
}

void model_builder::build_edge(const edge &_edge)
{
    if (!is_build())
        throw build_exception();

    _units->add_edge(_edge);
}

void model_builder::build_points(const std::vector<point> &points)
{
    for (auto _point : points)
        build_point(_point);
}

void model_builder::build_edges(const std::vector<edge> &edges)
{
    for (auto _edge : edges)
        build_edge(_edge);
}
