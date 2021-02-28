#include <iostream>
#include <stdio.h>
#include <QColor>
#include <QPointF>
#include <math.h>
#include "epycycloide.h"

double eps = 1e-6;
double eps_inter = 1;

epycycloide::epycycloide(double angle_min, double angle_max, double angle_step, double a, double b,
                         double rect_offset, double line_step, double line_angle, canvas &field)
    :angle_min(angle_min), angle_max(angle_max), angle_step(angle_step), a(a), b(b),
     rect_offset(rect_offset), line_step(line_step), line_angle(line_angle), field(field)
{
    to_begining(true);
}

epycycloide::~epycycloide()
{
    for (ep_point *point : epycycloide_points)
        delete point;

    for (ep_point *point : rect_points)
        delete point;

    for (ep_point *point : lines_points)
        delete point;

    for (move_state *state : history)
        delete state;
}

bool epycycloide::is_on_epycycloide(ep_point p)
{
    double x = p.x, y = p.y;

    double sq = sqrt(-y*y*(25*b*b*b*b - 34*b*b*(x*x+y*y) + 9*(x*x+y*y)*(x*x+y*y)));

    double xcr1 = (5*b*b*x + sq + 3*x*x*x + 3*x*y*y) / (6 * (x*x+y*y));
    double ycr1 = (5*b*b*y*y - x*sq + 3*x*x*y*y + 3*y*y*y*y) / (6 * y * (x*x + y*y));
    double xcr2 = (5*b*b*x - sq + 3*x*x*x + 3*x*y*y) / (6 * (x*x+y*y));
    double ycr2 = (5*b*b*y*y + x*sq + 3*x*x*y*y + 3*y*y*y*y) / (6 * y * (x*x + y*y));

    double t1 = acos(xcr1 / sqrt(xcr1 * xcr1 + ycr1 * ycr1));
    if (ycr1 > 0)
        t1 = 2 * M_PI - t1;

    double t2 = acos(xcr2 / sqrt(xcr2 * xcr2 + ycr2 * ycr2));
    if (ycr2 > 0)
        t2 = 2 * M_PI - t2;

    double ep_x1 = (a + b) * cos(t1) - a * cos((a + b) * t1 / a);
    double ep_y1 = - (a + b) * sin(t1) + a * sin((a + b) * t1 / a);

    double ep_x2 = (a + b) * cos(t2) - a * cos((a + b) * t2 / a);
    double ep_y2 = - (a + b) * sin(t2) + a * sin((a + b) * t2 / a);

    return (fabs(ep_x1 - p.x) < eps_inter && fabs(ep_y1 - p.y) < eps_inter) || \
           (fabs(ep_x2 - p.x) < eps_inter && fabs(ep_y2 - p.y) < eps_inter);
}

void epycycloide::move(double dx, double dy, bool remember)
{
    // move epycycloide
    for (ep_point *point : epycycloide_points)
    {
        point->x += dx;
        point->y += dy;
    }

    // move rectangle
    for (ep_point *point : rect_points)
    {
        point->x += dx;
        point->y += dy;
    }

    // move lines
    for (ep_point *point : lines_points)
    {
        point->x += dx;
        point->y += dy;
    }

    if (remember)
        history.push_back(new move_state(dx, dy, 0, 0, 1, 1, 0));

    draw();
}

void epycycloide::scale(double xm, double ym, double kx, double ky, bool remember)
{
    // scale epycycloide
    for (ep_point *point : epycycloide_points)
    {
        point->x = point->x * kx + (1 - kx) * xm;
        point->y = point->y * ky + (1 - ky) * ym;
    }

    // scale rectangle
    for (ep_point *point : rect_points)
    {
        point->x = point->x * kx + (1 - kx) * xm;
        point->y = point->y * ky + (1 - ky) * ym;
    }

    // scale lines
    for (ep_point *point : lines_points)
    {
        point->x = point->x * kx + (1 - kx) * xm;
        point->y = point->y * ky + (1 - ky) * ym;
    }

    if (remember)
        history.push_back(new move_state(0, 0, xm, ym, kx, ky, 0));

    draw();
}

void epycycloide::rotate(double xm, double ym, double angle, bool remember)
{
    double rad_angle = (angle * M_PI) / 180;

    // rotate epycycloide
    for (ep_point *point : epycycloide_points)
    {
        double x = point->x;
        double y = point->y;

        point->x = xm + (x - xm) * cos(rad_angle) + (y - ym) * sin(rad_angle);
        point->y = ym - (x - xm) * sin(rad_angle) + (y - ym) * cos(rad_angle);
    }

    // rotate rectangle
    for (ep_point *point : rect_points)
    {
        double x = point->x;
        double y = point->y;

        point->x = xm + (x - xm) * cos(rad_angle) + (y - ym) * sin(rad_angle);
        point->y = ym - (x - xm) * sin(rad_angle) + (y - ym) * cos(rad_angle);
    }

    // rotate lines
    for (ep_point *point : lines_points)
    {
        double x = point->x;
        double y = point->y;

        point->x = xm + (x - xm) * cos(rad_angle) + (y - ym) * sin(rad_angle);
        point->y = ym - (x - xm) * sin(rad_angle) + (y - ym) * cos(rad_angle);
    }

    if (remember)
        history.push_back(new move_state(0, 0, xm, ym, 1, 1, angle));

    draw();
}

void epycycloide::get_epycycloide_points()
{
    double x = (a + b) * cos(angle_min) - a * cos((a + b) * angle_min / a);
    double y = - (a + b) * sin(angle_min) + a * sin((a + b) * angle_min / a);
    epycycloide_points.push_back(new ep_point(x, y));

    for (double t = angle_min + angle_step; t < angle_max; t += angle_step)
    {
        x = (a + b) * cos(t) - a * cos((a + b) * t / a);
        y = - (a + b) * sin(t) + a * sin((a + b) * t / a);
        if (fabs(x - epycycloide_points[epycycloide_points.size() - 1]->x) > 1 ||
            fabs(y - epycycloide_points[epycycloide_points.size() - 1]->y) > 1)
            epycycloide_points.push_back(new ep_point(x , y));
    }
}

void epycycloide::get_rect_points()
{
    double xmin = epycycloide_points[1]->x, xmax = xmin, ymin = epycycloide_points[1]->y, ymax = ymin;

    size_t size = epycycloide_points.size();

    for (size_t i = 2; i < size; i++)
    {
        if (epycycloide_points[i]->x < xmin)
            xmin = epycycloide_points[i]->x;
        if (epycycloide_points[i]->x > xmax)
            xmax = epycycloide_points[i]->x;
        if (epycycloide_points[i]->y < ymin)
            ymin = epycycloide_points[i]->y;
        if (epycycloide_points[i]->y > ymax)
            ymax = epycycloide_points[i]->y;
    }

    rect_points.push_back(new ep_point(xmin - rect_offset, ymin - rect_offset));
    rect_points.push_back(new ep_point(xmin - rect_offset, ymax + rect_offset));
    rect_points.push_back(new ep_point(xmax + rect_offset, ymax + rect_offset));
    rect_points.push_back(new ep_point(xmax + rect_offset, ymin - rect_offset));
}

void epycycloide::get_line_points()
{
    double xmin = rect_points[0]->x, xmax = rect_points[3]->x;
    double ymin = rect_points[0]->y, ymax = rect_points[1]->y;
    for (double x0 = xmin + line_step; x0 < xmax + (ymax - ymin) / tan(line_angle); x0 += line_step)
    {
        double x1 = x0 - line_step;
        double y1 = ymin + line_step * tan(line_angle);
        double dx = x1 - x0, dy = y1 - ymin;

        double y_xmin = (xmin * dy - x0 * dy + ymin * dx) / dx;
        double y_xmax = (xmax * dy - x0 * dy + ymin * dx) / dx;
        double x_ymin = x0;
        double x_ymax = (dx * (ymax - ymin) + x0 * dy) / dy;

        if (x_ymin > xmin && x_ymin < xmax)
            lines_points.push_back(new ep_point(x_ymin, ymin));
        if (y_xmax > ymin && y_xmax < ymax)
            lines_points.push_back(new ep_point(xmax, y_xmax));
        if (x_ymax > xmin && x_ymax < xmax)
            lines_points.push_back(new ep_point(x_ymax, ymax));
        if (y_xmin > ymin && y_xmin < ymax)
            lines_points.push_back(new ep_point(xmin, y_xmin));
    }
}

void epycycloide::to_begining(bool clear_history)
{
    for (ep_point *point : epycycloide_points)
        delete point;
    epycycloide_points.clear();
    epycycloide_points.push_back(new ep_point(0, 0));

    for (ep_point *point : rect_points)
        delete point;
    rect_points.clear();

    for (ep_point *point : lines_points)
        delete point;
    lines_points.clear();

    get_epycycloide_points();
    get_rect_points();
    get_line_points();
    move_to_center(false);

    if (clear_history)
    {
        for (move_state *state : history)
            delete state;
        history.clear();
    }

    draw();
}

void epycycloide::find_center(double &xc, double &yc)
{
    xc = epycycloide_points[0]->x;
    yc = epycycloide_points[0]->y;
}

void epycycloide::move_to_center(bool remember)
{
    double xc, yc;
    find_center(xc, yc);

    double dx = field.width() / 2 - xc;
    double dy = field.height() / 2 - yc;

    move(dx, dy, remember);
}

void epycycloide::draw()
{
    field.clear();

    //draw rectangle
    size_t size = rect_points.size();
    for (size_t i = 0; i < size - 1; i++)
        field.draw_line(rect_points[i]->x, rect_points[i]->y,
                        rect_points[i + 1]->x, rect_points[i + 1]->y, QColor(0, 0, 0), 6);
    field.draw_line(rect_points[0]->x, rect_points[0]->y,
                    rect_points[size - 1]->x, rect_points[size - 1]->y, QColor(0, 0, 0), 6);

    //draw lines
    size = lines_points.size();
    for (size_t i = 0; i < size - 1; i += 2)
        field.draw_line(lines_points[i]->x, lines_points[i]->y,
                        lines_points[i + 1]->x, lines_points[i + 1]->y, QColor(0, 0, 0), 6);

    // draw epycycloide
    int points_len = epycycloide_points.size();
    QPointF *points = new QPointF[points_len - 1];
    for (int i = 1; i < points_len; i++)
        points[i - 1] = QPointF(epycycloide_points[i]->x, epycycloide_points[i]->y);
    field.draw_polygon(points, points_len - 1, QColor(0, 0, 0), QColor(255, 255, 255), 6);
}

void epycycloide::back()
{
    move_state *state = history[history.size() - 1];
    history.pop_back();

    if (fabs(state->kx) < eps || fabs(state->ky) < eps)
    {
        to_begining(false);
        for (move_state *state : history)
        {
            if (fabs(state->dx) > eps || fabs(state->dy) > eps)
                move(state->dx, state->dy, false);

            if (fabs(state->kx - 1) > eps || fabs(state->ky - 1) > eps)
                scale(state->xm, state->ym, state->kx, state->ky, false);

            if (fabs(state->angle) > eps)
                rotate(state->xm, state->ym, state->angle, false);
        }

    }
    else
    {

    if (fabs(state->dx) > eps || fabs(state->dy) > eps)
        move(-state->dx, -state->dy, false);

    if (fabs(state->kx - 1) > eps || fabs(state->ky - 1) > eps)
        scale(state->xm, state->ym, 1 / state->kx, 1 / state->ky, false);

    if (fabs(state->angle) > eps)
        rotate(state->xm, state->ym, -state->angle, false);
    }


    draw();

    delete state;
}

int epycycloide::is_empty_history()
{
    return !history.size();
}
