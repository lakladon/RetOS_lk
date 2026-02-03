; @lakladon: Bootloader for RetOS minimal shell
BITS 32

; @lakladon: Multiboot2 header section
section .multiboot
align 8
mb2_start:
    dd 0xe85250d6          ; multiboot2 magic
    dd 0                  ; architecture (i386)
    dd mb2_end - mb2_start
    dd -(0xe85250d6 + 0 + (mb2_end - mb2_start))

    dw 0
    dw 0
    dd 8
mb2_end:

; @lakladon: Text section with entry point
section .text
global _start
extern kernel_main

; @lakladon: Boot entry point
_start:
    call kernel_main
.hang:
    cli
    hlt
    jmp .hang
