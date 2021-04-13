STK SEGMENT PARA STACK 'STACK'
    db 100 dup (?)
STK ENDS

DATAS SEGMENT PARA PUBLIC 'DATA'
    counter db 0
DATAS ENDS

CODES SEGMENT PARA PUBLIC 'CODE'
    assume CS:CODES
my_9h proc
    push ax
    push dx
    mov ah, 02
    mov dl, 'F'
    int 21h

    pop dx
    pop ax

    mov al, 20h
    OUT 20h, AL

    iret
my_9h endp

init:
   mov ax, CODES
   mov ds, ax

   mov ax, 251Ch
   mov dx, offset my_9h
   int 21h

   mov ax, DATAS
   mov ds, ax

   mov ax, 3100h
   mov dx, 30h
   int 21h

main:
    jmp init

CODES ENDS
END main
