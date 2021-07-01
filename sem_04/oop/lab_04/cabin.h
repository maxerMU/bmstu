#ifndef CABIN_H
#define CABIN_H

#include <QObject>
#include <QTimer>
#include <doors.h>

#include "direction.h"

#define CROSS_FLOOR_TIME 3000

class cabin : public QObject
{
    Q_OBJECT

    enum cabin_state
    {
        WAITING_TARGET,
        START_MOVING,
        MOVE,
        STOP,
    };

public:
    explicit cabin(QObject *parent = nullptr);

signals:
    void cabin_called();
    void cabin_stopped();
    void cabin_achieved_target(long);
    void cabin_crossed_floor(long, const direction &_direction);
    void cabin_wait(long floor);

public slots:
    void move();
    void stop(long floor);
    void wait();
    void cabin_get_target(long floor, const direction &dir);

private:
    long cur_floor = 1;
    long cur_target = -1;
    direction cur_direction = STAY;
    doors _doors;
    cabin_state _state = WAITING_TARGET;
    QTimer cross_floor_timer;
};

#endif // CABIN_H
