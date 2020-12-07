#include "elem.h"
#include "exit_codes.h"

int fread_elem(FILE *src, elem_t *dst)
{
    if (fscanf(src, EL_SC, dst) != 1)
        return READ_ER;
    
    return EXIT_SUCCESS;
}

void fwrite_elem(FILE *dst, elem_t src)
{
    fprintf(dst, EL_PR, src);
}

int fwrite_file(FILE *dst, char *file_name)
{
    FILE *f = fopen(file_name, "r");
    if (!f)
        return OPEN_ER;
    
    elem_t el;
    while (!fread_elem(f, &el))
    {
        fwrite_elem(dst, el);
        fprintf(dst, "\n");
    }
    
    fclose(f);
    
    return EXIT_SUCCESS;
}
int add_to_file(char *file_name, elem_t elem)
{
    FILE *f = fopen(file_name, "a+");
    if (!f)
        return OPEN_ER;

    elem_t el;
    while (!fread_elem(f, &el))
        if (el == elem)
            break;
    
    if (feof(f))
        fwrite_elem(f, elem);

    fclose(f);
    
    return EXIT_SUCCESS;
}

int search_in_file(char *file_name, elem_t elem, size_t *comparisons, int *find)
{
    FILE *f = fopen(file_name, "r");
    if (!f)
        return OPEN_ER;

    *comparisons = 0;
    *find = 0;
    elem_t el;
    while (!fread_elem(f, &el) && !(*find))
    {
        *comparisons += 1;
        if (el == elem)
            *find = 1;
    }

    fclose(f);

    return EXIT_SUCCESS;
}

int delete_from_file(char *file_name, elem_t key)
{
    FILE *f = fopen(file_name, "r");
    if (!f)
      return OPEN_ER;
  
    FILE *temp = fopen("temp.txt", "w");
    if (!temp)
    {
        fclose(f);
        return OPEN_ER;
    }
  
    elem_t buf;
    while (fscanf(f, "%ld", &buf) == 1)
    {
        if (buf != key)
            fprintf(temp, "%ld\n", buf);
    }
    
    fclose(f);
    fclose(temp);
  
    remove(file_name);
    rename("temp.txt", file_name);

    return EXIT_SUCCESS;
}