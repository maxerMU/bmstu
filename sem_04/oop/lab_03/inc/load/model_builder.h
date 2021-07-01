#ifndef BUILDER_H
#define BUILDER_H

#include <memory>
#include <vector>

#include "model.h"
#include "point.h"
#include "edge.h"
#include "units.h"

class model_builder
{
public:
    model_builder();
    ~model_builder() = default;

    bool is_build();
    void reset();
    void build_center(const point &_point);
    void build_points(const std::vector<point> &points);
    void build_edges(const std::vector<edge> &edges);

    std::shared_ptr<model> get();

private:
    void build_point(const point &_point);
    void build_edge(const edge &_edge);

    std::shared_ptr<units> _units;
};

#endif // BUILDER_H
