#ifndef SCENE_BUILDER_H
#define SCENE_BUILDER_H

#include <memory>
#include <vector>

#include "model.h"
#include "camera.h"
#include "scene.h"
#include "object.h"

class scene_builder
{
public:
    scene_builder();
    ~scene_builder() = default;

    bool is_build() const;
    void reset();
    void build_model(const std::shared_ptr<object> &_model);
    void build_camera(const std::shared_ptr<object> &_camera);

    std::shared_ptr<scene> get();

private:
    std::shared_ptr<scene> _scene;
};

#endif // SCENE_BUILDER_H
