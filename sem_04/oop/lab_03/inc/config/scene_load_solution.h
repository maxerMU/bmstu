#ifndef SCENE_LOAD_SOLUTION_H
#define SCENE_LOAD_SOLUTION_H

#define SCENE_CFG_PATH "./data/scene_load.cfg"

#include "config_manager.h"

class scene_load_solution
{
public:
    scene_load_solution() = default;

    std::shared_ptr<loader_creator> get_creator();
};

#endif // SCENE_LOAD_SOLUTION_H
