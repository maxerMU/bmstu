#include "qt_drawer.h"

void qt_drawer::clear_scene()
{
    _scene->clear();
}

void qt_drawer::draw_line(const point &p1, const point &p2)
{
    _scene->addLine(p1.get_x(), p1.get_y(), p2.get_x(), p2.get_y());
}
