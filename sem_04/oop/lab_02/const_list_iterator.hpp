#ifndef CONST_LIST_ITERATOR_HPP
#define CONST_LIST_ITERATOR_HPP

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
    if (cur.lock())
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
    return cur.lock()->get_data();
}

template <typename T>
const T &con_list_iterator<T>::operator ->() const
{
    return cur.lock()->get_cdata();
}

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
con_list_iterator<T> &con_list_iterator<T>::operator =(const con_list_iterator<T> &iter)
{
    cur = iter.cur.lock();
    return *this;
}

template <typename T>
bool con_list_iterator<T>::operator !=(const con_list_iterator<T> &iter)
{
    return !(cur.lock() == iter.cur.lock()); // != removed in c++20
}

template <typename T>
bool con_list_iterator<T>::operator ==(const con_list_iterator<T> &iter)
{
    return cur.lock() == iter.cur.lock();
}

#endif // CONST_LIST_ITERATOR_HPP
