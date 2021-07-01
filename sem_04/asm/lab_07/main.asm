STK SEGMENT PARA STACK 'STACK'
    db 32 dup (?)
STK ENDS

DATAS SEGMENT PARA PUBLIC 'DATA'
    counter db 1 dup(0)
    speed db 31
    old_bx dw 1
    old_es dw 1
DATAS ENDS

CODES SEGMENT PARA PUBLIC 'CODE'
    assume CS:CODES, DS:DATAS
my_1ch proc
    push ax
    push dx
    push es
    push bx

    mov es, ds:old_es
    ;call es:old_bx

    mov al, ds:counter
    inc al
    mov ds:counter, al

    cmp ds:counter, 18
    jnz finish

    mov al, 0
    mov ds:counter, al

    cmp ds:speed, 0
    jnz set_speed

    mov al, 31
    mov ds:speed, al

    set_speed:
    mov al, ds:speed
    dec al
    mov ds:speed, al

    mov al, 0F3h
    OUT 60h, al
    mov al, ds:speed
    OUT 60h, al

    finish:

    pop bx
    pop es
    pop dx
    pop ax

    mov al, 20h
    OUT 20h, al

    iret
my_1ch endp

init:
   mov ax, 3508h
   int 21h

   mov ds:old_bx, bx
   mov ds:old_es, es

   mov ax, CODES
   mov ds, ax

   mov ax, 251Ch
   mov dx, offset my_1ch
   int 21h

   mov ax, DATAS
   mov ds, ax

   mov ax, 3100h
   mov dx, 30h
   int 21h

main:
    mov ax, DATAS
    mov ds, ax
    jmp init

CODES ENDS
END main
