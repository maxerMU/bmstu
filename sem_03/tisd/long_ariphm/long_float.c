#include "long_float.h"

void create_lf(long_float_t *dst)
{
    memset(dst->mantissa, 0, MANTISSA_LEN * sizeof (int));
    dst->exp = 0;
    dst->mean_start = 0;
    dst->mantissa_exp = 0;
    dst->mantissa_sign = 0;
}

int read_mantissa(long_float_t *dst)
{
    printf("                "
           "012345678901234567890123456789\n");
    printf("Input mantissa: ");
    char mantissa_input[MANTISSA_LEN];
    int l = 0, point_pos = -1, ch = getchar();
    dst->mantissa_sign = 0;
    if (ch == '-')
        dst->mantissa_sign = 1;
    else if (ch == '.')
        point_pos = 0;
    else if (isdigit(ch))
        mantissa_input[l++] = ch;
    else if (ch != '+')
        return MANTISSA_ER;
    for (ch = getchar(); ch != '\n'; ch = getchar())
    {
        if (ch == '.')
        {
            if (point_pos == -1)
                point_pos = l;
            else
                return MANTISSA_ER;
        }
        else if (l == MANTISSA_LEN || !isdigit(ch))
            return MANTISSA_ER;
        else
            mantissa_input[l++] = ch;
    }
    char buf[2];
    buf[1] = '\0';
    for (int i = 0; i < l; i++)
    {
        buf[0] = mantissa_input[l - i - 1];
        dst->mantissa[MANTISSA_LEN - i - 1] = atoi(buf);
    }
    for (dst->mean_start = 0; dst->mean_start < MANTISSA_LEN && !dst->mantissa[dst->mean_start]; dst->mean_start += 1);

    if (point_pos == -1)
        dst->mantissa_exp = 0;
    else
        dst->mantissa_exp = point_pos - l;

    return EXIT_SUCCESS;
}

int read_exp(long_float_t *dst)
{
    printf("Input exp without e letter: ");
    char exp_input[EXP_LEN + 2];
    int l = 0;
    int ch = getchar();
    if (ch == '-' || ch == '+')
        exp_input[l++] = ch;
    else if (isdigit(ch))
    {
        exp_input[l++] = '+';
        exp_input[l++] = ch;
    }
    else
        return EXP_ER;
    for (ch = getchar(); ch != '\n'; ch = getchar())
    {
        if (l == EXP_LEN + 1 || !isdigit(ch))
            return EXP_ER;
        exp_input[l++] = ch;
    }
    exp_input[l++] = '\0';
    dst->exp = atoi(exp_input);

    return EXIT_SUCCESS;
}

int read_lf(long_float_t *dst)
{
    create_lf(dst);
    int rc = read_mantissa(dst);
    if (rc)
        return rc;
    rc = read_exp(dst);
    if (rc)
        return rc;

    return EXIT_SUCCESS;
}

void write_lf(long_float_t src)
{
    if (MANTISSA_LEN - src.mean_start + src.mantissa_exp + src.exp > EXP_MAX)
    {
        printf("inf\nexp overflow\n");
        return;
    }
    else if (MANTISSA_LEN - src.mean_start + src.mantissa_exp + src.exp < EXP_MIN)
    {
        printf("0\nexp overflow\n");
        return;
    }

    if (src.mantissa_sign)
        printf("-");
    if (src.mantissa[src.mean_start])
        printf("0.");
    else
        printf("0");
    int end = MANTISSA_LEN - 1;
    for (; !src.mantissa[end]; end--);
    for (int i = src.mean_start; i <= end; i++)
        printf("%d", src.mantissa[i]);
    printf("e%d\n", MANTISSA_LEN - src.mean_start + src.mantissa_exp + src.exp);
}
