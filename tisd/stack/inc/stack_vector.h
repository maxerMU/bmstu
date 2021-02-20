#ifndef STACK_VECTOR_H
#define STACK_VECTOR_H

#include <stdio.h>
#include <stdlib.h>
#include "elem_type.h"

typedef struct
{
    elem_t *aub; //addres up bound
    elem_t *alb; //addres low bound
    elem_t *ps; //pointer stack
}stack_vector_t;

int allocate_vstack(stack_vector_t *stc, size_t n);
void free_vstack(stack_vector_t *stc);
int vpop(void *stc, elem_t *elem);
int vpush(void *stc, elem_t elem);
int read_vstack(stack_vector_t *stc);
void write_vstack(stack_vector_t *stc);
void init_vstack(stack_vector_t *stc);

#endif //STACK_VECTOR_H