#include <stdint.h>
#include <string.h>
#include <compat/twi.h>
#include <avr/interrupt.h>

#include "i2c.h"
#include "ports.h"
#include "debug_uart.h"

void i2c_init(uint8_t i2c_address) {
	debug_uart_tx_string("[+] I2C: I2C init\r\n\0");
	TWAR = (i2c_address << 1); // Disable general call.
	TWCR |= (_BV(TWIE) | _BV(TWEA) | _BV(TWINT) | _BV(TWEN));
}

ISR(TWI_vect) {
	switch((TWSR & 0xFC)) {
		// Slave RX.

		// TWSR = 0x60 (RX: START+ADDR+W, TX: ACK).
		case TW_SR_SLA_ACK:
			debug_uart_tx_string("[+] I2C: TW_SR_SLA_ACK: ACK -->\r\n\0");

			ctx_port_handler.idx_buffer = 0;
			ctx_port_handler.is_valid_data = false;

			TWCR |= RST_INT_ENA_ACK;

			break;

		// TWSR = 0x80 (Got TW_SR_SLA_ACK previously) (RX: DATA, TX: ACK).
		case TW_SR_DATA_ACK:
			debug_uart_tx_string("[+] I2C: TW_SR_DATA_ACK\r\n\0");

			if (ctx_port_handler.idx_buffer < (LEN_BUF_I2C - 1)) {
				debug_uart_tx_string("[+] I2C: TW_SR_DATA_ACK: ACK -->\r\n\0");

				ctx_port_handler.buffer[ctx_port_handler.idx_buffer] = TWDR;
				ctx_port_handler.idx_buffer++;

				TWCR |= RST_INT_ENA_ACK;
			}
			else if (ctx_port_handler.idx_buffer == (LEN_BUF_I2C - 1)) {
				debug_uart_tx_string("[+] I2C: TW_SR_DATA_ACK: NACK -->\r\n\0");

				ctx_port_handler.buffer[ctx_port_handler.idx_buffer] = TWDR;

				TWCR |= RST_INT_DIS_ACK;
			}
			else {
				TWCR |= RST_INT_DIS_ACK;
			}

			break;

		// TWSR = 0x88 (Got TW_SR_SLA_ACK previously) (RX: DATA, TX: NACK).
		case TW_SR_DATA_NACK:
			debug_uart_tx_string("[+] I2C: TW_SR_DATA_NACK: NACK -->\r\n\0");

			ctx_port_handler.idx_buffer = 0;

			TWCR |= RST_INT_DIS_ACK;

			break;

		// TWSR = 0xA0 (RX: Got STOP/RSTART while being addressed as slave, TX: N/A).
		case TW_SR_STOP:
			debug_uart_tx_string("[+] I2C: TW_SR_STOP: ACK -->\r\n\0");

			if (ctx_port_handler.idx_buffer == LEN_BUF_I2C - 1) {
				memcpy(
					&ctx_port_handler.port,
					&ctx_port_handler.buffer[IDX_PRT_RET],
					LEN_PRT_RET
				);

				memcpy(
					&ctx_port_handler.fid,
					&ctx_port_handler.buffer[IDX_FID],
					LEN_FID
				);

				memcpy(
					&ctx_port_handler.data,
					&ctx_port_handler.buffer[IDX_DAT],
					LEN_DAT
				);

				ctx_port_handler.is_valid_data = true;

				port_handler[ctx_port_handler.port]();
			}
			else {
				ctx_port_handler.is_valid_data = false;
			}

			TWCR |= RST_INT_ENA_ACK;

			break;

		// Slave TX.

		// TWSR = 0xA8 (RX: START+ADDR+R, TX: ACK).
		case TW_ST_SLA_ACK:
			debug_uart_tx_string("[+] I2C: TW_ST_SLA_ACK: ACK -->\r\n\0");

			ctx_port_handler.idx_buffer = 0;

			if (!ctx_port_handler.is_valid_data) {
				memset(&ctx_port_handler.buffer, 0, LEN_BUF_I2C);

				ctx_port_handler.buffer[IDX_PRT_RET] = (int8_t)FID_RET_ERR_INV_DAT;
			}

			TWDR = ctx_port_handler.buffer[ctx_port_handler.idx_buffer];

			ctx_port_handler.idx_buffer++;

			TWCR |= RST_INT_ENA_ACK;

			break;

		// TWSR = 0xB8 (RX: ACK, TX: TWDR).
		case TW_ST_DATA_ACK:
			debug_uart_tx_string("[+] I2C: TW_ST_DATA_ACK: ACK\r\n\0");

			if (ctx_port_handler.idx_buffer < (LEN_BUF_I2C - 1)) {
				debug_uart_tx_string("[+] I2C: TW_ST_DATA_ACK: ACK -->\r\n\0");

				TWDR = ctx_port_handler.buffer[ctx_port_handler.idx_buffer];
				ctx_port_handler.idx_buffer++;
				TWCR |= RST_INT_ENA_ACK;
			}
			else if (ctx_port_handler.idx_buffer == (LEN_BUF_I2C - 1)) {
				debug_uart_tx_string("[+] I2C: TW_ST_DATA_ACK: NACK -->\r\n\0");

				TWDR = ctx_port_handler.buffer[ctx_port_handler.idx_buffer];
				TWCR |= RST_INT_DIS_ACK;
			}
			else {
				TWCR |= RST_INT_DIS_ACK;
			}

			break;

		// TWSR = 0xC0 or 0xC8 (RX: NACK, TX: TWDR).
		case TW_ST_DATA_NACK:
		case TW_ST_LAST_DATA:
			// Reset internal data.
			debug_uart_tx_string("[+] I2C: TW_ST_DATA_NACK/TW_ST_LAST_DATA: ACK -->\r\n\0");

			ctx_port_handler.idx_buffer = 0;
			ctx_port_handler.is_valid_data = false;

			TWCR |= RST_INT_ENA_ACK;

			break;

		default:
			TWCR |= RST_INT_ENA_ACK;
	}
}
