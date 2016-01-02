#ifndef _DELAY_H_
#define _DELAY_H_

/*
 * Main "API". These functions will call the best available implementation.
 */
inline void delay_us(unsigned int microseconds);
inline void delay_ms(unsigned int milliseconds);

/*
 * Simple implementations that just busywait. These will not be precise,
 * especially when interrupts are enabled and firing.
 */
void delay_us_simple(unsigned int microseconds);
void delay_ms_simple(unsigned int milliseconds);

#endif
