#ifndef SCENE_H
#define SCENE_H

#include "object.h"
#include "composite.h"

class scene : public object
{
public:
    scene();

    virtual void accept(const std::shared_ptr<visitor> &_visitor) const override;

    void add_model(const std::shared_ptr<object> &_model);
    void remove_model(size_t index);

    void add_camera(const std::shared_ptr<object> &_camera);
    void remove_camera(size_t index);

    std::shared_ptr<object> get_model(size_t index) const;
    std::vector<std::shared_ptr<object>> get_models() const;
    std::shared_ptr<composite> get_models_composite() const;

    std::shared_ptr<object> get_camera(size_t index) const;
    std::vector<std::shared_ptr<object>> get_cameras() const;

    virtual void transform(const point &move, const point &scale, const point &rotate) override;

private:
    std::shared_ptr<composite> models;
    std::shared_ptr<composite> cameras;
};

#endif // SCENE_H
