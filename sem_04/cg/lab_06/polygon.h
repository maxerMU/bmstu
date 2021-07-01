#ifndef POLYGON_H
#define POLYGON_H

#include <vector>
#include <QImage>
#include "figure.h"

namespace polygon_fig {
    struct point
    {
        point()
            :x(0), y(0) {}
        point(long x, long y)
            :x(x), y(y) {}
        long x;
        long y;
    };

    struct edge
    {
        edge(point *p1, point *p2)
            :p1(p1), p2(p2)
        {}

        point *p1;
        point *p2;
    };
}

class polygon //: public Figure
{
public:
    polygon(const QColor &fg, const QColor &bg, const QColor &paint_col);

    ~polygon() = default;

//    virtual void draw(const QPainter &painter) const override;
//    virtual void paint(const QPainter &painter) const override;
//    virtual void set_delay(size_t delay) override;

    void draw(QPainter &painter) const;
    void paint(QPainter &painter, QImage *image, size_t delay, QWidget *widget);
    void seed_paint(QPainter &painter, QImage *image, size_t delay, QWidget *widget);


    void set_seed_ptr(const polygon_fig::point &ptr);
    void add_point(polygon_fig::point *point);
    void close();

    void add_hole();

    double paint_time();
    double seed_paint_time();

private:
    void find_extrems(polygon_fig::point &min, polygon_fig::point &max) const;
    static void paint_sleep(size_t delay);
    void sort_edges_points();

    bool new_edge_state = false;
    size_t start_pos = 0;

    QColor fg;
    QColor bg;
    QColor paint_col;

    polygon_fig::point seed_ptr;

    std::vector<polygon_fig::point *> points;
    std::vector<polygon_fig::edge> edges;

};

#endif // POLYGON_H
