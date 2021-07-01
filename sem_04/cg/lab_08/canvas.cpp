#include <iostream>
#include <QPointF>
#include <QApplication>
#include <QPen>
#include <QBrush>
#include "canvas.h"

//struct point
//{
//    point(long x, long y)
//        : x(x), y(y)
//    {}
//
//    long x;
//    long y;
//};
//
//struct can_point : Figure
//{
//    can_point(long x, long y, QColor fg, QColor bg)
//    : Figure(fg, bg), p(x, y)
//    {
//    }
//    void paint(QPainter &painter)
//    {
//        QPen pen = QPen(fg);
//        painter.setPen(pen);
//        painter.drawPoint(p.x, p.y);
//    }
//
//    point p;
//};
//
//struct can_line : Figure
//{
//    can_line(long x1, long y1, long x2, long y2, QColor fg, QColor bg)
//    : Figure(fg, bg), p1(x1, y1), p2(x2, y2)
//    {
//    }
//
//    void paint(QPainter &painter)
//    {
//        QPen pen = QPen(fg);
//        painter.setPen(pen);
//        painter.drawLine(p1.x, p1.y, p2.x, p2.y);
//    }
//
//    point p1;
//    point p2;
//};

canvas::canvas(QWidget *parent) : QWidget(parent)
{
    setMouseTracking(true);
}

canvas::~canvas()
{
}

void canvas::cut()
{
    _cutter.cut();
    this->update();
    is_adding = false;
}

void canvas::close()
{
    _cutter.close_polygon();
    this->update();
}

void canvas::set_bg(const QColor &color)
{
    bg = color;
}

void canvas::set_cut_col(const QColor &color)
{
    _cutter.set_cut_col(color);
    this->update();
}

void canvas::set_seg_col(const QColor &color)
{
    _cutter.set_seg_col(color);
    this->update();
}

void canvas::set_vis_col(const QColor &color)
{
    _cutter.set_vis_col(color);
    this->update();
}

void canvas::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);

    QPainter painter(this);

    painter.setBrush(bg);
    painter.setPen(QColor(0, 0, 0));
    painter.drawRect(0, 0, this->width(), this->height());

    _cutter.draw(painter);
}

void canvas::mousePressEvent(QMouseEvent *event)
{
    is_adding = true;
    Qt::KeyboardModifiers key = QApplication::queryKeyboardModifiers();
    bool is_hor = false, is_vert = false;
    if (key == Qt::ShiftModifier)
        is_hor = true;
    if (key == Qt::ControlModifier)
        is_vert = true;
    _cutter.add_point(event->pos().x(), event->pos().y(), is_hor, is_vert);
    this->update();
}

void canvas::mouseMoveEvent(QMouseEvent *event)
{
    if (!is_adding)
        return;
    Qt::KeyboardModifiers key = QApplication::queryKeyboardModifiers();
    bool is_hor = false, is_vert = false;
    if (key == Qt::ShiftModifier)
        is_hor = true;
    if (key == Qt::ControlModifier)
        is_vert = true;
    _cutter.render_point(event->pos().x(), event->pos().y(), is_hor, is_vert);
    this->update();
}

void canvas::add_point(long x, long y)
{
    _cutter.add_point(x, y, false, false);
    this->update();
}

void canvas::clear()
{
    _cutter.clear();
    is_adding = true;

    this->update();
}

//void canvas::draw_point(long x, long y, QColor fg, QColor bg)
//{
//    Figure *p = new can_point(x, y, fg, bg);
//
//    shapes.push_back(p);
//
//    this->update();
//}
//
//void canvas::draw_line(long x1, long y1, long x2, long y2, QColor fg, QColor bg)
//{
//    Figure *l = new can_line(x1, y1, x2, y2, fg, bg);
//
//    shapes.push_back(l);
//
//    this->update();
//}
