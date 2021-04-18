#ifndef LIST_NODE_H
#define LIST_NODE_H

#include <memory>

template <typename T>
class list_node
{
public:
    explicit list_node(const T &data);
    list_node(const T &data, const std::shared_ptr<list_node<T>> &next);
    explicit list_node(const std::shared_ptr<list_node<T>> &node);

    ~list_node() = default;

    void set_data(const T &data);
    void set_next(const std::shared_ptr<list_node<T>> &node);

    T &get_data();
    std::shared_ptr<list_node<T>> get_next() const;
    const T &get_cdata() const;

    bool operator ==(const list_node<T> &node) const;
    bool operator ==(const std::shared_ptr<list_node<T>> &node) const;
    bool operator !=(const list_node<T> &node) const;
    bool operator !=(const std::shared_ptr<list_node<T>> &node) const;

private:
    T data;
    std::shared_ptr<list_node<T>> next;

};

#include "list_node.hpp"

#endif // LIST_NODE_H
