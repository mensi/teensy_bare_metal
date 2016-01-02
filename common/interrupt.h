#ifndef _INTERRUPT_H_
#define _INTERRUPT_H_

/*
 * Generic ISRs for either ignoring or panic
 */
void isr_panic();
void isr_ignore();

/*
 * Macros to enable/disable interrupts
 *
 * The "i" after CPSIE/CPSID means that this applies to interrupts and configurable
 * fault handlers. "f" would disable all fault handlers too. (PRIMASK vs. FAULTMASK)
 *
 * These are declared volatile and with memory clobber to prevent GCC from caching
 * memory values across the instruction or move the instruction around. This ensures
 * enabling/disabling interrupts is as atomic as possible.
 */
#define interrupt_enable() __asm__ __volatile__("CPSIE i":::"memory")
#define interrupt_disable() __asm__ __volatile__("CPSID i":::"memory")


#endif
