#include "scene_manager.h"

scene_manager::scene_manager()
{
    _scene = std::shared_ptr<scene>(new scene());
    current_cam = nullptr;
}

std::shared_ptr<scene> scene_manager::get_scene() const
{
    return _scene;
}

void scene_manager::set_scene(const std::shared_ptr<scene> &_scene)
{
    this->_scene = _scene;
}

std::shared_ptr<camera> scene_manager::get_cur_camera() const
{
    return current_cam;
}

void scene_manager::set_cur_camera(size_t index)
{
    std::shared_ptr<object> obj_ptr = _scene->get_camera(index);
    current_cam = std::shared_ptr<camera>(dynamic_cast<camera *>(obj_ptr.get()));
}

bool scene_manager::is_camera_set() const
{
    return current_cam != nullptr;
}
