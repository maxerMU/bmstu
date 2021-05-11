#include "controller.h"
#include "file_loader.h"
#include "load_exceptions.h"

controller::controller()
{
    this->_draw_manager = std::shared_ptr<draw_manager>(new draw_manager());
    this->loader = std::shared_ptr<base_loader>(new file_loader());
}


void controller::load_model(const std::string &name)
{
    if (!_scene_manager.is_camera_set())
        throw no_camera_exception();

    std::shared_ptr<model> _model = loader->load_model(name);
    _scene_manager.get_scene()->add_model(_model);
}

void controller::add_model(const std::shared_ptr<model> &_model)
{
    _scene_manager.get_scene()->add_model(_model);
}

void controller::remove_model(size_t index)
{
    _scene_manager.get_scene()->remove_model(index);
}

void controller::add_camera(const point &cam_pos)
{
    std::shared_ptr<object> _camera(new camera(cam_pos));
    _scene_manager.get_scene()->add_camera(_camera);
}

void controller::set_camera(size_t index)
{
    _scene_manager.set_cur_camera(index);
}

void controller::remove_camera(size_t index)
{
    _scene_manager.get_scene()->remove_camera(index);
}

void controller::draw_scene(const std::shared_ptr<base_drawer> &drawer)
{
    if (!_scene_manager.is_camera_set())
        throw no_camera_exception();

    _draw_manager->set_cam(_scene_manager.get_cur_camera());
    _draw_manager->set_drawer(drawer);

    drawer->clear_scene();

    _scene_manager.get_scene()->get_models_composite()->accept(_draw_manager);
}

void controller::transform_model(size_t index, const point &move, const point &scale, const point &rotate)
{
    _reform_manager.reform_object(_scene_manager.get_scene()->get_model(index),
                                  move, scale, rotate);
}

void controller::transform_camera(size_t index, const point &move, const point &rotate)
{
    point scale(1, 1, 1);
    _reform_manager.reform_object(_scene_manager.get_scene()->get_camera(index),
                                  move, scale, rotate);
}
