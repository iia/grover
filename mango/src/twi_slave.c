#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "twi_slave.h"
#include "debug_mango.h"

ISR (TWI_vect) {
    /*
    BUG:
        Because of a silicon bug, the I2C module in Broadcom SoCs used in
        Raspberry Pis don't handle I2C clock stretching properly. Resulting
        in invalid I2C bus states.
        
        Check:
            https://github.com/raspberrypi/linux/issues/254
            http://www.advamation.com/knowhow/raspberrypi/rpi-i2c-bug.html

        Hence it is crucial to do the I2C ISR work as quick as possible and
        reset the interrupt flag to avoid I2C clock stretching. So avoid debug
        prints or doing anything time consuming in the ISR.
    */

    switch(TW_STATUS) {
        // Slave receiver (SR) .

        case TW_SR_SLA_ACK:
            // SLA+W received, ACK returned (0x60).
            TWCR |= (1 << TWEA);
            TWCR &= ~(1 << TWSTO);

            break;

        case TW_SR_GCALL_ACK:
            // General call received, ACK returned (0x70).
            TWCR |= (1 << TWEA);
            TWCR &= ~(1 << TWSTO);

            break;

        case TW_SR_DATA_ACK:
            // Data received, ACK returned (0x80).
            TWCR |= (1 << TWEA);
            TWCR &= ~(1 << TWSTO);

            break;

        case TW_SR_DATA_NACK:
            // Data received, NACK returned (0x88).
            TWCR |= (1 << TWEA);
            TWCR &= (~(1 << TWSTA) & ~(1 << TWSTO));

            break;

        case TW_SR_GCALL_DATA_ACK:
            // General call data received, ACK returned (0x90).
            TWCR |= (1 << TWEA);
            TWCR &= ~(1 << TWSTO);

            break;

        case TW_SR_GCALL_DATA_NACK:
            // General call data received, NACK returned (0x98).
            TWCR |= (1 << TWEA);
            TWCR &= (~(1 << TWSTA) & ~(1 << TWSTO));

            break;

        case TW_SR_STOP:
            // Stop or repeated start condition received while selected (0xA0).
            TWCR |= (1 << TWEA);
            TWCR &= (~(1 << TWSTA) & ~(1 << TWSTO));

            break;

        // Slave transmitter (ST).

        case TW_ST_SLA_ACK:
            // SLA+R received, ACK returned (0xA8).
            break;

        case TW_ST_ARB_LOST_SLA_ACK:
            // SLA+R received, ACK returned (0xB0).
            break;

        case TW_ST_DATA_ACK:
            // Data transmitted, ACK received (0xB8).
            break;

        case TW_ST_DATA_NACK:
            // Data transmitted, NACK received (0xC0).
            break;

        case TW_ST_LAST_DATA:
            // Last data byte transmitted, ACK received (0xC8).
            break;

        // Misc.

        case TW_NO_INFO:
            // No state information available as TWINT flag is not set (0xF8).
            break;

        case TW_BUS_ERROR:
            // Illegal start or stop condition (0x00).
            TWCR |= ((1 << TWEA) | (1 << TWSTO));

            break;

        default:
            TWCR &= (1 << TWSTA);
            TWCR |= (1 << TWSTO);
    }

    TWCR |= (1 << TWINT);
}

void twi_slave_init(uint8_t twi_slave_address) {
    DEBUG("\ntwi_slave_init(): ENTRY\n");
    DEBUG("\ntwi_slave_init(): TWI slave address = 0x%X\n", twi_slave_address);

    // Load slave address and enable general call.
    TWAR = ((twi_slave_address << 1) | (1 << TWGCE));

    // TWI slave mode configuration.
    TWCR = TWI_SLAVE_TWCR_INIT;

    DEBUG("\ntwi_slave_init(): TWCR = 0x%X\n", TWCR);
}
