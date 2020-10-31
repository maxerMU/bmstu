#ifndef DATE_TIME_H
#define DATE_TIME_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <inttypes.h>
#include "read_funcs.h"

#define YEAR_ER 100
#define MONTH_ER 101
#define DAY_ER 102

#define MAX_YEAR 2020
#define MIN_YEAR 0
#define MONTHS 12
#define MAX_DAY 31

typedef enum
{
    JAN = 1,
    FEB,
    MAR,
    APR,
    MAY,
    JUN,
    JUL,
    AUG,
    SEP,
    OCT,
    NOV,
    DEC
} month_t;

typedef struct
{
    int year;//0-2020
    month_t month;//1-12
    int day;//1-31
} date_t;

void fwrite_date(FILE *dst, date_t src);
int fread_date(FILE *src, date_t *dst);
date_t add_days(date_t src, int days);
int dates_diff(date_t date1, date_t date2);
int cmp_dates(date_t date1, date_t date2);
date_t current_date(void);

#endif // DATE_TIME_H
