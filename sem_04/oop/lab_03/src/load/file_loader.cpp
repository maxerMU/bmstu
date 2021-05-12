#include <fstream>
#include <vector>

#include "load_exceptions.h"
#include "file_loader.h"
#include "point.h"
#include "edge.h"

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
    _builder->build_center(point(x, y, z));

    size_t points_count = 0;
    file >> points_count;
    if (points_count <= 1)
        throw file_format_exception();

    std::vector<point> points;
    for (size_t i = 0; i < points_count; i++)
    {
        if (!(file >> x >> y >> z))
            throw file_format_exception();
        points.push_back(point(x, y, z));
    }
    _builder->build_points(points);

    size_t edges_count = 0;
    file >> edges_count;
    if (edges_count < 1)
        throw file_format_exception();

    std::vector<edge> edges;
    for (size_t i = 0; i < edges_count; i++)
    {
        size_t ind1, ind2;
        if (!(file >> ind1 >> ind2))
            throw file_format_exception();
        edges.push_back(edge(ind1, ind2));
    }
    _builder->build_edges(edges);

    return _builder->get();
}
