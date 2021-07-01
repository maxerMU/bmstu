#include <QDebug>
#include <math.h>
#include "cutter.h"

cutter::cutter(const QColor &cut_col, const QColor vis_col, const QColor seg_col)
    :state(FIRST_CUT_POL_LINE_POINT), cut_col(cut_col), vis_col(vis_col), seg_col(seg_col), cut_pol(polygon(cut_col)), input_pol(polygon(seg_col)), vis_pol(polygon(vis_col))
{
}

void cutter::add_point(long x, long y, bool is_hor, bool is_vert)
{
    approx_point(x, y, is_hor, is_vert);
    if (state == FIRST_CUT_POL_LINE_POINT)
    {
        cut_pol.add_p1(x, y);
        state = SECOND_CUT_POL_LINE_POINT;
    }
    else if (state == SECOND_CUT_POL_LINE_POINT)
    {
        cut_pol.add_p2(x, y);
    }
    else if (state == FIRST_INP_POL_LINE_POINT)
    {
        input_pol.add_p1(x, y);
        state = SECOND_INP_POL_LINE_POINT;
    }
    else if (state == SECOND_INP_POL_LINE_POINT)
    {
        input_pol.add_p2(x, y);
    }
}

void cutter::render_point(long x, long y, bool is_hor, bool is_vert)
{
    approx_point(x, y, is_hor, is_vert);
    if (state == SECOND_CUT_POL_LINE_POINT)
    {
        cut_pol.render_p2(x, y);
    }
    else if (state == SECOND_INP_POL_LINE_POINT)
    {
        input_pol.render_p2(x, y);
    }
}

void cutter::approx_point(long &x, long &y, bool is_hor, bool is_vert) const
{
    if (state == SECOND_CUT_POL_LINE_POINT)
    {
        const std::vector<line> pol_lines = cut_pol.get_lines();
        if (is_hor)
            y = pol_lines[pol_lines.size() - 1].get_p1().get_y();
        if (is_vert)
            x = pol_lines[pol_lines.size() - 1].get_p1().get_x();
        return;
    }
    else if (state == SECOND_INP_POL_LINE_POINT)
    {
        const std::vector<line> pol_lines = input_pol.get_lines();
        if (is_hor)
            y = pol_lines[pol_lines.size() - 1].get_p1().get_y();
        if (is_vert)
            x = pol_lines[pol_lines.size() - 1].get_p1().get_x();
    }

    for (auto _line : cut_pol.get_lines())
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
    cut_pol = polygon(cut_col);
    state = FIRST_CUT_POL_LINE_POINT;
    input_pol = polygon(seg_col);
}

void cutter::close_polygon()
{
    if (state == SECOND_CUT_POL_LINE_POINT)
    {
        cut_pol.close();
        state = FIRST_INP_POL_LINE_POINT;
    }
    else if (state == SECOND_INP_POL_LINE_POINT)
    {
        input_pol.close();
        state = FIRST_CUT_POL_LINE_POINT;
    }
}

void cutter::draw(QPainter &painter)
{
    cut_pol.paint(painter);
    input_pol.paint(painter);

    vis_pol.set_fg(vis_col);
    vis_pol.paint(painter);
    vis_pol = polygon(vis_col);
}

void cutter::set_cut_col(const QColor &color)
{
    cut_col = color;
    cut_pol.set_fg(color);
}

void cutter::set_vis_col(const QColor &color)
{
    vis_col = color;
}

void cutter::set_seg_col(const QColor &color)
{
    seg_col = color;
    input_pol.set_fg(color);
}

bool cutter::find_intersection(point &p, const line &cut_line, const line &pol_line, long norm) const
{
    bool vis1 = is_visible(pol_line.get_p1(), cut_line, norm);
    bool vis2 = is_visible(pol_line.get_p2(), cut_line, norm);
    bool is_inter = (vis1 || vis2) && (!(vis1 && vis2));

    if (is_inter)
    {
        point cut_vec = cut_line.get_vec();
        point pol_vec = pol_line.get_vec();

        long nominator = cut_vec.get_y() * (pol_line.get_p1().get_x() - cut_line.get_p1().get_x()) -\
                         cut_vec.get_x() * (pol_line.get_p1().get_y() - cut_line.get_p1().get_y());
        long denominator = pol_vec.get_y() * cut_vec.get_x() - pol_vec.get_x() * cut_vec.get_y();

        if (denominator == 0)
        {
            p = pol_line.get_p2();
        }
        else
        {
            double t = (double) nominator/ denominator;
            p = pol_line.get_p1() + (pol_line.get_p2() - pol_line.get_p1()) * t;
        }
    }

    return is_inter;
}

bool cutter::is_visible(const point &p, const line &_line, long norm) const
{
    point v1 = _line.get_vec();
    point v2 = line(_line.get_p2(), p).get_vec();

    long pr = v1.get_x() * v2.get_y() - v1.get_y() * v2.get_x();

    if (pr * norm >= 0)
        return true;

    return false;
}

void cutter::cut()
{
    long normal = cut_pol.is_convex();
    if (!normal)
        return;

    vis_pol = input_pol;
    for (auto cut_line : cut_pol.get_lines())
    {
        polygon new_vis_pol(vis_col);
        for (auto vis_line : vis_pol.get_lines())
        {
            point inter;
            bool is_inter = find_intersection(inter, cut_line, vis_line, normal);

            if (is_inter)
            {
                new_vis_pol.add_point(inter.get_x(), inter.get_y());
            }

            bool is_vis = is_visible(vis_line.get_p2(), cut_line, normal);
            if (is_vis)
                new_vis_pol.add_point(vis_line.get_p2().get_x(), vis_line.get_p2().get_y());
        }

        new_vis_pol.close();
        vis_pol = new_vis_pol;
    }
}

long scalar_mlt(const point &p1, const point &p2)
{
    return p1.get_x() * p2.get_x() + p1.get_y() * p2.get_y();
}
