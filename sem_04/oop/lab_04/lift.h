#ifndef LIFT_H
#define LIFT_H

#include <QObject>
#include "control_panel.h"
#include "cabin.h"

class lift : public QObject
{
    Q_OBJECT
public:
    explicit lift(QObject *parent = nullptr);

signals:

public slots:
    void floor_but_clicked(long floor);

private:
    control_panel _control_panel;
    cabin _cabin;
};

#endif // LIFT_H
