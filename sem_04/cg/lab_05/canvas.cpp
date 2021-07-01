#include <iostream>
#include <QPointF>
#include <QPen>
#include <QBrush>
#include "canvas.h"

canvas::canvas(QWidget *parent)
    : QWidget(parent)
{
}

canvas::~canvas()
{
    delete image;
    for (polygon *f : shapes)
        delete f;
}

void canvas::set_bg(const QColor &color)
{
    bg = color;
}

void canvas::set_fg(const QColor &color)
{
    fg = color;
}

void canvas::set_paint_col(const QColor &color)
{
    paint_col = color;
}

void canvas::redraw()
{
    if (!image)
        image = new QImage(this->width(), this->height(), QImage::Format_RGB32);
    QPainter painter(image);

    painter.setPen(QColor(0, 0, 0));
    painter.setBrush(bg);
    painter.drawRect(0, 0, this->width(), this->height());

    if (fill_state)
    {
        for(polygon *p : shapes)
            p->draw(painter);

        for (polygon * p : shapes)
            p->paint(painter, image, delay, this);
        fill_state = false;
    }

    for(polygon *p : shapes)
        p->draw(painter);


    update();
}

void canvas::paintEvent(QPaintEvent *event)
{
    if (!image)
        image = new QImage(this->width(), this->height(), QImage::Format_RGB32);

    QWidget::paintEvent(event);

    QPainter painter(this);
    painter.drawImage(0, 0, *image);
}

void canvas::add_point(long x, long y)
{
    polygon_fig::point *p = new polygon_fig::point(x, y);

    if (add_state == NEW)
    {
        polygon *pol = new polygon(fg, bg, paint_col);
        pol->add_point(p);
        shapes.push_back(pol);
        add_state = ADD;
    }
    else if (add_state == ADD)
    {
        shapes.back()->add_point(p);
    }

    redraw();
}

void canvas::mousePressEvent(QMouseEvent *event)
{
    add_point((long) event->pos().x(), (long) event->pos().y());
}

void canvas::finish_figure()
{
    shapes.back()->close();
    add_state = NEW;
    fill_state = true;

    redraw();
}

void canvas::add_hole()
{
    shapes.back()->add_hole();

    redraw();
}

void canvas::set_delay(size_t delay)
{
    this->delay = delay;
}

void canvas::clear()
{
    for (polygon *f : shapes)
        delete f;
    shapes.clear();

    redraw();
}

void canvas::get_times(std::vector<double> &times)
{
    for (polygon *p : shapes)
        times.push_back(p->paint_time());
}
