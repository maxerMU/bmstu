#ifndef VISITOR_H
#define VISITOR_H

class model;
class camera;
class composite;
class scene;

class visitor
{
public:
    visitor() = default;
    virtual ~visitor() = default;

    virtual void visit(const model &_model) = 0;
    virtual void visit(const camera &_camera) = 0;
    virtual void visit(const composite &_composite) = 0;
    virtual void visit(const scene &_scene) = 0;
};

#endif // VISITOR_H
