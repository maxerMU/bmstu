#ifndef EDGE_H
#define EDGE_H

#include <stdlib.h>
#include "point.h"

class edge
{
public:
    edge();
    edge(size_t index1, size_t index2);

    size_t get_first() const;
    void set_first(size_t index);

    size_t get_second() const;
    void set_second(size_t index);

private:
    size_t pt_index1;
    size_t pt_index2;
};

#endif // EDGE_H
