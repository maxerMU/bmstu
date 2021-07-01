#include <QDebug>
#include <math.h>
#include "cutter.h"

cutter::cutter(const QColor &cut_col, const QColor vis_col, const QColor seg_col)
    :state(FIRST_POL_LINE_POINT), cut_col(cut_col), vis_col(vis_col), seg_col(seg_col), _polygon(polygon(cut_col))
{
}

void cutter::next_state()
{
    if (state == FIRST_POL_LINE_POINT)
        state = SECOND_POL_LINE_POINT;
    else if (state == SECOND_POL_LINE_POINT)
        state = FIRST_LINE_POINT;
    else if (state == FIRST_LINE_POINT)
        state = SECOND_LINE_POINT;
    else if (state == SECOND_LINE_POINT)
        state = FIRST_LINE_POINT;
}

void cutter::add_point(long x, long y, bool is_hor, bool is_vert)
{
    approx_point(x, y, is_hor, is_vert);
    if (state == FIRST_POL_LINE_POINT)
    {
        _polygon.add_p1(x, y);
        state = SECOND_POL_LINE_POINT;
    }
    else if (state == SECOND_POL_LINE_POINT)
    {
        _polygon.add_p2(x, y);
    }
    else if (state == FIRST_LINE_POINT)
    {
        lines.push_back(line(seg_col, x, y));
        state = SECOND_LINE_POINT;
    }
    else if (state == SECOND_LINE_POINT)
    {
        lines[lines.size() - 1].set_p2(point(x, y));
        state = FIRST_LINE_POINT;
    }
}

void cutter::render_point(long x, long y, bool is_hor, bool is_vert)
{
    approx_point(x, y, is_hor, is_vert);
    if (state == SECOND_POL_LINE_POINT)
    {
        _polygon.render_p2(x, y);
    }
    else if (state == SECOND_LINE_POINT)
    {
        lines[lines.size() - 1].set_p2(point(x, y));
    }
}

void cutter::approx_point(long &x, long &y, bool is_hor, bool is_vert)
{
    if (state == SECOND_LINE_POINT)
    {
        if (is_hor)
            y = lines[lines.size() - 1].get_p1().get_y();
        if (is_vert)
            x = lines[lines.size() - 1].get_p1().get_x();
    }
    else if (state == SECOND_POL_LINE_POINT)
    {
        const std::vector<line> pol_lines = _polygon.get_lines();
        if (is_hor)
            y = pol_lines[pol_lines.size() - 1].get_p1().get_y();
        if (is_vert)
            x = pol_lines[pol_lines.size() - 1].get_p1().get_x();
        return;
    }

    for (auto _line : _polygon.get_lines())
    {
        point h = _line.find_distance(point(x, y));
        if (h - point(x, y) < 5)
        {
            x = h.get_x();
            y = h.get_y();
        }
    }
}

void cutter::clear()
{
    _polygon = polygon(cut_col);
    state = FIRST_POL_LINE_POINT;
    lines.clear();
}

void cutter::close_polygon()
{
    _polygon.close();
    state = FIRST_LINE_POINT;
}

void cutter::draw(QPainter &painter)
{
    _polygon.paint(painter);
    for (auto _line : lines)
        _line.paint(painter);
    for (line _line : vis_lines)
        _line.paint(painter);
    vis_lines.clear();
}

void cutter::set_cut_col(const QColor &color)
{
    cut_col = color;
    _polygon.set_fg(color);
}

void cutter::set_vis_col(const QColor &color)
{
    vis_col = color;
}

void cutter::set_seg_col(const QColor &color)
{
    seg_col = color;
    for (line &_line : lines)
        _line.set_fg(color);
}

void cutter::cut()
{
    long normal = _polygon.is_convex();
    if (!normal)
        return;

    line vis_line(vis_col);
    for (line _line : lines)
    {
        bool is_vis = cut_line(vis_line, _line, normal);
        if (is_vis)
            vis_lines.push_back(vis_line);
    }
}

long scalar_mlt(const point &p1, const point &p2)
{
    return p1.get_x() * p2.get_x() + p1.get_y() * p2.get_y();
}

bool cutter::cut_line(line &res, const line &src, long norm)
{
    bool is_vis = true;
    double tb = 0, te = 1;

    point d = src.get_p2() - src.get_p1();
    for (line _line : _polygon.get_lines())
    {
        point w = src.get_p1() - _line.get_p1();
        point line_vec = _line.get_vec();
        point n(-norm * line_vec.get_y(), norm * line_vec.get_x());

        long wscalar = scalar_mlt(w, n);
        long dscalar = scalar_mlt(d, n);

        if (dscalar == 0)
        {
            if (wscalar < 0)
                return false;
        }
        else
        {
            double t = - (double) wscalar / dscalar;
            if (dscalar > 0)
            {
                if (t > 1)
                    return false;
                if (t > tb)
                    tb = t;
            }
            else
            {
                if (t < 0)
                    return false;
                if (t < te)
                    te = t;
            }
        }
    }

    if (tb > te)
    {
        is_vis = false;
    }
    else
    {
        res.set_p1(src.get_p1() + (src.get_p2() - src.get_p1()) * tb);
        res.set_p2(src.get_p1() + (src.get_p2() - src.get_p1()) * te);
    }

    return is_vis;
}
