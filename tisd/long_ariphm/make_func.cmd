@ECHO OFF
CHCP 65001
gcc -std=c99 -Wall -Wpedantic -Wextra -Werror --coverage -O0 -Wvla -c main.c
gcc -std=c99 -Wall -Wpedantic -Wextra -Werror -O0 -Wvla -c long_float.c
gcc -std=c99 -Wall -Wpedantic -Wextra -Werror -O0 -Wvla -c long_integer.c
gcc -std=c99 -Wall -Wpedantic -Wextra -Werror -O0 -Wvla -c long_multiply.c
gcc --coverage -o app.exe main.o long_float.o long_integer.o long_multiply.o
PUSHD func
CALL ./all_test.cmd
PUSHD ..
gcov main.c