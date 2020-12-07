#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stdio.h>
#include <stdlib.h>
#include "elem.h"

typedef double func_const_t;

typedef size_t (*hash_func_t) (elem_t, func_const_t, size_t);
typedef func_const_t (*gen_const_func_t) (void);

typedef enum FIELD_TYPE
{
    DELETED = -1,
    EMPTY   =  0,
    USE     =  1
}field_type_t;

typedef struct
{
    elem_t elem;
    field_type_t field_type;
}field_t;

typedef struct
{
    field_t *table;
    size_t size;
    func_const_t func_const;
    hash_func_t hash_func;
}hash_table_t;

int create_table(hash_table_t *table, size_t size, hash_func_t h_func, gen_const_func_t gen_const);
void free_table(hash_table_t *table);
func_const_t gen_f0_t1();
size_t func_mlt(elem_t elem, func_const_t c, size_t size);
size_t func_mod(elem_t elem, func_const_t c, size_t size);
int add_to_table(hash_table_t *table, elem_t elem);
int fread_table(char *file_name, hash_table_t *table);
void delete_from_table(hash_table_t *table, elem_t elem);
double count_avg_comparisons(hash_table_t table);
int restruct_table(hash_table_t *table, hash_func_t h_func, gen_const_func_t gen_const);
void search_in_table(hash_table_t table, elem_t elem, size_t *comparisons, int *find);
void write_table(FILE *dst, hash_table_t table);

#endif //HASH_TABLE_H