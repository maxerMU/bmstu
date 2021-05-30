#include "lift.h"

lift::lift(QObject *parent) : QObject(parent)
{
    QObject::connect(&_control_panel, SIGNAL(panel_new_target(long,direction)), &_cabin, SLOT(cabin_get_target(long,direction)));
    QObject::connect(&_cabin, SIGNAL(cabin_crossed_floor(long,direction)), &_control_panel, SLOT(busy(long,direction)));
    QObject::connect(&_cabin, SIGNAL(cabin_wait(long)), &_control_panel, SLOT(free(long)));
}

void lift::floor_but_clicked(long floor)
{
    _control_panel.new_target(floor);
}
