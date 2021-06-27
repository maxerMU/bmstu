#include <stdlib.h>
#include <stdio.h>
#include <string.h>

float scalar_mlt(float a[], float b[], size_t size)
{
    float res = 0;
    for (size_t i = 0; i < size; i++)
        res += a[i] * b[i];
    
    return res;
}

float scalar_mlt_asm(float a[], float b[], size_t size)
{
    float res = 0;
    float a_buf[4];
    float b_buf[4];
    float res_buf[4];
    size /= 4;

    for (; size; size--)
    {
        memcpy(a_buf, a, 16);
        memcpy(b_buf, b, 16);
        __asm__("movups xmm0, %1\n"
                "movups xmm1, %2\n"
                "mulps xmm0, xmm1\n"
                "movups %0, xmm0\n"
                : "=m"(res_buf)
                : "m"(a_buf), "m"(b_buf)
                : "%xmm0", "%xmm1");
        for (size_t i = 0; i < 4; i++)
            res += res_buf[i];
        a += 4;
        b += 4;
    }

    return res;
}

int main()
{
    float a[4] = {1.0, 2.0, 3.0, 4.0};
    float b[4] = {1.0, 2.0, 3.0, 4.0};
    float res_asm = scalar_mlt_asm(a, b, 4);
    float res = scalar_mlt(a, b, 4);
    printf("res asm - %f\n", res_asm);
    printf("res - %f\n", res);
}