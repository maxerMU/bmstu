global copy

section .data
section .text

copy:
    mov RCX, RDX

    cmp RSI, RDI
    jg std_copy


    mov RAX, RDI
    sub RAX, RSI

    cmp RAX, RCX
    jg std_copy

    add RDI, RCX
    add RSI, RCX

    dec RDI
    dec RSI

    std
std_copy:
    rep movsb

    ret