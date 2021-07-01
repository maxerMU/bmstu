#ifndef SOLUTION_H
#define SOLUTION_H

#include <map>
#include "loaders.h"

class solution
{
public:
    solution() = default;
    ~solution() = default;

    bool registration(size_t index, const std::shared_ptr<loader_creator> &lc);
    std::shared_ptr<loader_creator> get_creator(size_t index);

private:
    using callback_map = std::map<size_t, std::shared_ptr<loader_creator>>;
    callback_map callback;

};

#endif // SOLUTION_H
