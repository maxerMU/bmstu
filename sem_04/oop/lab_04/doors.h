#ifndef DOORS_H
#define DOORS_H

#include <QObject>
#include <QTimer>

#define STAY_TIME 2000
#define DOORS_TIME 2000

class doors : public QObject
{
    Q_OBJECT

    enum doors_state
    {
        CLOSED,
        OPENING,
        OPENED,
        CLOSING,
    };

public:
    explicit doors(QObject *parent = nullptr);

signals:
    void doors_closed();
    void doors_opened();

public slots:
    void start_opening();
    void start_closing();

private slots:
    void opened();
    void closed();

private:
    doors_state _state = CLOSED;
    QTimer doors_open_timer;
    QTimer doors_stay_timer;
    QTimer doors_close_timer;
};

#endif // DOORS_H
