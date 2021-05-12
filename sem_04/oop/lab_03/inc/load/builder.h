#ifndef BUILDER_H
#define BUILDER_H

#include <memory>
#include <vector>

#include "model.h"
#include "point.h"
#include "edge.h"

class base_builder
{
public:
    base_builder() = default;
    virtual ~base_builder() = default;

    virtual bool is_build() = 0;
    virtual void reset() = 0;
    virtual void build_center(const point &_point) = 0;
    virtual void build_points(const std::vector<point> &points) = 0;
    virtual void build_edges(const std::vector<edge> &edge) = 0;

    virtual std::shared_ptr<model> get() = 0;
};

class model_builder : public base_builder
{
public:
    model_builder();
    ~model_builder() = default;

    virtual bool is_build() override;
    virtual void reset() override;
    virtual void build_center(const point &_point) override;
    virtual void build_points(const std::vector<point> &points) override;
    virtual void build_edges(const std::vector<edge> &edges) override;

    virtual std::shared_ptr<model> get() override;

private:
    virtual void build_point(const point &_point);
    virtual void build_edge(const edge &_edge);

    std::shared_ptr<model> _model;
};

#endif // BUILDER_H
