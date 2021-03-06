#ifndef LIST_ITERATOR_H
#define LIST_ITERATOR_H

#include <iterator>
#include <memory>

#include "list_node.h"

template <typename T>
class list;

template <typename T>
class list_iterator : std::iterator<std::forward_iterator_tag, list_node<T>>
{
    friend class list<T>;
public:
    list_iterator();
    explicit list_iterator(const std::shared_ptr<list_node<T>> &pnode);
    list_iterator(const list_iterator<T> &iter);

    ~list_iterator() = default;

    virtual void next();
    virtual bool is_invalid() const;

    operator bool();

    T &operator *();
    T *operator ->();
    const T &operator *() const;
    const T *operator ->() const;

    const T &get_data() const;
    const T &get_next_data() const;

    list_iterator<T> &operator ++(); // ++obj
    list_iterator<T> operator ++(int); // obj++

    list_iterator<T> &operator +=(long step);
    list_iterator<T> operator +(long step) const;

    list_iterator<T> &operator =(const list_iterator<T> &iter);

    bool operator !=(const list_iterator<T> &iter) const;
    bool operator ==(const list_iterator<T> &iter) const;

private:
    std::weak_ptr<list_node<T>> cur;
};

#include "list_iterator.hpp"

#endif // LIST_ITERATOR_H
