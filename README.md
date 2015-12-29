# Bare-metal Code Examples for the Teensy 3.1/3.2
This repository contains bare-metal (no Arduino compatibility) C code written from scratch based on the reference manuals.
It's aimed to be heavily commented to allow a smooth start for C-developers diving into embedded coding with the 
[Teensy](https://www.pjrc.com/teensy/).

The code is split into two parts:

 * **common** contains general-purpose/framework code, Makefile, linker script etc. shared amongst the different examples.
 * **src** has subdirectories with different examples.

To start experimenting yourself, simply create a new subfolder in *src* and create a symlink *Makefile -> ../../common/Makefile*.

## Prerequisites

 * GNU make
 * GCC arm-none-eabi
 * libusb (for teensy_loader_cli)

On Debian/Ubuntu, the following should install the necessary requirements:

```bash
apt-get install build-essential gcc-arm-none-eabi libusb-dev
```

If you did not use `--recursive` when cloning, don't forget to init submodules (for teensy_loader_cli):

```bash
git submodule init
git submodule update
```

You should now be able to run `make build` in any of the examples in *src*. Use `make load` to also load the resulting hex file with teensy_loader_cli.

## Reading Material
 * [Kinetis Peripheral Module Quick Reference (KQRUG)](http://cache.freescale.com/files/32bit/doc/quick_ref_guide/KQRUG.pdf)  
   Highly recommended read as it explains a lot of the components of the Kinetis family MCUs with concrete examples.
 * [K20 Sub-Family Reference Manual (K20P64M72SF1RM)](https://www.pjrc.com/teensy/K20P64M72SF1RM.pdf)  
   Reference manual of the MK20DX256VLH7 processor used in the Teensy 3.1/3.2
 * [K20 Sub-Family Datasheet (K20P64M72SF1)](http://cache.freescale.com/files/32bit/doc/data_sheet/K20P64M72SF1.pdf)  
   Operating characteristics, package pinouts.
 * [ARM Cortex‑M4 Processor Technical Reference Manual](http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.100166_0001_00_en/index.html)  
   Reference for the Cortex-M4. The interesting bits are however mostly in the ARMv7-M architecture reference.
 * [ARMv7-M Architecture Reference Manual](http://infocenter.arm.com/help/topic/com.arm.doc.ddi0403e.b/index.html)  
   This contains everything about the ARM-specific parts of the Kinetis MCU. This for example includes the NVIC or MPU.
 * [Teensy Schematic](https://www.pjrc.com/teensy/schematic.html)
