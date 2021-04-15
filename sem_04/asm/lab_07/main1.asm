.model tiny
CODE SEGMENT
    ASSUME CS:CODE, DS:CODE
    ORG 100h
main:	
	jmp init
	old          DD 0
	timer        DB 0
	speed 		 DB 00h

my_08h proc
	
	
	pushf
	push ax
	push bx
	push cx
	push dx
	push ds
	push es
	push si
	
	call cs:old
	xor ax, ax
    mov al, ds:timer
    inc al
    mov ds:timer, al

    cmp ds:timer, 18
    jnz finish

    xor al, al
    mov ds:timer, al

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
	pop si
	pop es
	pop ds
	pop dx
	pop cx
	pop bx
	pop ax
	
	iret
my_08h endp

init:
    mov ax, 3508h
	int 21h
	mov word ptr old,  bx
	mov word ptr old + 2,  es
	
	mov ax,  2508h
	mov dx, offset my_08h
	int 21h
	
	mov ax, 3100h
	mov dx, 30h
	int 21h
	

CODE ends
end main
