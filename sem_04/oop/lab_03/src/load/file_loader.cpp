#include <fstream>

#include "load_exceptions.h"
#include "file_loader.h"

file_loader::file_loader()
{
    _builder = std::shared_ptr<base_builder>(new model_builder);
}

std::shared_ptr<model> file_loader::load_model(const std::string &name)
{
    _builder->reset();

    std::ifstream file(name);

    if (!file)
        throw file_open_exception();

    double x, y, z;
    if (!(file >> x >> y >> z))
        throw file_format_exception();
    _builder->build_center(x, y, z);

    size_t points = 0;
    file >> points;

    if (points <= 1)
        throw file_format_exception();

    for (size_t i = 0; i < points; i++)
    {
        if (!(file >> x >> y >> z))
            throw file_format_exception();
        _builder->build_point(x, y, z);
    }

    size_t edges = 0;
    file >> edges;

    if (edges < 1)
        throw file_format_exception();

    for (size_t i = 0; i < edges; i++)
    {
        size_t ind1, ind2;
        if (!(file >> ind1 >> ind2))
            throw file_format_exception();
        _builder->build_edge(ind1, ind2);
    }

    return _builder->get();
}
