#include <stdio.h>
#include <stdlib.h>
#include "abonent.h"
#include "abonents_table.h"
#include "date_time.h"
#include "read_funcs.h"

int main()
{
    setbuf(stdout, NULL);
    abonent_table_t table;
    size_t len;
    puts("This programm revises records with information about abonents.\n"
         "Record consists of\n -Surname\n -Name\n -Phone number\n -Addres\n -Staus(private or official)\n "
         "If status is private:\n -Birth date\n Else:\n -Post\n -Organization");

    int rc = fread_table(table, &len, "D:\\scripts\\TiSD\\abonents\\in.txt");
    if (rc)
    {
        if (rc == FOPEN_ER)
            puts("open error");
        else if (rc == EMPTY_ER)
            puts("empty file");
        else
            puts("wrong data");
        return rc;
    }
    abonent_key_table_t keys;
    size_t keys_len;
    create_abonent_key_table(table, len, keys, &keys_len);

    int choise = 10;
    while (choise)
    {
        printf("1 - write table\n"
               "2 - write keys\n"
               "3 - add abonent to the end\n"
               "4 - delete abonent by index\n"
               "5 - write abonents whose birthday will be in one week\n"
               "6 - buble sort table by surname\n"
               "7 - buble sort table by surname using table of keys\n"
               "8 - write effience of algoritms and methods\n"
               "9 - quick sort table by surname\n"
               "10 - quick sort table by surname using table of keys\n"
               "0 - exit\n"
               "Your choise: ");
        int rc = fread_signed_int(&choise, stdin);
        if (rc)
            continue;
        switch (choise)
        {
        case 1:
            fwrite_table(stdout, table, len);
            break;

        case 2:
            fwrite_key_table(stdout, keys, len);
            break;

        case 3:
            rc = add_element(table, &len, keys);
            if (rc)
                printf("Wrong input\n");
            break;

        case 4:;
            int index;
            printf("Input index: ");
            rc = fread_signed_int(&index, stdin);
            if (rc)
                printf("Wrong index\n");
            else
            {
                rc = del_abonent_by_index(table, &len, keys, index);
                if (rc)
                    printf("Wrong index\n");
            }
            break;

        case 5:;
            date_t current = current_date();
            abonent_table_t birthdays;
            size_t birthdays_len = 0;
            find_birthdays(birthdays, &birthdays_len, table, len, 7, current);
            fwrite_table(stdout, birthdays, birthdays_len);
            break;

        case 6:
            buble_sort(table, len);
            create_abonent_key_table(table, len, keys, &keys_len);
            fwrite_table(stdout, table, len);
            break;

        case 7:
            buble_sort_by_keys(keys, len);
            fwrite_table_by_keys(stdout, table, len, keys);
            break;
        case 8:
            count_time(table, keys, len);
            break;
        case 9:
            quick_sort(table, 0, len - 1);
            create_abonent_key_table(table, len, keys, &keys_len);
            fwrite_table(stdout, table, len);
            break;
        case 10:
            quick_sort_by_keys(keys, 0, len - 1);
            fwrite_table_by_keys(stdout, table, len, keys);
            break;

        }
    }

    return EXIT_SUCCESS;
}
