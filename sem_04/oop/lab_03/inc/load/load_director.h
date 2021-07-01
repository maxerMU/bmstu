#ifndef LOAD_DIRECTOR_H
#define LOAD_DIRECTOR_H

#include <string>
#include <memory>

#include "source_loader.h"
#include "object.h"

class load_director
{
public:
    load_director() = default;
    virtual ~load_director() = default;

    virtual std::shared_ptr<object> load(const std::string &str) = 0;

protected:
    std::shared_ptr<source_loader> _loader;
};

#endif // LOAD_DIRECTOR_H
