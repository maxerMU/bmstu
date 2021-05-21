#include "load_exceptions.h"
#include "registration.h"
#include "file_loader.h"

void registration_maker::make_registration(solution &_solution)
{

    bool is_registered = _solution.registration(0,
                          std::shared_ptr<loader_creator>(new con_loader_creator<model_file_loader>()));
    if (!is_registered)
        throw config_exception();

    is_registered = _solution.registration(1,
                          std::shared_ptr<loader_creator>(new con_loader_creator<camera_file_loader>()));
    if (!is_registered)
        throw config_exception();

    is_registered = _solution.registration(2,
                          std::shared_ptr<loader_creator>(new con_loader_creator<scene_file_loader>()));
    if (!is_registered)
        throw config_exception();
}
