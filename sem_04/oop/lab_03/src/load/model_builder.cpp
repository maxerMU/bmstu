#include "model_builder.h"
#include "load_exceptions.h"

model_builder::model_builder()
    :_model(nullptr)
{
}

void model_builder::reset()
{
    _model = std::shared_ptr<model>(new model);
}

bool model_builder::is_build()
{
    return _model != nullptr;
}

std::shared_ptr<model> model_builder::get()
{
    return _model;
}

void model_builder::build_center(const point &_point)
{
    if (!is_build())
        throw build_exception();

    _model->set_center(_point);
}

void model_builder::build_point(const point &_point)
{
    if (!is_build())
        throw build_exception();

    _model->add_point(_point);
}

void model_builder::build_edge(const edge &_edge)
{
    if (!is_build())
        throw build_exception();

    _model->add_edge(_edge);
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
