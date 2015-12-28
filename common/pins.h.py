#!/usr/bin/env python

# The pinmap maps the zero-based pin number (the index in the list) used in
# teensy reference material (eg. https://www.pjrc.com/teensy/pinout.html) to
# the PORT [A-E] and port-relative pin number used when accessing registers.
pinmap = [
    ('B', 16),
    ('B', 17),
    ('D', 0),
    ('A', 12),
    ('A', 13),
    ('D', 7),
    ('D', 4),
    ('D', 2),
    ('D', 3),
    ('C', 3),
    ('C', 4),
    ('C', 6),
    ('C', 7),
    ('C', 5),
    ('D', 1),
    ('C', 0),
    ('B', 0),
    ('B', 1),
    ('B', 3),
    ('B', 2),
    ('D', 5),
    ('D', 6),
    ('C', 1),
    ('C', 2),
    ('A', 5),
    ('B', 19),
    ('E', 1),
    ('C', 9),
    ('C', 8),
    ('C', 10),
    ('C', 11),
    ('E', 0),
    ('B', 18),
    ('A', 4)]

def pin_iteration(fmt):
    """Iterate over the pinmap, yielding fmt formatted with idx, bank and pin."""
    for i, (bank, pin) in enumerate(pinmap):
        yield fmt.format(idx=i, bank=bank, pin=pin)

def strip(line):
    """Strip the identation of a line for the comment header."""
    if line.startswith(' ' * 4):
        line = line[4:]
    return line.rstrip()

def generate_contents():
    hdr = '''
    This is a generated file. Do not modify directly!
    -------------------------------------------------

    This file contains macros to access I/O pins based on their numbering according to the teensy
    pinout schema (https://www.pjrc.com/teensy/pinout.html). 
    
    Register aliases:

    - PINx_BANK
       The bank the pin maps to

    - PINx_PIN
       The bank-local pin number

    - PINx_PORT_PCR
       An alias to the pin's port PCR register

    - PINx_GPIO_PDDR
       An alias to the pin's GPIO PDDR register

    "Function"-like macros for convenience:

    - pinX_gpio_set_high() / pin_gpio_set_high(pin)
       Sets the GPIO pin to HIGH. Don't forget to configure the PORT in GPIO mode.

    - pinX_gpio_set_low() / pin_gpio_set_low(pin)
       Sets the GPIO pin to LOW.
    '''
    # Output file header
    lines = ['#ifndef _PINS_H_', '#define _PINS_H_', '#include "mk20dx256.h"']
    lines += ['/*'] + [' * ' + strip(line) for line in hdr.lstrip().split('\n')] + [' */']

    def section(title):
        """Yield an empty line and a section title comment."""
        yield ''
        yield '// ' + title

    # Constants and simple aliases. For the macros taking a pin parameter, there is a second
    # level of indirection to expand the parameter before token pasting (##). This
    # allows to use:
    #
    #  #define MYPIN 1
    #  PIN_FOO(MYPIN);
    #
    # Without this, we would end up with PINMYPIN_FOO after expansion.
    def ualias(name):
        """Create an alias that takes the pin as a parameter."""
        yield '#define PIN_' + name + '(idx) PIN_' + name + '_(idx)'
        yield '#define PIN_' + name + '_(idx) PIN##idx##_' + name

    lines += section('Pin banks')
    lines += pin_iteration('#define PIN{idx}_BANK {bank}')
    lines += ualias('BANK')

    lines += section('Bank-local pin numbers')
    lines += pin_iteration('#define PIN{idx}_PIN {pin}')
    lines += ualias('PIN')

    lines += section('PORT PCR aliases')
    lines += pin_iteration('#define PIN{idx}_PORT_PCR PORT{bank}_PCR{pin}')
    lines += ualias('PORT_PCR')
    
    lines += section('GPIO PDDR aliases')
    lines += pin_iteration('#define PIN{idx}_GPIO_PDDR GPIO{bank}_PDDR')
    lines += ualias('GPIO_PDDR')

    # Function-style macros. For the macros taking a pin parameter, there is a second
    # level of indirection to expand the parameter before token pasting (##). This
    # allows to use:
    #
    #  #define MYPIN 1
    #  pin_function(MYPIN);
    #
    # Without this, we would end up with pinMYPIN_function() after expansion.
    def lalias(name):
        """Create an alias that takes the pin as a parameter."""
        yield '#define pin_' + name + '(idx) pin_' + name + '_(idx)'
        yield '#define pin_' + name + '_(idx) pin##idx##_' + name + '()'

    lines += section('GPIO PSOR aliases')
    lines += pin_iteration('#define pin{idx}_gpio_set_high() GPIO{bank}_PSOR = (1<<{pin})')
    lines += lalias('gpio_set_high')

    lines += section('GPIO PCOR aliases')
    lines += pin_iteration('#define pin{idx}_gpio_set_low() GPIO{bank}_PCOR = (1<<{pin})')
    lines += lalias('gpio_set_low')

    lines += ['#endif']
    return lines

def print_contents():
    for line in generate_contents():
        print(line)

if __name__ == '__main__':
    print_contents()
