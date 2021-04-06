PUBLIC diff

STK SEGMENT PARA STACK 'STACK'
    db 100 dup(0)
STK ENDS

DATAS1 SEGMENT BYTE PUBLIC 'DATA'
    X LABEL BYTE
    ORG 1h
    Y LABEL BYTE
    ORG 2h
    RES LABEL BYTE
DATAS1 ENDS
DATAS2 SEGMENT PARA PUBLIC 'DATA'
    Z LABEL BYTE
DATAS2 ENDS

CSEG SEGMENT PARA PUBLIC 'CODE'
    assume CS:CSEG, DS:DATAS1
diff proc near
    mov ax, DATAS1
    mov ds, ax
    
    mov ah, 1h
    int 21h
    mov X, al

    mov ax, DATAS2
    mov es, ax

    mov ah, 1h
    mov dl, es:Z
    int 21h

    int 21h
    mov Y, al

    mov dl, X

    sub dl, Y

    mov RES, dl
    add RES, '0'

    ret
diff endp
CSEG ENDS
PUBLIC RES
END

