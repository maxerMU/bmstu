#include <math.h>

#include "camera.h"

void camera::accept(const std::shared_ptr<visitor> &_visitor) const
{
    _visitor->visit(*this);
}

void camera::transform(const point &move, const point &scale, const point &rotate)
{
    this->move(move);
    this->rotate(rotate);
}

void camera::move(const point &move)
{
    pos.move(move);
}

void camera::rotate(const point &rotate)
{
    x_angle += rotate.get_x();
    y_angle += rotate.get_y();
    z_angle += rotate.get_z();
}

point camera::get_pos() const
{
    return pos;
}

void camera::set_pos(const point &_point)
{
    pos = _point;
}

double camera::get_xangle() const
{
    return x_angle;
}

void camera::set_xangle(double angle)
{
    x_angle = angle;
}

double camera::get_yangle() const
{
    return y_angle;
}

void camera::set_yangle(double angle)
{
    y_angle = angle;
}

double camera::get_zangle() const
{
    return z_angle;
}

void camera::set_zangle(double angle)
{
    z_angle = angle;
}
