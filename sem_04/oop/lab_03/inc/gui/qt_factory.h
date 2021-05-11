#ifndef QT_FACTORY_H
#define QT_FACTORY_H

#include <QGraphicsScene>
#include "abstract_factory.h"
#include "qt_drawer.h"
#include "base_drawer.h"

class qt_factory : public abstract_factory
{
public:
    explicit qt_factory(const std::shared_ptr<QGraphicsScene> &_scene) : _scene(_scene) {}
    ~qt_factory() = default;

    virtual std::shared_ptr<base_drawer> create_drawer() override;

private:
    std::shared_ptr<QGraphicsScene> _scene;
};

#endif // QT_FACTORY_H
