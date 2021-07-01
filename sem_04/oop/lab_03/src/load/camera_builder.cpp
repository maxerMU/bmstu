#include "camera_builder.h"
#include "point.h"

camera_builder::camera_builder()
    :_camera(nullptr)
{
}

void camera_builder::reset()
{
    _camera = std::shared_ptr<camera>(new camera);
}

bool camera_builder::is_build() const
{
    return _camera != nullptr;
}

std::shared_ptr<camera> camera_builder::get()
{
    return _camera;
}

void camera_builder::build_pos(double x, double y, double z)
{
    _camera->set_pos(point(x, y, z));
}

void camera_builder::build_angles(double ox, double oy, double oz)
{
    _camera->set_xangle(ox);
    _camera->set_yangle(oy);
    _camera->set_zangle(oz);
}
