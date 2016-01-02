#include "config.h"
#include "delay.h"

inline void delay_us(unsigned int microseconds) {
  delay_us(microseconds);
}

inline void delay_ms(unsigned int milliseconds) {
  delay_ms(milliseconds);
}

/*
 * This implementation will be more imprecise with lower CPU frequencies and
 * not properly work at all with anything below 5 MHz
 */
void delay_us_simple(unsigned int microseconds) {
  while (microseconds--) {
    unsigned int inner = F_CPU / 5000000;

    // This loop should take 5 cycles
    while (inner--)
      __asm__ volatile ("nop");
  }
}

/*
 * For milliseconds, this loop approach is not too far off reality as long
 * as it runs uninterrupted.
 */
void delay_ms_simple(unsigned int milliseconds) {
  while (milliseconds--) {
    unsigned int inner = F_CPU / 10000;

    // This loop should take 10 cycles:
    //  inner--        sub: 1 cycle
    //  inner == 0     beq: 1 cycle if not taken
    //  6*nop          nop: 1 cycle
    //  endwhile       b:   1 + (1-3) cycles
    while (inner--) {
      __asm__ volatile ("nop");
      __asm__ volatile ("nop");
      __asm__ volatile ("nop");
      __asm__ volatile ("nop");
      __asm__ volatile ("nop");
      __asm__ volatile ("nop");
    }
  }
}

