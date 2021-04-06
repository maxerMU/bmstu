EXTRN sig_hex_input: near
EXTRN unsig_bin_output: near
EXTRN sig_oct_output: near

STK SEGMENT PARA STACK 'STACK'
    db 100 dup(?)
STK ENDS

DSEG SEGMENT PARA PUBLIC 'DATA'
    MENU_MSG_1 db "1 - input a signed 16-digit number in hexadecimal notation", 0Dh, 0Ah, '$'
    MENU_MSG_2 db "2 - output an unsigned 16-digit number in binary notation", 0Dh, 0Ah, '$'
    MENU_MSG_3 db "3 - output a signed 16-digit number in octal notation", 0Dh, 0Ah, '$'
    MENU_MSG_4 db "0 - exit", 0Dh, 0Ah, '$'

    funcs dw 3 dup(?)

    number dw 1 dup(?)
DSEG ENDS

CSEG SEGMENT PARA PUBLIC 'CODE'
    assume CS:CSEG, DS:DSEG, SS:STK
write_menu:
    mov ah, 9
    mov dx, OFFSET MENU_MSG_1
    int 21h
    
    mov dx, OFFSET MENU_MSG_2
    int 21h
    
    mov dx, OFFSET MENU_MSG_3
    int 21h
    
    mov dx, OFFSET MENU_MSG_4
    int 21h

    ret

new_line:
    mov ah, 02

    mov dl, 10
    int 21h

    mov dl, 13
    int 21h

    ret
read_command:
    mov ah, 1
    int 21h

    sub al, '0'

    ret
main:
    mov ax, DSEG
    mov ds, ax

    mov funcs[0 * 2], sig_hex_input
    mov funcs[1 * 2], unsig_bin_output
    mov funcs[2 * 2], sig_oct_output

    mov cx, 1
    menu:
        call write_menu

        call read_command
        jz menu_finish

        mov ah, 0
        sub al, 1
        mov bx, 2
        mul bx
        mov bx, ax

        call new_line

        mov dx, OFFSET number
        push cx
        push dx
        call funcs[bx]
        pop dx
        pop cx

        inc cx

    menu_finish:
    loop menu

    mov ax, 4c00h
    int 21h
CSEG ENDS
END main
