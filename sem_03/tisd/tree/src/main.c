#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "binary_tree.h"
#include "balance_tree.h"
#include "hash_table.h"
#include "elem.h"
#include "exit_codes.h"
#include "statistic.h"

#define INPUT_FILE "input.txt"
#define VIZ_TREE "viz/tree.gv"

int work_with_file()
{
    int choise = 10;
    while (choise)
    {
        printf("\n1 - add element to file\n"
               "2 - search element in file\n"
               "3 - delete from file\n"
               "4 - write file\n"
               "0 - exit\n"
               "your choise: ");
        scanf("%d", &choise);
        if (choise == 1)
        {
            elem_t elem;
            printf("input element: ");
            int rc = fread_elem(stdin, &elem);
            if (rc)
            {
                printf("Incorrect elemen\n");
                continue;
            }
            rc = add_to_file(INPUT_FILE, elem);
            assert(!rc);
        }
        else if (choise == 2)
        {
            elem_t elem;
            printf("input element: ");
            int rc = fread_elem(stdin, &elem);
            if (rc)
            {
                printf("Incorrect elemen\n");
                continue;
            }
            size_t comparisons = 0;
            int found;
            rc = search_in_file(INPUT_FILE, elem, &comparisons, &found);
            assert(!rc);
            if (found)
                printf("Element " EL_PR " was found with %zu comparisons\n", elem, comparisons);
            else
                printf("Not found.\n");
        }
        if (choise == 3)
        {
            elem_t elem;
            printf("input element: ");
            int rc = fread_elem(stdin, &elem);
            if (rc)
            {
                printf("Incorrect elemen\n");
                continue;
            }
            delete_from_file(INPUT_FILE, elem);
        }
        else if (choise == 4)
        {
            int rc = fwrite_file(stdout, INPUT_FILE);
            assert(!rc);
        }

    }
    
    return EXIT_SUCCESS;
}

int work_with_binary_tree()
{
    int choise = 10;
    node_t *root = NULL;
    while (choise)
    {
        printf("\n1 - add element to tree\n"
               "2 - search element in tree\n"
               "3 - delete element from tree\n"
               "4 - write tree\n"
               "0 - exit\n"
               "your choise: ");
        scanf("%d", &choise);
        if (choise == 1)
        {
            elem_t elem;
            printf("input element: ");
            int rc = fread_elem(stdin, &elem);
            if (rc)
            {
                printf("Incorrect elemen\n");
                continue;
            }
            rc = add_to_tree(&root, elem);
            assert(!rc);
        }
        else if (choise == 2)
        {
            elem_t elem;
            printf("input element: ");
            if (fread_elem(stdin, &elem))
            {
                printf("Incorrect elemen\n");
                continue;
            }
            size_t comparisons = 0;
            int found;
            search_in_tree(root, elem, &comparisons, &found);
            if (found)
                printf("Element " EL_PR " was found with %zu comparisons\n", elem, comparisons);
            else
                printf("Not found.\n");
        }
        if (choise == 3)
        {
            elem_t elem;
            printf("input element: ");
            int rc = fread_elem(stdin, &elem);
            if (rc)
            {
                printf("Incorrect elemen\n");
                continue;
            }
            delete_from_tree(&root, elem);
        }
        else if (choise == 4)
        {
            export_to_dot(root, VIZ_TREE, "tree");
            system("dot -Tpng viz/tree.gv -o viz/tree.png && libreoffice --draw viz/tree.png");
        }
    }

    free_tree(root);

    return EXIT_SUCCESS;
}

int work_with_balance_tree()
{
    int choise = 10;
    balance_node_t *root = NULL;
    while (choise)
    {
        printf("\n1 - add element to tree\n"
               "2 - search element in tree\n"
               "3 - delete element from tree\n"
               "4 - write tree\n"
               "0 - exit\n"
               "your choise: ");
        scanf("%d", &choise);
        if (choise == 1)
        {
            elem_t elem;
            printf("input element: ");
            int rc = fread_elem(stdin, &elem);
            if (rc)
            {
                printf("Incorrect elemen\n");
                continue;
            }
            rc = add_to_btree(&root, elem);
            assert(!rc);
        }
        else if (choise == 2)
        {
            elem_t elem;
            printf("input element: ");
            if (fread_elem(stdin, &elem))
            {
                printf("Incorrect elemen\n");
                continue;
            }
            size_t comparisons = 0;
            int found;
            search_in_btree(root, elem, &comparisons, &found);
            if (found)
                printf("Element " EL_PR " was found with %zu comparisons\n", elem, comparisons);
            else
                printf("Not found.\n");
        }
        if (choise == 3)
        {
            elem_t elem;
            printf("input element: ");
            int rc = fread_elem(stdin, &elem);
            if (rc)
            {
                printf("Incorrect elemen\n");
                continue;
            }
            delete_from_btree(&root, elem);
        }
        else if (choise == 4)
        {
            bexport_to_dot(root, VIZ_TREE, "tree");
            system("dot -Tpng viz/tree.gv -o viz/tree.png && libreoffice --draw viz/tree.png");
        }
        else if (choise == 5)
            fread_btree(FILE_NAME, &root);
    }

    free_btree(root);

    return EXIT_SUCCESS;
}

int work_with_hash_table()
{
    printf("Input table size: \n");
    size_t size;
    if (scanf("%zu", &size) != 1)
        return EXIT_FAILURE;
    printf("Input table max avg comparisons: \n");
    double max_avg_cmp;
    if (scanf("%lf", &max_avg_cmp) != 1)
        return EXIT_FAILURE;
    hash_table_t table;
    int rc = create_table(&table, size, func_mod, NULL);
    if (rc)
    {
        printf("can't create table\n");
        return rc;
    }
    int choise = 10;
    while (choise)
    {
        printf("\n1 - add element to table\n"
               "2 - search element in table\n"
               "3 - delete element from table\n"
               "4 - count avg comparisons\n"
               "5 - write table\n"
               "0 - exit\n"
               "your choise: ");
        scanf("%d", &choise);
        if (choise == 1)
        {
            elem_t elem;
            printf("input element: ");
            int rc = fread_elem(stdin, &elem);
            if (rc)
            {
                printf("Incorrect elemen\n");
                continue;
            }
            rc = add_to_table(&table, elem);
            if (rc)
            {
                printf("Table overflow\n");
                break;
            }
            while (count_avg_comparisons(table) > max_avg_cmp)
            {
                int rc = restruct_table(&table, func_mod, NULL);
                if (rc)
                    break;
            }
        }
        else if (choise == 2)
        {
            elem_t elem;
            printf("input element: ");
            if (fread_elem(stdin, &elem))
            {
                printf("Incorrect elemen\n");
                continue;
            }
            size_t comparisons = 0;
            int found;
            search_in_table(table, elem, &comparisons, &found);
            if (found)
                printf("Element " EL_PR " was found with %zu comparisons\n", elem, comparisons);
            else
                printf("Not found.\n");
        }
        if (choise == 3)
        {
            elem_t elem;
            printf("input element: ");
            int rc = fread_elem(stdin, &elem);
            if (rc)
            {
                printf("Incorrect elemen\n");
                continue;
            }
            delete_from_table(&table, elem);
        }
        else if (choise == 4)
        {
            printf("average comparosons - %lf\n", count_avg_comparisons(table));
        }
        else if (choise == 5)
        {
            // printf("funct const - %lf\n", table.func_const);
            write_table(stdout, table);
        }
    }

    free_table(&table);

    return EXIT_SUCCESS;
}


int main(void)
{
    int choise = 10;
    while (choise)
    {
        printf("\n1 - work with file\n"
               "2 - work with binary tree\n"
               "3 - work with balance tree\n"
               "4 - work with hash table\n"
               "5 - compare effiences\n"
               "0 - exit\n"
               "Your choise: ");
        if (scanf("%d", &choise) != 1)
            continue;
        if (choise == 1)
            work_with_file();
        else if (choise == 2)
            work_with_binary_tree();
        else if (choise == 3)
            work_with_balance_tree();
        else if (choise == 4)
            work_with_hash_table();
        else if (choise == 5)
            all_stat();
    }

    return EXIT_SUCCESS;
}