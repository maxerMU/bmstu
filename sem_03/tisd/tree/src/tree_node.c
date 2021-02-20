#include "exit_codes.h"
#include "tree_node.h"

node_t *create_node()
{
    node_t *node = malloc(sizeof(node_t));
    
    if (node)
    {
        node->left = NULL;
        node->right = NULL;
    }

    return node;
}

void free_node(node_t *node, void *param)
{
    free(node);
}

void to_dot(node_t *node, void *file)
{
    if (node->left)
        fprintf((FILE *) file, EL_PR " -> " EL_PR "\n", node->data, node->left->data);
    if (node->right)
        fprintf((FILE *) file, EL_PR " -> " EL_PR "\n", node->data, node->right->data);
    
    if (!node->left && !node->right)
        fprintf((FILE *) file, EL_PR "\n", node->data);
}