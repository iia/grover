#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <inttypes.h>

#include <periph/pm.h>

#include "twi_slave.h"
#include "debug_mango.h"

int main(void) {
    DEBUG("\nmain(): ENTRY\n");

    twi_slave_init((uint8_t)TWI_SLAVE_ADDRESS);

    DEBUG("\nmain(): TWI slave init done\n");

    return 0;
}
