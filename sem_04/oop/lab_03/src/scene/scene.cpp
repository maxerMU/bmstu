#include "scene.h"

scene::scene()
{
    models = std::shared_ptr<composite>(new composite);
    cameras = std::shared_ptr<composite>(new composite);
}

void scene::accept(const std::shared_ptr<visitor> &_visitor) const
{
    _visitor->visit(*this);
}

void scene::add_model(const std::shared_ptr<object> &_model)
{
    models->add(_model);
}

void scene::remove_model(size_t index)
{
    models->remove(index);
}

void scene::add_camera(const std::shared_ptr<object> &_camera)
{
    cameras->add(_camera);
}

void scene::remove_camera(size_t index)
{
    cameras->remove(index);
}

std::shared_ptr<object> scene::get_model(size_t index) const
{
    return models->get_objects().at(index);
}

std::vector<std::shared_ptr<object>> scene::get_models() const
{
    return models->get_objects();
}

std::shared_ptr<composite> scene::get_models_composite() const
{
    return models;
}

std::shared_ptr<object> scene::get_camera(size_t index) const
{
    return cameras->get_objects().at(index);
}

std::vector<std::shared_ptr<object>> scene::get_cameras() const
{
    return cameras->get_objects();
}

void scene::transform(const point &move, const point &scale, const point &rotate)
{
    for (auto _model : *models)
        _model->transform(move, scale, rotate);

    for (auto _camera : *cameras)
        _camera->transform(move, scale, rotate);
}
