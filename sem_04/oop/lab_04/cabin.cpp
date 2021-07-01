#include <QDebug>
#include "cabin.h"

cabin::cabin(QObject *parent) : QObject(parent)
{
    cross_floor_timer.setSingleShot(true);

    QObject::connect(this, SIGNAL(cabin_achieved_target(long)), this, SLOT(stop(long)));
    QObject::connect(&_doors, SIGNAL(doors_closed()), this, SLOT(wait()));
    QObject::connect(this, SIGNAL(cabin_stopped()), &_doors, SLOT(start_opening()));
    QObject::connect(&cross_floor_timer, SIGNAL(timeout()), this, SLOT(move()));
    QObject::connect(this, SIGNAL(cabin_called()), this, SLOT(move()));
}

void cabin::move()
{
    if (_state != START_MOVING && _state != MOVE)
        return;

    if (_state == MOVE)
        cur_floor += cur_direction;
    _state = MOVE;
    if (cur_floor == cur_target)
        emit cabin_achieved_target(cur_floor);
    else
    {
        emit cabin_crossed_floor(cur_floor, cur_direction);
        cross_floor_timer.start(CROSS_FLOOR_TIME);
    }
}

void cabin::stop(long floor)
{
    if (_state != MOVE)
        return;

    _state = STOP;
    qDebug() << "Cabin stopped at floor № " << cur_floor;
    emit cabin_stopped();
}

void cabin::wait()
{
    if (_state != STOP)
        return;

    _state = WAITING_TARGET;
    qDebug() << "Cabin waiting";

    emit cabin_wait(cur_floor);
}

void cabin::cabin_get_target(long floor, const direction &dir)
{
    if (_state != WAITING_TARGET)
        return;

    _state = START_MOVING;
    cur_target = floor;
    cur_direction = dir;

    emit cabin_called();
}
