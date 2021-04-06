PUBLIC input
PUBLIC output
PUBLIC action

EXTRN ROW_SIZE: byte
EXTRN COL_SIZE: byte
EXTRN MTR: byte

STK SEGMENT PARA STACK 'STACK'
    db 100 dup(0)
STK ENDS

DATAS SEGMENT PARA PUBLIC 'DATA'
    INPUT_SIZE_MSG db "input matrix size", 0Dh, 0AH, '$'
    INPUT_MTR_MSG db "input matrix", 0Dh, 0Ah, '$'
    OUTPUT_MTR_MSG db "matrix:", 0Dh, 0Ah, '$'
    temp db 1 dup(?)
DATAS ENDS

CSEG SEGMENT PARA PUBLIC 'CODE'
    assume CS:CSEG, DS:DATAS, SS:STK
space:
    mov ax, DATAS
    mov ds, ax

    mov ah, 02
    mov dl, ' '
    int 21h

    ret
new_line:
    mov ax, DATAS
    mov ds, ax

    mov ah, 02

    mov dl, 10
    int 21h

    mov dl, 13
    int 21h

    ret
input proc near
    mov ax, DATAS
    mov ds, ax

    mov dx, OFFSET INPUT_SIZE_MSG
    mov ah, 9
    int 21h

    mov ah, 1
    int 21h

    mov ROW_SIZE, al
    sub ROW_SIZE, '0'

    call space

    mov ah, 1
    int 21h

    mov COL_SIZE, al
    sub COL_SIZE, '0'

    call new_line

    mov dx, OFFSET INPUT_MTR_MSG
    mov ah, 9
    int 21h

    mov cx, 0
    mov cl, ROW_SIZE

    row_label:
        mov dh, cl
        mov cl, COL_SIZE
        col_label:
            mov ax, 0
            mov al, ROW_SIZE
            sub al, dh
            mul COL_SIZE
            mov bx, 0
            mov bl, COL_SIZE
            sub bl, cl
            add bx, ax

            mov ah, 01
            int 21h

            sub al, '0'
            mov MTR[bx], al

            call space
        loop col_label
        mov cl, dh
        call new_line
    loop row_label

    ret
input endp

output proc near
    mov ax, DATAS
    mov ds, ax

    mov dx, OFFSET OUTPUT_MTR_MSG
    mov ah, 9
    int 21h

    mov cx, 0
    mov cl, ROW_SIZE

    row_label:
        mov dh, cl
        mov cl, COL_SIZE
        col_label:
            mov ax, 0
            mov al, ROW_SIZE
            sub al, dh
            mul COL_SIZE
            mov bx, 0
            mov bl, COL_SIZE
            sub bl, cl
            add bx, ax

            mov dl, MTR[bx]
            add dl, '0'
            mov ah, 2
            int 21h

            call space
        loop col_label
        mov cl, dh
        call new_line
    loop row_label

    ret
output endp

action proc near
    mov cx, 0
    mov cl, ROW_SIZE

    row_label:
        mov dh, cl
        mov cl, COL_SIZE
        col_label:
            mov ax, 0
            mov al, dh
            sub al, 1
            mul COL_SIZE
            mov bx, 0
            mov bl, COL_SIZE
            sub bl, cl
            add bx, ax

            mov al, MTR[bx]
            and al, 1
            jz on_even

            on_odd:
                cmp dh, 1
                jz finish

                mov ax, 0
                mov al, dh
                sub al, 2
                mul COL_SIZE
                mov ah, COL_SIZE
                mov temp, ah
                sub temp, cl
                add temp, al
                
                mov ax, bx
                mov bx, 0
                mov bl, temp

                mov dl, MTR[bx]

                mov bx, ax
                mov MTR[bx], dl

                jmp finish
                
            on_even:
                inc MTR[bx]

            finish:

        loop col_label
        mov cl, dh
    loop row_label
    ret
action endp
CSEG ENDS
END
