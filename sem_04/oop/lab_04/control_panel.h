#ifndef CONTROL_PANEL_H
#define CONTROL_PANEL_H

#include <QObject>
#include <vector>
#include "direction.h"

class control_panel : public QObject
{
    Q_OBJECT

    enum panel_state
    {
        FREE,
        BUSY,
    };

public:
    explicit control_panel(QObject *parent = nullptr);
    void new_target(long floor);

public slots:
    void busy(long floor, const direction &_direction);
    void free(long floor);

signals:
    void panel_new_target(long floor, const direction &_direction);

private:
    void next_target();
    panel_state state = FREE;
    long current_floor = 1;
    long current_target = -1;
    direction current_direction = STAY;
    std::vector<bool> is_target;

};

#endif // CONTROL_PANEL_H
