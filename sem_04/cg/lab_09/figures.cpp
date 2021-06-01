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
    QString text("(");
    text.append(QString::number(p1.get_x()));
    text.append(", ");
    text.append(QString::number(p1.get_y()));
    text.append(")");
    painter.drawText(p1.get_x() - 5, p1.get_y() + 5, text);

    QString text2("(");
    text2.append(QString::number(p2.get_x()));
    text2.append(", ");
    text2.append(QString::number(p2.get_y()));
    text2.append(")");
    painter.drawText(p2.get_x() - 5, p2.get_y() + 5, text2);
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

point point::operator *(double num)
{
    return point(x * num, y * num);
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

long point::get_x() const
{
    return x;
}

long point::get_y() const
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

point line::get_vec() const
{
    return point(p2.get_x() - p1.get_x(), p2.get_y() - p1.get_y());
}

void line::set_p1(const point &p)
{
    p1 = p;
}

void line::set_p2(const point &p)
{
    p2 = p;
}

point line::find_distance(const point &a) const
{
    point p = this->get_vec();
    point h(0, 0);

    if (p.get_x() == 0)
    {
        h.set_x(p1.get_x());
        h.set_y(a.get_y());
    }
    else if (p.get_y() == 0)
    {
        h.set_x(a.get_x());
        h.set_y(p1.get_y());
    }
    else
    {
        double hy = (p.get_x() * p.get_y() * (a.get_x() - p1.get_x()) + p1.get_y() * p.get_x() * p.get_x() +
                 p.get_y() * p.get_y() * a.get_y()) / (p.get_x() * p.get_x() + p.get_y() * p.get_y());
        h.set_x((hy - p1.get_y()) / p.get_y() * p.get_x() + p1.get_x());
        h.set_y(hy);
    }

    return h;
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

void polygon::add_p1(long x, long y)
{
    lines.push_back(line(fg, x, y));
}

void polygon::add_p2(long x, long y)
{
    lines[lines.size() - 1].set_p2(point(x, y));
    lines.push_back(line(fg, x, y));
}

void polygon::render_p2(long x, long y)
{
    lines[lines.size() - 1].set_p2(point(x, y));
}

void polygon::add_point(long x, long y)
{
    if (lines.size() == 0)
        add_p1(x, y);
    else
        add_p2(x, y);
}

void polygon::set_fg(const QColor &fg)
{
    this->fg = fg;
    for (line &_line : lines)
        _line.set_fg(fg);
}

void polygon::close()
{
    if (lines.size() != 0)
        lines[lines.size() - 1].set_p2(lines[0].get_p1());
}

std::vector<line> polygon::get_lines() const
{
    return lines;
}

void polygon::paint(QPainter &painter) const
{
    for (auto _line : lines)
        _line.paint(painter);
}

long sign(long x)
{
    if (x > 0)
        return 1;
    if (x == 0)
        return 0;

    return -1;
}

long polygon::is_convex() const
{
    point v1 = lines[0].get_vec();
    point v2 = lines[1].get_vec();

    long pr = v1.get_x() * v2.get_y() - v1.get_y() * v2.get_x();
    long prev = sign(pr);

    for (size_t i = 2; i < lines.size(); i++)
    {
        v1 = v2;
        v2 = lines[i].get_vec();

        pr = v1.get_x() * v2.get_y() - v1.get_y() * v2.get_x();
        long cur = sign(pr);

        if (cur != prev)
            return 0;

        prev = cur;
    }

    v1 = v2;
    v2 = lines[0].get_vec();

    pr = v1.get_x() * v2.get_y() - v1.get_y() * v2.get_x();
    long cur = sign(pr);

    if (cur != prev)
        return 0;

    return cur;
}
