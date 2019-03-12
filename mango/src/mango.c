#include "mango.h"

CTX_MANGO_t ctx_mango;

int main() {
	cli();

	usart_init();
	i2c_init((uint8_t)I2C_ADDRESS);

	memset(&ctx_mango, 0, sizeof(ctx_mango));

	usart_tx_debug("[+] Mango: v1.0\r\n\0");

	sei();

	while(1) {
		if (ctx_mango.task_port != NULL) {
			ATOMIC_BLOCK(ATOMIC_FORCEON) {
				ctx_mango.task_port();

				ctx_mango.task_port = NULL;
				TWCR |= (uint8_t)((_BV(TWEA)));
			}
		}

		if (ctx_mango.task_i2c_isr_response != NULL) {
			ATOMIC_BLOCK(ATOMIC_FORCEON) {
				ctx_mango.task_i2c_isr_response();

				ctx_mango.task_i2c_isr_response = NULL;
				TWCR |= (uint8_t)((_BV(TWEA)));
			}
		}
	}

	return 0;
}
