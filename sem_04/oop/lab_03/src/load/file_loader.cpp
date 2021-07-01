#include <vector>

#include "load_exceptions.h"
#include "file_loader.h"
#include "point.h"
#include "edge.h"

model_file_loader::model_file_loader()
{
    _builder = std::shared_ptr<model_builder>(new model_builder);
}

model_file_loader::model_file_loader(std::shared_ptr<std::ifstream> &file)
{
    _builder = std::shared_ptr<model_builder>(new model_builder);
    this->file = file;
}

void model_file_loader::open(const std::string &name)
{
    file = std::shared_ptr<std::ifstream>(new std::ifstream(name));

    if (!*file)
        throw file_open_exception();
}

std::shared_ptr<object> model_file_loader::load()
{
    _builder->reset();

    if (!*file)
        throw file_open_exception();

    double x, y, z;
    if (!(*file >> x >> y >> z))
        throw file_format_exception();
    _builder->build_center(point(x, y, z));

    size_t points_count = 0;
    *file >> points_count;
    if (points_count <= 1)
        throw file_format_exception();

    std::vector<point> points;
    for (size_t i = 0; i < points_count; i++)
    {
        if (!(*file >> x >> y >> z))
            throw file_format_exception();
        points.push_back(point(x, y, z));
    }
    _builder->build_points(points);

    size_t edges_count = 0;
    *file >> edges_count;
    if (edges_count < 1)
        throw file_format_exception();

    std::vector<edge> edges;
    for (size_t i = 0; i < edges_count; i++)
    {
        size_t ind1, ind2;
        if (!(*file >> ind1 >> ind2))
            throw file_format_exception();
        edges.push_back(edge(ind1, ind2));
    }
    _builder->build_edges(edges);

    return std::dynamic_pointer_cast<object>(_builder->get());
}

void model_file_loader::close()
{
    file->close();
}

camera_file_loader::camera_file_loader()
{
    _builder = std::shared_ptr<camera_builder>(new camera_builder);
}

camera_file_loader::camera_file_loader(std::shared_ptr<std::ifstream> &file)
{
    _builder = std::shared_ptr<camera_builder>(new camera_builder);
    this->file = file;
}

void camera_file_loader::open(const std::string &name)
{
    file = std::shared_ptr<std::ifstream>(new std::ifstream(name));

    if (!*file)
        throw file_open_exception();
}

std::shared_ptr<object> camera_file_loader::load()
{
    _builder->reset();

    if (!*file)
        throw file_open_exception();

    double x, y, z;
    if (!(*file >> x >> y >> z))
        throw file_format_exception();
    _builder->build_pos(x, y, z);

    if (!(*file >> x >> y >> z))
        throw file_format_exception();
    _builder->build_angles(x, y, z);

    return std::dynamic_pointer_cast<object>(_builder->get());
}

void camera_file_loader::close()
{
    file->close();
}

scene_file_loader::scene_file_loader()
{
    _builder = std::shared_ptr<scene_builder>(new scene_builder);
}

scene_file_loader::scene_file_loader(std::shared_ptr<std::ifstream> &file)
{
    _builder = std::shared_ptr<scene_builder>(new scene_builder);
    this->file = file;
}

void scene_file_loader::open(const std::string &name)
{
    file = std::shared_ptr<std::ifstream>(new std::ifstream(name));

    if (!*file)
        throw file_open_exception();
}

std::shared_ptr<object> scene_file_loader::load()
{
    _builder->reset();

    if (!*file)
        throw file_open_exception();

    load_models();
    load_cameras();

    return std::dynamic_pointer_cast<object>(_builder->get());
}

void scene_file_loader::close()
{
    file->close();
}

void scene_file_loader::load_models()
{
    size_t models_count;
    if (!(*file >> models_count))
        throw file_format_exception();
    for (size_t i = 0; i < models_count; i++)
        _builder->build_model(model_file_loader(file).load());

}

void scene_file_loader::load_cameras()
{
    size_t cameras_count;
    if (!(*file >> cameras_count))
        throw file_format_exception();
    for (size_t i = 0; i < cameras_count; i++)
        _builder->build_camera(camera_file_loader(file).load());
}
