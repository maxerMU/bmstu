#ifndef FILE_LOADER_H
#define FILE_LOADER_H

#include "base_loader.h"
#include "builder.h"

class file_loader : public base_loader
{
public:
    file_loader();
    virtual std::shared_ptr<model> load_model(const std::string &name) override;

private:
    std::shared_ptr<base_builder> _builder;
};

#endif // FILE_LOADER_H
