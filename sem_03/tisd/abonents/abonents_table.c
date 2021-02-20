#include "abonents_table.h"

int fread_table(abonent_table_t table, size_t *len, char *file_name)
{
    FILE *src = fopen(file_name, "r");
    int rc = EXIT_SUCCESS;
    if (src)
    {
        *len = 0;
        while(!fread_abonent(&table[*len], src))
            (*len)++;
        if (!(*len))
            rc = EMPTY_FILE_ER;
        else
        {
            for (int ch = fgetc(src); isspace(ch); ch = fgetc(src));
            if (!feof(src))
                rc = WRONG_FILE_ER;
        }
        fclose(src);
    }
    else
        return FOPEN_ER;

    return rc;
}

void fwrite_table(FILE *dst, abonent_table_t table, size_t len)
{
    for (size_t i = 0; i < len; i++)
    {
        fprintf(dst, "%5zu", i);
        fwrite_abonent(dst, table[i]);
    }
}

void find_birthdays(abonent_table_t dst, size_t *dst_len, abonent_table_t src, size_t src_len, int day_diff, date_t current)
{
    *dst_len = 0;
    for (size_t i = 0; i < src_len; i++)
        if (src[i].status == PRIVATE)
        {
            int year = src[i].extra_inf.birh_date.year;
            src[i].extra_inf.birh_date.year = current.year;
            int diff = dates_diff(current, src[i].extra_inf.birh_date);
            src[i].extra_inf.birh_date.year = year;
            if (diff >= 0 && diff <= day_diff)
                abonent_copy(&dst[(*dst_len)++], src[i]);
        }
}

void buble_sort(abonent_table_t a, size_t len)
{
    for (size_t i = 0; i < len; i++)
        for (size_t j = 0; j < len - i - 1; j++)
            if (strcmp(a[j].surname, a[j+1].surname) > 0)
                abonent_swap(&a[j], &a[j + 1]);
}

void quick_sort(abonent_table_t a, long begin, long end)
{
    long left = begin, right = end;
    abonent_t mid = a[(right + left) / 2];
    while (left <= right)
    {

        while (strcmp(a[left].surname, mid.surname) < 0) left++;
        while (strcmp(a[right].surname, mid.surname) > 0) right--;
        if (left <= right)
        {
            abonent_t temp;
            abonent_copy(&temp, a[left]);
            abonent_copy(&a[left], a[right]);
            abonent_copy(&a[right], temp);
            left++, right--;
        }
    }
    if (right > begin)
        quick_sort(a, begin, right);
    if (left < end)
        quick_sort(a, left, end);
}

void create_abonent_key_table(abonent_table_t abonents, size_t len_table, abonent_key_table_t keys, size_t *keys_len)
{
    *keys_len = 0;
    for (size_t i = 0; i < len_table; i++)
    {
        keys[i].index = i;
        strcpy(keys[i].key, abonents[i].surname);
        (*keys_len)++;
    }
}

void fwrite_key_table(FILE *dst, abonent_key_table_t keys, size_t len)
{
    for (size_t i = 0; i < len; i++)
        fprintf(dst, "%zu %s\n", keys[i].index, keys[i].key);
}

void fwrite_table_by_keys(FILE *dst, abonent_table_t abonents, size_t len_table, abonent_key_table_t keys)
{
    for (size_t i = 0; i < len_table; i++)
    {
        fprintf(dst, "%5zu", i);
        fwrite_abonent(dst, abonents[keys[i].index]);
    }
}

void keys_copy(abonent_key_t *dst, abonent_key_t src)
{
    strcpy(dst->key, src.key);
    dst->index = src.index;
}

void swap_keys(abonent_key_t *key1, abonent_key_t *key2)
{
    abonent_key_t temp;
    temp.index = key1->index;
    strcpy(temp.key, key1->key);
    key1->index = key2->index;
    strcpy(key1->key, key2->key);
    key2->index = temp.index;
    strcpy(key2->key, temp.key);
}

void buble_sort_by_keys(abonent_key_table_t keys, size_t len)
{
    for (size_t i = 0; i < len; i++)
        for (size_t j = 0; j < len - i - 1; j++)
            if (strcmp(keys[j].key, keys[j+1].key) > 0)
                swap_keys(&keys[j], &keys[j + 1]);
}

void quick_sort_by_keys(abonent_key_table_t keys, long begin, long end)
{
    long left = begin, right = end;
    abonent_key_t mid = keys[(right + left) / 2];
    while (left <= right)
    {

        while (strcmp(keys[left].key, mid.key) < 0) left++;
        while (strcmp(keys[right].key, mid.key) > 0) right--;
        if (left <= right)
        {
            swap_keys(&keys[left], &keys[right]);
            left++, right--;
        }
    }
    if (right > begin)
        quick_sort_by_keys(keys, begin, right);
    if (left < end)
        quick_sort_by_keys(keys, left, end);
}

int add_element(abonent_table_t table, size_t *len_table, abonent_key_table_t keys)
{
    if (*len_table >= TABLE_LEN - 1)
        return TABLE_OVFL_ER;
    abonent_t el;
    int rc = read_abonent(&el);
    if (rc)
        return rc;
    strcpy(keys[*len_table].key, el.surname);
    keys[*len_table].index = *len_table - 1;
    abonent_copy(&table[(*len_table)++], el);

    return EXIT_SUCCESS;
}

int del_abonent_by_index(abonent_table_t table, size_t *len, abonent_key_table_t keys, size_t index)
{
    if (index >= *len)
        return INDEX_ER;

    for (size_t i = index; i < *len - 1; i++)
        abonent_copy(&table[i], table[i + 1]);

    size_t key_pos = 0;
    for (size_t i = 0; i < *len; i++)
        if (keys[i].index == index)
        {
            key_pos = i;
            break;

        }
    for (size_t i = key_pos; i < *len - 1; i++)
        keys_copy(&keys[i], keys[i + 1]);

    for (size_t i = 0; i < *(len); i++)
        if (keys[i].index > index)
            keys[i].index--;
    (*len)--;

    return EXIT_SUCCESS;
}

void abonents_table_copy(abonent_table_t dst, abonent_table_t src, size_t len)
{
    for (size_t i = 0; i < len; i++)
        abonent_copy(&dst[i], src[i]);
}

void keys_table_copy(abonent_key_table_t dst, abonent_key_table_t src, size_t len)
{
    for (size_t i = 0; i < len; i++)
        keys_copy(&dst[i], src[i]);
}

void count_time(abonent_table_t abonents, abonent_key_table_t keys, size_t len)
{
    clock_t buble, buble_keys, quick, quick_keys, copy;
    double buble_time, buble_keys_time, quick_time, quick_keys_time, copy_time;
    abonent_table_t abonets_copy;
    abonent_key_table_t keys_copy;

    copy = clock();
    for (size_t i = 0; i < TIME_ITERATIONS; i++)
    {
        abonents_table_copy(abonets_copy, abonents, len);
        keys_table_copy(keys_copy, keys, len);
    }
    copy = clock() - copy;
    copy_time = ((double)copy / CLOCKS_PER_SEC) / TIME_ITERATIONS;

    buble = clock();
    for (size_t i = 0; i < TIME_ITERATIONS; i++)
    {
        abonents_table_copy(abonets_copy, abonents, len);
        keys_table_copy(keys_copy, keys, len);
        buble_sort(abonets_copy, len);
    }
    buble = clock() - buble;
    buble_time = ((double) buble / CLOCKS_PER_SEC - copy_time) / TIME_ITERATIONS;

    quick = clock();
    for (size_t i = 0; i < TIME_ITERATIONS; i++)
    {
        abonents_table_copy(abonets_copy, abonents, len);
        keys_table_copy(keys_copy, keys, len);
        quick_sort(abonets_copy, 0, len - 1);
    }
    quick = clock() - quick;
    quick_time = ((double) quick / CLOCKS_PER_SEC - copy_time) / TIME_ITERATIONS;

    buble_keys = clock();
    for (size_t i = 0; i < TIME_ITERATIONS; i++)
    {
        abonents_table_copy(abonets_copy, abonents, len);
        keys_table_copy(keys_copy, keys, len);
        buble_sort_by_keys(keys, len);
    }
    buble_keys = clock() - buble_keys;
    buble_keys_time = ((double) buble_keys / CLOCKS_PER_SEC - copy_time) / TIME_ITERATIONS;

    quick_keys = clock();
    for (size_t i = 0; i < TIME_ITERATIONS; i++)
    {
        abonents_table_copy(abonets_copy, abonents, len);
        keys_table_copy(keys_copy, keys, len);
        quick_sort_by_keys(keys_copy, 0, len);
    }
    quick_keys = clock() - quick_keys;
    quick_keys_time = ((double) quick_keys / CLOCKS_PER_SEC - copy_time) / TIME_ITERATIONS;

    printf("%6s %9s %9s\n", "", "buble", "quick");
    printf("%6s %7lfs %7lfs\n", "table", buble_time, quick_time);
    printf("%6s %7lfs %7lfs\n", "keys", buble_keys_time, quick_keys_time);
    printf("buble by keys / buble = %7lf\n", buble_keys_time / buble_time);
    printf("quick by keys / quick = %7lf\n", quick_keys_time / quick_time);
    printf("quick / buble = %7lf\n", quick_time / buble_time);
    printf("quick by keys / buble by keys = %7lf\n", quick_keys_time / buble_keys_time);
}
