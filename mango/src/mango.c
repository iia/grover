#include "mango.h"

CTX_MANGO_t ctx_mango;

int main() {
	cli();

	debug_uart_init(9600);
	i2c_init((uint8_t)I2C_ADDRESS);

	memset(&ctx_mango, 0, sizeof(ctx_mango));

	debug_uart_tx_string("[+] Grover - Mango v1.0\r\n\0");

	sei();

	while(1) {
		;
	}

	return 0;
}
