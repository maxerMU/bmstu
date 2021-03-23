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
    Figure(const QColor &fg, const QColor &bg, size_t width)
        :fg(fg), bg(bg), width(width)
    {
    }
    virtual void paint(QPainter &painter) = 0;
    virtual ~Figure() {}

    QColor fg;
    QColor bg;
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
    void draw_point(long x, long y, QColor color, QColor bg, size_t width);
    void draw_line(long x1, long y1, long x2, long y2, QColor fg, QColor bg, size_t width);
    void set_bg(const QColor &color);

private:
    std::vector<Figure *> shapes;
    QColor bg = QColor(255, 255, 255);

signals:

};

#endif // CANVAS_H
