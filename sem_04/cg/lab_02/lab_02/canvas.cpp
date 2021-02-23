#include <iostream>
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
    can_point(long x, long y, QColor color, size_t width)
    : Figure(color, width), p(x, y)
    {
    }
    void paint(QPainter &painter)
    {
        QPen pen = QPen(color);
        QBrush brush = QBrush(color);

        painter.setPen(pen);
        painter.setBrush(brush);

        painter.drawEllipse(p.x - width / 2, p.y - width / 2, width, width);
    }

    point p;
};

struct can_line : Figure
{
    can_line(long x1, long y1, long x2, long y2, QColor color, size_t width)
    : Figure(color, width), p1(x1, y1), p2(x2, y2)
    {
    }

    void paint(QPainter &painter)
    {
        QPen pen = QPen(color);
        QBrush brush = QBrush(color);

        painter.setPen(pen);
        painter.setBrush(brush);

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

void canvas::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);

    QPainter painter(this);

    for(Figure *f : shapes)
        f->paint(painter);
}

void canvas::clear()
{
    for (Figure *f : shapes)
        delete f;
    shapes.clear();
}

void canvas::draw_point(long x, long y, QColor color, size_t width)
{
    Figure *p = new can_point(x, y, color, width);

    shapes.push_back(p);

    this->update();
}

void canvas::draw_line(long x1, long y1, long x2, long y2, QColor color, size_t width)
{
    Figure *l = new can_line(x1, y1, x2, y2, color, width);

    shapes.push_back(l);

    this->update();
}
