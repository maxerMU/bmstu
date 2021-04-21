#ifndef LIST_HPP
#define LIST_HPP

template <typename T>
list<T>::operator bool() const
{
    return size;
}

template <typename T>
list<T>::list()
    :head(std::shared_ptr<list_node<T>>()),
     tail(std::shared_ptr<list_node<T>>()),
     size(0)
{
}

template <typename T>
list<T>::list(const list<T> &l)
    :head(std::shared_ptr<list_node<T>>()),
     tail(std::shared_ptr<list_node<T>>()),
     size(0)
{
    for (con_list_iterator<T> it = l.cbegin(); it != l.cend(); ++it)
        push_back(*it);
}

template <typename T>
list<T>::list(list<T> &&l) noexcept
    :head(l.get_head()),
     tail(l.get_tail()),
     size(l.get_size())
{
}

template <typename T>
list<T>::list(const T *arr, long size)
    :head(std::shared_ptr<list_node<T>>()),
     tail(std::shared_ptr<list_node<T>>()),
     size(0)
{
    if (!arr)
    {
        auto timenow = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        throw list_pointer_exception(ctime(&timenow), __FILE__, typeid(list).name(), __FUNCTION__);
    }

    if (size <= 0)
    {
        auto timenow = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        throw list_size_exception(ctime(&timenow), __FILE__, typeid(list).name(), __FUNCTION__);
    }

    for (long i = 0; i < size; i++)
    {
        push_back(arr[i]);
    }
    this->size = size;
}

template <typename T>
list<T>::list(const std::initializer_list<T> &elems)
    :head(std::shared_ptr<list_node<T>>()),
     tail(std::shared_ptr<list_node<T>>()),
     size(0)
{
    for (auto elem : elems)
        push_back(elem);
}

template <typename T>
list<T> list<T>::operator =(const std::initializer_list<T> &in_list)
{
    clear();
    for (auto elem : in_list)
        push_back(elem);
}

//template <typename T>
//list<T>::list(list_iterator<T> begin, list_iterator<T> end)
//    :head(std::shared_ptr<list_node<T>>()),
//     tail(std::shared_ptr<list_node<T>>()),
//     size(0)
//{
//    for (list_iterator<T> it = begin; it != end; ++it)
//    {
//        if (it.is_invalid())
//        {
//            auto timenow = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
//            throw list_iterator_exception(ctime(&timenow), __FILE__, typeid(list).name(), __FUNCTION__);
//        }
//
//        push_back(*it);
//    }
//}

template <typename T>
template <typename iter>
list<T>::list(iter begin, iter end)
    :head(std::shared_ptr<list_node<T>>()),
     tail(std::shared_ptr<list_node<T>>()),
     size(0)
{
    for (iter it = begin; it != end; ++it)
    {
//        if (it)
//        {
//            auto timenow = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
//            throw list_iterator_exception(ctime(&timenow), __FILE__, typeid(list).name(), __FUNCTION__);
//        }

        push_back(*it);
    }
}

template <typename T>
long list<T>::get_size() const
{
    return size;
}

template <typename T>
bool list<T>::is_empty() const
{
    return !size;
}

template <typename T>
void list<T>::clear()
{
    while (size)
    {
        pop_front();
    }
}

template <typename T>
T list<T>::pop_back()
{
    if (!size)
    {
        auto timenow = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        throw list_empty_exception(ctime(&timenow), __FILE__, typeid(list).name(), __FUNCTION__);
    }

    T data = tail->get_data();
    if (size == 1)
    {
        head = std::shared_ptr<list_node<T>>();
        tail = std::shared_ptr<list_node<T>>();
    }
    else
    {
        list_iterator<T> it(this->begin());
        list_iterator<T> tail_it(tail);
        for (; it + (long) 1 != tail_it; ++it);

        it.cur.lock()->set_next(std::shared_ptr<list_node<T>>());
        tail = it.cur.lock();
        //it.set_next(std::shared_ptr<list_node<T>>());
        //tail = it.get_spnode();
    }
    size--;

    return data;
}

template <typename T>
T list<T>::pop_front()
{
    if (!size)
    {
        auto timenow = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        throw list_empty_exception(ctime(&timenow), __FILE__, typeid(list).name(), __FUNCTION__);
    }

    T data = head->get_data();
    if (size == 1)
    {
        tail = std::shared_ptr<list_node<T>>();
    }

    head = head->get_next();
    size--;

    return data;
}

template <typename T>
void list<T>::push_back(const T &data)
{
    std::shared_ptr<list_node<T>> pnode;

    try
    {
        pnode = std::shared_ptr<list_node<T>>(new list_node<T>(data));
    }
    catch (std::bad_alloc &error)
    {
       auto timenow = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
       throw list_memory_exception(ctime(&timenow), __FILE__, typeid(list).name(), __FUNCTION__);
    }

    pnode->set_next(std::shared_ptr<list_node<T>>());

    if (!size)
    {
        head = pnode;
        tail = pnode;
    }
    else
    {
        tail->set_next(pnode);
        tail = pnode;
    }
    size++;
}

template <typename T>
void list<T>::push_front(const T &data)
{
    std::shared_ptr<list_node<T>> pnode;

    try
    {
        pnode = std::shared_ptr<list_node<T>>(new list_node<T>(data));
    }
    catch (std::bad_alloc &error)
    {
       auto timenow = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
       throw list_memory_exception(ctime(&timenow), __FILE__, typeid(list).name(), __FUNCTION__);
    }

    pnode->set_next(head);

    if (!size)
        tail = pnode;
    head = pnode;

    size++;
}

template <typename T>
void list<T>::push_front(const list<T> &list)
{
    list_iterator<T> next_it = begin();
    for (con_list_iterator<T> it = list.cbegin(); it != list.cend(); ++it)
    {
        insert(next_it, *it);
    }
}

template <typename T>
void list<T>::push_back(const list<T> &list)
{
    for (con_list_iterator<T> it = list.cbegin(); it != list.cend(); ++it)
        push_back(*it);
}

template <typename T>
list_iterator<T> list<T>::insert(const list_iterator<T> &it, const T &data)
{
    if (it.is_invalid())
    {
        auto timenow = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        throw list_iterator_exception(ctime(&timenow), __FILE__, typeid(list).name(), __FUNCTION__);
    }

    if (it.cur.lock() == head)
    {
        push_front(data);
        return list_iterator<T>(head);
    }

    std::shared_ptr<list_node<T>> pnode;

    try
    {
        pnode = std::shared_ptr<list_node<T>>(new list_node<T>(data));
    }
    catch (std::bad_alloc &error)
    {
       auto timenow = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
       throw list_memory_exception(ctime(&timenow), __FILE__, typeid(list).name(), __FUNCTION__);
    }

    list_iterator<T> prev_it = begin();
    for (; prev_it + (long) 1 != it; ++prev_it);

    pnode->set_next(it.cur.lock());
    prev_it.cur.lock()->set_next(pnode);

    size++;

    return list_iterator<T>(pnode);
}

template <typename T>
list_iterator<T> list<T>::insert(const list_iterator<T> &it, const list<T> &l)
{
    if (it.is_invalid())
    {
        auto timenow = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        throw list_iterator_exception(ctime(&timenow), __FILE__, typeid(list).name(), __FUNCTION__);
    }

    list_iterator<T> res_it;

    for (con_list_iterator<T> cur_el_it = l.cbegin(); cur_el_it != l.cend(); ++cur_el_it)
        res_it = insert(it, *cur_el_it);

    return res_it;
}

template <typename T>
template <typename iter>
list_iterator<T> list<T>::insert(const list_iterator<T> &it, iter begin, iter end)
{
    if (it.is_invalid())
    {
        auto timenow = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        throw list_iterator_exception(ctime(&timenow), __FILE__, typeid(list).name(), __FUNCTION__);
    }

    list_iterator<T> res_it;

    for (iter cur_el_it = begin; cur_el_it != end; ++cur_el_it)
        res_it = insert(it, *cur_el_it);

    return res_it;
}

template <typename T>
void list<T>::remove(const list_iterator<T> &it)
{
    if (it.is_invalid())
    {
        auto timenow = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        throw list_iterator_exception(ctime(&timenow), __FILE__, typeid(list).name(), __FUNCTION__);
    }

    if (it.cur.lock() == head)
        pop_front();
    else if (it.cur.lock() == tail)
        pop_back();
    else
    {
        list_iterator<T> prev = begin();
        for (; prev + (long) 1 != it; ++prev);
        prev.cur.lock()->set_next(it.cur.lock()->get_next());
        size--;
    }
}

template <typename T>
void list<T>::remove(const list_iterator<T> &it, size_t count)
{
    list_iterator<T> cur_it = it;
    for (size_t i = 0; i < count; i++)
    {
        list_iterator<T> next = cur_it + (long) 1;
        remove(cur_it);
        cur_it = next;
    }
}

template <typename T>
void list<T>::remove(const list_iterator<T> &begin, const list_iterator<T> &end)
{
    list_iterator<T> cur_it = begin;
    while (cur_it != end)
    {
        list_iterator<T> next = cur_it + (long) 1;
        remove(cur_it);
        cur_it = next;
    }
}

template <typename T>
void list<T>::reverse()
{
    std::shared_ptr<list_node<T>> cur = head;
    std::shared_ptr<list_node<T>> next;
    std::shared_ptr<list_node<T>> prev;

    while (cur)
    {
        next = cur->get_next();
        cur->set_next(prev);
        prev = cur;
        cur = next;
    }

    prev = tail;
    tail = head;
    head = prev;
}

template <typename T>
list<T> &list<T>::merge(const T &data)
{
    push_back(data);
    return *this;
}

template <typename T>
list<T> &list<T>::merge(const list<T> &merge_list)
{
    push_back(merge_list);
    return *this;
}

template <typename T>
list<T> list<T>::operator +(const T &data) const
{
    list<T> tmp(*this);
    tmp.push_back(data);
    return tmp;
}

template <typename T>
list<T> list<T>::operator +(const list<T> &l) const
{
    list<T> tmp(*this);
    tmp.push_back(l);
    return tmp;
}

template <typename T>
list<T> &list<T>::operator +=(const T &data)
{
    push_back(data);
    return *this;
}

template <typename T>
list<T> &list<T>::operator +=(const list<T> &l)
{
    push_back(l);
    return *this;
}

template <typename T>
list<T> list<T>::operator =(const list<T> &l)
{
    clear();

    size = l.size;

    for (con_list_iterator<T> it = l.cbegin(); it != l.cend(); ++it)
        push_back(*it);

    return *this;
}

template <typename T>
list<T> list<T>::operator =(list<T> &&l) const
{
    clear();

    size = l.size;
    head = l.head;
    tail = l.tail;

    return *this;
}

template <typename T>
bool list<T>::operator ==(const list<T> &l) const
{
    bool cmp = (size == l.size);

    con_list_iterator<T> it1 = cbegin();
    con_list_iterator<T> it1_end = cend();
    con_list_iterator<T> it2 = l.cbegin();

    while (cmp && it1 != it1_end)
    {
        cmp = (*it1 == *it2);
        ++it1;
        ++it2;
    }

    return cmp;
}

template <typename T>
list_iterator<T> list<T>::begin()
{
    list_iterator<T> it(head);
    return it;
}

template <typename T>
list_iterator<T> list<T>::end()
{
    list_iterator<T> it(tail);
    return ++it;
}

template <typename T>
con_list_iterator<T> list<T>::cbegin() const
{
    con_list_iterator<T> it(head);
    return it;
}

template <typename T>
con_list_iterator<T> list<T>::cend() const
{
    con_list_iterator<T> it(tail);
    return ++it;
}

#endif // LIST_HPP
