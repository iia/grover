#ifndef TWI_SLAVE_H
#define TWI_SLAVE_H

#include <inttypes.h>

#include <avr/io.h>
#include <util/twi.h>
#include <avr/interrupt.h>

#define TWI_SLAVE_ADDRESS 0x2A // Because the answer is 42!

#define TWI_SLAVE_TWCR_INIT \
    ((1 << TWINT) | (1 << TWEA) | (1 << TWSTO) | (1 << TWEN) | (1 << TWIE))

void twi_slave_init(uint8_t);

#endif /* TWI_SLAVE_H */
