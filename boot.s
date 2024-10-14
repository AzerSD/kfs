section .multiboot
align 4
dd 0x1BADB002     ; Magic number
dd 0x0            ; Flags (0 for now)
dd - (0x1BADB002 + 0x0) ; Checksum

global _start
section .text
extern kernel_main

_start:
    ; Set up the stack and jump to kernel_main
    cli
    mov esp, stack_space + stack_size
    call kernel_main
    hlt

section .bss
align 16
stack_space: resb 16384  ; 16 KB stack
stack_size equ $ - stack_space
 