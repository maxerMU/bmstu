#include <string.h>
#include "stack_vector.h"
#include "exit_codes.h"

void init_vstack(stack_vector_t *stc)
{
    memset(stc, 0, sizeof(stack_vector_t));
}

int allocate_vstack(stack_vector_t *stc, size_t n)
{
    stc->alb = malloc(n * sizeof(elem_t));
    if (!stc->alb)
        return MEM_ER;
    
    stc->aub = stc->alb + n;
    stc->ps = stc->alb - 1;

    return EXIT_SUCCESS;
}

void free_vstack(stack_vector_t *stc)
{
    free(stc->alb);
    memset(stc, 0, sizeof(*stc));
}

int vpush(void *stc, elem_t elem)
{
    stack_vector_t *vstc = (stack_vector_t *) stc;
    vstc->ps += 1;
    if (vstc->ps >= vstc->aub)
        return PUSH_ER;
    
    *(vstc->ps) = elem;

    return EXIT_SUCCESS;
}

int vpop(void *stc, elem_t *elem)
{
    stack_vector_t *vstc = (stack_vector_t *) stc;
    if (vstc->ps < vstc->alb)
        return POP_ER;
    
    *elem = *(vstc->ps);
    vstc->ps -= 1;

    return EXIT_SUCCESS;
}

int read_vstack(stack_vector_t *stc)
{
    long n;
    printf("Input max stack size\n");
    if (scanf("%ld", &n) != 1 || n <= 0)
        return INPUT_ER;
    
    int rc = allocate_vstack(stc, n);
    if (rc)
        return rc;
    
    while (!rc)
    {
        printf("Input el (to exit input any letter): ");
        elem_t el;
        if (scanf("%"EL_SC, &el) != 1)
            return EXIT_SUCCESS;
        rc = vpush(stc, el);
    }

    return rc;
}

void write_vstack(stack_vector_t *stc)
{
    elem_t el;
    int rc = vpop(stc, &el);
    if (rc)
        printf("empty stack\n");
    else    
    {
        printf("  stack   addres\n");
        while (!rc)
        {
            printf("%7"EL_PR" %8p\n", el, (void *) (stc->ps + 1));
            rc = vpop(stc, &el);
        }
    }
}