/* Simple RISC-V linker script */

OUTPUT_FORMAT("elf32-littleriscv", "elf32-littleriscv", "elf32-littleriscv")
/*OUTPUT_ARCH(rv32i) */

ENTRY(_start)

SECTIONS
{
    . = 0x100000;
    .text :
    {
        *(.text)
    }

    .data :
    {
        *(.data)
    }

    /* Other sections can be added as needed */

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
