#include "mk20dx256.h"

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
  // Pin 13 (with the onboard LED) in teensy labelling == GPIO Port C, Pin 5
  // Set GPIOC pin 5 to output direction
  GPIOC_PDDR = (1<<5);

  // Set the MUX on Port C Pin 5 to use GPIO as the source
  PORTC_PCR5 = PORT_PCR_MUX(1) | PORT_PCR_SRE_MASK | PORT_PCR_DSE_MASK;

  while (1) {
    GPIOC_PSOR = (1<<5); // Set GPIO C pin 5 (make it HIGH)
    delay(500);
    GPIOC_PCOR = (1<<5); // Clear GPIO C pin 5 (make it LOW)
    delay(500);
  }
}

