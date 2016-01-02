#ifndef _SYSTICK_H_
#define _SYSTICK_H_

extern volatile unsigned int systick_ticks;

void systick_init();
unsigned int systick_get_ms();

#endif
