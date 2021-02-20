#ifndef READ_FUNCS_H
#define READ_FUNCS_H

#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

#define OVERFLOW_ER 1
#define NDIGIT_ER 2
#define EMPTY_ER 3

int fread_signed_int(int *dst, FILE *src);
int fread_str(FILE *src, char *buf, size_t buf_size, char *sep);

#endif // READ_FUNCS_H
