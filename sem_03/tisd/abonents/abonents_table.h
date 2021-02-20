#ifndef ABONENTS_TABLE_H
#define ABONENTS_TABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include "abonent.h"

#define EMPTY_FILE_ER 40
#define WRONG_FILE_ER 41
#define FOPEN_ER 42
#define TABLE_OVFL_ER 43
#define INDEX_ER 44

#define TIME_ITERATIONS 1000
#define TABLE_LEN 5000

typedef abonent_t abonent_table_t[TABLE_LEN];

typedef struct
{
    size_t index;
    char key[SURNAME_LEN + 1];
}abonent_key_t;

typedef abonent_key_t abonent_key_table_t[TABLE_LEN];

int fread_table(abonent_table_t table, size_t *len, char *file_name);
void fwrite_table(FILE *dst, abonent_table_t table, size_t len);
void find_birthdays(abonent_table_t dst, size_t *dst_len, abonent_table_t src, size_t src_len, int day_diff, date_t current);
void buble_sort(abonent_table_t a, size_t len);
void quick_sort(abonent_table_t a, long left, long right);
void create_abonent_key_table(abonent_table_t abonents, size_t len_table, abonent_key_table_t keys, size_t *keys_len);
void fwrite_key_table(FILE *dst, abonent_key_table_t keys, size_t len);
void fwrite_table_by_keys(FILE *dst, abonent_table_t abonents, size_t len_table, abonent_key_table_t keys);
void buble_sort_by_keys(abonent_key_table_t keys, size_t len);
void quick_sort_by_keys(abonent_key_table_t keys, long begin, long end);
int add_element(abonent_table_t table, size_t *len_table, abonent_key_table_t keys);
int del_abonent_by_index(abonent_table_t table, size_t *len, abonent_key_table_t keys, size_t index);
void count_time(abonent_table_t abonents, abonent_key_table_t keys, size_t len);

#endif // ABONENTS_TABLE_H
