#include <stdint.h>
#include <string.h>
#include <avr/interrupt.h>

#include "i2c.h"
#include "mango.h"
#include "ports.h"
#include "debug_uart.h"

int main(void) {
	cli();

	debug_uart_init(9600);
	i2c_init((uint8_t)I2C_ADDRESS);

	memset(&ctx_port_handler, 0, sizeof(ctx_port_handler));

	debug_uart_tx_string("Grover - Mango v1.0\r\n\0");

	sei();

	while(1) {
		;
	}

	return 0;
}
