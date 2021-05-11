#include "edge.h"

edge::edge()
    :pt_index1(0), pt_index2(0)
{
}

edge::edge(size_t index1, size_t index2)
    :pt_index1(index1), pt_index2(index2)
{
}

size_t edge::get_first() const
{
    return pt_index1;
}

void edge::set_first(size_t index)
{
    pt_index1 = index;
}

size_t edge::get_second() const
{
    return pt_index2;
}

void edge::set_second(size_t index)
{
    pt_index2 = index;
}
