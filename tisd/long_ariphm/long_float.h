#ifndef LONG_FLOAT_H
#define LONG_FLOAT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MANTISSA_ER 1
#define EXP_ER 2

#define MANTISSA_LEN 30
#define EXP_LEN 5
#define EXP_MIN -99999
#define EXP_MAX 99999

typedef struct
{
    int mantissa_sign;
    int mantissa[MANTISSA_LEN];
    int mean_start;
    int mantissa_exp;
    int exp;
}long_float_t;

void create_lf(long_float_t *dst);
int read_lf(long_float_t *dst);
void write_lf(long_float_t src);

#endif // LONG_FLOAT_H
