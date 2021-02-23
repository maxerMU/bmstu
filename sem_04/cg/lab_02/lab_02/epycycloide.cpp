#include <iostream>
#include <QColor>
#include <math.h>
#include "epycycloide.h"

double eps = 1e-6;

epycycloide::epycycloide(double angle_min, double angle_max, double angle_step, double a, double b, canvas &field)
    :angle_min(angle_min), angle_max(angle_max), angle_step(angle_step), a(a), b(b), field(field)
{
    points.push_back(new ep_point(0, 0));
    get_points();
    move_to_center(false);

    draw();
}

epycycloide::~epycycloide()
{
    for (ep_point *point : points)
        delete point;
    for (move_state *state : history)
        delete state;
}

void epycycloide::move(double dx, double dy, bool remember)
{
    for (ep_point *point : points)
    {
        point->x += dx;
        point->y += dy;
    }

    if (remember)
        history.push_back(new move_state(dx, dy, 0, 0, 1, 1, 0));
}

void epycycloide::scale(double xm, double ym, double kx, double ky, bool remember)
{
    for (ep_point *point : points)
    {
        point->x = point->x * kx + (1 - kx) * xm;
        point->y = point->y * ky + (1 - ky) * ym;
    }

    if (remember)
        history.push_back(new move_state(0, 0, xm, ym, kx, ky, 0));
}

void epycycloide::rotate(double xm, double ym, double angle, bool remember)
{
    double rad_angle = (angle * M_PI) / 180;
    for (ep_point *point : points)
    {
        double x = point->x;
        double y = point->y;

        point->x = xm + (x - xm) * cos(rad_angle) + (y - ym) * sin(rad_angle);
        point->y = ym - (x - xm) * sin(rad_angle) + (y - ym) * cos(rad_angle);
    }

    if (remember)
        history.push_back(new move_state(0, 0, xm, ym, 1, 1, angle));
}

void epycycloide::get_points()
{
    double x = (a + b) * cos(angle_min) - a * cos((a + b) * angle_min / a);
    double y = - (a + b) * sin(angle_min) + a * sin((a + b) * angle_min / a);
    points.push_back(new ep_point(x, y));

    for (double t = angle_min + angle_step; t < angle_max; t += angle_step)
    {
        x = (a + b) * cos(t) - a * cos((a + b) * t / a);
        y = - (a + b) * sin(t) + a * sin((a + b) * t / a);
        if (fabs(x - points[points.size() - 1]->x) > 1 || fabs(y - points[points.size() - 1]->y) > 1)
            points.push_back(new ep_point(x , y));
    }
}

void epycycloide::find_center(double &xc, double &yc)
{
    xc = points[0]->x;
    yc = points[0]->y;
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
    size_t size = points.size();
    for (size_t i = 1; i < size - 1; i++)
        field.draw_line(points[i]->x, points[i]->y, points[i + 1]->x, points[i + 1]->y, QColor(0, 0, 0), 6);
    field.draw_line(points[1]->x, points[1]->y, points[size - 1]->x, points[size - 1]->y, QColor(0, 0, 0), 6);
}

void epycycloide::back()
{
    move_state *state = history[history.size() - 1];
    history.pop_back();

    if (fabs(state->kx) < eps || fabs(state->ky) < eps)
    {
        for (ep_point *point : points)
            delete point;
        points.clear();
        points.push_back(new ep_point(0, 0));
        get_points();
        move_to_center(false);
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
