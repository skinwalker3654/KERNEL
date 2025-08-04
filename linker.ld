ENTRY(_start)
SECTIONS {
    .text : {*(.multiboot_header) *(.text)}
    .rodata : {*(.rodata)}
    .data : {*(.data)}
    .bss : {*(.bss)}
}
