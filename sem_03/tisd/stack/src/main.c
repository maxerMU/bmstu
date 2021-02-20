#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "exit_codes.h"
#include "stack_vector.h"
#include "stack_list.h"

#define TIME_ITERATIONS 100

int read_vstacks(stack_vector_t *vstc1, stack_vector_t *vstc2)
{
    printf("Input 1 stack\n");
    int rc = read_vstack(vstc1);
    if (rc)
        return rc;
    printf("Input 2 stack\n");
    for (int ch = getchar(); ch != '\n' && ch != EOF; ch = getchar());
    rc = read_vstack(vstc2);
    if (rc)
        return rc;
    for (int ch = getchar(); ch != '\n' && ch != EOF; ch = getchar());

    return EXIT_SUCCESS;
}

int read_lstacks(stack_list_t *lstc1, stack_list_t *lstc2)
{
    printf("Input 1 stack\n");
    int rc = read_lstack(lstc1);
    if (rc)
        return rc;
    printf("Input 2 stack\n");
    for (int ch = getchar(); ch != '\n' && ch != EOF; ch = getchar());
    rc = read_lstack(lstc2);
    if (rc)
        return rc;
    for (int ch = getchar(); ch != '\n' && ch != EOF; ch = getchar());
    
    return EXIT_SUCCESS;
}

void write_vstacks(stack_vector_t *vstc1, stack_vector_t *vstc2)
{
    write_vstack(vstc1);
    write_vstack(vstc2);
}

int write_lstacks(stack_list_t *lstc1, stack_list_t *lstc2)
{
    printf("1 stack\n");
    int rc = write_lstack(lstc1);
    if (rc)
        return rc;
    printf("2 stack\n");
    rc = write_lstack(lstc2);
    if (rc)
        return rc;
    
    return rc;
}

int push_to_any_stack(stack_vector_t *vstc1, stack_vector_t *vstc2, stack_list_t *lstc1, stack_list_t *lstc2)
{
    int choise;
    printf("\n select the stack where you want to push\n"
           "1 - first vector stack\n"
           "2 - second vector stack\n"
           "3 - first list stack\n"
           "4 - second list stack\n"
           "your choise: ");
    if (scanf("%d", &choise) != 1)
        return INPUT_ER;
    printf("Input element: ");
    elem_t el;
    if (scanf("%"EL_SC, &el) != 1)
        return INPUT_ER;

    int rc = EXIT_SUCCESS;
    if (choise == 1)
    {
        if (vstc1->ps)
            rc = vpush(vstc1, el);
        else
            printf("please, fill vector stack\n");
    }
    else if (choise == 2)
    {
        if (vstc2->ps)
            rc = vpush(vstc2, el);
        else
            printf("please, fill vector stack\n");
    }
    else if (choise == 3)
        rc = pushl(lstc1, el);
    else if (choise == 4)
        rc = pushl(lstc2, el);
    
    if (rc == PUSH_ER)
        printf("stack overflow\n");
    
    return rc;
}

int pop_from_any_stack(stack_vector_t *vstc1, stack_vector_t *vstc2, stack_list_t *lstc1, stack_list_t *lstc2)
{
    int choise;
    printf("\n select the stack from where you want to pop\n"
           "1 - first vector stack\n"
           "2 - second vector stack\n"
           "3 - first list stack\n"
           "4 - second list stack\n"
           "your choise: ");
    if (scanf("%d", &choise) != 1)
        return INPUT_ER;
    elem_t el;

    int rc = EXIT_SUCCESS;
    if (choise == 1)
        rc = vpop(vstc1, &el);
    else if (choise == 2)
        rc = vpop(vstc2, &el);
    else if (choise == 3)
        rc = popl(lstc1, &el);
    else if (choise == 4)
        rc = popl(lstc2, &el);
    if (rc)
    {
        if (rc == POP_ER)
            printf("empty stack\n");
        return rc;
    }
    printf("element - %"EL_PR, el);

    return EXIT_SUCCESS;
}

int sort_1_stack(void *stc, void *temp, int (*push)(void *, elem_t), int (*pop)(void *, elem_t *))
{
    elem_t elem;
    int rc = pop(stc, &elem);
    while (!rc)
    {
        elem_t temp_elem;
        int rc_temp = pop(temp, &temp_elem);
        if (rc_temp && rc_temp != POP_ER)
            return rc_temp;
        if (rc_temp == POP_ER)
        {
            int rc_push = push(temp, elem);
            if (rc_push)
                return rc_push;
        }
        else if (temp_elem <= elem)
        {
            int rc_push = push(temp, temp_elem);
            if (rc_push)
                return rc_push;
            rc_push = push(temp, elem);
            if (rc_push)
                return rc_push;
        }
        else
        {
            size_t counter = 0;
            while (temp_elem > elem && !rc_temp)
            {
                counter++;
                int rc_push = push(stc, temp_elem);
                if (rc_push)
                    return rc_push;
                rc_temp = pop(temp, &temp_elem);
            }
            if (rc_temp && rc_temp != POP_ER)
                return rc_temp;
            if (!rc_temp)
            {
                int rc_push = push(temp, temp_elem);
                if (rc_push)
                    return rc_push;
            }
            int rc_push = push(temp, elem);
            if (rc_push)
                return rc_push;
            for (size_t i = 0; i < counter; i++)
            {
                rc = pop(stc, &elem);
                if (rc)
                    return rc;
                rc_temp = push(temp, elem);
                if (rc_temp)
                    return rc_temp;
            }
        }
        rc = pop(stc, &elem);
    }
    if (rc != POP_ER)
        return rc;
    rc = pop(temp, &elem);
    while (!rc)
    {
        int rc_push = push(stc, elem);
        if (rc_push)
            return rc_push;
        rc = pop(temp, &elem);
    }
    if (rc != POP_ER)
        return rc;   

    return EXIT_SUCCESS;
}

int sort_2_stacks(void *stc1, void *stc2, void *stc3, int (*push)(void *, elem_t), int (*pop)(void *, elem_t *))
{
    int rc = sort_1_stack(stc1, stc3, push, pop);
    if (rc)
        return rc;
    rc = sort_1_stack(stc2, stc3, push, pop);
    if (rc)
        return rc;

    elem_t elem1;
    int rc1 = pop(stc1, &elem1);
    elem_t elem2;
    int rc2 = pop(stc2, &elem2);
    int sorted = 0;
    while (!sorted)
    {
        if (rc1 && rc1 != POP_ER)
            return rc1;
        if (rc2 && rc2 != POP_ER)
            return rc2;
        if (!rc1 && !rc2)
        {
            int rc_push;
            if (elem1 < elem2)
            {
                rc_push = push(stc3, elem1);
                rc1 = pop(stc1, &elem1);
            }
            else
            {
                rc_push = push(stc3, elem2);
                rc2 = pop(stc2, &elem2);
            }
            if (rc_push)
                return rc_push;
        }
        else if (!rc1)
        {
            while (!rc1)
            {
                int rc_push = push(stc3, elem1);
                if (rc_push)
                    return rc_push;
                rc1 = pop(stc1, &elem1);
            }
            if (rc1 != POP_ER)
                return POP_ER;
        }
        else if (!rc2)
        {
            while (!rc2)
            {
                int rc_push = push(stc3, elem2);
                if (rc_push)
                    return rc_push;
                rc2 = pop(stc2, &elem2);
            }
            if (rc2 != POP_ER)
                return POP_ER;
        }
        if (rc1 == POP_ER && rc2 == POP_ER)
            sorted = 1;
    }

    return EXIT_SUCCESS;
}

int gen_stack(size_t size, stack_vector_t *vstc, stack_list_t *lstc)
{
    const long min = -1000;
    const long max = 1000;
    free_lstack(lstc);
    free_vstack(vstc);
    int rc = allocate_vstack(vstc, size);
    if (rc)
        return rc;
    for (size_t i = 0; i < size; i++)
    {
        elem_t el = min + rand() % (max - min);
        int rc = pushl(lstc, el);
        if (rc)
            return rc;
        rc = vpush(vstc, el);
        if (rc)
            return rc;
    }

    return EXIT_SUCCESS;
}

int copy_vstack(stack_vector_t *dst, stack_vector_t src)
{
    for (elem_t *current = src.alb; current <= src.ps; current++)
    {
        int rc = vpush(dst, *current);
        if (rc)
            return rc;
    }

    return EXIT_SUCCESS;
}

int copy_lstack(stack_list_t *dst, stack_list_t src)
{
    if (!dst->top)
    {
        int rc = alloc_node(&dst->top);
        if (rc)
            return rc;
    }
    node_t *prev_dst = dst->top;
    for (node_t *current_src = src.top, *current_dst = dst->top; current_src;\
         current_src = current_src->next, current_dst = current_dst->next)
    {
        if (!current_dst)
        {
            int rc = alloc_node(&current_dst);
            if (rc)
                return rc;
            prev_dst->next = current_dst;
        }
        current_dst->value = current_src->value;
        prev_dst = current_dst;
    }

    return EXIT_SUCCESS;
}

int time_table()
{
    for (size_t k = 1; k <= 8; k *= 2)
    {
        printf("vector stack max - size * %zu\n", k);
        for (size_t size = 100; size <= 400; size *= 2)
        {
            stack_vector_t vstc1;
            init_vstack(&vstc1);
            stack_vector_t vstc2;
            init_vstack(&vstc2);
            stack_vector_t vstc_res;
            init_vstack(&vstc_res);
            stack_list_t lstc1;
            lstack_init(&lstc1);
            stack_list_t lstc2;
            lstack_init(&lstc2);
            stack_list_t lstc_res;
            lstack_init(&lstc_res);

            int rc = gen_stack(size * k, &vstc1, &lstc1);
            if (rc)
                return rc;
            rc = gen_stack(size * k, &vstc2, &lstc2);
            if (rc)
                return rc;
            rc = allocate_vstack(&vstc_res, size * 2 * k + 1);
            if (rc)
                return rc;
            stack_vector_t vstc1_copy;
            rc = allocate_vstack(&vstc1_copy, size * k);
            if (rc)
                return rc;
            stack_vector_t vstc2_copy;
            rc = allocate_vstack(&vstc2_copy, size * k);
            if (rc)
                return rc;
            stack_list_t lstc1_copy;
            lstack_init(&lstc1_copy);
            stack_list_t lstc2_copy;
            lstack_init(&lstc2_copy);

            clock_t vcopy = clock();
            for (size_t i = 0; i < TIME_ITERATIONS; i++)
            {
                vstc1_copy.ps = vstc1_copy.alb - 1;
                copy_vstack(&vstc1_copy, vstc1);
            }
            vcopy = clock() - vcopy;
            double vcopy_time = ((double)vcopy / CLOCKS_PER_SEC) / TIME_ITERATIONS;

            clock_t lcopy = clock();
            for (size_t i = 0; i < TIME_ITERATIONS; i++)
                copy_lstack(&lstc1_copy, lstc1);
            lcopy = clock() - lcopy;
            double lcopy_time = ((double)lcopy / CLOCKS_PER_SEC) / TIME_ITERATIONS;

            clock_t vsort = clock();
            for (size_t i = 0; i < TIME_ITERATIONS; i++)
            {
                vstc1_copy.ps = vstc1_copy.alb - 1;
                vstc2_copy.ps = vstc2_copy.alb - 1;
                rc = copy_vstack(&vstc1_copy, vstc1);
                if (rc)
                    return rc;
                rc = copy_vstack(&vstc2_copy, vstc2);
                if (rc)
                    return rc;
                //Очистка стека!!
                vstc_res.ps = vstc_res.alb - 1;
                sort_2_stacks(&vstc1_copy, &vstc2_copy, &vstc_res, vpush, vpop);
            }
            vsort = clock() - vsort;
            double vsort_time = ((double)vsort / CLOCKS_PER_SEC) / TIME_ITERATIONS - 2 * vcopy_time;

            clock_t lsort = clock();
            for (size_t i = 0; i < TIME_ITERATIONS; i++)
            {
                copy_lstack(&lstc1_copy, lstc1);
                copy_lstack(&lstc2_copy, lstc2);
                sort_2_stacks(&lstc1_copy, &lstc2_copy, &lstc_res, pushl, popl);
                //Очистка стека!!
                free_lstack(&lstc_res);
            }
            lsort = clock() - lsort;
            double lsort_time = ((double)lsort / CLOCKS_PER_SEC) / TIME_ITERATIONS - 2 * lcopy_time;

            size_t vsize = sizeof(vstc1) + sizeof(elem_t) * (vstc1.aub - vstc1.alb);
            size_t lsize = sizeof(node_t *) + sizeof(node_t) * size;
            printf("stack sizes %zu\n", size);
            printf("| list time | vector time | list memory | vector memory |\n");
            printf("| %8lfs | %10lfs | %10zub | %12zub |\n", lsort_time, vsort_time, lsize, vsize);

            free_vstack(&vstc1);
            free_vstack(&vstc2);
            free_vstack(&vstc_res);
            free_lstack(&lstc1);
            free_lstack(&lstc2);
            free_lstack(&lstc_res);
            free_vstack(&vstc1_copy);
            free_vstack(&vstc2_copy);
            free_lstack(&lstc1_copy);
            free_lstack(&lstc2_copy);
        }
    }

    return EXIT_SUCCESS;
}

int main(void)
{
    stack_vector_t vstc1;
    init_vstack(&vstc1);
    stack_vector_t vstc2;
    init_vstack(&vstc2);
    stack_vector_t vstc_res;
    init_vstack(&vstc_res);
    stack_list_t lstc1;
    lstack_init(&lstc1);
    stack_list_t lstc2;
    lstack_init(&lstc2);
    stack_list_t lstc_res;
    lstack_init(&lstc_res);

    int choise = 10;
    int rc = EXIT_SUCCESS;
    while (choise)
    {
        printf("\n1 - read stacks like vector\n"
               "2 - read stacks like list\n"
               "3 - write stacks like vector\n"
               "4 - write stacks like list\n"
               "5 - write free spaces vector\n"
               "6 - push element to any stack\n"
               "7 - pop element from any stack\n"
               "8 - sort two stacks in third using stack like vector\n"
               "9 - sort two stacks in third using stack like list\n"
               "10 - compare effiences\n"
               "0 - exit\n"
               "Your choise: ");
        if (scanf("%d", &choise) != 1)
            continue;
        if (choise == 1)
        {
            rc = read_vstacks(&vstc1, &vstc2);
            if (rc == PUSH_ER)
                printf("Stack overflow\n");
            else if (rc)
                break;
            rc = allocate_vstack(&vstc_res, vstc1.aub - vstc1.alb + vstc2.aub - vstc2.alb);
            if (rc)
                break;
        }
        else if (choise == 2)
        {
            rc = read_lstacks(&lstc1, &lstc2);
            if (rc)
                break;
        }
        else if (choise == 3)
            write_vstacks(&vstc1, &vstc2);
        else if (choise == 4)
        {
            rc = write_lstacks(&lstc1, &lstc2);
            if (rc)
                break;
        }
        else if (choise == 5)
        {
            printf("1 stack list free spaces");
            write_free_spaces(lstc1);
            printf("2 stack list free spaces");
            write_free_spaces(lstc2);
        }
        else if (choise == 6)
        {
            rc = push_to_any_stack(&vstc1, &vstc2, &lstc1, &lstc2);
            if (rc == MEM_ER)
                break;
        }
        else if (choise == 7)
        {
            rc = pop_from_any_stack(&vstc1, &vstc2, &lstc1, &lstc2);
            if (rc == MEM_ER)
                break;
        }
        else if (choise == 8)
        {
            rc = sort_2_stacks(&vstc1, &vstc2, &vstc_res, vpush, vpop);
            if (rc)
                break;
            printf("vector stacks\n");
            write_vstack(&vstc_res);
        }
        else if (choise == 9)
        {
            rc = sort_2_stacks(&lstc1, &lstc2, &lstc_res, pushl, popl);
            if (rc)
                break;
            
            printf("list stacks\n");
            write_lstack(&lstc_res);
        }
        else if (choise == 10)
        {
            rc = time_table();
            if (rc)
                break;
        }
        //dev fitch
        else if (choise == 32)
        {
            rc = sort_1_stack(&vstc1, &vstc_res, vpush, vpop);
            if (rc)
                break;
            printf("vector stack\n");
            write_vstack(&vstc_res);
            rc = sort_1_stack(&lstc1, &lstc_res, pushl, popl);
            if (rc)
                break;
            printf("list stack\n");
            write_lstack(&lstc_res);
        }
        else if (choise == 33)
        {
            vstc2.ps = vstc2.alb - 1;
            rc = copy_vstack(&vstc2, vstc1);
            if (rc)
                return rc;
        }
        else if (choise == 34)
        {
            rc = copy_lstack(&lstc2, lstc1);
            if (rc)
                break;
        }

    }
    
    free_vstack(&vstc1);
    free_vstack(&vstc2);
    free_vstack(&vstc_res);
    free_lstack(&lstc1);
    free_lstack(&lstc2);
    free_lstack(&lstc_res);

    return rc;
}