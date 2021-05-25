#include <QPen>
#include <math.h>

#include "figures.h"

void point::paint(QPainter &painter) const
{
    painter.setPen(QPen(fg));
    painter.drawPoint(x, y);
}

void line::paint(QPainter &painter) const
{
    painter.setPen(QPen(fg));
    painter.drawLine(p1.get_x(), p1.get_y(), p2.get_x(), p2.get_y());
}

void rectangle::paint(QPainter &painter) const
{
    painter.setPen(QPen(fg));
    painter.drawRect(p1.get_x(), p1.get_y(), p2.get_x() - p1.get_x(), p2.get_y() - p1.get_y());
}

point point::operator -(const point &p)
{
    return point(x - p.x, y - p.y);
}

point point::operator +(const point &p)
{
    return point(x + p.x, y + p.y);
}

point point::operator /(double num)
{
    return point(x / num, y / num);
}

bool point::operator <(double eps)
{
    if (fabs(x) < eps && fabs(y) < eps)
        return true;

    return false;
}

double point::get_x() const
{
    return x;
}

double point::get_y() const
{
    return y;
}

void point::set_x(long x)
{
    this->x = x;
}

void point::set_y(long y)
{
    this->y = y;
}

point line::get_p1() const
{
    return p1;
}

point line::get_p2() const
{
    return p2;
}

void line::set_p1(const point &p)
{
    p1 = p;
}

void line::set_p2(const point &p)
{
    p2 = p;
}

point rectangle::get_p1() const
{
    return p1;
}

point rectangle::get_p2() const
{
    return p2;
}

void rectangle::set_p1(const point &p)
{
    p1 = p;
}

void rectangle::set_p2(const point &p)
{
    p2 = p;
}

long rectangle::get_top() const
{
    if (p1.get_y() > p2.get_y())
        return p1.get_y();

    return p2.get_y();
}

long rectangle::get_bottom() const
{
    if (p1.get_y() < p2.get_y())
        return p1.get_y();

    return p2.get_y();
}

long rectangle::get_left() const
{
    if (p1.get_x() < p2.get_x())
        return p1.get_x();

    return p2.get_x();
}

long rectangle::get_right() const
{
    if (p1.get_x() > p2.get_x())
        return p1.get_x();

    return p2.get_x();
}
