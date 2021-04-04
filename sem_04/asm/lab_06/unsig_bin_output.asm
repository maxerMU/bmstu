PUBLIC unsig_bin_output

STK SEGMENT PARA STACK 'STACK'
    db 100 dup(?)
STK ENDS

DSEG SEGMENT PARA PUBLIC 'DATA'
DSEG ENDS

CSEG SEGMENT PARA PUBLIC 'CODE'
    assume CS:CSEG, DS:DSEG, SS:STK
test_bit:
    mov dx, [di]
    mov bh, cl
    mov cl, bl
    
    sar dx, cl

    mov cl, bh
    mov bh, 0

    and dx, 1

    ret

new_line:
    mov ah, 02

    mov dl, 10
    int 21h

    mov dl, 13
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

write_bin:
    mov cx, 10h
    mov bx, 10h

    bit_loop:
        dec bx
        call test_bit
        jz write_zero_call

        call write_one
        jmp write_finish

        write_zero_call:
            call write_zero

        write_finish:
    loop bit_loop

    call new_line

    ret

unsig_bin_output:
    mov bp, sp

    mov di, ss:[bp + 2]

    call write_bin

    ret
CSEG ENDS
END
