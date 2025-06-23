/* Simple linker script for ARM Cortex-M4 bare-metal compilation */
/* This is a minimal example for CI/CD testing purposes */

MEMORY
{
    FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 1024K
    RAM (rwx)  : ORIGIN = 0x20000000, LENGTH = 128K
}

ENTRY(main)

SECTIONS
{
    .text : {
        . = ALIGN(4);
        *(.text)
        *(.text*)
        . = ALIGN(4);
    } > FLASH

    .data : {
        . = ALIGN(4);
        *(.data)
        *(.data*)
        . = ALIGN(4);
    } > RAM AT > FLASH

    .bss : {
        . = ALIGN(4);
        *(.bss)
        *(.bss*)
        *(COMMON)
        . = ALIGN(4);
    } > RAM

    /DISCARD/ : {
        *(.note.gnu.build-id)
        *(.comment)
        *(.ARM.attributes)
    }
}
