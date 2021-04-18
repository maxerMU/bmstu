#ifndef LIST_NODE_HPP
#define LIST_NODE_HPP

template <typename T>
list_node<T>::list_node(const T &data)
    :data(data), next(nullptr)
{
}

template <typename T>
list_node<T>::list_node(const std::shared_ptr<list_node<T> > &node)
    :data(node->data), next(node->next)
{
}

template <typename T>
list_node<T>::list_node(const T &data, const std::shared_ptr<list_node<T> > &next)
    :data(data), next(next)
{
}

template <typename T>
void list_node<T>::set_data(const T &data)
{
    this->data = data;
}

template <typename T>
void list_node<T>::set_next(const std::shared_ptr<list_node<T>> &node)
{
    this->next = node;
}

template <typename T>
T &list_node<T>::get_data()
{
    return data;
}

template <typename T>
const T &list_node<T>::get_cdata() const
{
    return data;
}

template <typename T>
std::shared_ptr<list_node<T>> list_node<T>::get_next() const
{
    return next;
}

template <typename T>
bool list_node<T>::operator ==(const list_node<T> &node) const
{
    bool cmp = (this->data == node.data);
    if (cmp)
        cmp = (this->next == node.next);

    return cmp;
}

template <typename T>
bool list_node<T>::operator !=(const list_node<T> &node) const
{
    bool cmp = (this->data != node.data);
    if (cmp)
        cmp = (this->next != node.next);

    return cmp;
}

template <typename T>
bool list_node<T>::operator ==(const std::shared_ptr<list_node<T>> &node) const
{
    return this == node;
}

template <typename T>
bool list_node<T>::operator !=(const std::shared_ptr<list_node<T>> &node) const
{
    return this != node;
}

#endif // LIST_NODE_HPP
