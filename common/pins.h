#ifndef _PINS_H_
#define _PINS_H_
#include "mk20dx256.h"
/*
 * This is a generated file. Do not modify directly!
 * -------------------------------------------------
 * 
 * This file contains macros to access I/O pins based on their numbering according to the teensy
 * pinout schema (https://www.pjrc.com/teensy/pinout.html).
 * 
 * Register aliases:
 * 
 * - PINx_BANK
 *    The bank the pin maps to
 * 
 * - PINx_PIN
 *    The bank-local pin number
 * 
 * - PINx_PORT_PCR
 *    An alias to the pin's port PCR register
 * 
 * - PINx_GPIO_PDDR
 *    An alias to the pin's GPIO PDDR register
 * 
 * "Function"-like macros for convenience:
 * 
 * - pinX_gpio_set_high() / pin_gpio_set_high(pin)
 *    Sets the GPIO pin to HIGH. Don't forget to configure the PORT in GPIO mode.
 * 
 * - pinX_gpio_set_low() / pin_gpio_set_low(pin)
 *    Sets the GPIO pin to LOW.
 * 
 */

// Pin banks
#define PIN0_BANK B
#define PIN1_BANK B
#define PIN2_BANK D
#define PIN3_BANK A
#define PIN4_BANK A
#define PIN5_BANK D
#define PIN6_BANK D
#define PIN7_BANK D
#define PIN8_BANK D
#define PIN9_BANK C
#define PIN10_BANK C
#define PIN11_BANK C
#define PIN12_BANK C
#define PIN13_BANK C
#define PIN14_BANK D
#define PIN15_BANK C
#define PIN16_BANK B
#define PIN17_BANK B
#define PIN18_BANK B
#define PIN19_BANK B
#define PIN20_BANK D
#define PIN21_BANK D
#define PIN22_BANK C
#define PIN23_BANK C
#define PIN24_BANK A
#define PIN25_BANK B
#define PIN26_BANK E
#define PIN27_BANK C
#define PIN28_BANK C
#define PIN29_BANK C
#define PIN30_BANK C
#define PIN31_BANK E
#define PIN32_BANK B
#define PIN33_BANK A
#define PIN_BANK(idx) PIN_BANK_(idx)
#define PIN_BANK_(idx) PIN##idx##_BANK

// Bank-local pin numbers
#define PIN0_PIN 16
#define PIN1_PIN 17
#define PIN2_PIN 0
#define PIN3_PIN 12
#define PIN4_PIN 13
#define PIN5_PIN 7
#define PIN6_PIN 4
#define PIN7_PIN 2
#define PIN8_PIN 3
#define PIN9_PIN 3
#define PIN10_PIN 4
#define PIN11_PIN 6
#define PIN12_PIN 7
#define PIN13_PIN 5
#define PIN14_PIN 1
#define PIN15_PIN 0
#define PIN16_PIN 0
#define PIN17_PIN 1
#define PIN18_PIN 3
#define PIN19_PIN 2
#define PIN20_PIN 5
#define PIN21_PIN 6
#define PIN22_PIN 1
#define PIN23_PIN 2
#define PIN24_PIN 5
#define PIN25_PIN 19
#define PIN26_PIN 1
#define PIN27_PIN 9
#define PIN28_PIN 8
#define PIN29_PIN 10
#define PIN30_PIN 11
#define PIN31_PIN 0
#define PIN32_PIN 18
#define PIN33_PIN 4
#define PIN_PIN(idx) PIN_PIN_(idx)
#define PIN_PIN_(idx) PIN##idx##_PIN

// PORT PCR aliases
#define PIN0_PORT_PCR PORTB_PCR16
#define PIN1_PORT_PCR PORTB_PCR17
#define PIN2_PORT_PCR PORTD_PCR0
#define PIN3_PORT_PCR PORTA_PCR12
#define PIN4_PORT_PCR PORTA_PCR13
#define PIN5_PORT_PCR PORTD_PCR7
#define PIN6_PORT_PCR PORTD_PCR4
#define PIN7_PORT_PCR PORTD_PCR2
#define PIN8_PORT_PCR PORTD_PCR3
#define PIN9_PORT_PCR PORTC_PCR3
#define PIN10_PORT_PCR PORTC_PCR4
#define PIN11_PORT_PCR PORTC_PCR6
#define PIN12_PORT_PCR PORTC_PCR7
#define PIN13_PORT_PCR PORTC_PCR5
#define PIN14_PORT_PCR PORTD_PCR1
#define PIN15_PORT_PCR PORTC_PCR0
#define PIN16_PORT_PCR PORTB_PCR0
#define PIN17_PORT_PCR PORTB_PCR1
#define PIN18_PORT_PCR PORTB_PCR3
#define PIN19_PORT_PCR PORTB_PCR2
#define PIN20_PORT_PCR PORTD_PCR5
#define PIN21_PORT_PCR PORTD_PCR6
#define PIN22_PORT_PCR PORTC_PCR1
#define PIN23_PORT_PCR PORTC_PCR2
#define PIN24_PORT_PCR PORTA_PCR5
#define PIN25_PORT_PCR PORTB_PCR19
#define PIN26_PORT_PCR PORTE_PCR1
#define PIN27_PORT_PCR PORTC_PCR9
#define PIN28_PORT_PCR PORTC_PCR8
#define PIN29_PORT_PCR PORTC_PCR10
#define PIN30_PORT_PCR PORTC_PCR11
#define PIN31_PORT_PCR PORTE_PCR0
#define PIN32_PORT_PCR PORTB_PCR18
#define PIN33_PORT_PCR PORTA_PCR4
#define PIN_PORT_PCR(idx) PIN_PORT_PCR_(idx)
#define PIN_PORT_PCR_(idx) PIN##idx##_PORT_PCR

// GPIO PDDR aliases
#define PIN0_GPIO_PDDR GPIOB_PDDR
#define PIN1_GPIO_PDDR GPIOB_PDDR
#define PIN2_GPIO_PDDR GPIOD_PDDR
#define PIN3_GPIO_PDDR GPIOA_PDDR
#define PIN4_GPIO_PDDR GPIOA_PDDR
#define PIN5_GPIO_PDDR GPIOD_PDDR
#define PIN6_GPIO_PDDR GPIOD_PDDR
#define PIN7_GPIO_PDDR GPIOD_PDDR
#define PIN8_GPIO_PDDR GPIOD_PDDR
#define PIN9_GPIO_PDDR GPIOC_PDDR
#define PIN10_GPIO_PDDR GPIOC_PDDR
#define PIN11_GPIO_PDDR GPIOC_PDDR
#define PIN12_GPIO_PDDR GPIOC_PDDR
#define PIN13_GPIO_PDDR GPIOC_PDDR
#define PIN14_GPIO_PDDR GPIOD_PDDR
#define PIN15_GPIO_PDDR GPIOC_PDDR
#define PIN16_GPIO_PDDR GPIOB_PDDR
#define PIN17_GPIO_PDDR GPIOB_PDDR
#define PIN18_GPIO_PDDR GPIOB_PDDR
#define PIN19_GPIO_PDDR GPIOB_PDDR
#define PIN20_GPIO_PDDR GPIOD_PDDR
#define PIN21_GPIO_PDDR GPIOD_PDDR
#define PIN22_GPIO_PDDR GPIOC_PDDR
#define PIN23_GPIO_PDDR GPIOC_PDDR
#define PIN24_GPIO_PDDR GPIOA_PDDR
#define PIN25_GPIO_PDDR GPIOB_PDDR
#define PIN26_GPIO_PDDR GPIOE_PDDR
#define PIN27_GPIO_PDDR GPIOC_PDDR
#define PIN28_GPIO_PDDR GPIOC_PDDR
#define PIN29_GPIO_PDDR GPIOC_PDDR
#define PIN30_GPIO_PDDR GPIOC_PDDR
#define PIN31_GPIO_PDDR GPIOE_PDDR
#define PIN32_GPIO_PDDR GPIOB_PDDR
#define PIN33_GPIO_PDDR GPIOA_PDDR
#define PIN_GPIO_PDDR(idx) PIN_GPIO_PDDR_(idx)
#define PIN_GPIO_PDDR_(idx) PIN##idx##_GPIO_PDDR

// GPIO PSOR aliases
#define pin0_gpio_set_high() GPIOB_PSOR = (1<<16)
#define pin1_gpio_set_high() GPIOB_PSOR = (1<<17)
#define pin2_gpio_set_high() GPIOD_PSOR = (1<<0)
#define pin3_gpio_set_high() GPIOA_PSOR = (1<<12)
#define pin4_gpio_set_high() GPIOA_PSOR = (1<<13)
#define pin5_gpio_set_high() GPIOD_PSOR = (1<<7)
#define pin6_gpio_set_high() GPIOD_PSOR = (1<<4)
#define pin7_gpio_set_high() GPIOD_PSOR = (1<<2)
#define pin8_gpio_set_high() GPIOD_PSOR = (1<<3)
#define pin9_gpio_set_high() GPIOC_PSOR = (1<<3)
#define pin10_gpio_set_high() GPIOC_PSOR = (1<<4)
#define pin11_gpio_set_high() GPIOC_PSOR = (1<<6)
#define pin12_gpio_set_high() GPIOC_PSOR = (1<<7)
#define pin13_gpio_set_high() GPIOC_PSOR = (1<<5)
#define pin14_gpio_set_high() GPIOD_PSOR = (1<<1)
#define pin15_gpio_set_high() GPIOC_PSOR = (1<<0)
#define pin16_gpio_set_high() GPIOB_PSOR = (1<<0)
#define pin17_gpio_set_high() GPIOB_PSOR = (1<<1)
#define pin18_gpio_set_high() GPIOB_PSOR = (1<<3)
#define pin19_gpio_set_high() GPIOB_PSOR = (1<<2)
#define pin20_gpio_set_high() GPIOD_PSOR = (1<<5)
#define pin21_gpio_set_high() GPIOD_PSOR = (1<<6)
#define pin22_gpio_set_high() GPIOC_PSOR = (1<<1)
#define pin23_gpio_set_high() GPIOC_PSOR = (1<<2)
#define pin24_gpio_set_high() GPIOA_PSOR = (1<<5)
#define pin25_gpio_set_high() GPIOB_PSOR = (1<<19)
#define pin26_gpio_set_high() GPIOE_PSOR = (1<<1)
#define pin27_gpio_set_high() GPIOC_PSOR = (1<<9)
#define pin28_gpio_set_high() GPIOC_PSOR = (1<<8)
#define pin29_gpio_set_high() GPIOC_PSOR = (1<<10)
#define pin30_gpio_set_high() GPIOC_PSOR = (1<<11)
#define pin31_gpio_set_high() GPIOE_PSOR = (1<<0)
#define pin32_gpio_set_high() GPIOB_PSOR = (1<<18)
#define pin33_gpio_set_high() GPIOA_PSOR = (1<<4)
#define pin_gpio_set_high(idx) pin_gpio_set_high_(idx)
#define pin_gpio_set_high_(idx) pin##idx##_gpio_set_high()

// GPIO PCOR aliases
#define pin0_gpio_set_low() GPIOB_PCOR = (1<<16)
#define pin1_gpio_set_low() GPIOB_PCOR = (1<<17)
#define pin2_gpio_set_low() GPIOD_PCOR = (1<<0)
#define pin3_gpio_set_low() GPIOA_PCOR = (1<<12)
#define pin4_gpio_set_low() GPIOA_PCOR = (1<<13)
#define pin5_gpio_set_low() GPIOD_PCOR = (1<<7)
#define pin6_gpio_set_low() GPIOD_PCOR = (1<<4)
#define pin7_gpio_set_low() GPIOD_PCOR = (1<<2)
#define pin8_gpio_set_low() GPIOD_PCOR = (1<<3)
#define pin9_gpio_set_low() GPIOC_PCOR = (1<<3)
#define pin10_gpio_set_low() GPIOC_PCOR = (1<<4)
#define pin11_gpio_set_low() GPIOC_PCOR = (1<<6)
#define pin12_gpio_set_low() GPIOC_PCOR = (1<<7)
#define pin13_gpio_set_low() GPIOC_PCOR = (1<<5)
#define pin14_gpio_set_low() GPIOD_PCOR = (1<<1)
#define pin15_gpio_set_low() GPIOC_PCOR = (1<<0)
#define pin16_gpio_set_low() GPIOB_PCOR = (1<<0)
#define pin17_gpio_set_low() GPIOB_PCOR = (1<<1)
#define pin18_gpio_set_low() GPIOB_PCOR = (1<<3)
#define pin19_gpio_set_low() GPIOB_PCOR = (1<<2)
#define pin20_gpio_set_low() GPIOD_PCOR = (1<<5)
#define pin21_gpio_set_low() GPIOD_PCOR = (1<<6)
#define pin22_gpio_set_low() GPIOC_PCOR = (1<<1)
#define pin23_gpio_set_low() GPIOC_PCOR = (1<<2)
#define pin24_gpio_set_low() GPIOA_PCOR = (1<<5)
#define pin25_gpio_set_low() GPIOB_PCOR = (1<<19)
#define pin26_gpio_set_low() GPIOE_PCOR = (1<<1)
#define pin27_gpio_set_low() GPIOC_PCOR = (1<<9)
#define pin28_gpio_set_low() GPIOC_PCOR = (1<<8)
#define pin29_gpio_set_low() GPIOC_PCOR = (1<<10)
#define pin30_gpio_set_low() GPIOC_PCOR = (1<<11)
#define pin31_gpio_set_low() GPIOE_PCOR = (1<<0)
#define pin32_gpio_set_low() GPIOB_PCOR = (1<<18)
#define pin33_gpio_set_low() GPIOA_PCOR = (1<<4)
#define pin_gpio_set_low(idx) pin_gpio_set_low_(idx)
#define pin_gpio_set_low_(idx) pin##idx##_gpio_set_low()
#endif
