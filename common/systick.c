#include "config.h"
#include "systick.h"
#include "mk20dx256.h"

#define F_SYSTICK 10

volatile unsigned int systick_ticks = 0;

void systick_init() {
  SYST_RVR = F_CPU / F_SYSTICK;
  SYST_CSR = SysTick_CSR_ENABLE_MASK | SysTick_CSR_TICKINT_MASK | SysTick_CSR_CLKSOURCE_MASK;
}

unsigned int systick_get_ms() {
  return systick_ticks * (1000 / F_SYSTICK) + 
    (F_CPU / F_SYSTICK - (SysTick_CVR_CURRENT_MASK & SYST_CVR)) / (F_CPU/1000);
}

#if ENABLE_SYSTICK_HANDLER
void isr_systick(void) {
  systick_ticks++;
}
#endif
