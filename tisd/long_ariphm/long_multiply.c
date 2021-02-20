#include "long_multiply.h"

void create_dmlt(digit_mlt_t *dst)
{
    memset(dst->mantissa, 0, DIGIT_MLT_LEN * sizeof (int));
    dst->exp = 0;
    dst->mantissa_sign = 0;
}

void create_res(mlt_res_t *dst)
{
    memset(dst->mantissa, 0, (RES_MLT_LEN) * sizeof (int));
    dst->exp = 0;
    dst->mantissa_sign = 0;
    dst->mean_start = RES_MLT_LEN - 1;
}

digit_mlt_t digit_mlt(long_float_t f, int digit)
{
    digit_mlt_t res;
    create_dmlt(&res);
    int transfer = 0;
    for (int i = MANTISSA_LEN - 1; i >= f.mean_start; i--)
    {
        res.mantissa[i + 1] = (f.mantissa[i] * digit + transfer) % 10;
        transfer = (f.mantissa[i] * digit + transfer) / 10;
    }
    if (transfer)
    {
        res.mantissa[f.mean_start] = transfer;
        res.mean_start = f.mean_start;
    }
    else
        res.mean_start = f.mean_start + 1;
    return res;
}

void add_to_res(mlt_res_t *res, digit_mlt_t mlt)
{
    int dif = RES_MLT_LEN - (DIGIT_MLT_LEN) - mlt.exp;
    int transfer = 0;
    int i = DIGIT_MLT_LEN + dif - 1;
    for (; i - dif >= mlt.mean_start; i--)
    {
        int digit = res->mantissa[i] + mlt.mantissa[i - dif] + transfer;
        res->mantissa[i] = digit % 10;
        transfer = digit / 10;
    }
    if (transfer)
        res->mantissa[i] = transfer;
    for (res->mean_start = 0; !res->mantissa[res->mean_start]; res->mean_start += 1);
}

long_float_t res_to_lf(mlt_res_t res)
{
    long_float_t lf;
    create_lf(&lf);
    lf.exp = res.exp;
    lf.mantissa_sign = res.mantissa_sign;
    if (RES_MLT_LEN - res.mean_start - 1 < MANTISSA_LEN)
    {
        for (int i = MANTISSA_LEN - 1; i + RES_MLT_LEN - MANTISSA_LEN >= res.mean_start; i--)
            lf.mantissa[i] = res.mantissa[i + RES_MLT_LEN - MANTISSA_LEN];
        lf.mean_start = res.mean_start - RES_MLT_LEN + MANTISSA_LEN;
    }
    else
    {
        lf.mean_start = 0;
        for (int i = 0; i < MANTISSA_LEN; i++)
            lf.mantissa[i] = res.mantissa[res.mean_start + i];
        if (res.mantissa[MANTISSA_LEN + res.mean_start] > 4)
        {
            int transfer = 1;
            for (int i = MANTISSA_LEN - 1; transfer && i >= 0; i--)
            {
                int digit = transfer + lf.mantissa[i];
                lf.mantissa[i] = digit % 10;
                transfer = digit / 10;
                if (!i)
                    lf.exp += 1;
            }
            if (transfer)
            {
                lf.mean_start = MANTISSA_LEN - 1;
                lf.mantissa[lf.mean_start] = 1;
                lf.exp += 1;
            }
        }
    }
    int end = MANTISSA_LEN - 1;
    for (; end > lf.mean_start && !lf.mantissa[end]; end--);
    for (int i = MANTISSA_LEN - 1; i > end; i--)
    {
        lf.exp += 1;
        for (int j = MANTISSA_LEN - 1; j > lf.mean_start; j--)
            lf.mantissa[j] = lf.mantissa[j - 1];
        lf.mantissa[lf.mean_start++] = 0;
    }

    return lf;
}

long_float_t mlt(long_float_t f, long_integer_t d)
{
    mlt_res_t res;
    create_res(&res);
    if (f.mantissa_sign == d.sign)
        res.mantissa_sign = 0;
    else
        res.mantissa_sign = 1;

    for (int i = INT_LEN - 1; i >= d.mean_start; i--)
    {
        digit_mlt_t mlt = digit_mlt(f, d.mantissa[i]);
        mlt.exp = INT_LEN - 1 - i;
        add_to_res(&res, mlt);
    }

    if (d.mean_start != INT_LEN && f.mean_start != MANTISSA_LEN)
        res.exp = f.exp + f.mantissa_exp;
    else
    {
        res.exp = 0;
        res.mean_start = RES_MLT_LEN;
    }

    return res_to_lf(res);
}

void write_mlt(digit_mlt_t src)
{
    if (src.mantissa_sign)
        printf("-");
    printf("0.");
    for (int i = src.mean_start; i < DIGIT_MLT_LEN; i++)
        printf("%d", src.mantissa[i]);
    printf("e%d\n", DIGIT_MLT_LEN - src.mean_start + src.exp);
}

void write_res(mlt_res_t src)
{
    /*end 0*/
    if (src.mantissa_sign)
        printf("-");
    printf("0.");
    for (int i = src.mean_start; i < RES_MLT_LEN; i++)
        printf("%d", src.mantissa[i]);
    printf("e%d\n", RES_MLT_LEN - src.mean_start + src.exp);
}
