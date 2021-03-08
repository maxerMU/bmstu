StkSeg SEGMENT PARA STACK 'STACK'
    DB      200h DUP (?)
StkSeg  ENDS
DataS   SEGMENT WORD 'DATA'
HelloMessage    DB   13
                DB   10
                DW   'Hello, world !'
                DB '$'
DataS Ends
Code    SEGMENT WORD 'CODE'
        ASSUME  CS:Code, DS:DataS
DispMsg:
    mov AX,DataS
    mov DS,AX
    mov DX,OFFSET HelloMessage
    mov AH,9
    mov CX,3
label1:
    int 21h
    loop label1
    mov AH,7
    int 21h
    mov AH,4Ch
    int 21h
Code    ENDS
        END DispMsg
