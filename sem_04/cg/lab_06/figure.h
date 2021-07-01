#ifndef FIGURE_H
#define FIGURE_H

#include <QColor>
#include <QPainter>

class Figure
{
public:
    virtual void draw(const QPainter &painter) const = 0;
    virtual void paint(const QPainter &painter) const = 0;
    virtual void set_delay(size_t delay) = 0;

    virtual ~Figure() = default;

};

#endif // FIGURE_H
