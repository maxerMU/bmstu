#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <QColor>
#include <QPainter>
#include <stdio.h>
#include <vector>
#include <stdlib.h>

#include "figures.h"

class canvas : public QWidget
{
    Q_OBJECT
public:
    explicit canvas(QWidget *parent = nullptr);
    ~canvas();
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);

    void clear();
    void draw_point(long x, long y, QColor fg); //deprec
    void draw_line(long x1, long y1, long x2, long y2, QColor fg); //deprec
    void draw_lines(const std::vector<line> &lines);
    void set_bg(const QColor &color);

signals:
    void resize();

private:
    std::vector<Figure *> shapes;
    QColor bg = QColor(255, 255, 255);
};

#endif // CANVAS_H
