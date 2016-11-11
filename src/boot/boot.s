/* Constants */
    .set ALIGN,     1<<0
    .set MEMINFO,   1<<1
    .set FLAGS,     ALIGN | MEMINFO
    .set MAGIC,     0x1badb002
    .set CHECKSUM,  -(MAGIC + FLAGS)

/* Multiboot header */
    .section .multiboot
    .align 4
    .long MAGIC
    .long FLAGS
    .long CHECKSUM

/* Stack space */
    .section .bss
    .align 16
stack_bottom:
    .skip 16*1024
stack_top:


/* Entry point */
    .section .text
    .global _start
    .type _start, @function
_start:
    mov $stack_top, %esp
    call kernel_main
    cli
1:  hlt
    jmp 1b

    .size _start, . - _start
