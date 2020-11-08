#include <string.h>
#include "stack_list.h"
#include "exit_codes.h"
//#define DEBUG 1

#ifdef DEBUG
#define print_debug(fmt, ...) fprintf(stderr, __FILE__ " :%d " fmt, __LINE__, __VA_ARGS__)
#else
#define print_debug(fmt, ...)
#endif

void free_node(node_t *node)
{
    free(node);
}

void free_spaces_array(node_t **a, size_t *len)
{
//    for (size_t i = 0; i < len; i++)
//        free_node(a[i]);
    *len = 0;
    free(a);
}

void free_lstack(stack_list_t *stc)
{
    free_spaces_array(stc->free_spaces, &stc->spaces_alloc);
    while (stc->top)
    {
        node_t *next = stc->top->next;
        free_node(stc->top);
        stc->top = next;
    }
    lstack_init(stc);
}

void lstack_init(stack_list_t *stc)
{
    memset(stc, 0, sizeof(stack_list_t));
}

int alloc_node(node_t **dst)
{
    *dst = calloc(1, sizeof(node_t));
    if (!(*dst))
        return MEM_ER;
    
    return EXIT_SUCCESS;
}

int change_array_size(stack_list_t *stc, size_t new_size)
{
    node_t **buf = realloc(stc->free_spaces, new_size * sizeof(node_t *));
    if (!buf)
        return MEM_ER;
    
    stc->free_spaces = buf;
    stc->spaces_alloc = new_size;

    return EXIT_SUCCESS;
}

void push_el(stack_list_t *stc, node_t *node, elem_t elem)
{
    node->next = stc->top;
    node->value = elem;
    stc->top = node;
}

int pushl(void *stc, elem_t elem)
{
    print_debug("push - %ld\n", elem);
    stack_list_t *lstc = (stack_list_t *) stc;
//    if (lstc->spaces_len)
//    {
//        push_el(lstc, lstc->free_spaces[lstc->spaces_len - 1], elem);
//        lstc->spaces_len -= 1;
//        return EXIT_SUCCESS;
//    }

    node_t *node = NULL;
    int rc = alloc_node(&node);
    if (rc)
        return rc;
    
    push_el(lstc, node, elem);

    return EXIT_SUCCESS;
}

int popl(void *stc, elem_t *elem)
{
    stack_list_t *lstc = (stack_list_t *) stc;
    if (!lstc->top)
        return POP_ER;
    
    *elem = lstc->top->value;
    if (lstc->spaces_len >= lstc->spaces_alloc)
    {
        int rc = change_array_size(lstc, lstc->spaces_alloc ? lstc->spaces_alloc * INC_SIZE : 1000);
        if (rc)
            return rc;
    }
    lstc->free_spaces[lstc->spaces_len] = lstc->top;
    lstc->spaces_len += 1;
    lstc->top = lstc->top->next;
    free_node(lstc->free_spaces[lstc->spaces_len - 1]);
    print_debug("pop - %ld\n", *elem);

    return EXIT_SUCCESS;
}

int read_lstack(stack_list_t *stc)
{
    elem_t el;
    printf("Input element (to exit input any letter): ");
    while (scanf("%"EL_SC, &el) == 1)
    {
        int rc = pushl(stc, el);
        if (rc)
            return rc;
        printf("Input element (to exit input any letter): ");
    }
    
    return EXIT_SUCCESS;
}

void write_free_spaces(stack_list_t stc)
{
    for (size_t i = 0; i < stc.spaces_len; i++)
        printf("%p\n", (void *) stc.free_spaces[i]);
}

int write_lstack(stack_list_t *stc)
{
    elem_t el;
    int rc = popl(stc, &el);
    if (rc == POP_ER)
        printf("empty stack\n");
    else
    {
        printf("  stack   addres\n");
        while (rc != POP_ER)
        {
            if (rc == MEM_ER)
                return rc;
            printf("%7"EL_PR" %8p\n", el, (void *) (stc->free_spaces[stc->spaces_len - 1]));
            rc = popl(stc, &el);
        }
    }

    return EXIT_SUCCESS;
}