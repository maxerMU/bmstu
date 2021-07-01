#ifndef DIRECTORS_H
#define DIRECTORS_H

#include "load_director.h"

class model_director : public load_director
{
public:
    model_director();
    ~model_director() = default;

    virtual std::shared_ptr<object> load(const std::string &str) override;
};

class camera_director : public load_director
{
public:
    camera_director();
    ~camera_director() = default;

    virtual std::shared_ptr<object> load(const std::string &str) override;
};

class scene_director : public load_director
{
public:
    scene_director();
    ~scene_director() = default;

    virtual std::shared_ptr<object> load(const std::string &str) override;
};

#endif // DIRECTORS_H
