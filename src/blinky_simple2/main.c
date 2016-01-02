#include "mk20dx256.h"
#include "pins.h"
#include "interrupt.h"
#include "uart.h"

// Pin 13 has the onboard LED
#define BLINK_PIN 13

void delay(unsigned int duration) {
  // Hacky approximation: We're running at 72 MHz by default, so let's
  // just take something around 10 cycles long and do it 72000/10 times
  // to wait one millisecond. With interrupts disabled, this should be
  // in the ballpark of real time.
  while (duration > 0) {
    int inner = 72000 / 10;
    while (inner--) {
      __asm__ volatile ("nop");
      __asm__ volatile ("nop");
      __asm__ volatile ("nop");
      __asm__ volatile ("nop");
      __asm__ volatile ("nop");
      __asm__ volatile ("nop");
      __asm__ volatile ("nop");
    }
    duration--;
  }
}

void isr_systick(void) {
  uart_putchar(UART0_BASE_PTR, '.');
}

int main(void) {
  // We'll use UART0, so set it up
  PIN0_PORT_PCR = PORT_PCR_MUX(3);
  PIN1_PORT_PCR = PORT_PCR_MUX(3);
  uart_setup(UART0_BASE_PTR, 115200);

  uart_putline(UART0_BASE_PTR, "\r\nHello there!");

  // Set direction to output
  PIN_GPIO_PDDR( BLINK_PIN ) = (1 << PIN_PIN( BLINK_PIN ));

  // Select the GPIO function on the port
  PIN_PORT_PCR( BLINK_PIN ) = PORT_PCR_MUX(1) | PORT_PCR_SRE_MASK | PORT_PCR_DSE_MASK;

  // Let's also systick!
  interrupt_enable();
  SYST_RVR = 7200000;//(SYST_CALIB & SysTick_CALIB_TENMS_MASK) * 10;
  SYST_CSR = SysTick_CSR_ENABLE_MASK | SysTick_CSR_TICKINT_MASK | SysTick_CSR_CLKSOURCE_MASK;

  while (1) {
    pin_gpio_set_high(BLINK_PIN);
    uart_putchar(UART0_BASE_PTR, 'H');
    delay(500);
    pin_gpio_set_low(BLINK_PIN);
    uart_putchar(UART0_BASE_PTR, 'L');
    delay(500);
  }
}

