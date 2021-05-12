#include "commands.h"

load_command::load_command(const std::string &file_name)
    :file_name(file_name)
{
}

void load_command::execute(const std::shared_ptr<base_controller> &_controller) const
{
    _controller->load_model(file_name);
}

void remove_model_command::execute(const std::shared_ptr<base_controller> &_controller) const
{
    _controller->remove_model(index);
}

void add_camera_command::execute(const std::shared_ptr<base_controller> &_controller) const
{
    _controller->add_camera(pos);
}

void set_camera_command::execute(const std::shared_ptr<base_controller> &_controller) const
{
    _controller->set_camera(index);
}

void remove_camera_command::execute(const std::shared_ptr<base_controller> &_controller) const
{
    _controller->remove_camera(index);
}

void draw_scene_command::execute(const std::shared_ptr<base_controller> &_controller) const
{
    _controller->draw_scene(_drawer);
}

void move_model_command::execute(const std::shared_ptr<base_controller> &_controller) const
{
    point scale(1, 1, 1);
    point rotate(0, 0, 0);
    _controller->transform_model(index, move, scale, rotate);
}

void scale_model_command::execute(const std::shared_ptr<base_controller> &_controller) const
{
    point move(0, 0, 0);
    point rotate(0, 0, 0);
    _controller->transform_model(index, move, scale, rotate);
}

void rotate_model_command::execute(const std::shared_ptr<base_controller> &_controller) const
{
    point move(0, 0, 0);
    point scale(1, 1, 1);
    _controller->transform_model(index, move, scale, rotate);
}

void move_camera_command::execute(const std::shared_ptr<base_controller> &_controller) const
{
    point rotate(0, 0, 0);
    _controller->transform_camera(index, move, rotate);
}

void rotate_camera_command::execute(const std::shared_ptr<base_controller> &_controller) const
{
    point move(0, 0, 0);
    _controller->transform_camera(index, move, rotate);
}
