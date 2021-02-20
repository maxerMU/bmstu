#include <string.h>
#include "exit_codes.h"
#include "queue_vector.h"

int allocate_qvec(queue_vec_t *qvec, size_t n)
{
    qvec->start = malloc(n * sizeof(request_t));
    if (!qvec->start)
        return MEM_ER;
    qvec->end = qvec->start + n;
    qvec->pin = qvec->start + (qvec->end - qvec->start) / 2;
    qvec->pout = qvec->pin;
    qvec->size = 0;

    return EXIT_SUCCESS;
}

void free_qvec(queue_vec_t *qvec)
{
    free(qvec->start);
    memset(qvec, 0, sizeof(queue_vec_t));
}

request_t *inc_pin(queue_vec_t qvec)
{
    if (qvec.pin + 1 == qvec.end)
        return qvec.start;
    else
        return qvec.pin + 1;
}

request_t *inc_pout(queue_vec_t qvec)
{
    if (qvec.pout + 1 == qvec.end)
        return qvec.start;
    else
        return qvec.pout + 1;
}

int push_qvec(void *queue, request_t req)
{
    queue_vec_t *qvec = queue;
    if (qvec->pin == qvec->pout && qvec->size)
        return PUSH_ER;
    
    *(qvec->pin) = req;
    qvec->pin = inc_pin(*qvec);
    qvec->size += 1;

    return EXIT_SUCCESS;
}

int pop_qvec(void *queue, request_t *req)
{
    queue_vec_t *qvec = queue;
    if (!qvec->size)
        return POP_ER;
    
    *req = *(qvec->pout);
    qvec->pout = inc_pout(*qvec);
    qvec->size -= 1;

    return EXIT_SUCCESS;
}

void fread_qvec(FILE *src, queue_vec_t *qvec)
{
    request_t req;
    printf("to exit input letter\n");
    while (!fread_req(src, &req))
    {
        int rc = push_qvec(qvec, req);
        if (rc)
            printf("Queue oferflow\n");
    }
}

void fwrite_qvec(FILE *dst, queue_vec_t qvec)
{
    if (!qvec.size)
        printf("empty queue\n");
    else
    {
        for (size_t i = 0; i < qvec.size; i++)
        {
            fwrite_req(dst, *(qvec.pout));
            qvec.pout = inc_pout(qvec);
        }
    }
}