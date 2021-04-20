#ifndef CONST_LIST_ITERATOR_HPP
#define CONST_LIST_ITERATOR_HPP

#include "list_exceptions.h"

template <typename T>
con_list_iterator<T>::operator bool()
{
    return is_invalid();
}

template <typename T>
std::shared_ptr<list_node<T>> con_list_iterator<T>::get_next() const
{
    return cur.lock()->get_next();
}

template <typename T>
const T &con_list_iterator<T>::get_data() const
{
    return cur.lock()->get_data();
}

template <typename T>
void con_list_iterator<T>::set_next(const std::shared_ptr<list_node<T> > &next)
{
    cur.lock()->set_next(next);
}

template <typename T>
void con_list_iterator<T>::set_data(const T &data)
{
    cur.lock()->set_data(data);
}

template <typename T>
con_list_iterator<T>::con_list_iterator()
    :cur(std::weak_ptr<list_node<T>>())
{
}

template <typename T>
con_list_iterator<T>::con_list_iterator(const std::shared_ptr<list_node<T>> &pnode)
    :cur(pnode)
{
}

template <typename T>
con_list_iterator<T>::con_list_iterator(const con_list_iterator<T> &iter)
    :cur(iter.cur.lock())
{
}

template <typename T>
void con_list_iterator<T>::next()
{
    if (!is_invalid())
    {
        cur = cur.lock()->get_next();
    }
}

template <typename T>
bool con_list_iterator<T>::is_invalid() const
{
    return cur.expired();
}

template <typename T>
const T &con_list_iterator<T>::operator *() const
{
    if (is_invalid())
    {
        auto timenow = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        throw list_iterator_exception(ctime(&timenow), __FILE__, typeid(con_list_iterator).name(), __FUNCTION__);
    }

    return cur.lock()->get_data();
}

template <typename T>
const T *con_list_iterator<T>::operator ->() const
{
    if (is_invalid())
    {
        auto timenow = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        throw list_iterator_exception(ctime(&timenow), __FILE__, typeid(con_list_iterator).name(), __FUNCTION__);
    }

    return cur.lock()->get_pdata();
}

template <typename T>
std::shared_ptr<list_node<T>> con_list_iterator<T>::get_spnode() const
{
    if (is_invalid())
    {
        auto timenow = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        throw list_iterator_exception(ctime(&timenow), __FILE__, typeid(con_list_iterator).name(), __FUNCTION__);
    }

    return cur.lock();
}

//template <typename T>
//const std::shared_ptr<list_node<T>> con_list_iterator<T>::get_cspnode() const
//{
//    return cur.lock();
//}

template <typename T>
con_list_iterator<T> &con_list_iterator<T>::operator ++()
{
    next();
    return *this;
}

template <typename T>
con_list_iterator<T> con_list_iterator<T>::operator ++(int)
{
    con_list_iterator<T> temp = *this;
    next();
    return temp;
}

template <typename T>
con_list_iterator<T> &con_list_iterator<T>::operator +=(long step)
{
    for (long i = 0; i < step; i++)
        next();

    return *this;
}

template <typename T>
con_list_iterator<T> con_list_iterator<T>::operator +(long step) const
{
    con_list_iterator it(*this);
    it += step;
    return it;
}

template <typename T>
con_list_iterator<T> &con_list_iterator<T>::operator =(const con_list_iterator<T> &iter)
{
    cur = iter.cur;
    return *this;
}

template <typename T>
bool con_list_iterator<T>::operator !=(const con_list_iterator<T> &iter) const
{
    return !(cur.lock() == iter.cur.lock()); // != removed in c++20
}

template <typename T>
bool con_list_iterator<T>::operator ==(const con_list_iterator<T> &iter) const
{
    return cur.lock() == iter.cur.lock();
}

#endif // CONST_LIST_ITERATOR_HPP
