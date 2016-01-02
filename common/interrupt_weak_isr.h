#ifndef _INTERRUPT_WEAK_ISR_H_
#define _INTERRUPT_WEAK_ISR_H_

#ifndef _INTERRUPT_TABLE_SETUP_
#error "This file should only be included where the interrupt vector table is defined"
#endif

#include "interrupt.h"

/*
 * Interrupt service routine defaults.
 *
 * This header defines weak symbols for all ISRs and should therefore only be 
 * included by startup.c
 */

static void isr_panic_alias(void) {
  isr_panic();
}

static void isr_ignore_alias(void) {
  isr_ignore();
}

void isr_non_maskable(void)	     __attribute__ ((weak, alias("isr_panic_alias")));
void isr_hard_fault(void)	     __attribute__ ((weak, alias("isr_panic_alias")));
void isr_memmanage_fault(void)	     __attribute__ ((weak, alias("isr_panic_alias")));
void isr_bus_fault(void)	     __attribute__ ((weak, alias("isr_panic_alias")));
void isr_usage_fault(void)	     __attribute__ ((weak, alias("isr_panic_alias")));

void isr_svcall(void)		     __attribute__ ((weak, alias("isr_ignore_alias")));
void isr_debug_monitor(void)	     __attribute__ ((weak, alias("isr_ignore_alias")));

void isr_pendablesrvreq(void)	     __attribute__ ((weak, alias("isr_ignore_alias")));
void isr_systick(void)		     __attribute__ ((weak, alias("isr_ignore_alias")));
void isr_dma_ch0_complete(void)	     __attribute__ ((weak, alias("isr_ignore_alias")));
void isr_dma_ch1_complete(void)	     __attribute__ ((weak, alias("isr_ignore_alias")));
void isr_dma_ch2_complete(void)	     __attribute__ ((weak, alias("isr_ignore_alias")));
void isr_dma_ch3_complete(void)	     __attribute__ ((weak, alias("isr_ignore_alias")));
void isr_dma_ch4_complete(void)	     __attribute__ ((weak, alias("isr_ignore_alias")));
void isr_dma_ch5_complete(void)	     __attribute__ ((weak, alias("isr_ignore_alias")));
void isr_dma_ch6_complete(void)	     __attribute__ ((weak, alias("isr_ignore_alias")));
void isr_dma_ch7_complete(void)	     __attribute__ ((weak, alias("isr_ignore_alias")));
void isr_dma_ch8_complete(void)	     __attribute__ ((weak, alias("isr_ignore_alias")));
void isr_dma_ch9_complete(void)	     __attribute__ ((weak, alias("isr_ignore_alias")));
void isr_dma_ch10_complete(void)     __attribute__ ((weak, alias("isr_ignore_alias")));
void isr_dma_ch11_complete(void)     __attribute__ ((weak, alias("isr_ignore_alias")));
void isr_dma_ch12_complete(void)     __attribute__ ((weak, alias("isr_ignore_alias")));
void isr_dma_ch13_complete(void)     __attribute__ ((weak, alias("isr_ignore_alias")));
void isr_dma_ch14_complete(void)     __attribute__ ((weak, alias("isr_ignore_alias")));
void isr_dma_ch15_complete(void)     __attribute__ ((weak, alias("isr_ignore_alias")));
void isr_dma_error(void)             __attribute__ ((weak, alias("isr_ignore_alias")));

void isr_flash_cmd_complete(void)    __attribute__ ((weak, alias("isr_ignore_alias")));
void isr_flash_read_collision(void)  __attribute__ ((weak, alias("isr_ignore_alias")));
void isr_low_voltage_warning(void)   __attribute__ ((weak, alias("isr_ignore_alias")));
void isr_low_voltage_wakeup(void)    __attribute__ ((weak, alias("isr_ignore_alias")));
void isr_wdog_or_emw(void)           __attribute__ ((weak, alias("isr_ignore_alias")));

void isr_i2c0(void)                  __attribute__ ((weak, alias("isr_ignore_alias")));
void isr_i2c1(void)                  __attribute__ ((weak, alias("isr_ignore_alias")));
void isr_spi0(void)                  __attribute__ ((weak, alias("isr_ignore_alias")));
void isr_spi1(void)                  __attribute__ ((weak, alias("isr_ignore_alias")));

void isr_can0_or_msg_buf(void)       __attribute__ ((weak, alias("isr_ignore_alias")));
void isr_can0_bus_off(void)          __attribute__ ((weak, alias("isr_ignore_alias")));
void isr_can0_error(void)            __attribute__ ((weak, alias("isr_ignore_alias")));
void isr_can0_transmit_warn(void)    __attribute__ ((weak, alias("isr_ignore_alias")));
void isr_can0_receive_warn(void)     __attribute__ ((weak, alias("isr_ignore_alias")));
void isr_can0_wakeup(void)           __attribute__ ((weak, alias("isr_ignore_alias")));
void isr_i2s0_transmit(void)         __attribute__ ((weak, alias("isr_ignore_alias")));
void isr_i2s0_receive(void)          __attribute__ ((weak, alias("isr_ignore_alias")));

void isr_uart0_lon(void)             __attribute__ ((weak, alias("isr_ignore_alias")));
void isr_uart0_status(void)          __attribute__ ((weak, alias("isr_ignore_alias")));
void isr_uart0_error(void)           __attribute__ ((weak, alias("isr_ignore_alias")));
void isr_uart1_status(void)          __attribute__ ((weak, alias("isr_ignore_alias")));
void isr_uart1_error(void)           __attribute__ ((weak, alias("isr_ignore_alias")));
void isr_uart2_status(void)          __attribute__ ((weak, alias("isr_ignore_alias")));
void isr_uart2_error(void)           __attribute__ ((weak, alias("isr_ignore_alias")));


void isr_adc0(void)                  __attribute__ ((weak, alias("isr_ignore_alias")));
void isr_adc1(void)                  __attribute__ ((weak, alias("isr_ignore_alias")));
void isr_cmp0(void)                  __attribute__ ((weak, alias("isr_ignore_alias")));
void isr_cmp1(void)                  __attribute__ ((weak, alias("isr_ignore_alias")));
void isr_cmp2(void)                  __attribute__ ((weak, alias("isr_ignore_alias")));
void isr_ftm0(void)                  __attribute__ ((weak, alias("isr_ignore_alias")));
void isr_ftm1(void)                  __attribute__ ((weak, alias("isr_ignore_alias")));
void isr_ftm2(void)                  __attribute__ ((weak, alias("isr_ignore_alias")));
void isr_cmt(void)                   __attribute__ ((weak, alias("isr_ignore_alias")));
void isr_rtc_alarm(void)             __attribute__ ((weak, alias("isr_ignore_alias")));
void isr_rtc_seconds(void)           __attribute__ ((weak, alias("isr_ignore_alias")));
void isr_pit_ch0(void)               __attribute__ ((weak, alias("isr_ignore_alias")));
void isr_pit_ch1(void)               __attribute__ ((weak, alias("isr_ignore_alias")));
void isr_pit_ch2(void)               __attribute__ ((weak, alias("isr_ignore_alias")));
void isr_pit_ch3(void)               __attribute__ ((weak, alias("isr_ignore_alias")));
void isr_pdb(void)                   __attribute__ ((weak, alias("isr_ignore_alias")));
void isr_usb_otg(void)               __attribute__ ((weak, alias("isr_ignore_alias")));
void isr_usb_charger(void)           __attribute__ ((weak, alias("isr_ignore_alias")));

void isr_dac0(void)                  __attribute__ ((weak, alias("isr_ignore_alias")));

void isr_tsi(void)                   __attribute__ ((weak, alias("isr_ignore_alias")));
void isr_mcg(void)                   __attribute__ ((weak, alias("isr_ignore_alias")));
void isr_lpt(void)                   __attribute__ ((weak, alias("isr_ignore_alias")));

void isr_port_a(void)                __attribute__ ((weak, alias("isr_ignore_alias")));
void isr_port_b(void)                __attribute__ ((weak, alias("isr_ignore_alias")));
void isr_port_c(void)                __attribute__ ((weak, alias("isr_ignore_alias")));
void isr_port_d(void)                __attribute__ ((weak, alias("isr_ignore_alias")));
void isr_port_e(void)                __attribute__ ((weak, alias("isr_ignore_alias")));

void isr_software(void)              __attribute__ ((weak, alias("isr_ignore_alias")));

#endif
