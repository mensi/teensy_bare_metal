#ifndef _CONFIG_H_
#define _CONFIG_H_

#include "mk20dx256.h"

#ifndef F_CPU
#define F_CPU 72000000
#endif

#ifndef ENABLED_POWER_MODES
#define ENABLED_POWER_MODES (SMC_PMPROT_AVLP_MASK | SMC_PMPROT_ALLS_MASK | SMC_PMPROT_AVLLS_MASK)
#endif

#endif
