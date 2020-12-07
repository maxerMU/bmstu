#ifndef BALANCE_TREE_H
#define BALANCE_TREE_H

#include <stdio.h>
#include <stdlib.h>
#include "balance_node.h"

void free_btree(balance_node_t *root);
int add_to_btree(balance_node_t **root, elem_t elem);
int fread_btree(char *file_name, balance_node_t **root);
void delete_from_btree(balance_node_t **root, elem_t elem);
int bexport_to_dot(balance_node_t *root, char *file_dst, char *tree_name);
void search_in_btree(balance_node_t *root, elem_t elem, size_t *comparisons, int *find);

#endif //BALANCE_TREE_H