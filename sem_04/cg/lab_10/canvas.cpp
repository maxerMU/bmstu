#include <iostream>
#include <QPointF>
#include <QPen>
#include <QBrush>
#include "canvas.h"

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

void canvas::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);

    emit resize();
}

void canvas::clear()
{
    for (Figure *f : shapes)
        delete f;
    shapes.clear();

    this->update();
}

void canvas::draw_point(long x, long y, QColor fg)
{
    Figure *p = new point(x, y, fg);

    shapes.push_back(p);

    this->update();
}

void canvas::draw_line(long x1, long y1, long x2, long y2, QColor fg)
{
    Figure *l = new line(x1, y1, x2, y2, fg);

    shapes.push_back(l);

    this->update();
}

void canvas::draw_lines(const std::vector<line> &lines)
{
    for (auto _line : lines)
        shapes.push_back(new line(_line));

    this->update();
}
