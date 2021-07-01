#ifndef CAMERA_BUILDER_H
#define CAMERA_BUILDER_H

#include <memory>
#include <vector>

#include "camera.h"

class camera_builder
{
public:
    camera_builder();
    ~camera_builder() = default;

    bool is_build() const;
    void reset();
    void build_pos(double x, double y, double z);
    void build_angles(double ox, double oy, double oz);

    std::shared_ptr<camera> get();

private:
    std::shared_ptr<camera> _camera;
};

#endif // CAMERA_BUILDER_H
