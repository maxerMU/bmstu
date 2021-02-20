#ifndef LONG_INTEGER_H
#define LONG_INTEGER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define INT_LEN 30

#define INT_ER 3

typedef struct
{
    int sign;
    int mantissa[INT_LEN];
    int mean_start;
}long_integer_t;

int read_li(long_integer_t *dst);
void write_li(long_integer_t src);

#endif // LONG_INTEGER_H
