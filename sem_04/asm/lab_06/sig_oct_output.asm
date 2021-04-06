PUBLIC sig_oct_output

STK SEGMENT PARA STACK 'STACK'
    db 100 dup(?)
STK ENDS

DSEG SEGMENT PARA PUBLIC 'DATA'
    sign db 1
    num_copy dw 1
DSEG ENDS

CSEG SEGMENT PARA PUBLIC 'CODE'
    assume CS:CSEG, DS:DSEG, SS:STK
check_sign:
    mov dx, 1
    mov cl, 15
    sal dx, cl

    test [di], dx
    jnz set_minus

    mov sign, 0
    ret

    set_minus:
        mov sign, 1
    ret

change_format:
    mov ax, num_copy
    not ax
    add ax, 1
    mov num_copy, ax

    ret

new_line:
    mov ah, 02

    mov dl, 10
    int 21h

    mov dl, 13
    int 21h

    ret

write_minus:
    mov ah, 2
    mov dl, '-'
    int 21h

    ret

write_zero:
    mov ah, 2
    mov dl, '0'
    int 21h

    ret

write_one:
    mov ah, 2
    mov dl, '1'
    int 21h

    ret

write_two:
    mov ah, 2
    mov dl, '2'
    int 21h

    ret

write_three:
    mov ah, 2
    mov dl, '3'
    int 21h

    ret

write_four:
    mov ah, 2
    mov dl, '4'
    int 21h

    ret

write_five:
    mov ah, 2
    mov dl, '5'
    int 21h

    ret

write_six:
    mov ah, 2
    mov dl, '6'
    int 21h

    ret

write_seven:
    mov ah, 2
    mov dl, '7'
    int 21h

    ret

test_bit:
    mov dx, num_copy
    mov bh, cl
    mov cl, bl
    
    sar dx, cl

    mov cl, bh
    mov bh, 0

    and dx, 1

    ret

write_digit:
    dec bx
    call test_bit
    jnz first_one

    first_zero:
        dec bx
        call test_bit
        jnz zero_one
    
        zero_zero:
            dec bx
            call test_bit
            jnz zero_zero_one
        
            zero_zero_zero:
                call write_zero
                ret
            
            zero_zero_one:
                call write_one
                ret
    
        zero_one:
            dec bx
            call test_bit
            jnz zero_one_one
        
            zero_one_zero:
                call write_two
                ret
            
            zero_one_one:
                call write_three
                ret
    
    first_one:
        dec bx
        call test_bit
        jnz one_one
    
        one_zero:
            dec bx
            call test_bit
            jnz one_zero_one
        
            one_zero_zero:
                call write_four
                ret
            
            one_zero_one:
                call write_five
                ret
    
        one_one:
            dec bx
            call test_bit
            jnz one_one_one
        
            one_one_zero:
                call write_six
                ret
            
            one_one_one:
                call write_seven
                ret

write_oct_number:
    mov dx, [di]
    mov num_copy, dx
    call check_sign
    cmp sign, 0
    jz start_write
    call change_format
    call write_minus

    start_write:

    mov cx, 5
    mov bx, 15

    write_dig_loop:
        call write_digit
    loop write_dig_loop

    call new_line

    ret

sig_oct_output:
    mov bp, sp
    mov di, ss:[bp + 2]

    call write_oct_number

    ret
CSEG ENDS
END
