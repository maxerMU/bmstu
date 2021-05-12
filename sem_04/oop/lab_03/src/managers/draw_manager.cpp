#include <math.h>
#include "draw_manager.h"
#include "model.h"
#include "camera.h"
#include "composite.h"

void draw_manager::set_cam(const std::shared_ptr<camera> &_camera)
{
    cur_cam = _camera;
}

void draw_manager::set_drawer(const std::shared_ptr<base_drawer> &_drawer)
{
    this->_drawer = _drawer;
}

void draw_manager::visit(const camera &_camera)
{
}

void draw_manager::visit(const composite &_composite)
{
}

void draw_manager::visit(const model &_model)
{
    auto _points = _model.get_units()->get_points();

    for (point &_point : _points)
        proect_point(_point);

    auto _edges = _model.get_units()->get_edges();
    for (auto _edge : _edges)
        _drawer->draw_line(_points[_edge.get_first()], _points[_edge.get_second()]);
}

void draw_manager::proect_point(point &_point)
{
    point move(cur_cam->get_pos().get_x(), cur_cam->get_pos().get_x(), 0);

    _point.move(move);

    point center(0, 0, 0);
    point rotate(cur_cam->get_xangle(), cur_cam->get_yangle(), cur_cam->get_zangle());
    _point.rotate(center, rotate);

    double eps = 1e-10;
    double dist = cur_cam->get_pos().get_z() + _point.get_z();

    if (fabs(dist) < eps)
        dist = eps;

    double dist_coef = cur_cam->get_pos().get_z() / dist;
    _point.set_x(_point.get_x() * dist_coef);
    _point.set_y(_point.get_y() * dist_coef);
}
