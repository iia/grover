#include "mango.h"

void port_handler_A0() {
	debug_uart_tx_string("[+] PORTS: Handler A0\r\n\0");

	switch (ctx_mango.port.fid) {
		default:
			i2c_load_response((int8_t)FID_RET_ERR_INV_FID, ctx_mango.port.fid, NULL);
	}
}

void port_handler_A1() {
	debug_uart_tx_string("[+] PORTS: Handler A1\r\n\0");

	switch (ctx_mango.port.fid) {
		default:
			i2c_load_response((int8_t)FID_RET_ERR_INV_FID, ctx_mango.port.fid, NULL);
	}
}

void port_handler_A2() {
	debug_uart_tx_string("[+] PORTS: Handler A2\r\n\0");

	switch (ctx_mango.port.fid) {
		default:
			i2c_load_response((int8_t)FID_RET_ERR_INV_FID, ctx_mango.port.fid, NULL);
	}
}

void port_handler_serial() {
	debug_uart_tx_string("[+] PORTS: Handler serial\r\n\0");

	switch (ctx_mango.port.fid) {
		default:
			i2c_load_response((int8_t)FID_RET_ERR_INV_FID, ctx_mango.port.fid, NULL);
	}
}

void port_handler_D2() {
	debug_uart_tx_string("[+] PORTS: Handler D2\r\n\0");

	switch (ctx_mango.port.fid) {
		default:
			i2c_load_response((int8_t)FID_RET_ERR_INV_FID, ctx_mango.port.fid, NULL);
	}
}

void port_handler_D3() {
	debug_uart_tx_string("[+] PORTS: Handler D3\r\n\0");

	switch (ctx_mango.port.fid) {
		default:
			i2c_load_response((int8_t)FID_RET_ERR_INV_FID, ctx_mango.port.fid, NULL);
	}
}

void port_handler_D4() {
	debug_uart_tx_string("[+] PORTS: Handler D4\r\n\0");

	switch (ctx_mango.port.fid) {
		default:
			i2c_load_response((int8_t)FID_RET_ERR_INV_FID, ctx_mango.port.fid, NULL);
	}
}

void port_handler_D5() {
	debug_uart_tx_string("[+] PORTS: Handler D5\r\n\0");

	switch (ctx_mango.port.fid) {
		default:
			i2c_load_response((int8_t)FID_RET_ERR_INV_FID, ctx_mango.port.fid, NULL);
	}
}

void port_handler_D6() {
	debug_uart_tx_string("[+] PORTS: Handler D6\r\n\0");

	switch (ctx_mango.port.fid) {
		default:
			i2c_load_response((int8_t)FID_RET_ERR_INV_FID, ctx_mango.port.fid, NULL);
	}
}

void port_handler_D7() {
	debug_uart_tx_string("[+] PORTS: Handler D7\r\n\0");

	switch (ctx_mango.port.fid) {
		/*
		Channel 0 = PD7
		Channel 1 = PB0

		Input = 0
		Output = 1

		PORTx = 1 When pin is configured as input = PUEN
		PORTx = 0 When pin is configured as input = PUD
		*/

		case FID_PORT_D7_CH0_SET_CFG_DIN:
			debug_uart_tx_string("[+] PORTS: Handler D7: CH0_SET_CFG_DIN\r\n\0");

			DDRD &= ~_BV(PIND7);

			i2c_load_response((int8_t)FID_RET_OK, ctx_mango.port.fid, NULL);

			break;

		case FID_PORT_D7_CH0_SET_CFG_DOU:
			debug_uart_tx_string("[+] PORTS: Handler D7: CH0_SET_CFG_DOU\r\n\0");

			DDRD |= _BV(PORTD7);

			i2c_load_response((int8_t)FID_RET_OK, ctx_mango.port.fid, NULL);

			break;

		case FID_PORT_D7_CH0_SET_CFG_DIN_PUP:
			debug_uart_tx_string("[+] PORTS: Handler D7: CH0_SET_CFG_DIN_PUP\r\n\0");

			DDRD &= ~_BV(PIND7);
			PORTD |= _BV(PORTD7);

			i2c_load_response((int8_t)FID_RET_OK, ctx_mango.port.fid, NULL);

			break;

		case FID_PORT_D7_CH0_GET_CFG:
			break;

		case FID_PORT_D7_CH0_SET_VAL:
			debug_uart_tx_string("[+] PORTS: Handler D7: CH0_SET_VAL\r\n\0");

			// TODO: Check current direction first and then set accordingly!
			if (ctx_mango.port.data[(LEN_DAT - 1)] == 1) {
				PORTD |= _BV(PORTD7);

				i2c_load_response((int8_t)FID_RET_OK, ctx_mango.port.fid, NULL);
			}
			else if (ctx_mango.port.data[(LEN_DAT - 1)] == 0) {
				PORTD &= ~_BV(PORTD7);

				i2c_load_response((int8_t)FID_RET_OK, ctx_mango.port.fid, NULL);
			}
			else {
				i2c_load_response((int8_t)FID_RET_ERR_INV_DAT, ctx_mango.port.fid, NULL);
			}

			break;

		case FID_PORT_D7_CH0_GET_VAL:
			break;

		case FID_PORT_D7_CH1_SET_CFG_DIN:
			break;

		case FID_PORT_D7_CH1_SET_CFG_DOU:
			break;

		case FID_PORT_D7_CH1_SET_CFG_DIN_PUP:
			break;

		case FID_PORT_D7_CH1_SET_VAL:
			break;

		case FID_PORT_D7_CH1_GET_CFG:
			break;

		case FID_PORT_D7_CH1_GET_VAL:
			break;

		default:
			i2c_load_response((int8_t)FID_RET_ERR_INV_FID, ctx_mango.port.fid, NULL);
	}
}

void port_handler_D8() {
	debug_uart_tx_string("[+] PORTS: Handler D8\r\n\0");

	switch (ctx_mango.port.fid) {
		default:
			i2c_load_response((int8_t)FID_RET_ERR_INV_FID, ctx_mango.port.fid, NULL);
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
