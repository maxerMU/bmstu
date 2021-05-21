#include "load_exceptions.h"
#include "solution.h"

bool solution::registration(size_t index, const std::shared_ptr<loader_creator> &lc)
{
    return callback.insert(callback_map::value_type(index, lc)).second;
}

std::shared_ptr<loader_creator> solution::get_creator(size_t index)
{
    callback_map::const_iterator it = callback.find(index);
    if (it == callback.end())
        throw config_exception();

    return it->second;
}
