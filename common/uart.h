#ifndef _UART_H_
#define _UART_H_

#include "mk20dx256.h"

void uart_setup(UART_MemMapPtr base, int baud);
void uart_putchar(UART_MemMapPtr base, char ch);
void uart_putline(UART_MemMapPtr base, char * str);

#endif
