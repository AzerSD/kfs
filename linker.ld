OUTPUT_FORMAT(elf32-i386)
ENTRY(_start)
SECTIONS
{
    . = 2M;  /* Kernel starts at 2MB */

    .text BLOCK(4K) : ALIGN(4K)
    {
        *(.multiboot2)   /* Multiboot 2 header */
        *(.text)         /* Kernel code */
    }

    .rodata BLOCK(4K) : ALIGN(4K)
    {
        *(.rodata)
    }

    .data BLOCK(4K) : ALIGN(4K)
    {
        *(.data)
    }

    .bss BLOCK(4K) : ALIGN(4K)
    {
        *(COMMON)
        *(.bss)
    }
}
