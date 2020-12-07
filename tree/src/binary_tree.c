#include "binary_tree.h"
#include "exit_codes.h"

#define DEBUG 1

#ifdef DEBUG
#define print_debug(fmt, ...) fprintf(stderr, __FILE__ " :%d " fmt, __LINE__, __VA_ARGS__)
#else
#define print_debug(fmt, ...)
#endif

void post_apply(node_t *root, void (*func)(node_t *, void *), void *param)
{
    if (!root)
        return;
    
    post_apply(root->left, func, param);
    post_apply(root->right, func, param);

    func(root, param);
}

void pre_apply(node_t *root, void (*func)(node_t *, void *), void *param)
{
    if (!root)
        return;

    func(root, param);
    
    pre_apply(root->left, func, param);
    pre_apply(root->right, func, param);
}

void free_tree(node_t *root)
{
    post_apply(root, free_node, NULL);
}

int add_to_tree(node_t **root, elem_t elem)
{
    if (!(*root))
    {
        node_t *node = create_node();
        if (!node)
            return MEM_ER;
        node->data = elem;
        *root = node;
    }
    else if (elem > (*root)->data)
        return add_to_tree(&(*root)->right, elem);
    else if (elem < (*root)->data)
        return add_to_tree(&(*root)->left, elem);
    
    return EXIT_SUCCESS;
}

elem_t find_tree_min(node_t *root)
{
    if (!root->left)
        return root->data;
    
    return find_tree_min(root->left);
}

elem_t find_tree_max(node_t *root)
{
    if (!root->right)
        return root->data;
    
    return find_tree_min(root->right);
}

int fread_tree(char *file_name, node_t **root)
{
    FILE *f = fopen(file_name, "r");
    if (!f)
        return OPEN_ER;
    
    elem_t elem;
    while (!fread_elem(f, &elem))
    {
        int rc = add_to_tree(root, elem);
        if (rc)
        {
            fclose(f);
            return rc;
        }
    }

    fclose(f);
    
    return EXIT_SUCCESS;
}

void delete_from_tree(node_t **root, elem_t elem)
{
    if (!(*root))
        return;
    else if (elem > (*root)->data)
    {
        delete_from_tree(&(*root)->right, elem);
        return;
    }
    else if (elem < (*root)->data)
    {
        delete_from_tree(&(*root)->left, elem);
        return;
    }
    else
    {
        if (!(*root)->left && !(*root)->right)
        {
            free_node(*root, NULL);
            *root = NULL;
            return;
        }
        else if ((*root)->left && !(*root)->right)
        {
            node_t *node = *root;
            *root = (*root)->left;
            free_node(node, NULL);
        }
        else if (!(*root)->left && (*root)->right)
        {
            node_t *node = *root;
            *root = (*root)->right;
            free_node(node, NULL);
        }
        else
        {
            elem_t min = find_tree_min((*root)->right);
            (*root)->data = min;
            delete_from_tree(&(*root)->right, min);
        }
    }
}

void search_in_tree(node_t *root, elem_t elem, size_t *comparisons, int *find)
{
    *comparisons = 0;
    *find = 0;

    while (root && !(*find))
    {
        *comparisons += 1;
        if (root->data == elem)
            *find = 1;
        else if (root->data > elem)
            root = root->left;
        else
            root = root->right;
    }
}

int export_to_dot(node_t *root, char *file_dst, char *tree_name)
{
    FILE *f = fopen(file_dst, "w");
    if (!f)
        return OPEN_ER;

    fprintf(f, "digraph %s {\n", tree_name);

    pre_apply(root, to_dot, f);

    fprintf(f, "}\n");

    fclose(f);

    return EXIT_SUCCESS;
}