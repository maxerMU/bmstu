#include "scene_manager.h"

std::shared_ptr<scene_manager> scene_manager_creator::get_manager()
{
    if (_manager == nullptr)
        create_manager();

    return _manager;
}

void scene_manager_creator::create_manager()
{
    static std::shared_ptr<scene_manager> _manager(new scene_manager());
    this->_manager = _manager;
}

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
    current_cam = std::dynamic_pointer_cast<camera>(obj_ptr);
}

bool scene_manager::is_camera_set() const
{
    return current_cam != nullptr;
}
