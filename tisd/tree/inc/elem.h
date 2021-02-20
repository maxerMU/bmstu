#ifndef ELEM_H
#define ELEM_H

#include <stdio.h>
#include <stdlib.h>

#define EL_SC "%ld"
#define EL_PR "%ld"

typedef long elem_t;

void fwrite_elem(FILE *dst, elem_t src);
int fread_elem(FILE *src, elem_t *dst);
int add_to_file(char *file_name, elem_t elem);
int delete_from_file(char *file_name, elem_t key);
int search_in_file(char *file_name, elem_t elem, size_t *comparisons, int *find);
int fwrite_file(FILE *dst, char *file_name);

#endif //ELEM_H