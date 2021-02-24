#ifndef EPYCYCLOIDE_H
#define EPYCYCLOIDE_H

#include <vector>
#include "canvas.h"

struct ep_point
{
    ep_point(double x, double y)
        :x(x), y(y)
    {}

    double x;
    double y;
};

struct move_state
{
    move_state(double dx, double dy, double xm, double ym, double kx, double ky, double angle)
        : dx(dx), dy(dy), xm(xm), ym(ym), kx(kx), ky(ky), angle(angle)
    {}

    double dx;
    double dy;
    double xm;
    double ym;
    double kx;
    double ky;
    double angle;
};

struct epycycloide
{
    epycycloide(double angle_min, double angle_max, double angle_step, double a, double b, canvas &field);
    ~epycycloide();
    void find_center(double &xc, double &yc);
    void move_to_center(bool remember);
    void move(double dx, double dy, bool remember);
    void scale(double xm, double ym, double kx, double ky, bool remember);
    void rotate(double xm, double ym, double angle, bool remember);
    void to_begining(bool clear_history);
    void back();
    int is_empty_history();

private:
    void get_points();
    void draw();

    double angle_min;
    double angle_max;
    double angle_step;
    double a;
    double b;
    canvas &field;
    std::vector<ep_point *> points;
    std::vector<move_state *> history;
};

#endif // EPYCYCLOIDE_H
