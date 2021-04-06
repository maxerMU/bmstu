EXTRN input: near
EXTRN output: near
EXTRN action: near

STK SEGMENT PARA STACK 'STACK'
    db 100 dup(0)
STK ENDS

DATAS SEGMENT PARA PUBLIC 'DATA'
    ROW_SIZE db 1 dup(?)
    COL_SIZE db 1 dup(?)
    MTR db 9 * 9 dup(?)
DATAS ENDS

CSEG SEGMENT PARA PUBLIC 'CODE'
    assume CS:CSEG, DS:DATAS, SS:STK
main:
    mov ax, DATAS
    mov ds, ax

    call input
    call action
    call output

    mov ax, 4c00h
    int 21h
CSEG ENDS
PUBLIC ROW_SIZE
PUBLIC COL_SIZE
PUBLIC MTR

END main
