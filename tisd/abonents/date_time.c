#include "date_time.h"

date_t current_date(void)
{
    time_t seconds = time(NULL);
    struct tm *date = localtime(&seconds);
    date_t res;
    res.day = date->tm_mday;
    res.month = date->tm_mon + 1;
    res.year = date->tm_year + 1900;

    return res;
}

int8_t days_in_month(date_t date)
{
    const int8_t days_sep[MONTHS] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (date.month == FEB && date.year % 4 == 0)
        return days_sep[date.month - 1] + 1;
    return days_sep[date.month - 1];
}

int days_to_new_year(date_t date)
{
    int days = days_in_month(date) - date.day + 1;
    for (date.month++; date.month <= DEC; date.month++)
        days+=days_in_month(date);

    return days;
}

void fwrite_date(FILE *dst, date_t src)
{
    fprintf(dst, "%d.%d.%d", src.day, src.month, src.year);
}

int fread_date(FILE *src, date_t *dst)
{
    if (fread_signed_int(&(dst->year), src) || dst->year < MIN_YEAR || dst->year > MAX_YEAR)
        return YEAR_ER;

    int month;
    if (fread_signed_int(&month, src))
        return MONTH_ER;
    dst->month = month;
    if (dst->month > DEC || dst->month < JAN)
        return MONTH_ER;

    if (fread_signed_int(&(dst->day), src) || dst->day < 1 || dst->day > MAX_DAY)
        return DAY_ER;
    if (dst->day > days_in_month(*dst))
        return DAY_ER;

    return EXIT_SUCCESS;
}

date_t add_days(date_t src, int days)
{
    date_t date = src;
    while (days)
    {
        if (date.day + days <= days_in_month(date))
        {
            date.day += days;
            days = 0;
        }
        else
        {
            days -= (days_in_month(date) - date.day + 1);
            date.day = 1;
            if (date.month < DEC)
                date.month++;
            else
            {
                date.month = JAN;
                date.year++;
            }
        }
    }

    return date;
}

int dates_diff(date_t date1, date_t date2)
{
    int days = 0;
    int sign = 1;
    if (cmp_dates(date1, date2) > 0)
    {
        date_t temp = date1;
        date1 = date2;
        date2 = temp;
        sign = -1;
    }
    while (cmp_dates(date1, date2))
    {
        if (date1.year != date2.year)
        {
            days += days_to_new_year(date1);
            date1.day = 1;
            date1.month = JAN;
            date1.year++;
        }
        else if (date1.month != date2.month)
        {
            days += (days_in_month(date1) - date1.day + 1);
            date1.day = 1;
            date1.month++;
        }
        else
        {
            days += (date2.day - date1.day);
            date1.day = date2.day;
        }
    }

    return days * sign;
}

int cmp_dates(date_t date1, date_t date2)
{
    if (date1.year != date2.year)
        return date1.year - date2.year;

    if (date1.month != date2.month)
        return date1.month - date2.month;

    return date1.day - date2.day;
}
