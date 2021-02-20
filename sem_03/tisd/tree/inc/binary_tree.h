#ifndef BINARY_TREE
#define BINARY_TREE

#include <stdio.h>
#include <stdlib.h>
#include "tree_node.h"
#include "elem.h"

void free_tree(node_t *root);
int add_to_tree(node_t **root, elem_t elem);
int fread_tree(char *file_name, node_t **root);
void delete_from_tree(node_t **root, elem_t elem);
void search_in_tree(node_t *root, elem_t elem, size_t *comparisons, int *find);
int export_to_dot(node_t *root, char *file_dst, char *tree_name);

#endif //BINARY_TREE