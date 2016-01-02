#ifndef _CONFIG_H_
#define _CONFIG_H_

#include "mk20dx256.h"

// The CPU frequency in Hz. eg: 72000000 for 72 MHz
#ifndef F_CPU
#define F_CPU 72000000
#endif

// Controls which power modes can be entered after startup
#ifndef ENABLED_POWER_MODES
#define ENABLED_POWER_MODES (SMC_PMPROT_AVLP_MASK | SMC_PMPROT_ALLS_MASK | SMC_PMPROT_AVLLS_MASK)
#endif

// If 1, turns on interrupts before entering main
#ifndef ENABLE_INTERRUPTS_ON_STARTUP
#define ENABLE_INTERRUPTS_ON_STARTUP 0
#endif

// If 1, uses the systick handler in common
#ifndef ENABLE_SYSTICK_HANDLER
#define ENABLE_SYSTICK_HANDLER 0
#endif

#endif
