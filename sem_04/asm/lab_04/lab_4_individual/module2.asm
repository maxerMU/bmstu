EXTRN diff: near
EXTRN RES: byte

CSEG SEGMENT PARA PUBLIC 'CODE'
    assume CS:CSEG
main:
    call diff

    mov ah, 2h
    mov dl, 10
    int 21h

    mov dl, 13
    int 21h

    mov dl, RES
    int 21h

    mov ax, 4c00h
    int 21h
CSEG ENDS
END main
