#include "directors.h"
#include "file_loader.h"
#include "config_manager.h"
#include "model_load_solution.h"
#include "camera_load_solution.h"
#include "scene_load_solution.h"

model_director::model_director()
{
    std::shared_ptr<loader_creator> cr = model_load_solution().get_creator();
    _loader = std::shared_ptr<source_loader>(cr->create_loader());
}

std::shared_ptr<object> model_director::load(const std::string &str)
{
    _loader->open(str);
    std::shared_ptr<object> _model = _loader->load();
    _loader->close();

    return _model;
}

camera_director::camera_director()
{
    std::shared_ptr<loader_creator> cr = camera_load_solution().get_creator();
    _loader = std::shared_ptr<source_loader>(cr->create_loader());
}

std::shared_ptr<object> camera_director::load(const std::string &str)
{
    _loader->open(str);
    std::shared_ptr<object> _camera = _loader->load();
    _loader->close();

    return _camera;
}

scene_director::scene_director()
{
    std::shared_ptr<loader_creator> cr = scene_load_solution().get_creator();
    _loader = std::shared_ptr<source_loader>(cr->create_loader());
}

std::shared_ptr<object> scene_director::load(const std::string &str)
{
    _loader->open(str);
    std::shared_ptr<object> _scene = _loader->load();
    _loader->close();

    return _scene;
}
