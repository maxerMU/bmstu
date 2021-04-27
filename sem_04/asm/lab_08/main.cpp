#include <iostream>
#include <string.h>

extern "C"
{
void copy(char *dest, char *src, int len);
}

size_t asmstrlen(const char *str)
{
    size_t len;

    __asm__ (".intel_syntax noprefix\n"
             "mov RDI, %1\n"
             "mov RCX, -1\n"
             "mov AL, 0\n"
             "REPNZ SCASB\n"
             "mov RAX, -1\n"
             "sub RAX, RCX\n"
             "sub RAX, 1\n"
             "mov %0, RAX\n"
             : "=r"(len)
             : "r"(str)
             : "%rax", "%rdi", "%rcx");

    return len;
}

int main(void)
{
    char str[100];
    strcpy(str, "123456789");

    size_t len = asmstrlen(str);

    std::cout << len << std::endl;

    char buf[100] = {'0'};

    copy(str + 1, str, 3);

    std::cout << str << std::endl;

    return len;
}