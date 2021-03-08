#ifndef CONVERT_H
#define CONVERT_H

typedef struct
{
    double dx;
    double dy;
    double dz;
}move_t;

typedef struct
{
    double xc;
    double yc;
    double zc;
    double kx;
    double ky;
    double kz;
}scale_t;

typedef struct
{
    double xc;
    double yc;
    double zc;
    double xy_angle;
    double xz_angle;
    double yz_angle;
}rotate_t;

typedef struct
{
    long x;
    long y;
}display_point_t;

typedef struct
{
    display_point_t p1;
    display_point_t p2;
}display_edge_t;

#endif // CONVERT_H
