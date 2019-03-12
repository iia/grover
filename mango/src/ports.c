#include "mango.h"

void port_handler_A0() {
	usart_tx_debug("[+] PORTS: Handler A0\r\n\0");

	switch (ctx_mango.port.fid) {
		default:
			i2c_load_response((int8_t)PRT_RET_ERR_INV_FID, ctx_mango.port.fid, NULL);
	}
}

void port_handler_A1() {
	usart_tx_debug("[+] PORTS: Handler A1\r\n\0");

	switch (ctx_mango.port.fid) {
		default:
			i2c_load_response((int8_t)PRT_RET_ERR_INV_FID, ctx_mango.port.fid, NULL);
	}
}

void port_handler_A2() {
	usart_tx_debug("[+] PORTS: Handler A2\r\n\0");

	switch (ctx_mango.port.fid) {
		default:
			i2c_load_response((int8_t)PRT_RET_ERR_INV_FID, ctx_mango.port.fid, NULL);
	}
}

void port_handler_serial() {
	usart_tx_debug("[+] PORTS: Handler serial\r\n\0");

	switch (ctx_mango.port.fid) {
		default:
			i2c_load_response((int8_t)PRT_RET_ERR_INV_FID, ctx_mango.port.fid, NULL);
	}
}

void port_handler_D2() {
	usart_tx_debug("[+] PORTS: Handler D2\r\n\0");

	switch (ctx_mango.port.fid) {
		default:
			i2c_load_response((int8_t)PRT_RET_ERR_INV_FID, ctx_mango.port.fid, NULL);
	}
}

void port_handler_D3() {
	usart_tx_debug("[+] PORTS: Handler D3\r\n\0");

	switch (ctx_mango.port.fid) {
		default:
			i2c_load_response((int8_t)PRT_RET_ERR_INV_FID, ctx_mango.port.fid, NULL);
	}
}

void port_handler_D4() {
	usart_tx_debug("[+] PORTS: Handler D4\r\n\0");

	switch (ctx_mango.port.fid) {
		default:
			i2c_load_response((int8_t)PRT_RET_ERR_INV_FID, ctx_mango.port.fid, NULL);
	}
}

void port_handler_D5() {
	usart_tx_debug("[+] PORTS: Handler D5\r\n\0");

	switch (ctx_mango.port.fid) {
		default:
			i2c_load_response((int8_t)PRT_RET_ERR_INV_FID, ctx_mango.port.fid, NULL);
	}
}

void port_handler_D6() {
	usart_tx_debug("[+] PORTS: Handler D6\r\n\0");

	switch (ctx_mango.port.fid) {
		default:
			i2c_load_response((int8_t)PRT_RET_ERR_INV_FID, ctx_mango.port.fid, NULL);
	}
}

void port_handler_D7() {
	usart_tx_debug("[+] PORTS: Handler D7\r\n\0");

	uint8_t* data;

	switch (ctx_mango.port.fid) {
		/*
		Port info:
			Channels can be configured as digital I/O.

			Channel 0 = PD7.
			Channel 1 = PB0.
		*/

		case FID_PORT_D7_CH0_SET_CFG_DIN:
			usart_tx_debug("[+] PORTS: Handler D7: CH0_SET_CFG_DIN\r\n\0");

			DDRD &= ~(_BV(PORTD7));
			PORTD &= ~(_BV(PORTD7));

			i2c_load_response((int8_t)PRT_RET_OK, ctx_mango.port.fid, NULL);

			break;

		case FID_PORT_D7_CH0_SET_CFG_DIN_PUP:
			usart_tx_debug("[+] PORTS: Handler D7: CH0_SET_CFG_DIN_PUP\r\n\0");

			DDRD &= ~(_BV(PORTD7));
			PORTD |= (_BV(PORTD7));

			i2c_load_response((int8_t)PRT_RET_OK, ctx_mango.port.fid, NULL);

			break;

		case FID_PORT_D7_CH0_SET_CFG_DOU:
			usart_tx_debug("[+] PORTS: Handler D7: CH0_SET_CFG_DOU\r\n\0");

			DDRD |= (_BV(PORTD7));

			i2c_load_response((int8_t)PRT_RET_OK, ctx_mango.port.fid, NULL);

			break;

		case FID_PORT_D7_CH0_SET_VAL:
			usart_tx_debug("[+] PORTS: Handler D7: CH0_SET_VAL\r\n\0");

			// Check if port is configured as input in which case a value can not be set.
			if (!(DDRD & (_BV(PORTD7)))) {
				i2c_load_response((int8_t)PRT_RET_ERR_INV_OPS, ctx_mango.port.fid, NULL);

				break;
			}

			if (ctx_mango.port.data[(LEN_DAT - 1)] == 1) {
				PORTD |= _BV(PORTD7);

				i2c_load_response((int8_t)PRT_RET_OK, ctx_mango.port.fid, NULL);
			}
			else if (ctx_mango.port.data[(LEN_DAT - 1)] == 0) {
				PORTD &= ~_BV(PORTD7);

				i2c_load_response((int8_t)PRT_RET_OK, ctx_mango.port.fid, NULL);
			}
			else {
				i2c_load_response((int8_t)PRT_RET_ERR_INV_DAT, ctx_mango.port.fid, NULL);
			}

			break;

		case FID_PORT_D7_CH0_GET_CFG:
			usart_tx_debug("[+] PORTS: Handler D7: CH0_GET_CFG\r\n\0");

			i2c_load_response((int8_t)PRT_RET_ERR_INV_FID, ctx_mango.port.fid, NULL);

			break;

		case FID_PORT_D7_CH0_GET_VAL:
			usart_tx_debug("[+] PORTS: Handler D7: CH0_GET_VAL\r\n\0");

			data = (uint8_t*)malloc(LEN_DAT);

			if (!(DDRD & (_BV(PORTD7)))) {
				// Port is configured as input.
				if ((PIND & (_BV(PIND7)))) {
					data[LEN_DAT - 1] = 1;
				}
				else {
					data[LEN_DAT - 1] = 0;
				}

				i2c_load_response((int8_t)PRT_RET_OK, ctx_mango.port.fid, data);
				free(data);

				break;
			}
			else {
				// Port is configured as output.
				if ((PORTD & (_BV(PORTD7)))) {
					data[LEN_DAT - 1] = 1;
				}
				else {
					data[LEN_DAT - 1] = 0;
				}

				i2c_load_response((int8_t)PRT_RET_OK, ctx_mango.port.fid, data);
				free(data);

				break;
			}

		case FID_PORT_D7_CH1_SET_CFG_DIN:
			usart_tx_debug("[+] PORTS: Handler D7: CH1_SET_CFG_DIN\r\n\0");

			i2c_load_response((int8_t)PRT_RET_ERR_INV_FID, ctx_mango.port.fid, NULL);

			break;

		case FID_PORT_D7_CH1_SET_CFG_DIN_PUP:
			usart_tx_debug("[+] PORTS: Handler D7: CH1_SET_CFG_DIN_PUP\r\n\0");

			i2c_load_response((int8_t)PRT_RET_ERR_INV_FID, ctx_mango.port.fid, NULL);

			break;

		case FID_PORT_D7_CH1_SET_CFG_DOU:
			usart_tx_debug("[+] PORTS: Handler D7: CH1_SET_CFG_DOU\r\n\0");

			i2c_load_response((int8_t)PRT_RET_ERR_INV_FID, ctx_mango.port.fid, NULL);

			break;

		case FID_PORT_D7_CH1_SET_VAL:
			usart_tx_debug("[+] PORTS: Handler D7: CH1_SET_VAL\r\n\0");

			i2c_load_response((int8_t)PRT_RET_ERR_INV_FID, ctx_mango.port.fid, NULL);

			break;

		case FID_PORT_D7_CH1_GET_CFG:
			usart_tx_debug("[+] PORTS: Handler D7: CH1_GET_CFG\r\n\0");

			i2c_load_response((int8_t)PRT_RET_ERR_INV_FID, ctx_mango.port.fid, NULL);

			break;

		case FID_PORT_D7_CH1_GET_VAL:
			usart_tx_debug("[+] PORTS: Handler D7: CH1_GET_VAL\r\n\0");

			i2c_load_response((int8_t)PRT_RET_ERR_INV_FID, ctx_mango.port.fid, NULL);

			break;

		default:
			i2c_load_response((int8_t)PRT_RET_ERR_INV_FID, ctx_mango.port.fid, NULL);
	}
}

void port_handler_D8() {
	usart_tx_debug("[+] PORTS: Handler D8\r\n\0");

	switch (ctx_mango.port.fid) {
		default:
			i2c_load_response((int8_t)PRT_RET_ERR_INV_FID, ctx_mango.port.fid, NULL);
	}
}

TASK_PORT_t port_handler[GROVEPI_PORTS] =
	{
		&port_handler_A0,
		&port_handler_A1,
		&port_handler_A2,
		&port_handler_serial,
		&port_handler_D2,
		&port_handler_D3,
		&port_handler_D4,
		&port_handler_D5,
		&port_handler_D6,
		&port_handler_D7,
		&port_handler_D8
	};
