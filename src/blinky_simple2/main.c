#include "mk20dx256.h"
#include "pins.h"

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

int main(void) {
  // Pin 13 has the onboard LED
  // Set direction to output
  PIN_GPIO_PDDR( BLINK_PIN ) = (1 << PIN_PIN( BLINK_PIN ));

  // Select the GPIO function on the port
  PIN_PORT_PCR( BLINK_PIN ) = PORT_PCR_MUX(1) | PORT_PCR_SRE_MASK | PORT_PCR_DSE_MASK;

  while (1) {
    pin_gpio_set_high(BLINK_PIN);
    delay(500);
    pin_gpio_set_low(BLINK_PIN);
    delay(500);
  }
}

