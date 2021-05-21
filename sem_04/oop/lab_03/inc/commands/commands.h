#ifndef COMMANDS_H
#define COMMANDS_H

#include <string>
#include <memory>
#include "base_drawer.h"
#include "point.h"

class base_command
{
public:
    base_command() = default;
    virtual ~base_command() = default;

    virtual void execute() const = 0;
};

class load_command : public base_command
{
public:
    explicit load_command(const std::string &file_name);

    virtual void execute() const override;

private:
    std::string file_name;
};

class load_camera_command : public base_command
{
public:
    explicit load_camera_command(const std::string &file_name) : file_name(file_name) {}

    virtual void execute() const override;

private:
    std::string file_name;
};

class remove_model_command : public base_command
{
public:
    explicit remove_model_command(size_t index) : index(index) {}

    virtual void execute() const override;

private:
    size_t index;
};

class add_camera_command : public base_command
{
public:
    explicit add_camera_command(const point &pos) : pos(pos) {}

    virtual void execute() const override;

private:
    point pos;
};

class set_camera_command : public base_command
{
public:
    explicit set_camera_command(size_t index) : index(index) {}

    virtual void execute() const override;

private:
    size_t index;
};

class remove_camera_command : public base_command
{
public:
    explicit remove_camera_command(size_t index) : index(index) {}

    virtual void execute() const override;

private:
    size_t index;
};

class draw_scene_command : public base_command
{
public:
    explicit draw_scene_command(const std::shared_ptr<base_drawer> &_drawer) : _drawer(_drawer) {}

    virtual void execute() const override;

private:
    std::shared_ptr<base_drawer> _drawer;
};

class move_model_command : public base_command
{
public:
    move_model_command(size_t index, const point &move) : index(index), move(move) {}

    virtual void execute() const override;

private:
    size_t index;
    point move;
};

class scale_model_command : public base_command
{
public:
    scale_model_command(size_t index, const point &scale) : index(index), scale(scale) {}

    virtual void execute() const override;

private:
    size_t index;
    point scale;
};

class rotate_model_command : public base_command
{
public:
    rotate_model_command(size_t index, const point &rotate) : index(index), rotate(rotate) {}

    virtual void execute() const override;

private:
    size_t index;
    point rotate;
};

class move_camera_command : public base_command
{
public:
    move_camera_command(size_t index, const point &move) : index(index), move(move) {}

    virtual void execute() const override;

private:
    size_t index;
    point move;
};

class rotate_camera_command : public base_command
{
public:
    rotate_camera_command(size_t index, const point &rotate) : index(index), rotate(rotate) {}

    virtual void execute() const override;

private:
    size_t index;
    point rotate;
};

#endif // COMMANDS_H
