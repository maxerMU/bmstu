#ifndef CONST_LIST_ITERATOR_H
#define CONST_LIST_ITERATOR_H

#include <iterator>
#include <memory>

#include "list_node.h"

template <typename T>
class con_list_iterator : std::iterator<std::forward_iterator_tag, list_node<T>>
{
public:
    con_list_iterator();
    explicit con_list_iterator(const std::shared_ptr<list_node<T>> &pnode);
    con_list_iterator(const con_list_iterator<T> &iter);

    ~con_list_iterator() = default;

    virtual void next();
    virtual bool is_invalid() const;

    const T &operator *() const;
    const T &operator ->() const;

    con_list_iterator<T> &operator ++(); // ++obj
    con_list_iterator<T> operator ++(int); // obj++

    con_list_iterator<T> &operator =(const con_list_iterator<T> &iter);

    bool operator !=(const con_list_iterator<T> &iter);
    bool operator ==(const con_list_iterator<T> &iter);

private:
    std::weak_ptr<list_node<T>> cur;
};

#include "const_list_iterator.hpp"

#endif // CONST_LIST_ITERATOR_H
