#ifndef STACK_LIST_H
#define STACK_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include "elem_type.h"

#define INC_SIZE 2

struct node
{
    elem_t value;
    struct node *next;
};

typedef struct node node_t;

typedef struct
{
    node_t *top; //stack top
    node_t **free_spaces; //free elements
    size_t spaces_len; //length of free spaces array
    size_t spaces_alloc; //allocated lenght of spaces array
}stack_list_t;

void free_lstack(stack_list_t *stc);
void lstack_init(stack_list_t *stc);
int write_lstack(stack_list_t *stc);
void write_free_spaces(stack_list_t stc);
int read_lstack(stack_list_t *stc);
int alloc_node(node_t **dst);
int popl(void *stc, elem_t *elem);
int pushl(void *stc, elem_t elem);
void push_el(stack_list_t *stc, node_t *node, elem_t elem);

#endif //STACK_LIST_H