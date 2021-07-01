#ifndef QT_DRAWER_H
#define QT_DRAWER_H

#include <QGraphicsScene>
#include <memory>

#include "base_drawer.h"

class qt_drawer : public base_drawer
{
public:
    qt_drawer() : _scene(nullptr) {}
    qt_drawer(const std::shared_ptr<QGraphicsScene> &_scene) : _scene(_scene) {}
    ~qt_drawer() = default;

    virtual void draw_line(const point &p1, const point &p2) override;
    virtual void clear_scene() override;

private:
    std::shared_ptr<QGraphicsScene> _scene;
};

#endif // QT_DRAWER_H
