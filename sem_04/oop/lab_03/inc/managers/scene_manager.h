#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include "base_manager.h"
#include "scene.h"
#include "camera.h"

class scene_manager : public base_manager
{
public:
    scene_manager();

    std::shared_ptr<scene> get_scene() const;
    void set_scene(const std::shared_ptr<scene> &_scene);

    std::shared_ptr<camera> get_cur_camera() const;
    void set_cur_camera(size_t index);

    bool is_camera_set() const;

private:
    std::shared_ptr<scene> _scene;
    std::shared_ptr<camera> current_cam;
};

class scene_manager_creator
{
public:
    std::shared_ptr<scene_manager> get_manager();

private:
    void create_manager();

    std::shared_ptr<scene_manager> _manager;
};

#endif // SCENE_MANAGER_H
