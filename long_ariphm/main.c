#include <stdio.h>
#include <stdlib.h>
#include "long_float.h"
#include "long_integer.h"
#include "long_multiply.h"

int main()
{
    printf("This program multiply real and integer\n");
    printf("Real consists of mantissa and exponent. Number of digits in mantissa can not be more than 30.\n");
    printf("Exponent is integer between -99999 and 99999. Real is <mantissa>*10^<exponent>.\n");
    printf("Number of digits in integer can not be more than 30. Mantissa examples: 1.234; .01; -.2; 123.; 123\n");
    printf("Exponent examples: 0; 10; -12. Integer examples: 0; 10; -12\n");
    long_float_t f;
    int rc = read_lf(&f);
    if (rc)
    {
        if (rc == MANTISSA_ER)
            printf("Wrong mantissa.\nMantissa examples: 1.234; .01; -.2; 123.; 123\n");
        else if (rc == EXP_ER)
            printf("Wrong exponent.\nExponent examples: 0; 10; -12;\n");
        return rc;
    }
    long_integer_t i;
    rc = read_li(&i);
    if (rc)
    {
        printf("Wrong integer.\nInteger examples: 0; 10; -12\n");
        return rc;
    }
    long_float_t res = mlt(f, i);
    printf("Multiply result: ");
    write_lf(res);

    return EXIT_SUCCESS;
}
