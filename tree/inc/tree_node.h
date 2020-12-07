#ifndef TREE_NODE_H
#define TREE_NODE_H

#include <stdio.h>
#include <stdlib.h>
#include "elem.h"

typedef struct node node_t;

struct node
{
    elem_t data;
    node_t *left;
    node_t *right;
};

node_t *create_node();
void free_node(node_t *node, void *param);
void to_dot(node_t *node, void *file);

#endif //TREE_NODE_H