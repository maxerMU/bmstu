#ifndef COMPOSITE_H
#define COMPOSITE_H

#include <vector>

#include "object.h"

class composite : public object
{
public:
    composite();

    virtual void accept(const std::shared_ptr<visitor> &_visitor) const override;

    virtual bool add(const std::shared_ptr<object> _object) override;
    virtual bool remove(size_t index) override;

    virtual std::vector<std::shared_ptr<object>>::iterator begin() override;
    virtual std::vector<std::shared_ptr<object>>::iterator end() override;
    virtual std::vector<std::shared_ptr<object>>::const_iterator cbegin() const override;
    virtual std::vector<std::shared_ptr<object>>::const_iterator cend() const override;

    std::vector<std::shared_ptr<object>> get_objects() const;

    virtual bool is_composite() const override {return true;}

    virtual void transform(const point &move, const point &scale, const point &rotate) override;

private:
    std::vector<std::shared_ptr<object>> objects;
};

#endif // COMPOSITE_H
