#ifndef BASE_DRAWER_H
#define BASE_DRAWER_H

#include "point.h"

class base_drawer
{
public:
    base_drawer() = default;
    virtual ~base_drawer() = default;

    virtual void draw_line(const point &p1, const point &p2) = 0;
    virtual void clear_scene() = 0;
};

#endif // BASE_DRAWER_H
