#ifndef LIST_H
#define LIST_H

#include <chrono>
#include <memory>
#include <initializer_list>

#include "abstract_container.h"
#include "list_exceptions.h"
#include "list_node.h"
#include "list_iterator.h"
#include "const_list_iterator.h"

template <typename T>
class list : public abstract_container
{
public:
    list();
    list(const list<T> &l);
    list(const list<T> &&l);
    list(T * const arr, long size);
    explicit list(std::initializer_list<T> elems);
    list(list_iterator<T> begin, list_iterator<T> end);

    ~list() = default;

    virtual bool is_empty() const override;
    virtual void clear() override;

    T pop_back();
    T pop_front();

    void push_back(const T &data);
    void push_front(const T &data);

    void push_back(const list<T> &list);
    void push_front(const list<T> &list);

    list_iterator<T> insert(const list_iterator<T> &it, const T &data);
    list_iterator<T> insert(const list_iterator<T> &it, const list<T> &l);

    void remove(const list_iterator<T> &it);

    void reverse();

    list<T> &merge(const T &data);
    list<T> &merge(const list<T> &merge_list);

    list<T> operator +(const T &data) const;
    list<T> &operator +=(const T &data);
    list<T> operator +(const list<T> &l) const;
    list<T> &operator +=(const list<T> &l);

    list<T> operator =(const list<T> &l);
    list<T> operator =(const list<T> &&l);

    bool operator ==(const list<T> &l) const;

    list_iterator<T> begin();
    list_iterator<T> end();
    con_list_iterator<T> cbegin() const;
    con_list_iterator<T> cend() const;

    long get_size() const; // uses for tests

protected:
    std::shared_ptr<list_node<T>> &get_head() const;
    std::shared_ptr<list_node<T>> &get_tail() const;

private:
    std::shared_ptr<list_node<T>> head;
    std::shared_ptr<list_node<T>> tail;
    long size;
};

#include "list.hpp"

#endif // LIST_H
