#include "scene_builder.h"
#include "load_exceptions.h"

scene_builder::scene_builder()
    :_scene(nullptr)
{
}

void scene_builder::reset()
{
    _scene = std::shared_ptr<scene>(new scene);
}

bool scene_builder::is_build() const
{
    return _scene != nullptr;
}

std::shared_ptr<scene> scene_builder::get()
{
    return _scene;
}

void scene_builder::build_model(const std::shared_ptr<object> &_model)
{
    _scene->add_model(_model);
}

void scene_builder::build_camera(const std::shared_ptr<object> &_camera)
{
    _scene->add_camera(_camera);
}
