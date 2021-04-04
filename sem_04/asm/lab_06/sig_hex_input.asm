PUBLIC sig_hex_input

STK SEGMENT PARA STACK 'STACK'
    db 100 dup(?)
STK ENDS

DSEG SEGMENT PARA PUBLIC 'DATA'
    sign db 1
DSEG ENDS

CSEG SEGMENT PARA PUBLIC 'CODE'
    assume CS:CSEG, DS:DSEG, SS:STK
reset:
    mov dx, di
    mov sign, 0
    mov cx, 2
    mov al, 0
    reset_loop:
        mov [di], al
        inc di
    loop reset_loop

    mov di, dx

    ret

set_zero:
    mov bh, cl
    mov cl, bl

    mov dx, 1

    rol dx, cl
    not dx

    and [di], dx

    mov cl, bh
    mov bh, 0

    ret

set_bit:
    mov bh, cl
    mov cl, bl

    mov dx, 1
    rol dx, cl

    or [di], dx

    mov cl, bh
    mov bh, 0

    ret

write_sign:
    mov sign, 1
    inc cx

    ret

write_zero:
    call set_zero
    dec bx
    call set_zero
    dec bx
    call set_zero
    dec bx
    call set_zero
    dec bx

    ret

write_one:
    call set_zero
    dec bx
    call set_zero
    dec bx
    call set_zero
    dec bx
    call set_bit
    dec bx

    ret

write_two:
    call set_zero
    dec bx
    call set_zero
    dec bx
    call set_bit
    dec bx
    call set_zero
    dec bx

    ret

write_three:
    call set_zero
    dec bx
    call set_zero
    dec bx
    call set_bit
    dec bx
    call set_bit
    dec bx

    ret

write_four:
    call set_zero
    dec bx
    call set_bit
    dec bx
    call set_zero
    dec bx
    call set_zero
    dec bx

    ret

write_five:
    call set_zero
    dec bx
    call set_bit
    dec bx
    call set_zero
    dec bx
    call set_bit
    dec bx

    ret

write_six:
    call set_zero
    dec bx
    call set_bit
    dec bx
    call set_bit
    dec bx
    call set_zero
    dec bx

    ret

write_seven:
    call set_zero
    dec bx
    call set_bit
    dec bx
    call set_bit
    dec bx
    call set_bit
    dec bx

    ret

write_eight:
    call set_bit
    dec bx
    call set_zero
    dec bx
    call set_zero
    dec bx
    call set_zero
    dec bx

    ret

write_nine:
    call set_bit
    dec bx
    call set_zero
    dec bx
    call set_zero
    dec bx
    call set_bit
    dec bx

    ret

write_a:
    call set_bit
    dec bx
    call set_zero
    dec bx
    call set_bit
    dec bx
    call set_zero
    dec bx

    ret

write_b:
    call set_bit
    dec bx
    call set_zero
    dec bx
    call set_bit
    dec bx
    call set_bit
    dec bx

    ret

write_c:
    call set_bit
    dec bx
    call set_bit
    dec bx
    call set_zero
    dec bx
    call set_zero
    dec bx

    ret

write_d:
    call set_bit
    dec bx
    call set_bit
    dec bx
    call set_zero
    dec bx
    call set_bit
    dec bx

    ret

write_e:
    call set_bit
    dec bx
    call set_bit
    dec bx
    call set_bit
    dec bx
    call set_zero
    dec bx

    ret

write_f:
    call set_bit
    dec bx
    call set_bit
    dec bx
    call set_bit
    dec bx
    call set_bit
    dec bx

    ret

set_digit:
    cmp al, '-'
    jz write_sign_call

    cmp al, '0'
    jz write_zero_call

    cmp al, '1'
    jz write_one_call

    cmp al, '2'
    jz write_two_call

    cmp al, '3'
    jz write_three_call

    cmp al, '4'
    jz write_four_call

    cmp al, '5'
    jz write_five_call

    cmp al, '6'
    jz write_six_call

    cmp al, '7'
    jz write_seven_call

    cmp al, '8'
    jz write_eight_call

    cmp al, '9'
    jz write_nine_call

    cmp al, 'A'
    jz write_a_call

    cmp al, 'B'
    jz write_b_call

    cmp al, 'C'
    jz write_c_call

    cmp al, 'D'
    jz write_d_call

    cmp al, 'E'
    jz write_e_call

    cmp al, 'F'
    jz write_f_call

    write_sign_call:
        call write_sign
        jmp set_digit_finish

    write_zero_call:
        call write_zero
        jmp set_digit_finish

    write_one_call:
        call write_one
        jmp set_digit_finish

    write_two_call:
        call write_two
        jmp set_digit_finish

    write_three_call:
        call write_three
        jmp set_digit_finish

    write_four_call:
        call write_four
        jmp set_digit_finish

    write_five_call:
        call write_five
        jmp set_digit_finish

    write_six_call:
        call write_six
        jmp set_digit_finish

    write_seven_call:
        call write_seven
        jmp set_digit_finish

    write_eight_call:
        call write_eight
        jmp set_digit_finish

    write_nine_call:
        call write_nine
        jmp set_digit_finish

    write_a_call:
        call write_a
        jmp set_digit_finish

    write_b_call:
        call write_b
        jmp set_digit_finish

    write_c_call:
        call write_c
        jmp set_digit_finish

    write_d_call:
        call write_d
        jmp set_digit_finish

    write_e_call:
        call write_e
        jmp set_digit_finish

    write_f_call:
        call write_f
        jmp set_digit_finish

    set_digit_finish:
    ret

check_sign:
    cmp sign, 1
    jnz check_finish

    mov ax, [di]
    not ax
    add ax, 1
    mov [di], ax


    check_finish:
    ret

new_line:
    mov ah, 02

    mov dl, 10
    int 21h

    mov dl, 13
    int 21h

    ret

read_number:
    mov cx, 4
    mov bx, 15
    read_digit:
        mov ah, 1
        int 21h

        cmp al, 13
        jz read_finish

        call set_digit

    loop read_digit

    read_finish:
    call new_line

    mov ax, cx
    mov dx, 4
    mul dx
    mov cx, ax
    mov dx, [di]
    ror dx, cl
    mov [di], dx

    call check_sign

    ret
    
sig_hex_input:
    mov ax, DSEG
    mov ds, ax

    mov bp, sp

    mov di, ss:[bp + 2]

    call reset

    call read_number

    ret
CSEG ENDS
END
