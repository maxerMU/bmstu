#include "balance_node.h"
#include "exit_codes.h"

balance_node_t *create_bnode()
{
    balance_node_t *node = malloc(sizeof(balance_node_t));
    
    if (node)
    {
        node->height = 0;
        node->left = NULL;
        node->right = NULL;
    }

    return node;
}

void free_bnode(balance_node_t *node, void *param)
{
    free(node);
}

unsigned char height(balance_node_t *node)
{
    return node ? node->height : 0;
}

int bfactor(balance_node_t *node)
{
    return height(node->right) - height(node->left);
}

void fix_height(balance_node_t *node)
{
    unsigned char hl = height(node->left);
    unsigned char hr = height(node->right);
    node->height = (hl > hr ? hl : hr) + 1;
}

void bto_dot(balance_node_t *node, void *file)
{
    if (node->left)
        fprintf((FILE *) file, EL_PR " -> " EL_PR "\n", node->data, node->left->data);
    if (node->right)
        fprintf((FILE *) file, EL_PR " -> " EL_PR "\n", node->data, node->right->data);
    
    if (!node->left && !node->right)
        fprintf((FILE *) file, EL_PR "\n", node->data);
}