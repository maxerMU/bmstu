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
    _point.set_x(_point.get_x() - cur_cam->get_pos().get_x());
    _point.set_y(_point.get_y() - cur_cam->get_pos().get_y());
}
