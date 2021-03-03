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

point_t *create_point();
void delete_point(point_t *point);
int read_point(FILE *src, point_t &point);
void write_point(FILE *dst, point_t point);

#endif // POINT_CPP
