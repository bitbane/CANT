/* Entry Point */
ENTRY(Reset_Handler)

_estack = 0x2001C000;
_stack_size = 64K;

MEMORY
{
    ram (rwx)   : ORIGIN = 0x20000000, LENGTH = 112K
    rom (rx)    : ORIGIN = 0x08000000, LENGTH = 1024K
}

SECTIONS
{
    . = 0x0;

    .text :
    {
        *(.isr_vector)
        *(.text)
        *(.text.*)
    } >rom

    .rodata :
    {
        . = ALIGN(4);
        *(.rodata)
        *(.rodata.*)
        . = ALIGN(4);
    } >rom

    . = 0x20000000;
    _sidata = LOADADDR(.data);
    .data :
    {
        . = ALIGN(4);
        _sdata = .;
        *(.data)
        *(.data.*)
        . = ALIGN(4);
        _edata = .;
    } >ram AT > rom

    .bss :
    {
        . = ALIGN(4);
        _sbss = .;
        *(.bss)
        *(.bss.*)
        . = ALIGN(4);
        _ebss = .;
    } >ram

    _heap_bottom = .;
    _heap_top = ORIGIN(ram) + LENGTH(ram) - _stack_size;

    _stack_bottom = _heap_top;
    _stack_top = ORIGIN(ram) + LENGTH(ram);
}

