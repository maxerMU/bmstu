#ifndef BASE_CONTROLLER_H
#define BASE_CONTROLLER_H

#include <stdlib.h>
#include <string>
#include <memory>

#include "object.h"
#include "point.h"
#include "base_drawer.h"

class base_controller
{
public:
    base_controller() = default;
    virtual ~base_controller() = default;

    virtual void load_model(const std::string &name) = 0;
    virtual void add_model(const std::shared_ptr<model> &_model) = 0;
    virtual void remove_model(size_t index) = 0;

    virtual void add_camera(const point &cam_pos) = 0;
    virtual void set_camera(size_t index) = 0;
    virtual void remove_camera(size_t index) = 0;

    virtual void draw_scene(const std::shared_ptr<base_drawer> &drawer) = 0;

    virtual void transform_model(size_t index, const point &move, const point &scale, const point &rotate) = 0;
    virtual void transform_camera(size_t index, const point &move, const point &rotate) = 0;
};

#endif // BASE_CONTROLLER_H
