app.exe: strcpy.asm main.cpp
    mkdir -p bin
    nasm -f elf64 strcpy.asm -o bin/strcpy.o
    g++ -c main.cpp -o bin/main.o
    g++ ./bin/main.o ./bin/strcpy.o -o app.exe
