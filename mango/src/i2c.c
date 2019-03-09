#include "mango.h"

void i2c_init(uint8_t i2c_address) {
	debug_uart_tx_string("[+] I2C: I2C init\r\n\0");

	TWAR = (uint8_t)(i2c_address << 1); // Disable general call.
	TWCR |= (uint8_t)((_BV(TWIE)) | (_BV(TWEN)) | (_BV(TWEA)) | (_BV(TWINT)));
}

/*
NOTE:
	Do not use the USART interface (debug_uart_tx_string) or use any hardware
	peripherals from within the interrupt handler!
*/
ISR(TWI_vect) {
	switch((TWSR & 0xFC)) {
		// Slave RX.

		// TWSR = 0x60 (RX: START+ADDR+W, TX: ACK).
		case TW_SR_SLA_ACK:
			ctx_mango.i2c.idx_buffer = 0;
			ctx_mango.port.is_valid_data = false;

			// Reset interrupt and enable ACK.
			TWCR |= (uint8_t)((_BV(TWEA)) | (_BV(TWINT)));

			break;

		// TWSR = 0x80 (Got TW_SR_SLA_ACK previously) (RX: DATA, TX: ACK).
		case TW_SR_DATA_ACK:
			if (ctx_mango.i2c.idx_buffer < (LEN_BUF_I2C - 1)) {
				ctx_mango.i2c.buffer[ctx_mango.i2c.idx_buffer] = TWDR;
				ctx_mango.i2c.idx_buffer++;

				// Reset interrupt and enable ACK.
				TWCR |= (uint8_t)((_BV(TWEA)) | (_BV(TWINT)));
			}
			else if (ctx_mango.i2c.idx_buffer == (LEN_BUF_I2C - 1)) {
				ctx_mango.i2c.buffer[ctx_mango.i2c.idx_buffer] = TWDR;

				// Reset interrupt and disable ACK.
				TWCR |= (uint8_t)((_BV(TWINT)));
				TWCR &= (uint8_t)(~(_BV(TWEA)));
			}
			else {
				// Reset interrupt and disable ACK.
				TWCR |= (uint8_t)((_BV(TWINT)));
				TWCR &= (uint8_t)(~(_BV(TWEA)));
			}

			break;

		// TWSR = 0x88 (Got TW_SR_SLA_ACK previously) (RX: DATA, TX: NACK).
		case TW_SR_DATA_NACK:
			ctx_mango.i2c.idx_buffer = 0;

			// Reset interrupt and disable ACK.
			TWCR |= (uint8_t)((_BV(TWINT)));
			TWCR &= (uint8_t)(~(_BV(TWEA)));

			break;

		// TWSR = 0xA0 (RX: Got STOP/RSTART while being addressed as slave, TX: N/A).
		case TW_SR_STOP:
			if (ctx_mango.i2c.idx_buffer == LEN_BUF_I2C - 1) {
				memcpy(
					&ctx_mango.port.port,
					&ctx_mango.i2c.buffer[IDX_PRT_RET],
					LEN_PRT_RET
				);

				memcpy(
					&ctx_mango.port.fid,
					&ctx_mango.i2c.buffer[IDX_FID],
					LEN_FID
				);

				memcpy(
					&ctx_mango.port.data,
					&ctx_mango.i2c.buffer[IDX_DAT],
					LEN_DAT
				);

				ctx_mango.port.is_valid_data = true;

				port_handler[ctx_mango.port.port]();
			}
			else {
				ctx_mango.port.is_valid_data = false;
			}

			// Reset interrupt and enable ACK.
			TWCR |= (uint8_t)((_BV(TWEA)) | (_BV(TWINT)));

			break;

		// Slave TX.

		// TWSR = 0xA8 (RX: START+ADDR+R, TX: ACK).
		case TW_ST_SLA_ACK:
			ctx_mango.i2c.idx_buffer = 0;

			if (!ctx_mango.port.is_valid_data) {
				memset(&ctx_mango.i2c.buffer, 0, LEN_BUF_I2C);

				ctx_mango.i2c.buffer[IDX_PRT_RET] = (int8_t)FID_RET_ERR_INV_DAT;
			}

			TWDR = ctx_mango.i2c.buffer[ctx_mango.i2c.idx_buffer];

			ctx_mango.i2c.idx_buffer++;

			// Reset interrupt and enable ACK.
			TWCR |= (uint8_t)((_BV(TWEA)) | (_BV(TWINT)));

			break;

		// TWSR = 0xB8 (RX: ACK, TX: TWDR).
		case TW_ST_DATA_ACK:
			if (ctx_mango.i2c.idx_buffer < (LEN_BUF_I2C - 1)) {
				TWDR = ctx_mango.i2c.buffer[ctx_mango.i2c.idx_buffer];

				ctx_mango.i2c.idx_buffer++;

				// Reset interrupt and enable ACK.
				TWCR |= (uint8_t)((_BV(TWEA)) | (_BV(TWINT)));
			}
			else if (ctx_mango.i2c.idx_buffer == (LEN_BUF_I2C - 1)) {
				TWDR = ctx_mango.i2c.buffer[ctx_mango.i2c.idx_buffer];

				// Reset interrupt and disable ACK.
				TWCR |= (uint8_t)((_BV(TWINT)));
				TWCR &= (uint8_t)(~(_BV(TWEA)));
			}
			else {
				// Reset interrupt and disable ACK.
				TWCR |= (uint8_t)((_BV(TWINT)));
				TWCR &= (uint8_t)(~(_BV(TWEA)));
			}

			break;

		// TWSR = 0xC0 or 0xC8 (RX: NACK, TX: TWDR).
		case TW_ST_DATA_NACK:
		case TW_ST_LAST_DATA:
			// Reset internal data.
			ctx_mango.i2c.idx_buffer = 0;
			ctx_mango.port.is_valid_data = false;

			// Reset interrupt and enable ACK.
			TWCR |= (uint8_t)((_BV(TWEA)) | (_BV(TWINT)));

			break;

		default:
			// Reset interrupt and enable ACK.
			TWCR |= (uint8_t)((_BV(TWEA)) | (_BV(TWINT)));
	}
}
