#ifndef BALANCE_NODE_H
#define BALANCE_NODE_H

#include <stdio.h>
#include <stdlib.h>
#include "elem.h"

typedef struct balance_node balance_node_t;

struct balance_node
{
    elem_t data;
    unsigned char height;
    balance_node_t *right;
    balance_node_t *left;
};

balance_node_t *create_bnode();
void free_bnode(balance_node_t *node, void *param);
unsigned char height(balance_node_t *node);
int bfactor(balance_node_t *node);
void fix_height(balance_node_t *node);
void bto_dot(balance_node_t *node, void *file);

#endif //BALANCE_NODE_H