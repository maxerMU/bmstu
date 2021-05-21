#ifndef FILE_LOADER_H
#define FILE_LOADER_H

#include <fstream>
#include <string>

#include "source_loader.h"
#include "model_builder.h"
#include "camera_builder.h"
#include "scene_builder.h"
#include "object.h"

class model_file_loader : public base_model_loader
{
public:
    model_file_loader();
    explicit model_file_loader(std::shared_ptr<std::ifstream> &file);
    virtual void open(const std::string &name) override;
    virtual std::shared_ptr<object> load() override;
    virtual void close() override;

private:
    std::shared_ptr<model_builder> _builder;
    std::shared_ptr<std::ifstream> file;
};

class camera_file_loader : public base_camera_loader
{
public:
    camera_file_loader();
    explicit camera_file_loader(std::shared_ptr<std::ifstream> &file);
    virtual void open(const std::string &name) override;
    virtual std::shared_ptr<object> load() override;
    virtual void close() override;

private:
    std::shared_ptr<camera_builder> _builder;
    std::shared_ptr<std::ifstream> file;
};

class scene_file_loader : public base_camera_loader
{
public:
    scene_file_loader();
    explicit scene_file_loader(std::shared_ptr<std::ifstream> &file);
    virtual void open(const std::string &name) override;
    virtual std::shared_ptr<object> load() override;
    virtual void close() override;

private:
    std::shared_ptr<scene_builder> _builder;
    std::shared_ptr<std::ifstream> file;

    void load_models();
    void load_cameras();
};

#endif // FILE_LOADER_H
