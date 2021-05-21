#ifndef BASE_LOADER_H
#define BASE_LOADER_H

#include <string>
#include <memory>

class object;

class source_loader
{
public:
    source_loader() = default;
    virtual ~source_loader() = default;

    virtual void open(const std::string &name) = 0;
    virtual std::shared_ptr<object> load() = 0;
    virtual void close() = 0;
};

class base_model_loader : public source_loader
{
public:
    base_model_loader() = default;
    virtual ~base_model_loader() = default;

    virtual void open(const std::string &name) = 0;
    virtual std::shared_ptr<object> load() = 0;
    virtual void close() = 0;
};

class base_scene_loader : public source_loader
{
public:
    base_scene_loader() = default;
    virtual ~base_scene_loader() = default;

    virtual void open(const std::string &name) = 0;
    virtual std::shared_ptr<object> load() = 0;
    virtual void close() = 0;
};

class base_camera_loader : public source_loader
{
public:
    base_camera_loader() = default;
    virtual ~base_camera_loader() = default;

    virtual void open(const std::string &name) = 0;
    virtual std::shared_ptr<object> load() = 0;
    virtual void close() = 0;
};

#endif // BASE_LOADER_H
