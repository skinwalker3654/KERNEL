section .multiboot_header
header_start:
    dd 0xE85250D6
    dd 0
    dd header_end - header_start
    dd -(0xE85250D6 + 0 + (header_end - header_start))

    dw 0
    dw 0
    dd 8
header_end:

section .text
    global _start
    extern kernel_main

_start:
    mov esp, stack_top
    call kernel_main
    cli
    hlt

section .bss
stack_botto:
    resb 16384
stack_top:
