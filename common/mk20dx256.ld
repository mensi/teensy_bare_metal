/*
 * First off, let's define the regions for flash and RAM.
 * The teensy 3.1/3.2 uses a MK20DX256VLH7 with 256K flash starting at 0
 *
 * The RAM is split into two halfes called SRAM_L and SRAM_U.
 * SRAM_L ends at 0x1fff ffff and SRAM_U starts with 0x2000 0000
 * for most purposes, both blocks can be used as one. However, when in
 * VLLS2 power mode, only SRAM_U is powered.
 *
 * For the 64K of RAM in the MK20DX256VLH7, this translates to a
 * start address of 0x1fff8000
 */

MEMORY
{
  FLASH (rx)  : ORIGIN = 0x00000000, LENGTH = 256K
  RAM   (rwx) : ORIGIN = 0x1FFF8000, LENGTH =  64K
}

SECTIONS
{
  .text : {
    /* The .text section is placed at the start in flash, which starts at address 0 */
    . = 0;

    /* First up is the interrupt vectors. The first two entries are even more special,
     * as they old the initial stack pointer and the initial program counter.
     * Mark this section KEEP to prevent it being garbage collected.
     * The syntax *(.foo) means take the .foo sections from all files (*). */
    KEEP(*(.vectors))

    /* We have some space between the end of the vectors and the flash config,
     * so let's squeeze in some startup code. If it gets too long, we'll have
     * to put it elsewhere. */
    *(.startup*)

    /* The flashconfig has to appear at 0x400, so we'll move there by explicitly
     * assigning the location counter (.). Since the location counter can only
     * move forward, this also serves as a protection from .startup spilling over
     * into .flashconfig. 
     *
     * WARNING: Be very careful with the flashconfig, as wrong values can lead
     * to various degrees of bricking your teensy */
    . = 0x400;
    KEEP(*(.flashconfig*))

    /* Now let's load all the code */
    *(.text*)

    /* And read-only data */
    *(.rodata*)
  } > FLASH = 0xFF

  /* This is the end of the data that will remain in flash. We need to
   * keep this for later for any sections that are loaded in flash but
   * need to be relocated to RAM */
  . = ALIGN(4);
  _etext = .;


  /* Data contains all the (mutable) variables with predefined data.
   * Therefore, we need to put it in flash but the code should refer
   * to addresses in RAM.
   * AT (_etext) places the "payload" after everything we put in flash
   * so far, but > RAM puts this section in RAM for linking.
   *
   * This means that early during the boot, we have to copy this from
   * flash to ram at the provided locations. We therefore need to 
   * save the start and end (_sdata, _edata) for the memcopy. 
   *
   * We also align start and end to 4 byte = 32bit boundaries so we can
   * simply copy whole registers/int32 instead of byte per byte */
  .data : AT (_etext) {
    . = ALIGN(4);
    _sdata = .; 
    *(.data*)
    . = ALIGN(4);
    _edata = .; 
  } > RAM

  /* The .bss section needs to be zeroed out, so it's similar to
   * .data in that we need to remember start and end and make it easy
   * to zero in int32 sizes instead of byte per byte. We however
   * don't need to put this in flash */
  .bss : {
    . = ALIGN(4);
    _sbss = .;
    *(.bss*)
    *(COMMON)
    . = ALIGN(4);
    _ebss = .;
  } > RAM

  /* Create a symbol for the end of the RAM as we will put the stack there */
  _eram = ORIGIN(RAM) + LENGTH(RAM);
}

