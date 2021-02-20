#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "exit_codes.h"
#include "request.h"
#include "queue_vector.h"
#include "queue_list.h"

#define ACCURACY 1e-6
#define MAX_ITER 5

#define ITERATIONS 100

typedef struct
{
    int state;
    request_t req;
    double rest_time;
}apparat_t;

void check_queue_on_vec()
{
    queue_vec_t qvec;
    size_t size;
    printf("Input vec size: ");
    if (scanf("%zu", &size) != 1)
    {
        printf("Incorrect size\n");
        return;
    }
    assert(!allocate_qvec(&qvec, size));
    int choise = 10;
    while (choise)
    {
        printf("\n1 - push\n"
               "2 - pop\n"
               "3 - write\n"
               "0- exit\n"
               "your choise: ");
        if (scanf("%d", &choise) != 1)
            continue;
        if (choise == 1)
        {
            request_t req;
            int rc = fread_req(stdin, &req);
            if (rc)
            {
                printf("wrong input\n");
                break;
            }
            rc = push_qvec(&qvec, req);
            assert(rc != MEM_ER);
            if (rc)
            {
                printf("queue overflow\n");
                break;
            }
        }
        else if (choise == 2)
        {
            request_t req;
            int rc = pop_qvec(&qvec, &req);
            if (rc)
            {
                printf("empty queue\n");
                break;
            }
            fwrite_req(stdout, req);
        }
        else if (choise == 3)
        {
            fwrite_qvec(stdout, qvec);
        }
    }

    free_qvec(&qvec);
}

void check_queue_on_list()
{
    queue_list_t qlist;
    qlist_init(&qlist);
    int choise = 10;
    while (choise)
    {
        printf("\n1 - push\n"
               "2 - pop\n"
               "3 - write\n"
               "0- exit\n"
               "your choise: ");
        if (scanf("%d", &choise) != 1)
            continue;
        if (choise == 1)
        {
            request_t req;
            int rc = fread_req(stdin, &req);
            if (rc)
            {
                printf("wrong input\n");
                break;
            }
            rc = push_qlist(&qlist, req);
            assert(rc != MEM_ER);
        }
        else if (choise == 2)
        {
            request_t req;
            int rc = pop_qlist(&qlist, &req);
            if (rc)
            {
                printf("empty queue\n");
                break;
            }
            fwrite_req(stdout, req);
        }
        else if (choise == 3)
        {
            fwrite_qlist(stdout, qlist);
        }
    }

    free_qlist(qlist);
}

int model_apparat(long beg_min, long beg_max, long proc_min, long proc_max, void *queue,
                  int (*push)(void *, request_t), int (*pop)(void *, request_t *))
{
    size_t cur_len = 0, avg_count_len = 0;
    double avg_sum_len = 0.0;
    size_t count_in = 0, count_out = 0, count_proc = 0;
    double time_all = 0.0, downtime = 0.0;

    request_t cur_req;
    req_init(&cur_req, beg_min, beg_max, proc_min, proc_max);

    apparat_t apparat;
    apparat.state = 0;

    size_t last_print = count_out;

    double my_sum = 0.0;
    size_t my_k = 0;

    while (count_out < 1000)
    {
        if (count_out % 100 == 0 && count_out != last_print)
        {
            printf("\nelements out - %zu\n", count_out);
            printf("queue current len - %zu\n", cur_len);
            printf("avg queue lenght - %lf\n", avg_sum_len / avg_count_len);
            last_print = count_out;
        }
        //push current request
        if (fabs(cur_req.time_begin) < ACCURACY)
        {
            int rc = push(queue, cur_req);
            if (rc)
            {
                printf("unable to push\n");
                return rc;
            }
            req_init(&cur_req, beg_min, beg_max, proc_min, proc_max);
            my_sum += cur_req.time_begin;
            my_k++;
            cur_len++;
            avg_count_len++;
            avg_sum_len += cur_len;
            count_in++;
        }
        //end process
        if (apparat.state && fabs(apparat.rest_time) < ACCURACY)
        {
            apparat.req.iterations += 1;
            if (apparat.req.iterations == MAX_ITER)
                count_out++;
            else
            {
                int rc = push(queue, apparat.req);
                if (rc)
                {
                    printf("unable to push\n");
                    return rc;
                }
                cur_len++;
            }
            apparat.state = 0;
            count_proc++;
        }
        //start process
        if (cur_len && !apparat.state)
        {
            apparat.state = 1;
            pop(queue, &apparat.req);
            apparat.rest_time = apparat.req.time_process;
            cur_len--;
        }
        if (!apparat.state || cur_req.time_begin < apparat.rest_time)
        {
            if (apparat.state)
                apparat.rest_time -= cur_req.time_begin;
            else
                downtime += cur_req.time_begin;
            time_all += cur_req.time_begin;
            cur_req.time_begin = 0.0;
        }
        else
        {
            cur_req.time_begin -= apparat.rest_time;
            time_all += apparat.rest_time;
            apparat.rest_time = 0.0;
        }
    }

    printf("\n*************\n");
    printf("total time: %lf\n", time_all);
    printf("elements in: %zu\n", count_in);
    printf("elements out: %zu\n", count_out);
    printf("apparat processes: %zu\n", count_proc);
    printf("downtime - %lf\n", downtime);
    printf("\nAccuracy\n");
    double ideal_in = time_all / ((beg_max + beg_min) / 2.0);
    printf("elements in accuracy - %lf%%\n", 100 * fabs(count_in - ideal_in) / ideal_in);
    double ideal_proc = downtime + count_proc * ((proc_max + proc_min) / 2.0);
    printf("apparat processes accuracy - %lf%%\n", 100 * fabs(time_all- ideal_proc) / ideal_proc);

    printf("time begin - %lf\n", my_sum / my_k);

    return EXIT_SUCCESS;
}

void time_table()
{
    for (size_t max_size = 1000; max_size <= 1000000; max_size *= 10)
    {
        printf("size - %zu\n", max_size);
        for (double fullness = 0.25; fabs(fullness - 2) > ACCURACY; fullness *= 2)
        {
            size_t elements = max_size * fullness;
            queue_vec_t qvec;
            int rc = allocate_qvec(&qvec, max_size);
            assert(!rc);

            request_t req;
            req_init(&req, 0, 5, 0, 1);

            clock_t vproc = clock();
            for (size_t i = 0; i < ITERATIONS; i++)
            {
                for (size_t i = 0; i < elements; i++)
                {
                    int rc = push_qvec(&qvec, req);
                    if (rc)
                    {
                        printf("push error\n");
                        return;
                    }
                }
                for (size_t i = 0; i < elements; i++)
                {
                    pop_qvec(&qvec, &req);
                }
            }
            vproc = clock() - vproc;
            double vproc_time = ((double)vproc / CLOCKS_PER_SEC) / ITERATIONS;

            queue_list_t qlist;
            qlist_init(&qlist);

            clock_t lproc = clock();
            for (size_t i = 0; i < ITERATIONS; i++)
            {
                for (size_t i = 0; i < elements; i++)
                {
                    int rc = push_qlist(&qlist, req);
                    if (rc)
                    {
                        printf("push error\n");
                        return;
                    }
                }
                for (size_t i = 0; i < elements; i++)
                {
                    pop_qlist(&qlist, &req);
                }
            }
            lproc = clock() - lproc;
            double lproc_time = ((double)lproc / CLOCKS_PER_SEC) / ITERATIONS;
            
            size_t vsize = sizeof(queue_vec_t) + sizeof(request_t) * (qvec.end - qvec.start);
            size_t lsize = sizeof(queue_list_t) + sizeof(node_t) * elements;
            printf("elments - %zu\n", elements);
            printf("| list time | vector time | list memory | vector memory |\n");
            printf("| %8lfs | %10lfs | %10zub | %12zub |\n", lproc_time, vproc_time, lsize, vsize);

            free_qvec(&qvec);
            free_qlist(qlist);
        }
    }
}

int main(void)
{
    int choise = 10;
    while (choise)
    {
        printf("\n1 - check queue on vector\n"
               "2 - check queue on list\n"
               "3 - model process on vector\n"
               "4 - model process on list\n"
               "5 - compare effiences\n"
               "0 - exit\n"
               "Your choise: ");
        if (scanf("%d", &choise) != 1)
            continue;
        if (choise == 1)
            check_queue_on_vec();
        else if (choise == 2)
            check_queue_on_list();
        else if (choise == 3)
        {
            long begin_min, begin_max, proc_min, proc_max;
            printf("Input min and max time to push: ");
            if (scanf("%ld %ld", &begin_min, &begin_max) != 2 || begin_max < begin_min || begin_min < 0)
            {
                printf("Incorrect input\n");
                continue;
            }
            printf("Input min and max time to processing: ");
            if (scanf("%ld %ld", &proc_min, &proc_max) != 2 || proc_max < proc_min || proc_min < 0)
            {
                printf("Incorrect input\n");
                continue;
            }
            size_t queue_len;
            printf("Input queue max len - ");
            if (scanf("%zu", &queue_len) != 1)
            {
                printf("Incorrect input\n");
                continue;
            }
            queue_vec_t qvec;
            int rc = allocate_qvec(&qvec, queue_len);
            assert(!rc);
            model_apparat(begin_min, begin_max, proc_min, proc_max, 
                          &qvec, push_qvec, pop_qvec);
            free_qvec(&qvec);
        }
        else if (choise == 4)
        {
            long begin_min, begin_max, proc_min, proc_max;
            printf("Input min and max time to push: ");
            if (scanf("%ld %ld", &begin_min, &begin_max) != 2 || begin_max < begin_min || begin_min < 0)
            {
                printf("Incorrect input\n");
                continue;
            }
            printf("Input min and max time to processing: ");
            if (scanf("%ld %ld", &proc_min, &proc_max) != 2 || proc_max < proc_min || proc_min < 0)
            {
                printf("Incorrect input\n");
                continue;
            }
            queue_list_t qlist;
            qlist_init(&qlist);
            model_apparat(begin_min, begin_max, proc_min, proc_max, 
                          &qlist, push_qlist, pop_qlist);
            free_qlist(qlist);
        }
        else if (choise == 5)
        {
            time_table();
        }
    }

    return EXIT_SUCCESS;
}
