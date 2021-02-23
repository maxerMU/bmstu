#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <QColor>
#include <QPainter>
#include <stdio.h>
#include <vector>
#include <stdlib.h>

struct Figure
{
    Figure(QColor color, size_t width)
        :color(color), width(width)
    {
    }
    virtual void paint(QPainter &painter) = 0;
    virtual ~Figure() {}

    QColor color;
    size_t width;
};

class canvas : public QWidget
{
    Q_OBJECT
public:
    explicit canvas(QWidget *parent = nullptr);
    ~canvas();
    void paintEvent(QPaintEvent *event);

    void clear();
    void draw_point(long x, long y, QColor color, size_t width);
    void draw_line(long x1, long y1, long x2, long y2, QColor color, size_t width);

private:
    std::vector<Figure *> shapes;

signals:

};

#endif // CANVAS_H
