#ifndef CUTTER_H
#define CUTTER_H

#include <QPainter>
#include <vector>

#include "figures.h"

class cutter
{
    enum cutter_state
    {
        FIRST_CUT_POL_LINE_POINT,
        SECOND_CUT_POL_LINE_POINT,
        FIRST_INP_POL_LINE_POINT,
        SECOND_INP_POL_LINE_POINT,
    };

public:
    cutter(const QColor &cut_col, const QColor vis_col, const QColor seg_col);
    void clear();
    void close_polygon();
    void draw(QPainter &painter);
    void cut();
    void add_point(long x, long y, bool is_hor, bool is_vert);
    void render_point(long x, long y, bool is_hor, bool is_vert);
    void set_cut_col(const QColor &color);
    void set_vis_col(const QColor &color);
    void set_seg_col(const QColor &color);

private:
    void approx_point(long &x, long &y, bool is_hor, bool is_vert) const;
    bool find_intersection(point &p, const line &cut_line, const line &pol_line, long norm) const;
    bool is_visible(const point &p, const line &_line, long norm) const;

    cutter_state state;

    QColor cut_col;
    QColor vis_col;
    QColor seg_col;

    polygon cut_pol;
    polygon input_pol;
    polygon vis_pol;
};

#endif // CUTTER_H
