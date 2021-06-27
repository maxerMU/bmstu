#include <stdio.h>
#include <math.h>
#include "pi_accuracy_compare.h"

void test_sin()
{
    printf("c sin\n");
    double pi1 = 3.14;
    double pi2 = 3.141596;

    printf("sin(%lf) = %lf\nsin(%lf) = %f\n", pi1, sin(pi1), pi2, sin(pi2));
    printf("sin(%lf / 2) = %lf\nsin(%lf / 2) = %f\n", pi1, sin(pi1 / 2), pi2, sin(pi2 / 2));

    printf("pi from lib\n");
    printf("sin(pi) = %lf\nsin(pi / 2) = %f\n", sin(M_PI), sin(M_PI_2));
}

double asm_sin(double angle)
{
    double res;
    __asm__("FLD %1\n"
            "FSIN\n"
            "FSTP %0\n"
            : "=m"(res)
            : "m"(angle));
    
    return res;
}

double asm_sin_pi()
{
    double res;
    __asm__("FLDPI\n"
            "FSIN\n"
            "FSTP %0\n"
            : "=m"(res));
    
    return res;
}

double asm_sin_pi2()
{
    double res;
    __asm__("FLDPI\n"
            "FLD1\n"
            "FLD1\n"
            "FADDP\n"
            "FDIVP\n"
            "FSIN\n"
            "FSTP %0\n"
            : "=m"(res));
    
    return res;
}

void test_sin_asm()
{
    printf("asm sin\n");
    double pi1 = 3.14;
    double pi2 = 3.141596;

    printf("sin(%lf) = %lf\nsin(%lf) = %f\n", pi1, asm_sin(pi1), pi2, asm_sin(pi2));
    printf("sin(%lf / 2) = %lf\nsin(%lf / 2) = %f\n", pi1, asm_sin(pi1 / 2), pi2, asm_sin(pi2 / 2));

    printf("pi from soproc\n");
    printf("sin(pi) = %lf\nsin(pi / 2) = %f\n", asm_sin_pi(), asm_sin_pi2());
}

void print_pi_accuracy_compare()
{
    test_sin();
    test_sin_asm();
}