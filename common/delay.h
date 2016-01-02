#ifndef _DELAY_H_
#define _DELAY_H_

#include "config.h"

/*
 * Simple implementations that just busywait. These will not be precise,
 * especially when interrupts are enabled and firing.
 */
void delay_us_simple(unsigned int microseconds);
void delay_ms_simple(unsigned int milliseconds);

/*
 * More advanced, SysTick-based implementation
 */
void delay_ms_systick(unsigned int milliseconds);

/*
 * Main "API". These functions will call the best available implementation.
 */
inline static void delay_us(unsigned int microseconds) {
    delay_us_simple(microseconds);
}

inline static void delay_ms(unsigned int milliseconds) {
#if ENABLE_SYSTICK_HANDLER
  delay_ms_systick(milliseconds);
#else
  delay_ms_simple(milliseconds);
#endif
}

#endif
