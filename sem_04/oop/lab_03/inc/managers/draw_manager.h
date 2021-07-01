#ifndef DRAW_MANAGER_H
#define DRAW_MANAGER_H

#include <memory>

#include "base_manager.h"
#include "base_drawer.h"
#include "visitor.h"

class draw_manager : public visitor, public base_manager
{
public:
    draw_manager() = default;
    ~draw_manager() = default;

    virtual void visit(const model &_model) override;
    virtual void visit(const camera &_camera) override;
    virtual void visit(const composite &_composite) override;
    virtual void visit(const scene &_scene) override;

    void set_cam(const std::shared_ptr<camera> &_camera);
    void set_drawer(const std::shared_ptr<base_drawer> &_drawer);
private:
    void proect_point(point &_point);

    std::shared_ptr<camera> cur_cam;
    std::shared_ptr<base_drawer> _drawer;
};

class draw_manager_creator
{
public:
    std::shared_ptr<draw_manager> get_manager();

private:
    void create_manager();

    std::shared_ptr<draw_manager> _manager;
};


#endif // DRAW_MANAGER_H
