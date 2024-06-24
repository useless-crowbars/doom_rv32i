OUTPUT_FORMAT("elf32-littleriscv", "elf32-littleriscv", "elf32-littleriscv")
/*OUTPUT_ARCH(rv32i)*/

ENTRY(_start)

SECTIONS
{
    . = 0x0;
    .text :
    {
        *(.text)
    }

    . = 0x100000;

    .data : { *(.data) }
    .sdata : { *(.sdata) }
    .sbss : { *(.sbss) }
    .bss : { *(.bss) }

    . = 0x10000000;
    .rodata :
    {
        *(.rodata)
    }

    /DISCARD/ :
    {
        *(.debug_info)
        *(.debug_abbrev)
        *(.debug_aranges)
        *(.debug_line)
        *(.debug_str)
        *(.debug_line_str)
        *(.debug_frame)
        *(.comment)
        *(.riscv.attributes)
    }
}
