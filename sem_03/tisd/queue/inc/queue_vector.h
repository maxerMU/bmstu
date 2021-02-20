#ifndef QUEUE_VECTOR_H
#define QUEUE_VECTOR_H

#include <stdlib.h>
#include <stdio.h>
#include "request.h"

typedef struct
{
    request_t *start;
    request_t *end;
    request_t *pin;
    request_t *pout;
    size_t size;
}queue_vec_t;

void free_qvec(queue_vec_t *qvec);
int allocate_qvec(queue_vec_t *qvec, size_t n);
int push_qvec(void *queue, request_t req);
int pop_qvec(void *queue, request_t *req);
void fwrite_qvec(FILE *dst, queue_vec_t qvec);
void fread_qvec(FILE *src, queue_vec_t *qvec);

#endif //QUEUE_VECTOR_H