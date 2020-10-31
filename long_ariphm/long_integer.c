#include "long_integer.h"

void create_li(long_integer_t *dst)
{
    memset(dst->mantissa, 0, INT_LEN * sizeof (int));
    dst->sign = 0;
    dst->mean_start = 0;
}

int read_li(long_integer_t *dst)
{
    printf("Input integer: ");
    create_li(dst);
    char mantissa_input[INT_LEN];
    int l = 0, ch = getchar();
    dst->sign = 0;
    if (ch == '-')
        dst->sign = 1;
    else if (isdigit(ch))
        mantissa_input[l++] = ch;
    else if (ch != '+')
        return INT_ER;
    for (ch = getchar(); ch != '\n'; ch = getchar())
    {
        if (l == INT_LEN || !isdigit(ch))
            return INT_ER;
        else
            mantissa_input[l++] = ch;
    }
    char buf[2];
    buf[1] = '\0';
    for (int i = 0; i < l; i++)
    {
        buf[0] = mantissa_input[l - i - 1];
        dst->mantissa[INT_LEN - i - 1] = atoi(buf);
    }
    for (dst->mean_start = 0; dst->mean_start < INT_LEN && !dst->mantissa[dst->mean_start]; dst->mean_start += 1);

    return EXIT_SUCCESS;
}

void write_li(long_integer_t src)
{
    if (src.sign)
        printf("-");
    for (int i = src.mean_start; i < INT_LEN; i++)
        printf("%d", src.mantissa[i]);
    printf("\n");
}
