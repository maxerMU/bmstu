#include "commands.h"
#include "file_loader.h"
#include "load_exceptions.h"
#include "model_exceptions.h"
#include "load_manager.h"
#include "directors.h"
#include "draw_manager.h"
#include "reform_manager.h"
#include "scene_manager.h"

load_command::load_command(const std::string &file_name)
    :file_name(file_name)
{
}

void load_command::execute() const
{
    if (!scene_manager_creator().get_manager()->is_camera_set())
        throw no_camera_exception();

    std::shared_ptr<load_manager> _lm = load_manager_creator().get_manager();
    _lm->set_director(std::shared_ptr<load_director>(new model_director));
    std::shared_ptr<object> _model_obj = _lm->load(file_name);
    scene_manager_creator().get_manager()->get_scene()->add_model(_model_obj);
}

void load_camera_command::execute() const
{
    std::shared_ptr<load_manager> _lm = load_manager_creator().get_manager();
    _lm->set_director(std::shared_ptr<load_director>(new camera_director));
    std::shared_ptr<object> _camera_obj = _lm->load(file_name);
    scene_manager_creator().get_manager()->get_scene()->add_camera(_camera_obj);
}

void load_scene_command::execute() const
{
    std::shared_ptr<load_manager> _lm = load_manager_creator().get_manager();
    _lm->set_director(std::shared_ptr<load_director>(new scene_director));
    std::shared_ptr<object> _scene_obj = _lm->load(file_name);
    scene_manager_creator().get_manager()->set_scene(std::dynamic_pointer_cast<scene>(_scene_obj));
}

void remove_model_command::execute() const
{
    scene_manager_creator().get_manager()->get_scene()->remove_model(index);
}

void add_camera_command::execute() const
{
    std::shared_ptr<object> _camera(new camera(pos));
    scene_manager_creator().get_manager()->get_scene()->add_camera(_camera);
}

void set_camera_command::execute() const
{
    scene_manager_creator().get_manager()->set_cur_camera(index);
}

void remove_camera_command::execute() const
{
    scene_manager_creator().get_manager()->get_scene()->remove_camera(index);
}

void draw_scene_command::execute() const
{
    if (!scene_manager_creator().get_manager()->is_camera_set())
        throw no_camera_exception();

    draw_manager_creator().get_manager()->set_cam(scene_manager_creator().get_manager()->get_cur_camera());
    draw_manager_creator().get_manager()->set_drawer(_drawer);

    _drawer->clear_scene();

    scene_manager_creator().get_manager()->get_scene()->get_models_composite()->accept(
                draw_manager_creator().get_manager());
}

void move_model_command::execute() const
{
    point scale(1, 1, 1);
    point rotate(0, 0, 0);
    reform_manager_creator().get_manager()->reform_object(
                scene_manager_creator().get_manager()->get_scene()->get_model(index), move, scale, rotate);
}

void scale_model_command::execute() const
{
    point move(0, 0, 0);
    point rotate(0, 0, 0);
    reform_manager_creator().get_manager()->reform_object(
                scene_manager_creator().get_manager()->get_scene()->get_model(index), move, scale, rotate);
}

void rotate_model_command::execute() const
{
    point move(0, 0, 0);
    point scale(1, 1, 1);
    reform_manager_creator().get_manager()->reform_object(
                scene_manager_creator().get_manager()->get_scene()->get_model(index), move, scale, rotate);
}

void move_camera_command::execute() const
{
    point rotate(0, 0, 0);
    point scale(1, 1, 1);
    reform_manager_creator().get_manager()->reform_object(
                scene_manager_creator().get_manager()->get_scene()->get_camera(index), move, scale, rotate);
}

void rotate_camera_command::execute() const
{
    point move(0, 0, 0);
    point rotate(0, 0, 0);
    point scale(1, 1, 1);
    reform_manager_creator().get_manager()->reform_object(
                scene_manager_creator().get_manager()->get_scene()->get_camera(index), move, scale, rotate);
}
