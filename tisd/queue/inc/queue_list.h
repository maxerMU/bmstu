#ifndef QUEUE_LIST_H
#define QUEUE_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include "request.h"

typedef struct node node_t;

struct node
{
    request_t req;
    node_t *next;    
};

typedef struct
{
    node_t *head;
    node_t *tail;
}queue_list_t;

void qlist_init(queue_list_t *qlist);
void free_qlist(queue_list_t qlist);
void fwrite_qlist(FILE *dst, queue_list_t qlist);
int pop_qlist(void *queue, request_t *req);
int push_qlist(void *queue, request_t req);

#endif //QUEUE_LIST_H