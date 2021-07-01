#include "fstream"
#include "scene_load_solution.h"
#include "load_exceptions.h"

std::shared_ptr<loader_creator> scene_load_solution::get_creator()
{
    std::ifstream file(SCENE_CFG_PATH);

    if (!file)
        throw file_open_exception();

    size_t id;
    if (!(file >> id))
        throw file_format_exception();

    return config_manager_creator().get_manager()->get_creator(id);
}
