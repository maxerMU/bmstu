#include "builder.h"
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

void model_builder::build_center(double x, double y, double z)
{
    if (!is_build())
        throw build_exception();

    _model->set_center(point(x, y, z));
}

void model_builder::build_point(double x, double y, double z)
{
    if (!is_build())
        throw build_exception();

    _model->add_point(point(x, y, z));
}

void model_builder::build_edge(size_t pt_index1, size_t pt_index2)
{
    if (!is_build())
        throw build_exception();

    _model->add_edge(edge(pt_index1, pt_index2));
}
