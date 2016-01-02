#include "delay.h"
#include "systick.h"

/*
 * Reads the number of elapsed milliseconds from systick
 */
void delay_ms_systick(unsigned int milliseconds) {
  unsigned int cur = systick_get_ms();
  unsigned int end = cur + milliseconds;

  // Handle sum overflow
  if (end < cur) while (systick_get_ms() > cur);

  // Normal case
  while (systick_get_ms() < end);
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
