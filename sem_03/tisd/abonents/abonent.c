#include "abonent.h"

int fread_surname(abonent_t *dst, FILE *src)
{
    if (fread_str(src, dst->surname, SURNAME_LEN + 1, " \n"))
        return SURNAME_ER;

    return EXIT_SUCCESS;
}

void fwrite_surname(FILE *dst, abonent_t src)
{
    fprintf(dst, "%"SSURNAME_LEN"s", src.surname);
}

int fread_name(abonent_t *dst, FILE *src)
{
    if (fread_str(src, dst->name, NAME_LEN + 1, " \n"))
        return NAME_ER;

    return EXIT_SUCCESS;
}

void fwrite_name(FILE *dst, abonent_t src)
{
    fprintf(dst, "%"SNAME_LEN"s", src.name);
}

int fread_number(abonent_t *dst, FILE *src)
{
    int ch = fgetc(src);
    size_t i = 0;
    for (; isspace(ch) && ch != EOF; ch = fgetc(src));
    if (ch == '+')
    {
        dst->phone_number[i++] = ch;
        ch = fgetc(src);
    }
    for (; !isspace(ch) && ch != EOF; ch = fgetc(src))
        if (isdigit(ch) && i < NUMBER_LEN)
            dst->phone_number[i++] = ch;
        else
            return NUMBER_ER;

    if (i == 0 || (i == 1 && dst->phone_number[i] == '+'))
        return NUMBER_ER;

    return EXIT_SUCCESS;
}

void fwrite_number(FILE *dst, abonent_t src)
{
    fprintf(dst, "%"SNUMBER_LEN"s", src.phone_number);
}

int fread_addres(abonent_t *dst, FILE *src)
{
    if (fread_str(src, dst->addres, ADDRES_LEN + 1, ".\n"))
        return ADDRES_ER;

    return EXIT_SUCCESS;
}

void fwrite_addres(FILE *dst, abonent_t src)
{
    fprintf(dst, "%"SADDRES_LEN"s", src.addres);
}

int fread_status(abonent_t *dst, FILE *src)
{
    int status;
    int rc = fread_signed_int(&(status), src);
    dst->status = status;
    if (rc || dst->status < PRIVATE || dst->status > OFFICIAL)
        return STATUS_ER;

    return EXIT_SUCCESS;
}

void fwrite_status(FILE *dst, abonent_t src)
{
    if (src.status == PRIVATE)
        fprintf(dst, "%"SSTATUS_LEN"s", "private");
    else
        fprintf(dst, "official");
}

int fread_post(abonent_t *dst, FILE *src)
{
    if (fread_str(src, dst->extra_inf.official.post, POST_LEN + 1, " \n"))
        return POST_ER;
    return EXIT_SUCCESS;
}

void fwrite_post(FILE *dst, abonent_t src)
{
    fprintf(dst, "%"SPOST_LEN"s", src.extra_inf.official.post);
}

int fread_organization(abonent_t *dst, FILE *src)
{
    if (fread_str(src, dst->extra_inf.official.organization, ORGANIZATION_LEN + 1, " \n"))
        return ORGANIZATION_ER;
    return EXIT_SUCCESS;
}

void fwrite_organization(FILE *dst, abonent_t src)
{
    fprintf(dst, "%"SORGANIZATION_LEN"s", src.extra_inf.official.organization);
}

int fread_official_title(abonent_t *dst, FILE *src)
{
    int rc = fread_post(dst, src);
    if (rc)
        return rc;
    rc = fread_organization(dst, src);

    return rc;
}

void fwrite_official_title(FILE *dst, abonent_t src)
{
    fwrite_post(dst, src);
    fprintf(dst, " ");
    fwrite_organization(dst, src);
}

int fread_birth_date(abonent_t *dst, FILE *src)
{
    int rc = fread_date(src, &(dst->extra_inf.birh_date));
    return rc;
}

void fwrite_birth_date(FILE *dst, abonent_t src)
{
    fwrite_date(dst, src.extra_inf.birh_date);
}

int fread_abonent(abonent_t *dst, FILE *src)
{
    int rc;
    if ((rc = fread_surname(dst, src)))
        return rc;

    if ((rc = fread_name(dst, src)))
        return rc;

    if ((rc = fread_number(dst, src)))
        return rc;

    if ((rc = fread_addres(dst, src)))
        return rc;

    if ((rc = fread_status(dst, src)))
        return rc;

    if (dst->status == PRIVATE)
    {
        if ((rc = fread_birth_date(dst, src)))
            return rc;
    }
    else
        if ((rc = fread_official_title(dst, src)))
            return rc;

    return EXIT_SUCCESS;
}

int read_abonent(abonent_t *dst)
{
    printf("Input surname (maximum 15 characters): ");
    int rc = fread_surname(dst, stdin);
    if (rc)
        return rc;

    printf("Input name (maximum 10 characters): ");
    rc = fread_name(dst, stdin);
    if (rc)
        return rc;

    printf("Input number (maximum 15 digits and \"+\"): ");
    rc = fread_number(dst, stdin);
    if (rc)
        return rc;

    printf("Input addres (maximum 30 characters, you can't use \".\"): ");
    rc = fread_addres(dst, stdin);
    if (rc)
        return rc;

    printf("Input status (0 - private, 1 - official): ");
    rc = fread_status(dst, stdin);
    if (rc)
        return rc;

    if (dst->status == PRIVATE)
    {
        printf("Input birth date (YYYY MM DD): ");
        rc = fread_birth_date(dst, stdin);
        if (rc)
            return rc;
    }
    else
    {
        printf("Input post and organization (maximum 10 characters in post and 15 in organization): ");
        rc = fread_official_title(dst, stdin);
        if (rc)
            return rc;
    }

    return EXIT_SUCCESS;
}

void fwrite_abonent(FILE *dst, abonent_t src)
{
    fwrite_surname(dst, src);
    fprintf(dst, " ");

    fwrite_name(dst, src);
    fprintf(dst, " ");

    fwrite_number(dst, src);
    fprintf(dst, " ");

    fwrite_addres(dst, src);
    fprintf(dst, " ");

    fwrite_status(dst, src);
    fprintf(dst, " ");

    if (src.status == PRIVATE)
        fwrite_birth_date(dst, src);
    else
        fwrite_official_title(dst, src);
    fprintf(dst, "\n");
}

void abonent_copy(abonent_t *dst, abonent_t src)
{
    strcpy(dst->surname, src.surname);
    strcpy(dst->name, src.name);
    strcpy(dst->phone_number, src.phone_number);
    strcpy(dst->addres, src.addres);
    dst->status = src.status;
    if (dst->status == OFFICIAL)
    {
        strcpy(dst->extra_inf.official.post, src.extra_inf.official.post);
        strcpy(dst->extra_inf.official.organization, src.extra_inf.official.organization);
    }
    else
        dst->extra_inf.birh_date = src.extra_inf.birh_date;
}

void abonent_swap(abonent_t *a, abonent_t *b)
{
    abonent_t temp;
    abonent_copy(&temp, *a);
    abonent_copy(a, *b);
    abonent_copy(b, temp);
}
