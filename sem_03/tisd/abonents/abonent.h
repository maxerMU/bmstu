#ifndef ABONENT_H
#define ABONENT_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "date_time.h"
#include "read_funcs.h"

#define NAME_ER 10
#define SURNAME_ER 11
#define NUMBER_ER 12
#define ADDRES_ER 13
#define STATUS_ER 14
#define POST_ER 15
#define ORGANIZATION_ER 16

#define NAME_LEN 10
#define SURNAME_LEN 15
#define NUMBER_LEN 15
#define ADDRES_LEN 30
#define POST_LEN 10
#define ORGANIZATION_LEN 15

#define SNAME_LEN "10"
#define SSURNAME_LEN "15"
#define SNUMBER_LEN "15"
#define SADDRES_LEN "30"
#define SPOST_LEN "10"
#define SORGANIZATION_LEN "15"
#define SSTATUS_LEN "8"

typedef enum
{
    PRIVATE,
    OFFICIAL
} status_t;

typedef struct
{
    char post[POST_LEN + 1];
    char organization[ORGANIZATION_LEN + 1];
}official_title_t;

typedef struct
{
    char surname[SURNAME_LEN + 1];
    char name[NAME_LEN + 1];
    char phone_number[NUMBER_LEN + 1];
    char addres[ADDRES_LEN + 1];
    status_t status;
    union
    {
        date_t birh_date;
        official_title_t official;
    }extra_inf;
} abonent_t;

int fread_surname(abonent_t *dst, FILE *src);
void fwrite_surname(FILE *dst, abonent_t src);
int fread_name(abonent_t *dst, FILE *src);
void fwrite_name(FILE *dst, abonent_t src);
int fread_number(abonent_t *dst, FILE *src);
void fwrite_number(FILE *dst, abonent_t src);
int fread_addres(abonent_t *dst, FILE *src);
void fwrite_addres(FILE *dst, abonent_t src);
int fread_status(abonent_t *dst, FILE *src);
void fwrite_status(FILE *dst, abonent_t src);
int fread_post(abonent_t *dst, FILE *src);
void fwrite_post(FILE *dst, abonent_t src);
int fread_organization(abonent_t *dst, FILE *src);
void fwrite_organization(FILE *dst, abonent_t src);
int fread_official_title(abonent_t *dst, FILE *src);
void fwrite_official_title(FILE *dst, abonent_t src);
int fread_birth_date(abonent_t *dst, FILE *src);
void fwrite_birth_date(FILE *dst, abonent_t src);
int fread_abonent(abonent_t *dst, FILE *src);
int read_abonent(abonent_t *dst);
void fwrite_abonent(FILE *dst, abonent_t src);
void abonent_copy(abonent_t *dst, abonent_t src);
void abonent_swap(abonent_t *a, abonent_t *b);

#endif // ABONENT_H
