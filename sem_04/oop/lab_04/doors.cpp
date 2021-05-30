#include <QDebug>
#include "doors.h"

doors::doors(QObject *parent) : QObject(parent)
{
    doors_stay_timer.setInterval(STAY_TIME);

    doors_stay_timer.setSingleShot(true);
    doors_open_timer.setSingleShot(true);
    doors_close_timer.setSingleShot(true);

    QObject::connect(&doors_open_timer, SIGNAL(timeout()), this, SLOT(opened()));
    QObject::connect(&doors_close_timer, SIGNAL(timeout()), this, SLOT(closed()));
    QObject::connect(this, SIGNAL(doors_opened()), &doors_stay_timer, SLOT(start()));
    QObject::connect(&doors_stay_timer, SIGNAL(timeout()), this, SLOT(start_closing()));
}

void doors::start_opening()
{
    if (_state != CLOSING && _state != CLOSED)
        return;

    qDebug() << "Doors are opening...";
    if (_state == CLOSED)
    {
        _state = OPENING;
        doors_open_timer.start(DOORS_TIME);
    }
    else
    {
        _state = OPENING;
        int t = doors_close_timer.remainingTime();
        doors_close_timer.stop();
        doors_open_timer.start(DOORS_TIME - t);
    }
}

void doors::start_closing()
{
    if (_state != OPENED)
        return;

    _state = CLOSING;

    qDebug() << "Doors are closing...";

    doors_close_timer.start(DOORS_TIME);
}

void doors::opened()
{
    if (_state != OPENING)
        return;

    _state = OPENED;
    qDebug() << "The doors are opened.";

    emit doors_opened();
}

void doors::closed()
{
    if (_state != CLOSING)
        return;

    _state = CLOSED;
    qDebug() << "The doors are closed.";

    emit doors_closed();
}
