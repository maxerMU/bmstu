#ifndef CUTTER_H
#define CUTTER_H

#include <QPainter>
#include <vector>

#include "figures.h"

class cutter
{
    enum cutter_state
    {
        FIRST_POL_LINE_POINT,
        SECOND_POL_LINE_POINT,
        FIRST_LINE_POINT,
        SECOND_LINE_POINT,
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
    typedef bool point_code[4];
    void next_state();
    void approx_point(long &x, long &y, bool is_hor, bool is_vert);
    bool cut_line(line &res, const line &src, long norm);
    void find_point_code(long &sum, point_code &code, const point &p);
    long log_mlt(const point_code &code1, const point_code &code2);


    cutter_state state;

    QColor cut_col;
    QColor vis_col;
    QColor seg_col;

    polygon _polygon;
    std::vector<line> lines;
    std::vector<line> vis_lines;
};

#endif // CUTTER_H
