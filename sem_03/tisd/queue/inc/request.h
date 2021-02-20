#ifndef REQUEST_H
#define REQUEST_H

#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    double time_begin;
    double time_process;
    size_t iterations;
}request_t;

void req_init(request_t *req, long begin_min, long begin_max, long proc_min, long proc_max);
int fread_req(FILE *src, request_t *req);
void fwrite_req(FILE *dst, request_t req);

#endif //REQUEST_H