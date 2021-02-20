#ifndef LONG_MULTIPLY_H
#define LONG_MULTIPLY_H

#include <stdio.h>
#include <stdlib.h>
#include "long_float.h"
#include "long_integer.h"

#define DIGIT_MLT_LEN (MANTISSA_LEN + 1)
#define RES_MLT_LEN (MANTISSA_LEN + INT_LEN)

typedef struct
{
    int mantissa_sign;
    int mantissa[DIGIT_MLT_LEN];
    int mean_start;
    int exp;
}digit_mlt_t;

typedef struct
{
    int mantissa_sign;
    int mantissa[RES_MLT_LEN];
    int mean_start;
    int exp;
}mlt_res_t;

void write_res(mlt_res_t src);
long_float_t mlt(long_float_t f, long_integer_t d);

#endif // LONG_MULTIPLY_H
