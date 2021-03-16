#include <math.h>
#include "methods.h"

int sign(int x)
{
    return x / abs(x);
}

void lib(QPainter &painter, const QPoint &p1, const QPoint &p2)
{
    painter.drawLine(p1, p2);
}

void cda(QPainter &painter, const QPoint &p1, const QPoint &p2)
{
    int x1 = p1.x(), y1 = p1.y(), x2 = p2.x(), y2 = p2.y();

    int length = abs(x2 - x1);
    if (abs(y2 - y1) > length)
        length = abs(y2 - y1);

    int x = x1, y = y1;
    double dx = (x2 - x1) / (double) length;
    double dy = (y2 - y1) / (double) length;

    for (int i = 1; i <= length; i++)
    {
        painter.drawPoint(round(x), round(y));
        x += dx;
        y += dy;
    }
}

void brezenhem_real(QPainter &painter, const QPoint &p1, const QPoint &p2)
{
    int x1 = p1.x(), y1 = p1.y(), x2 = p2.x(), y2 = p2.y();

    int dx = x2 - x1, dy = y2 - y1;

    int sx = sign(dx), sy = sign(dy);

    dx = abs(dx);
    dy = abs(dy);

    double m = (double) dy / (double) dx;

    bool swap = false;
    if (m > 1)
    {
        int temp = dx;
        dx = dy;
        dy = temp;
        m = 1 / m;
        swap = true;
    }

    double e = m - 0.5;
    int x = x1, y = y1;

    for (int i = 1; i <= dx; i++)
    {
        painter.drawPoint(x, y);

        if (e > 0)
        {
            if (swap)
                x = x + sx;
            else
                y = y + sy;
            e -= 1;
        }
        else
        {
            if (swap)
                y = y + sy;
            else
                x = x + sx;
        }
        e += m;
    }
}
