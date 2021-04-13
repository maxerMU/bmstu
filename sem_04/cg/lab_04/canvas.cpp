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
    can_point(long x, long y, QColor fg, QColor bg)
    : Figure(fg, bg), p(x, y)
    {
    }
    void paint(QPainter &painter)
    {
        QPen pen = QPen(fg);
        painter.setPen(pen);
        painter.drawPoint(p.x, p.y);
    }

    point p;
};

struct can_line : Figure
{
    can_line(long x1, long y1, long x2, long y2, QColor fg, QColor bg)
    : Figure(fg, bg), p1(x1, y1), p2(x2, y2)
    {
    }

    void paint(QPainter &painter)
    {
        QPen pen = QPen(fg);
        painter.setPen(pen);
        painter.drawLine(p1.x, p1.y, p2.x, p2.y);
    }

    point p1;
    point p2;
};

struct can_ellipse : Figure
{
    can_ellipse(long x1, long y1, long width, long height, QColor fg, QColor bg)
    : Figure(fg, bg), p(x1, y1), width(width), height(height)
    {
    }

    void paint(QPainter &painter)
    {
        QPen pen = QPen(fg);
        painter.setPen(pen);
        painter.drawEllipse(p.x, p.y, width, height);
    }

    point p;
    long width;
    long height;
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

    this->update();
}

void canvas::draw_point(long x, long y, QColor fg, QColor bg)
{
    Figure *p = new can_point(x, y, fg, bg);

    shapes.push_back(p);

    this->update();
}

void canvas::draw_line(long x1, long y1, long x2, long y2, QColor fg, QColor bg)
{
    Figure *l = new can_line(x1, y1, x2, y2, fg, bg);

    shapes.push_back(l);

    this->update();
}

void canvas::draw_ellipse(long x1, long y1, long width, long height, QColor fg, QColor bg)
{
    Figure *e = new can_ellipse(x1, y1, width, height, fg, bg);

    shapes.push_back(e);

    this->update();
}
