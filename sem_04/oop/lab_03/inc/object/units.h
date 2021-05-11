#ifndef UNITS_H
#define UNITS_H

#include <vector>

#include "point.h"
#include "edge.h"

class units
{
public:
    units();
    void add_point(const point &_point);
    void add_edge(const edge &_edge);

    std::vector<point> get_points();
    std::vector<edge> get_edges();

    void set_center(const point &pos);
    point get_center() const;

    void move(const point &move);
    void scale(const point &scale);
    void rotate(const point &rotate);

    void transform(const point &move, const point &scale, const point &rotate);

private:
    std::vector<point> points;
    std::vector<edge> edges;
    point center;
};

#endif // UNITS_H
