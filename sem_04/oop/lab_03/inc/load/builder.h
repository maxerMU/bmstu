#ifndef BUILDER_H
#define BUILDER_H

#include <memory>

#include "model.h"

class base_builder
{
public:
    base_builder() = default;
    virtual ~base_builder() = default;

    virtual bool is_build() = 0;
    virtual void reset() = 0;
    virtual void build_center(double x, double y, double z) = 0;
    virtual void build_point(double x, double y, double z) = 0;
    virtual void build_edge(size_t pt_index1, size_t pt_index2) = 0;

    virtual std::shared_ptr<model> get() = 0;
};

class model_builder : public base_builder
{
public:
    model_builder();
    ~model_builder() = default;

    virtual bool is_build() override;
    virtual void reset() override;
    virtual void build_center(double x, double y, double z) override;
    virtual void build_point(double x, double y, double z) override;
    virtual void build_edge(size_t pt_index1, size_t pt_index2) override;

    virtual std::shared_ptr<model> get() override;

private:
    std::shared_ptr<model> _model;
};

#endif // BUILDER_H
