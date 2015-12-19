#include "mk20dx256.h"

#define WDOG_UNLOCK_SEQ1  ((uint16_t)0xC520)
#define WDOG_UNLOCK_SEQ2  ((uint16_t)0xD928)

void watchdog_disable(void) {
  // First, we have to unlock the watch dog by writing two magic
  // values. This has to happen within 20 bus clock cycles.
  WDOG_UNLOCK = WDOG_UNLOCK_SEQ1;
  WDOG_UNLOCK = WDOG_UNLOCK_SEQ2;
  // Now, we have to wait one bus clock cycle. Usually, the clock ratio is 1:1 or 1:2
  __asm__ volatile ("nop");
  __asm__ volatile ("nop");

  // And finally, we can disable the watchdog while allowing changes later on
  WDOG_STCTRLH = WDOG_STCTRLH_ALLOWUPDATE_MASK;
}
