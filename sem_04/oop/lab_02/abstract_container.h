#ifndef ABSTRACT_CONTAINER_H
#define ABSTRACT_CONTAINER_H

class abstract_container
{
public:
    virtual ~abstract_container() = default;
    virtual bool is_empty() const = 0;
    virtual void clear() = 0;
};

#endif // ABSTRACT_CONTAINER_H
