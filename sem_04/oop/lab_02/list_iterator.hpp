#ifndef LIST_ITERATOR_HPP
#define LIST_ITERATOR_HPP

template <typename T>
list_iterator<T>::list_iterator()
    :cur(std::weak_ptr<list_node<T>>())
{
}

template <typename T>
list_iterator<T>::list_iterator(const std::shared_ptr<list_node<T>> &pnode)
    :cur(pnode)
{
}

template <typename T>
list_iterator<T>::list_iterator(const list_iterator<T> &iter)
    :cur(iter.cur.lock())
{
}

template <typename T>
void list_iterator<T>::next()
{
    if (cur.lock())
    {
        cur = cur.lock()->get_next();
    }
}

template <typename T>
bool list_iterator<T>::is_invalid() const
{
    return cur.expired();
}

template <typename T>
T &list_iterator<T>::operator *()
{
    return cur.lock()->get_data();
}

template <typename T>
T &list_iterator<T>::operator ->()
{
    return cur.lock()->get_data();
}

template <typename T>
std::shared_ptr<list_node<T>> list_iterator<T>::get_spnode()
{
    return cur.lock();
}

template <typename T>
const std::shared_ptr<list_node<T>> list_iterator<T>::get_cspnode() const
{
    return cur.lock();
}

template <typename T>
list_iterator<T> &list_iterator<T>::operator ++()
{
    next();
    return *this;
}

template <typename T>
list_iterator<T> list_iterator<T>::operator ++(int)
{
    list_iterator<T> temp = *this;
    next();
    return temp;
}

template <typename T>
list_iterator<T> &list_iterator<T>::operator +=(long step)
{
    for (long i = 0; i < step; i++)
        next();

    return *this;
}

template <typename T>
list_iterator<T> list_iterator<T>::operator +(long step)
{
    list_iterator it(*this);
    it += step;
    return it;
}

template <typename T>
list_iterator<T> &list_iterator<T>::operator =(const list_iterator<T> &iter)
{
    cur = iter.cur.lock();
    return *this;
}

template <typename T>
bool list_iterator<T>::operator !=(const list_iterator<T> &iter)
{
    return !(cur.lock() == iter.cur.lock()); // != removed in c++20
}

template <typename T>
bool list_iterator<T>::operator ==(const list_iterator<T> &iter)
{
    return cur.lock() == iter.cur.lock();
}

#endif // LIST_ITERATOR_HPP
