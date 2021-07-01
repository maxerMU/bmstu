#ifndef LOADERS_H
#define LOADERS_H

#include "source_loader.h"

class loader_creator
{
public:
    loader_creator() = default;
    virtual ~loader_creator() = default;
    virtual std::shared_ptr<source_loader> create_loader() = 0;
};

template <typename T>
class con_loader_creator : public loader_creator
{
public:
    con_loader_creator() = default;
    virtual ~con_loader_creator() = default;

    virtual std::shared_ptr<source_loader> create_loader() override;
};

template <typename T>
std::shared_ptr<source_loader> con_loader_creator<T>::create_loader()
{
    return std::shared_ptr<source_loader>(new T());
}

#endif // LOADERS_H
