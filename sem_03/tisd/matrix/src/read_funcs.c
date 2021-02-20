#include "read_funcs.h"

int fread_signed_int(int *dst, FILE *src)
{
    int ch, digit, x = 0;
    enum bool_t
    {
        FALSE,
        TRUE
    } negative = FALSE, sign = FALSE;
    size_t size = 0;

    ch = fgetc(src);
    while (isspace(ch))
        ch = fgetc(src);

    while (ch != EOF && !isspace(ch))
    {
        if ((ch == '-' || ch == '+') && !sign)
        {
            if (ch == '-')
                negative = TRUE;
            sign = TRUE;
        }
        else
        {
            if (isdigit(ch))
            {
                digit = ch - '0';
                if ((INT_MAX - digit + negative) / 10.0 < x)
                    return OVERFLOW_ER;
                x = 10 * x + digit;
                size++;
            }
            else
                return NDIGIT_ER;
        }
        ch = fgetc(src);
    }

    if (!size)
        return EMPTY_ER;
    *dst = x * (1 - 2 * negative);
    return EXIT_SUCCESS;
}

int fread_str(FILE *src, char *buf, size_t buf_size, char *sep)
{
    int ch = fgetc(src);
    size_t read = 0;
    for (; strchr(sep, ch) && ch != EOF; ch = fgetc(src));
    for (; !strchr(sep, ch) && ch != EOF; ch = fgetc(src))
        if (read < buf_size - 1)
            buf[read++] = ch;
        else
            return OVERFLOW_ER;

    if (!read)
        return EMPTY_ER;

    for (size_t i = read; i < buf_size; i++)
        buf[i] = '\0';

    return EXIT_SUCCESS;
}
