#include "pins.h"
#include "uart.h"
#include "delay.h"

#define OUTPUT_PIN 2

int main(void) {
  uart0_setup_default();
  uart0_putline("\r\nbitbang_square_wave");

  PIN_GPIO_PDDR( OUTPUT_PIN ) = (1 << PIN_PIN( OUTPUT_PIN ));
  PIN_PORT_PCR( OUTPUT_PIN ) = PORT_PCR_MUX(1) | PORT_PCR_SRE_MASK | PORT_PCR_DSE_MASK;

  while(1) {
    pin_gpio_set_high(OUTPUT_PIN);
    delay_ms(1);
    pin_gpio_set_low(OUTPUT_PIN);
    delay_ms(2);
  }
}
