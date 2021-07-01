#include <math.h>
#include "cutter.h"

cutter::cutter(const QColor &cut_col, const QColor vis_col, const QColor seg_col)
    :state(FIRST_RECT_POINT), cut_col(cut_col), vis_col(vis_col), seg_col(seg_col), rect(rectangle(cut_col))
{
}

void cutter::next_state()
{
    if (state == FIRST_RECT_POINT)
        state = SECOND_RECT_POINT;
    else if (state == SECOND_RECT_POINT)
        state = FIRST_LINE_POINT;
    else if (state == FIRST_LINE_POINT)
        state = SECOND_LINE_POINT;
    else if (state == SECOND_LINE_POINT)
        state = FIRST_LINE_POINT;
}

void cutter::add_point(long x, long y, bool is_hor, bool is_vert)
{
    approx_point(x, y, is_hor, is_vert);
    if (state == FIRST_RECT_POINT)
    {
        rect = rectangle(cut_col, x, y);
    }
    else if (state == SECOND_RECT_POINT)
    {
        rect.set_p2(point(x, y));
    }
    else if (state == FIRST_LINE_POINT)
    {
        lines.push_back(line(seg_col, x, y));
    }
    else if (state == SECOND_LINE_POINT)
    {
        lines[lines.size() - 1].set_p2(point(x, y));
    }
    next_state();
}

void cutter::render_point(long x, long y, bool is_hor, bool is_vert)
{
    approx_point(x, y, is_hor, is_vert);
    if (state == SECOND_RECT_POINT)
    {
        rect.set_p2(point(x, y));
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

    long min_x = rect.get_left();
    long max_x = rect.get_right();
    long min_y = rect.get_bottom();
    long max_y = rect.get_top();

    long eps = 4;
    if (abs(rect.get_p1().get_x() - x) < eps && y >= min_y && y <= max_y)
        x = rect.get_p1().get_x();
    if (abs(rect.get_p2().get_x() - x) < eps && y >= min_y && y <= max_y)
        x = rect.get_p2().get_x();
    if (abs(rect.get_p1().get_y() - y) < eps && x >= min_x && x <= max_x)
        y = rect.get_p1().get_y();
    if (abs(rect.get_p2().get_y() - y) < eps && x >= min_x && x <= max_x)
        y = rect.get_p2().get_y();
}

void cutter::clear()
{
    rect = rectangle(cut_col);
    state = FIRST_RECT_POINT;
    lines.clear();
}

void cutter::draw(QPainter &painter)
{
    rect.paint(painter);
    for (auto _line : lines)
        _line.paint(painter);
    for (line _line : vis_lines)
        _line.paint(painter);
    vis_lines.clear();
}

void cutter::set_cut_col(const QColor &color)
{
    cut_col = color;
    rect.set_fg(color);
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
    line vis_line(vis_col);
    for (line _line : lines)
    {
        bool is_vis = cut_line(vis_line, _line);
        if (is_vis)
            vis_lines.push_back(vis_line);
    }
}

void cutter::find_point_code(long &sum, point_code &code, const point &p)
{
    long min_x = rect.get_left();
    long max_x = rect.get_right();
    long min_y = rect.get_bottom();
    long max_y = rect.get_top();

    for (size_t i = 0; i < 4; i++)
        code[i] = false;

    if ((p.get_x()) < min_x)
        code[0] = true;
    else if ((p.get_x()) > max_x)
        code[1] = true;
    if ((p.get_y()) < min_y)
        code[2] = true;
    else if ((p.get_y()) > max_y)
        code[3] = true;

    sum = 0;
    for (size_t i = 0; i < 4; i++)
        sum += code[i];
}

long cutter::log_mlt(const point_code &code1, const point_code &code2)
{
    long mlt = 0;
    for (size_t i = 0; i < 4; i++)
        mlt += code1[i] && code2[i];

    return mlt;
}

bool cutter::cut_line(line &res, const line &src)
{
    point p1 = src.get_p1();
    point p2 = src.get_p2();
    bool is_vis = false;

    point_code t1, t2;
    long sum1, sum2;

    for (size_t i = 0; i < 2; i++)
    {
        find_point_code(sum1, t1, p1);
        find_point_code(sum2, t2, p2);
        if (sum1 == 0 && sum2 == 0)
        {
            is_vis = true;
            break;
        }
        if (log_mlt(t1, t2) != 0)
            return false;

        point work = p1;
        if (sum2 != 0)
        {
            double eps = 0.05;
            while (!(p1 - p2 < eps))
            {
                point pm = (p1 + p2) / 2.0;
                point mem = p1;

                p1 = pm;
                find_point_code(sum1, t1, p1);

                if (log_mlt(t1, t2) != 0)
                {
                    p1 = mem;
                    p2 = pm;
                    find_point_code(sum2, t2, p2);
                }
            }
        }
        p1 = p2;
        p2 = work;
    }

    if (!is_vis)
    {
        find_point_code(sum1, t1, p1);
        find_point_code(sum2, t2, p2);
        if (log_mlt(t1, t2) == 0)
            is_vis = true;
    }

    if (is_vis)
    {
        res.set_p1(p1);
        res.set_p2(p2);
    }

    return is_vis;
}
