#include "uart.h"
#include "config.h"

int uart_get_port_index(UART_MemMapPtr base) {
  if (base == UART0_BASE_PTR)
    return 0;
  else if (base == UART1_BASE_PTR)
    return 1;
  else if (base == UART2_BASE_PTR)
    return 2;
  else if (base == UART3_BASE_PTR)
    return 3;
  else if (base == UART4_BASE_PTR)
    return 4;

  // So, if we get here, the base pointer is off.
  // For now, just go into an endless loop until we have
  // a better failure mode.
  while (1);
}

void uart_setup(UART_MemMapPtr base, int baud) {
  // First off, enable the peripherial clock for the UART
  switch (uart_get_port_index(base)) {
    case 0: SIM_SCGC4 |= SIM_SCGC4_UART0_MASK; break;
    case 1: SIM_SCGC4 |= SIM_SCGC4_UART1_MASK; break;
    case 2: SIM_SCGC4 |= SIM_SCGC4_UART2_MASK; break;
    case 3: SIM_SCGC4 |= SIM_SCGC4_UART3_MASK; break;
    case 4: SIM_SCGC1 |= SIM_SCGC1_UART4_MASK; break;
  }

  // Set defaults (8bit no parity)
  base->C1 = 0;

  // Set the baud rate. This has 3 components:
  //  BDH = Contains interrupt enable bits and the high 5 bits of the divisor
  //  BDL = Contains the low 8 bits of the divisor
  //  C4_BRFA = The fine adjust value
  //
  //  tx baud = module clock / (16 * (divisor + BRFA/32))
  int divisor = F_CPU / (baud * 16);
  int brfa = (2*F_CPU) / baud - divisor * 32;

  base->BDH = UART_BDH_SBR(divisor >> 8);
  base->BDL = UART_BDL_SBR(divisor);
  base->C4 = UART_C4_BRFA(brfa);

  // Enable Tx
  base->C2 = UART_C2_TE_MASK;
}

void uart_putchar(UART_MemMapPtr base, char ch) {
  // Wait until space is available
  while(!(base->S1 & UART_S1_TDRE_MASK));

  // Write character
  base->D = (uint8_t)ch;
}

void uart_putline(UART_MemMapPtr base, char * str) {
  while (*str != '\0') {
    uart_putchar(base, *str);
    str++;
  }

  uart_putchar(base, '\r');
  uart_putchar(base, '\n');
}

