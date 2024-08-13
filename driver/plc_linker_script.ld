/* GROUP(libnosys.a) */

_Min_Heap_Size = 0x00; /* required amount of heap */
_Min_Stack_Size = 0x00; /* required amount of stack */

/* ENTRY(main) */

SECTIONS
{
    . = 0x00000;

    .symbol_table : 
    {
        KEEP(*(*.symbol_table)) 
    }

    . = 0x00050;

    .text : 
    { 
        *(.text) 
        __exidx_start = .;
        __exidx_end = .;
    }

    .data : 
    { 

        *(.data)    

    }

    .bss : 
    { 
        __bss_start__ = .;
        *(.bss)
        __bss_end__ = .;
    }

    /* create this section only for compiler to STFU */
    ._user_heap_stack :
    {
        . = ALIGN(8);
        PROVIDE ( end = . );
        PROVIDE ( _end = . );
        . = . + _Min_Heap_Size;
        . = . + _Min_Stack_Size;
        . = ALIGN(8);
    }
}
