#ifndef _UART_H_
#define _UART_H_

#include "mk20dx256.h"
#include "pins.h"

void uart_setup(UART_MemMapPtr base, int baud);
void uart_putchar(UART_MemMapPtr base, char ch);
void uart_putline(UART_MemMapPtr base, char * str);


/*
 * Convenience function to setup UART0 on pins 0 and 1 with 115200 baud
 */
inline static void uart0_setup_default() {
  PIN0_PORT_PCR = PORT_PCR_MUX(3);
  PIN1_PORT_PCR = PORT_PCR_MUX(3);
  uart_setup(UART0_BASE_PTR, 115200);
}

inline static void uart0_putchar(char ch) {
  uart_putchar(UART0_BASE_PTR, ch);
}

inline static void uart0_putline(char * str) {
  uart_putline(UART0_BASE_PTR, str);
}

#endif
