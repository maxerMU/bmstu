#ifndef POINT_CPP
#define POINT_CPP

#include <stdio.h>

#define POINT_SUCCESS 0
#define POINT_READ_ER 1

typedef struct
{
    double x;
    double y;
    double z;
}point_t;

typedef struct
{
    long x;
    long y;
}display_point_t;

int read_point(FILE *src, point_t &point);
void write_point(FILE *dst, const point_t &point);
void move_point(const double dx, const double dy, const double dz, point_t &point);
void scale_point(point_t c, double kx, double ky, double kz, point_t &point);
void rotate_point(point_t c, double xy_ang, double xz_ang, double yz_ang, point_t &point);
void to_display_point(display_point_t &disp_point, const point_t &point);

#endif // POINT_CPP
