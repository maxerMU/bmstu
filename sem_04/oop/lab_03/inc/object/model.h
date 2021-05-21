#ifndef MODEL_H
#define MODEL_H

#include "object.h"
#include "units.h"

#include "draw_manager.h"

class model : public visible_object
{
    friend void draw_manager::visit(const model &_model);
public:
    model();
    explicit model(const std::shared_ptr<units> &_units);

    virtual void accept(const std::shared_ptr<visitor> &_visitor) const override;
    virtual void transform(const point &move, const point &scale, const point &rotate) override;

private:
    std::shared_ptr<units> get_units() const;
    std::shared_ptr<units> _units;
};

#endif // MODEL_H
