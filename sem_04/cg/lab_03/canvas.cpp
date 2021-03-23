#include <iostream>
#include <QPointF>
#include <QPen>
#include <QBrush>
#include "canvas.h"

struct point
{
    point(long x, long y)
        : x(x), y(y)
    {}

    long x;
    long y;
};

struct can_point : Figure
{
    can_point(long x, long y, QColor fg, QColor bg, size_t width)
    : Figure(fg, bg, width), p(x, y)
    {
    }
    void paint(QPainter &painter)
    {
        QPen pen = QPen(bg);
        painter.setPen(pen);
        painter.drawPoint(p.x, p.y);
        pen = QPen(fg);
        painter.setPen(pen);
        painter.drawPoint(p.x, p.y);
    }

    point p;
};

struct can_line : Figure
{
    can_line(long x1, long y1, long x2, long y2, QColor fg, QColor bg, size_t width)
    : Figure(fg, bg, width), p1(x1, y1), p2(x2, y2)
    {
    }

    void paint(QPainter &painter)
    {
        QPen pen = QPen(bg);
        painter.setPen(pen);
        painter.drawLine(p1.x, p1.y, p2.x, p2.y);
        pen = QPen(fg);
        painter.setPen(pen);
        painter.drawLine(p1.x, p1.y, p2.x, p2.y);
    }

    point p1;
    point p2;
};

canvas::canvas(QWidget *parent) : QWidget(parent)
{
}

canvas::~canvas()
{
    for (Figure *f : shapes)
        delete f;
}

void canvas::set_bg(const QColor &color)
{
    bg = color;
}

void canvas::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);

    QPainter painter(this);

    painter.setBrush(bg);
    painter.setPen(QColor(0, 0, 0));
    painter.drawRect(0, 0, this->width(), this->height());

    for(Figure *f : shapes)
        f->paint(painter);
}

void canvas::clear()
{
    for (Figure *f : shapes)
        delete f;
    shapes.clear();
}

void canvas::draw_point(long x, long y, QColor fg, QColor bg, size_t width)
{
    Figure *p = new can_point(x, y, fg, bg, width);

    shapes.push_back(p);

    this->update();
}

void canvas::draw_line(long x1, long y1, long x2, long y2, QColor fg, QColor bg, size_t width)
{
    Figure *l = new can_line(x1, y1, x2, y2, fg, bg, width);

    shapes.push_back(l);

    this->update();
}
