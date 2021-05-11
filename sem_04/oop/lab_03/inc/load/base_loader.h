#ifndef BASE_LOADER_H
#define BASE_LOADER_H

#include <string>
#include <memory>

class model;

class base_loader
{
public:
    base_loader() = default;
    virtual ~base_loader() = default;

    virtual std::shared_ptr<model> load_model(const std::string &name) = 0;
};

#endif // BASE_LOADER_H
