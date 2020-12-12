#include <math.h>
#include <string.h>
#include "hash_table.h"
#include "exit_codes.h"

int is_prime(size_t n)
{
    if (n <= 1)
        return 0;
    size_t i;
    i = 2;
    while (i < n / 2 + 1)
    {
        if (n % i == 0)
            return 0;
        i++;
    }
    return 1;
}

size_t find_next_prime(size_t n)
{
    size_t next = n + 2;
    for (; !is_prime(next); next++);
    return next;
}

int create_table(hash_table_t *table, size_t size, hash_func_t h_func, gen_const_func_t gen_const)
{
    table->table = calloc(size, sizeof(field_t));
    if (!table->table)
        return MEM_ER;
    
    table->size = size;
    
    if (gen_const)
        table->func_const = gen_const();
    
    table->hash_func = h_func;

    return EXIT_SUCCESS;
}

void free_table(hash_table_t *table)
{
    free(table->table);
    memset(table, 0, sizeof(hash_table_t));
}

func_const_t gen_f0_t1()
{
    return (double) rand() / RAND_MAX;
}

size_t func_mlt(elem_t elem, func_const_t c, size_t size)
{
    double fraction_part;
    double int_part;
    fraction_part = modf(fabs(elem * c), &int_part);

    return floor(fraction_part * size);
}

size_t func_mod(elem_t elem, func_const_t c, size_t size)
{
    return elem % size;
}

size_t get_table_next(hash_table_t table, size_t cur_pos)
{
    if (cur_pos + 1 >= table.size)
        return 0;
    
    return cur_pos + 1;
}

size_t get_table_prev(hash_table_t table, size_t cur_pos)
{
    if (cur_pos == 0)
        return table.size - 1;
    
    return cur_pos - 1;
}

int add_to_table(hash_table_t *table, elem_t elem)
{
    size_t pos = table->hash_func(elem, table->func_const, table->size);
    size_t looked = 0;
    while (table->table[pos].field_type == USE && looked < table->size)
    {
        looked++;
        pos++;
        pos %= table->size;
    }
    if (looked == table->size)
        return TABLE_OVR;
    
    table->table[pos].elem = elem;
    table->table[pos].field_type = USE;

    return EXIT_SUCCESS;
}

int fread_table(char *file_name, hash_table_t *table)
{
    FILE *f = fopen(file_name, "r");
    if (!f)
        return OPEN_ER;
    
    elem_t elem;
    while (!fread_elem(f, &elem))
    {
        int rc = add_to_table(table, elem);
        if (rc)
        {
            fclose(f);
            return rc;
        }
    }

    fclose(f);
    
    return EXIT_SUCCESS;
}

void delete_from_table(hash_table_t *table, elem_t elem)
{
    size_t pos = table->hash_func(elem, table->func_const, table->size);
    size_t looked = 0;
    while (table->table[pos].field_type != EMPTY && looked < table->size)
    {
        if (table->table[pos].field_type == USE)
        {
            if (elem == table->table[pos].elem)
                table->table[pos].field_type = DELETED;
        }
        looked++;
        pos = get_table_next(*table, pos);
    }
}

double count_avg_comparisons(hash_table_t table)
{
    size_t comparisons = 0, elems = 0;
    for (size_t i = 0; i < table.size; i++)
        if (table.table[i].field_type == USE)
        {
            size_t cur_cmp;
            int find;
            search_in_table(table, table.table[i].elem, &cur_cmp, &find);
            comparisons += cur_cmp;
            elems++;
        }
    
    return elems ? (double) comparisons / elems : 0;
}

int restruct_table(hash_table_t *table, hash_func_t h_func, gen_const_func_t gen_const)
{
    hash_table_t temp;
    int rc = create_table(&temp, find_next_prime(table->size), h_func, gen_const);
    if (rc)
        return rc;
    
    for (size_t i = 0; i < table->size; i++)
        if (table->table[i].field_type == USE)
            add_to_table(&temp, table->table[i].elem);
    
    free_table(table);

    *table = temp;

    return EXIT_SUCCESS;
}

void search_in_table(hash_table_t table, elem_t elem, size_t *comparisons, int *find)
{
    size_t pos = table.hash_func(elem, table.func_const, table.size);
    *comparisons = 0;
    *find = 0;
    size_t looked = 0;
    while (table.table[pos].field_type != EMPTY && looked < table.size && !*find)
    {
        if (table.table[pos].field_type == USE)
        {
            *comparisons += 1;
            if (elem == table.table[pos].elem)
                *find = 1;
        }
        looked++;
        pos++;
        pos = pos % table.size;
    }
}

//not universal
void write_table(FILE *dst, hash_table_t table)
{
    fprintf(dst, "| index | value | state |\n");
    for (size_t i = 0; i < table.size; i++)
        fprintf(dst, "|%7zu|%7ld|%7d|\n", i, table.table[i].elem, table.table[i].field_type);
}