#ifndef MODEL_H
#define MODEL_H

#include "object.h"
#include "units.h"

class model : public visible_object
{
public:
    model();
    explicit model(const std::shared_ptr<units> &_units);

    void add_point(const point &_point);
    void add_edge(const edge &_edge);

    void set_center(const point &pos);

    std::shared_ptr<units> get_units() const;

    virtual void accept(const std::shared_ptr<visitor> &_visitor) const override;
    virtual void transform(const point &move, const point &scale, const point &rotate) override;

private:
    std::shared_ptr<units> _units;
};

#endif // MODEL_H
