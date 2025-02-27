section .multiboot
dd 0xE85250D6   ; Multiboot 2 Magic Number
dd 0             ; Architecture (0 for i386)
dd header_end - header_start  ; Header Length
dd -(0xE85250D6 + 0 + (header_end - header_start)) ; Checksum

header_start:

; Multiboot 2 required end tag
align 8
dw 0  ; Tag type (End tag)
dw 0  ; Reserved
dd 8  ; Size of the tag (including size field)

header_end:

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


