#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "base_controller.h"
#include "scene_manager.h"
#include "draw_manager.h"
#include "reform_manager.h"
#include "base_loader.h"

class controller : public base_controller
{
public:
    controller();
    ~controller() = default;

    virtual void load_model(const std::string &name) override;
    virtual void add_model(const std::shared_ptr<model> &_model) override;
    virtual void remove_model(size_t index) override;

    virtual void add_camera(const point &cam_pos) override;
    virtual void set_camera(size_t index) override;
    virtual void remove_camera(size_t index) override;

    virtual void draw_scene(const std::shared_ptr<base_drawer> &drawer) override;

    virtual void transform_model(size_t index, const point &move, const point &scale, const point &rotate) override;
    virtual void transform_camera(size_t index, const point &move, const point &rotate) override;

private:
    scene_manager _scene_manager;
    reform_manager _reform_manager;
    std::shared_ptr<draw_manager> _draw_manager;
    std::shared_ptr<base_loader> loader;
};

#endif // CONTROLLER_H
