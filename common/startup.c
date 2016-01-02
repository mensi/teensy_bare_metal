#define _INTERRUPT_TABLE_SETUP_
/*
 * This file contains everything necessary to boot and jump to main()
 * 
 * It's structured in the same sequence sections will appear on flash
 */

#include "config.h"
#include "interrupt.h"
#include "interrupt_weak_isr.h"
#include "systick.h"
#include "watchdog.h"
#include "mk20dx256.h"

// Hook to customize watchdog init. Defaults to disable, implement to override.
static void watchdog_hook_default(void) { watchdog_disable(); } // Why do you have to go and make things so complicated? 
								//  Because aliases are only possible within a compilation unit
void startup_watchdog_hook(void) __attribute__ ((weak, alias("watchdog_hook_default")));

/*
 * Initial stack pointer. _eram will be set in the linker script to be
 * the end of the RAM. The stack grows "upwards", so that's where we 
 * want to start the stack.
 */
extern unsigned long _eram;

/*
 * Other linker symbols
 */
extern unsigned long _etext;
extern unsigned long _sdata;
extern unsigned long _edata;
extern unsigned long _sbss;
extern unsigned long _ebss;

/*
 * Main function we will eventually call after startup
 */
void main(void);


/*
 * Initial program counter. The address where we want to start execution.
 * The actual function is implemented further down.
 */
void __startup(void);

/*
 * Initial interrupt vector table, of which the first two entries are 
 * stack pointer and initial PC.
 */
__attribute__ ((section(".vectors"), used))
void (* const interrupt_vectors[])(void) =
{
  (void (*)(void))((unsigned long)&_eram),
  __startup,
  isr_non_maskable,
  isr_hard_fault,
  isr_memmanage_fault,
  isr_bus_fault,
  isr_usage_fault,
  isr_ignore,  // Reserved 7
  isr_ignore,  // Reserved 8
  isr_ignore,  // Reserved 9
  isr_ignore,  // Reserved 10
  isr_svcall,
  isr_debug_monitor,
  isr_ignore,  // Reserved 13
  isr_pendablesrvreq,
  isr_systick,
  isr_dma_ch0_complete,
  isr_dma_ch1_complete,
  isr_dma_ch2_complete,
  isr_dma_ch3_complete,
  isr_dma_ch4_complete,
  isr_dma_ch5_complete,
  isr_dma_ch6_complete,
  isr_dma_ch7_complete,
  isr_dma_ch8_complete,
  isr_dma_ch9_complete,
  isr_dma_ch10_complete,
  isr_dma_ch11_complete,
  isr_dma_ch12_complete,
  isr_dma_ch13_complete,
  isr_dma_ch14_complete,
  isr_dma_ch15_complete,
  isr_dma_error,
  isr_ignore, // Unused ? INT_MCM ?
  isr_flash_cmd_complete,
  isr_flash_read_collision,
  isr_low_voltage_warning,
  isr_low_voltage_wakeup,
  isr_wdog_or_emw,
  isr_ignore, // Reserved 39
  isr_i2c0,
  isr_i2c1,
  isr_spi0,
  isr_spi1,
  isr_ignore, // Teensy does not have SPI2
  isr_can0_or_msg_buf,
  isr_can0_bus_off,
  isr_can0_error,
  isr_can0_transmit_warn,
  isr_can0_receive_warn,
  isr_can0_wakeup,
  isr_i2s0_transmit,
  isr_i2s0_receive,
  isr_ignore, // Teensy does not have CAN1
  isr_ignore, // Teensy does not have CAN1
  isr_ignore, // Teensy does not have CAN1
  isr_ignore, // Teensy does not have CAN1
  isr_ignore, // Teensy does not have CAN1
  isr_ignore, // Teensy does not have CAN1
  isr_ignore, // Reserved 59
  isr_uart0_lon,
  isr_uart0_status,
  isr_uart0_error,
  isr_uart1_status,
  isr_uart1_error,
  isr_uart2_status,
  isr_uart2_error,
  isr_ignore, // Teensy does not have UART3
  isr_ignore, // Teensy does not have UART3
  isr_ignore, // Teensy does not have UART4
  isr_ignore, // Teensy does not have UART4
  isr_ignore, // Teensy does not have UART5
  isr_ignore, // Teensy does not have UART5
  isr_adc0,
  isr_adc1,
  isr_cmp0,
  isr_cmp1,
  isr_cmp2,
  isr_ftm0,
  isr_ftm1,
  isr_ftm2,
  isr_cmt,
  isr_rtc_alarm,
  isr_rtc_seconds,
  isr_pit_ch0,
  isr_pit_ch1,
  isr_pit_ch2,
  isr_pit_ch3,
  isr_pdb,
  isr_usb_otg,
  isr_usb_charger,
  isr_ignore, // Reserved 91
  isr_ignore, // Reserved 92
  isr_ignore, // Reserved 93
  isr_ignore, // Reserved 94
  isr_ignore, // Nothing according to manual, I2S0 according to headers
  isr_ignore, // Nothing according to manual, SDHC according to headers
  isr_dac0,
  isr_ignore, // Teensy does not have DAC1
  isr_tsi,
  isr_mcg,
  isr_lpt,
  isr_ignore, // Reserved 102
  isr_port_a,
  isr_port_b,
  isr_port_c,
  isr_port_d,
  isr_port_e,
  isr_ignore, // Reserved 108
  isr_ignore, // Reserved 109
  isr_software,
  isr_ignore  // Reserved 111
};

/*
 * The flash configuration appears at 0x400 and is loaded on boot.
 *   The first 8 bytes are the backdoor comparison key. 
 *   The next 4 bytes are the FPROT registers.
 *
 *   Then, there's one byte each:
 *    FSEC, FOPT, FEPROT, FDPROT
 *
 * For most of these fields, 0xFF are the permissive defaults. For
 * FSEC, we'll set SEC to 10 to put the MCU in unsecure mode for
 * unlimited flash access -> 0xFE.
 */
__attribute__ ((section(".flashconfig"), used))
const uint8_t flashconfigbytes[16] = {
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xFF, 0xFF, 0xFF
};

/*
 * Reset handler code. This function is executed when starting.
 * Optimize for space, since we are trying to squeeze in between
 * interrupt vectors and flashconfig.
 */
__attribute__ ((section(".startup"), optimize("-Os")))
void __startup(void) {
  // The CPU has a watchdog feature which is on by default,
  // so we have to configure it to not have nasty reset-surprises
  // later on.
  startup_watchdog_hook();

  // If the system was in VLLS mode, some peripherials and 
  // the I/O pins are in latched mode. We need to restore
  // config and can then acknowledge the isolation to get back
  // to normal. For now, we'll just ack TODO: properly do this
  if (PMC_REGSC & PMC_REGSC_ACKISO_MASK) PMC_REGSC |= PMC_REGSC_ACKISO_MASK;

  // There is a write-once-after-reset register that allows to
  // set which power states are available. Let's set it here.
  SMC_PMPROT = ENABLED_POWER_MODES;

  // For the sake of simplicity, enable all GPIO port clocks
  SIM_SCGC5 |= (  SIM_SCGC5_PORTA_MASK
                | SIM_SCGC5_PORTB_MASK
                | SIM_SCGC5_PORTC_MASK
	        | SIM_SCGC5_PORTD_MASK
	        | SIM_SCGC5_PORTE_MASK);

  // ----------------------------------------------------------------------------------
  // Setup clocks
  // ----------------------------------------------------------------------------------
  // See section 5 in the Freescale K20 manual for how clock distribution works
  // The limits are outlined in section 5.5:
  //   Core and System clocks: max 72 MHz
  //   Bus/peripherial clock:  max 50 MHz (integer divide of core)
  //   Flash clock:            max 25 MHz
  //
  // The teensy 3.x has a 16 MHz external oscillator
  // So we'll enable the external clock for the OSC module. Since
  // we're in high-frequency mode, also enable capacitors
  OSC_CR = OSC_CR_SC8P_MASK | OSC_CR_SC2P_MASK; // TODO This does not actually seem enable the ext crystal

  // Set MCG to very high frequency crystal and request oscillator. We have
  // to do this first so that the divisor will be correct (512 and not 16)
  MCG_C2 = MCG_C2_RANGE0(2) | MCG_C2_EREFS0_MASK;

  // Select the external reference clock for MCGOUTCLK
  // The divider for the FLL has to be chosen that we get something in 31.25 to 39.0625 kHz
  // 16MHz / 512 = 31.25 kHz -> set FRDIV to 4
  MCG_C1 =  MCG_C1_CLKS(2) | MCG_C1_FRDIV(4);

  // Wait for OSC to become ready
  while ((MCG_S & MCG_S_OSCINIT0_MASK) == 0) ;

  // Wait for the FLL to synchronize to external reference
  while ((MCG_S & MCG_S_IREFST_MASK) != 0) ;

  // Wait for the clock mode to synchronize to external
  while ((MCG_S & MCG_S_CLKST_MASK) != MCG_S_CLKST(2)) ;

  // The clock is now in FBE mode

#if F_CPU <= 16000000
  // For 16 MHz and below, the crystal is fast enough
  // -> enable BLPE mode which will disable both FLL and PLL
  MCG_C2 = MCG_C2_RANGE0(2) | MCG_C2_EREFS_MASK | MCG_C2_LP_MASK;
#else
  // We need PLL to go above 16 MHz
  #if   F_CPU == 96000000
    MCG_C5 = MCG_C5_PRDIV0(3); // 16MHz / 4 = 4MHz (this needs to be 2-4MHz)
    MCG_C6 = MCG_C6_PLLS_MASK | MCG_C6_VDIV0(0); // Enable PLL*24 = 96 MHz
  #elif F_CPU == 72000000
    MCG_C5 = MCG_C5_PRDIV0(5); // 16 MHz / 6 = 2.66 MHz (this needs to be 2-4MHz)
    MCG_C6 = MCG_C6_PLLS_MASK | MCG_C6_VDIV0(3); // Enable PLL*27 = 71.82 MHz
  #elif F_CPU == 48000000
    MCG_C5 = MCG_C5_PRDIV0(7); // 16 MHz / 8 = 2 MHz (this needs to be 2-4MHz)
    MCG_C6 = MCG_C6_PLLS_MASK | MCG_C6_VDIV0(0); // Enable PLL*24 = 48 MHz
  #elif F_CPU == 24000000
    // For 24 MHz, we'll use a 48 MHz PLL and divide in the SIM
    MCG_C5 = MCG_C5_PRDIV0(7); // 16 MHz / 8 = 2 MHz (this needs to be 2-4MHz)
    MCG_C6 = MCG_C6_PLLS_MASK | MCG_C6_VDIV0(0); // Enable PLL*24 = 48 MHz
  #else
    #error "Unknown F_CPU value"
  #endif

  // Now that we setup and enabled the PLL, wait for it to become active
  while (!(MCG_S & MCG_S_PLLST_MASK)) ;
  // and locked
  while (!(MCG_S & MCG_S_LOCK0_MASK)) ;
#endif

  // Next up: Setup clock dividers for MCU, peripherials, flash and USB
  // This is done by the SIM (System Integration Module)
  // There are two registers:
  //  SIM_CLKDIV1:
  //   OUTDIV1: Core/system clock divider
  //   OUTDIV2: Peripherial/Bus clock
  //   OUTDIV4: Flash clock
  //  SIM_CLKDIV2:
  //   USBDIV: Divisor
  //   USBFRAC: Fraction
  //   Output is input_clock*(USBFRAC+1)/(USBDIV+1)
  //
  // USB needs a 48MHz clock, so the divider should be setup accordingly. Also,
  // for the USB FS OTG controller to work, the system clock needs to be >= 20 MHz
#if F_CPU == 96000000
  // 96 MHz core, 48 MHz bus, 24 MHz flash (OVERCLOCKED!)
  SIM_CLKDIV1 = SIM_CLKDIV1_OUTDIV1(0) | SIM_CLKDIV1_OUTDIV2(1) | SIM_CLKDIV1_OUTDIV4(3);
  SIM_CLKDIV2 = SIM_CLKDIV2_USBDIV(1); // 96 * 1/2 = 48
#elif F_CPU == 72000000
  // 72 MHz core, 36 MHz bus, 24 MHz flash
  SIM_CLKDIV1 = SIM_CLKDIV1_OUTDIV1(0) | SIM_CLKDIV1_OUTDIV2(1) | SIM_CLKDIV1_OUTDIV4(2);
  SIM_CLKDIV2 = SIM_CLKDIV2_USBDIV(2) | SIM_CLKDIV2_USBFRAC_MASK; // 72 * 2/3 = 48
#elif F_CPU == 48000000
  // 48 MHz core, 48 MHz bus, 24 MHz flash, USB = 96 / 2
  SIM_CLKDIV1 = SIM_CLKDIV1_OUTDIV1(0) | SIM_CLKDIV1_OUTDIV2(0) | SIM_CLKDIV1_OUTDIV4(1);
  SIM_CLKDIV2 = SIM_CLKDIV2_USBDIV(0); // 48 * 1/1 = 48
#elif F_CPU == 24000000
  // PLL is 48 MHz
  // 24 MHz core, 24 MHz bus, 24 MHz flash
  SIM_CLKDIV1 = SIM_CLKDIV1_OUTDIV1(1) | SIM_CLKDIV1_OUTDIV2(1) | SIM_CLKDIV1_OUTDIV4(1);
  SIM_CLKDIV2 = SIM_CLKDIV2_USBDIV(0); // 48 * 1/1 = 48

  // -- For the modes <= 16 MHz, we have the MCG clock on 16 MHz, without FLL/PLL
  //    Also, USB is not possible
#elif F_CPU == 16000000
  // 16 MHz core, 16 MHz bus, 16 MHz flash
  SIM_CLKDIV1 = SIM_CLKDIV1_OUTDIV1(0) | SIM_CLKDIV1_OUTDIV2(0) | SIM_CLKDIV1_OUTDIV4(0);
#elif F_CPU == 8000000
  // 8 MHz core, 8 MHz bus, 8 MHz flash
  SIM_CLKDIV1 = SIM_CLKDIV1_OUTDIV1(1) | SIM_CLKDIV1_OUTDIV2(1) | SIM_CLKDIV1_OUTDIV4(1);
#else
  #error "Unsupported F_CPU value"
#endif

  // The dividers are set, so we can transition over to PLL for > 16 MHz
#if F_CPU > 16000000
  // Switch clock source to PLL, keep FLL divider at 512
  MCG_C1 = MCG_C1_CLKS(0) | MCG_C1_FRDIV(4);

  // Wait for the clock to sync
  while ((MCG_S & MCG_S_CLKST_MASK) != MCG_S_CLKST(3)) ;

  // Use PLL for USB and Bus/peripherals, core for trace and put OSCERCLK0 on CLKOUT pin
  SIM_SOPT2 = SIM_SOPT2_USBSRC_MASK | SIM_SOPT2_PLLFLLSEL_MASK | SIM_SOPT2_TRACECLKSEL_MASK | SIM_SOPT2_CLKOUTSEL(6);
#endif


  // ----------------------------------------------------------------------------------
  // Relocate data from flash to RAM as necessary
  // ----------------------------------------------------------------------------------
  //
  // At the minimum, the .data and .bss sections have to be setup in RAM. Also, since
  // they are aligned to 4 bytes, we can use uint32s for copying (which is faster than
  // byte by byte)
  uint32_t * src = &_etext;
  uint32_t * dest = &_sdata;
  while (dest < &_edata) *dest++ = *src++;

  // Also zero out .bss
  dest = &_sbss;
  while (dest < &_ebss) *dest++ = 0;

  // TODO: Relocate interrupt vector to RAM for speed?


  // Init systick?
#if ENABLE_SYSTICK_HANDLER
  systick_init();
#endif

  // Enable interrupts before entering main?
#if ENABLE_INTERRUPTS_ON_STARTUP
  interrupt_enable();
#endif

  // After everthing is done, call main
  main(); 

  // This should be unreachable code as long as main() does not return.
  // To avoid running the instruction pointer into places it shouldn't go, 
  // loop forever
  // TODO: Going into sleep would maybe be a better solution
  while (1);
}
