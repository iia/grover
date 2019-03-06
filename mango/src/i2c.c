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
	TWCR |= _BV(TWIE) | _BV(TWEA) | _BV(TWINT) | _BV(TWEN);
}

ISR(TWI_vect) {
	switch((TWSR & 0xFC)) {
		// Slave RX (Write GrovePi).

		// TWSR = 0x60 (RX: START+ADDR+W, TX: ACK).
		case TW_SR_SLA_ACK:
			debug_uart_tx_string("[+] I2C: TW_SR_SLA_ACK: ACK -->\r\n\0");

			ctx_port_handler.rx_tx_buffer_idx = 0;
			ctx_port_handler.rx_tx_data_valid = false;
			TWCR |= RST_INT_ENA_ACK;

			break;

		// TWSR = 0x80 (Got TW_SR_SLA_ACK previously) (RX: DATA, TX: ACK).
		case TW_SR_DATA_ACK:
			debug_uart_tx_string("[+] I2C: TW_SR_DATA_ACK\r\n\0");

			if (ctx_port_handler.rx_tx_buffer_idx == RX_TX_BUF_LEN - 1) {
				debug_uart_tx_string("[+] I2C: TW_SR_DATA_ACK: NACK -->\r\n\0");

				ctx_port_handler.rx_tx_buffer[ctx_port_handler.rx_tx_buffer_idx] = TWDR;
				TWCR |= RST_INT_DIS_ACK;
			}
			else {
				debug_uart_tx_string("[+] I2C: TW_SR_DATA_ACK: ACK -->\r\n\0");

				ctx_port_handler.rx_tx_buffer[ctx_port_handler.rx_tx_buffer_idx] = TWDR;
				ctx_port_handler.rx_tx_buffer_idx++;
				TWCR |= RST_INT_ENA_ACK;
			}

			break;

		// TWSR = 0x88 (Got TW_SR_SLA_ACK previously) (RX: DATA, TX: NACK).
		case TW_SR_DATA_NACK:
			debug_uart_tx_string("[+] I2C: TW_SR_DATA_NACK: NACK -->\r\n\0");

			ctx_port_handler.rx_tx_buffer_idx = 0;
			TWCR |= RST_INT_DIS_ACK;

			break;

		// TWSR = 0xA0 (RX: Got STOP/RSTART while being addressed as slave, TX: N/A).
		case TW_SR_STOP:
			debug_uart_tx_string("[+] I2C: TW_SR_STOP: ACK -->\r\n\0");

			if (ctx_port_handler.rx_tx_buffer_idx == RX_TX_BUF_LEN - 1) {
				ctx_port_handler.rx_tx_data_valid = true;

				memcpy(
					&ctx_port_handler.rx_port,
					&ctx_port_handler.rx_tx_buffer[RX_BUF_IDX_PRT],
					RX_BUF_LEN_PRT
				);

				memcpy(
					&ctx_port_handler.rx_fid,
					&ctx_port_handler.rx_tx_buffer[RX_BUF_IDX_FID],
					RX_BUF_LEN_FID
				);

				memcpy(
					&ctx_port_handler.rx_data,
					&ctx_port_handler.rx_tx_buffer[RX_BUF_IDX_DAT],
					RX_BUF_LEN_DAT
				);

				port_handler[ctx_port_handler.rx_port](ctx_port_handler.rx_fid);
			}
			else {
				ctx_port_handler.rx_tx_data_valid = false;

				memset(&ctx_port_handler.rx_tx_buffer, 0, RX_TX_BUF_LEN);

				ctx_port_handler.rx_tx_buffer[1] = (int8_t)FID_RET_ERR_INV_DAT;
			}

			TWCR |= RST_INT_ENA_ACK;

			break;

		// Slave TX (Read GrovePi).

		// TWSR = 0xA8 (RX: START+ADDR+R, TX: ACK).
		case TW_ST_SLA_ACK:
			debug_uart_tx_string("[+] I2C: TW_ST_SLA_ACK: ACK -->\r\n\0");

			ctx_port_handler.rx_tx_buffer_idx = 0;

			if (!ctx_port_handler.rx_tx_data_valid) {
				memset(&ctx_port_handler.rx_tx_buffer, 0, RX_TX_BUF_LEN);
				ctx_port_handler.rx_tx_buffer[1] = (int8_t)FID_RET_ERR_INV_DAT;
			}

			TWDR = ctx_port_handler.rx_tx_buffer[ctx_port_handler.rx_tx_buffer_idx];
			ctx_port_handler.rx_tx_buffer_idx++;

			TWCR |= RST_INT_ENA_ACK;

			break;

		// TWSR = 0xB8 (RX: ACK, TX: TWDR).
		case TW_ST_DATA_ACK:
			debug_uart_tx_string("[+] I2C: TW_ST_DATA_ACK: ACK -->\r\n\0");

			if (ctx_port_handler.rx_tx_buffer_idx == RX_TX_BUF_LEN - 1) {
				debug_uart_tx_string("[+] I2C: TW_ST_DATA_ACK: NACK -->\r\n\0");

				TWDR = ctx_port_handler.rx_tx_buffer[ctx_port_handler.rx_tx_buffer_idx];
				TWCR |= RST_INT_DIS_ACK;
			}
			else {
				debug_uart_tx_string("[+] I2C: TW_ST_DATA_ACK: ACK -->\r\n\0");

				TWDR = ctx_port_handler.rx_tx_buffer[ctx_port_handler.rx_tx_buffer_idx];
				ctx_port_handler.rx_tx_buffer_idx++;
				TWCR |= RST_INT_ENA_ACK;
			}

			break;

		// TWSR = 0xC0 or 0xC8 (RX: NACK, TX: TWDR).
		case TW_ST_DATA_NACK:
		case TW_ST_LAST_DATA:
			// Reset internal data.
			debug_uart_tx_string("[+] I2C: TW_ST_DATA_NACK/TW_ST_LAST_DATA: ACK -->\r\n\0");

			ctx_port_handler.rx_tx_buffer_idx = 0;
			ctx_port_handler.rx_tx_data_valid = false;

			TWCR |= RST_INT_ENA_ACK;

			break;

		default:
			TWCR |= RST_INT_DIS_ACK;
	}
}
