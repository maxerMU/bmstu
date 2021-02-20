#include <assert.h>
#include <string.h>
#include "queue_list.h"
#include "exit_codes.h"

int allocate_node(node_t **node)
{
    *node = malloc(sizeof(node_t));
    if (!*node)
        return MEM_ER;
    
    return EXIT_SUCCESS;
}

void free_node(node_t *node)
{
    free(node);
}

void free_list(node_t *head)
{
    while (head)
    {
        node_t *next = head->next;
        free(head);
        head = next;
    }
}

void free_qlist(queue_list_t qlist)
{
    free_list(qlist.head);
}

void qlist_init(queue_list_t *qlist)
{
    memset(qlist, 0, sizeof(queue_list_t));
}

int push_qlist(void *queue, request_t req)
{
    queue_list_t *qlist = queue;
    node_t *node;
    int rc = allocate_node(&node);
    if (rc)
        return rc;

    node->req = req;
    node->next = NULL;
    if (qlist->head)
    {
        qlist->tail->next = node;
        qlist->tail = node;
    }
    else
    {
        qlist->tail = node;
        qlist->head = node;
    }
    
    return EXIT_SUCCESS;
}

int pop_qlist(void *queue, request_t *req)
{
    queue_list_t *qlist = queue;
    if (!qlist->head)
        return POP_ER;
    
    *req = qlist->head->req;
    node_t *cur = qlist->head;
    qlist->head = qlist->head->next;
    free_node(cur);

    return EXIT_SUCCESS;
}

void fwrite_qlist(FILE *dst, queue_list_t qlist)
{
    if (!qlist.head)
        fprintf(dst, "empty queue\n");
    else
    {
        while (qlist.head)
        {
            fprintf(dst, "addres - %p\n", (void *) qlist.head);
            fwrite_req(dst, qlist.head->req);
            qlist.head = qlist.head->next;
        }
    }
}