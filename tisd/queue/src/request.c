#include "exit_codes.h"
#include "request.h"

void req_init(request_t *req, long begin_min, long begin_max, long proc_min, long proc_max)
{
    req->iterations = 0;
    double k = (double) rand() / RAND_MAX;
    req->time_begin = (begin_max - begin_min) * k + begin_min;
    k = (double) rand() / RAND_MAX;
    req->time_process = (proc_max - proc_min) * k + proc_min;
}

int fread_req(FILE *src, request_t *req)
{
    long begin_min, begin_max, proc_min, proc_max;
    printf("Input min and max time to push: ");
    if (fscanf(src, "%ld %ld", &begin_min, &begin_max) != 2)
        return READ_ER;
    printf("Input min and max time to process: ");
    if (fscanf(src, "%ld %ld", &proc_min, &proc_max) != 2)
        return READ_ER;

    req_init(req, begin_min, begin_max, proc_min, proc_max);

    return EXIT_SUCCESS;
}

void fwrite_req(FILE *dst, request_t req)
{
    fprintf(dst, "%ld %.6lf %.6lf\n", req.iterations, req.time_begin, req.time_process);
}