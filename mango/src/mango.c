#define UART_DATA 3
#define UART_BAUD 9600
#define F_CPU 16000000UL
#define UART_UBRR (F_CPU / 16) / UART_BAUD - 1

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <avr/io.h>
#include <compat/twi.h>
#include <avr/interrupt.h>

#include "mango.h"

static struct {
	uint8_t rx_fid;
	uint8_t rx_port;
	bool tx_data_valid;
	uint8_t rx_tx_buffer_idx;
	uint8_t rx_buffer[RX_BUF_LEN];
	uint8_t tx_buffer[TX_BUF_LEN];
	uint8_t rx_data[RX_BUF_LEN_DAT];
} ctx_port_handler;

static int8_t port_handler_0(uint8_t fid) {
	PORT_0_FID_t port_fid = (PORT_0_FID_t)fid;

	switch (port_fid) {
		default:
			return (int8_t)ERR_PRT_HND_INV_FID;
	}

	return 0;
}

static int8_t port_handler_1(uint8_t fid) {
	PORT_1_FID_t port_fid = (PORT_1_FID_t)fid;

	switch (port_fid) {
		default:
			return (int8_t)ERR_PRT_HND_INV_FID;
	}

	return 0;
}

static int8_t port_handler_2(uint8_t fid) {
	PORT_2_FID_t port_fid = (PORT_2_FID_t)fid;

	switch (port_fid) {
		default:
			return (int8_t)ERR_PRT_HND_INV_FID;
	}

	return 0;
}

static int8_t port_handler_3(uint8_t fid) {
	PORT_3_FID_t port_fid = (PORT_3_FID_t)fid;

	switch (port_fid) {
		default:
			return (int8_t)ERR_PRT_HND_INV_FID;
	}

	return 0;
}

static int8_t port_handler_4(uint8_t fid) {
	PORT_4_FID_t port_fid = (PORT_4_FID_t)fid;

	switch (port_fid) {
		default:
			return (int8_t)ERR_PRT_HND_INV_FID;
	}

	return 0;
}

static int8_t port_handler_5(uint8_t fid) {
	PORT_5_FID_t port_fid = (PORT_5_FID_t)fid;

	switch (port_fid) {
		default:
			return (int8_t)ERR_PRT_HND_INV_FID;
	}

	return 0;
}

static int8_t port_handler_6(uint8_t fid) {
	PORT_6_FID_t port_fid = (PORT_6_FID_t)fid;

	switch (port_fid) {
		default:
			return (int8_t)ERR_PRT_HND_INV_FID;
	}

	return 0;
}

static int8_t port_handler_7(uint8_t fid) {
	PORT_7_FID_t port_fid = (PORT_7_FID_t)fid;

	switch (port_fid) {
		default:
			return (int8_t)ERR_PRT_HND_INV_FID;
	}

	return 0;
}

static int8_t port_handler_8(uint8_t fid) {
	PORT_8_FID_t port_fid = (PORT_8_FID_t)fid;

	switch (port_fid) {
		default:
			return (int8_t)ERR_PRT_HND_INV_FID;
	}

	return 0;
}

static int8_t port_handler_9(uint8_t fid) {
	PORT_9_FID_t port_fid = (PORT_9_FID_t)fid;

	switch (port_fid) {
		default:
			return (int8_t)ERR_PRT_HND_INV_FID;
	}

	return 0;
}

static int8_t port_handler_10(uint8_t fid) {
	PORT_10_FID_t port_fid = (PORT_10_FID_t)fid;

	switch (port_fid) {
		default:
			return (int8_t)ERR_PRT_HND_INV_FID;
	}

	return 0;
}

static void i2c_init(uint8_t i2c_address) {
	TWAR = (i2c_address << 1); // GCALL disabled.
	TWCR = (1 << TWIE) | (1 << TWEA) | (1 << TWINT) | (1 << TWEN);
}

static void uart_init(void) {
	UBRR0H = ((UART_UBRR) & 0xF00);
	UBRR0L = (uint8_t)((UART_UBRR) & 0xFF);

	UCSR0B |= _BV(TXEN0);

	UCSR0C = (UART_DATA << UCSZ00);
}

static void uart_tx_char(char data) {
	while (!(UCSR0A & _BV(UDRE0))) {
		;
	}

	UDR0 = (char)data;
}

static void uart_tx_string(char* string) {
	while (*string != '\0') {
		uart_tx_char(*string);

		++string;
	}
}

static PORT_HANDLER_t port_handler[NUMBER_OF_PORTS] =
	{
		&port_handler_0,
		&port_handler_1,
		&port_handler_2,
		&port_handler_3,
		&port_handler_4,
		&port_handler_5,
		&port_handler_6,
		&port_handler_7,
		&port_handler_8,
		&port_handler_9,
		&port_handler_10
	};

int main(void) {
	cli();

	uart_init();
	i2c_init((uint8_t)I2C_ADDRESS);

	memset(&ctx_port_handler, 0, sizeof(ctx_port_handler));

	uart_tx_string("Running...\n\0");

	sei();

	while(1) {
		;
	}

	return 0;
}

ISR(TWI_vect) {
	switch((TWSR & 0xFC)) {
		// Slave RX (Write GrovePi)

		// TWSR = 0x60 (RX: ADDR+W, TX: ACK)
		case TW_SR_SLA_ACK:
			ctx_port_handler.rx_tx_buffer_idx = 0;
			ctx_port_handler.tx_data_valid = false;
			TWCR |= RST_INT_ENA_ACK;

			break;

		// TWSR = 0x80 (Got TW_SR_SLA_ACK previously) (RX: DATA, TX: ACK)
		case TW_SR_DATA_ACK:
			ctx_port_handler.rx_buffer[ctx_port_handler.rx_tx_buffer_idx] = TWDR;

			ctx_port_handler.rx_tx_buffer_idx++;

			if (ctx_port_handler.rx_tx_buffer_idx >= RX_BUF_LEN) {
				ctx_port_handler.rx_tx_buffer_idx = 0;
			}

			TWCR |= RST_INT_ENA_ACK;

			break;

		// TWSR = 0x88 (Got TW_SR_SLA_ACK previously) (RX: DATA, TX: NACK)
		case TW_SR_DATA_NACK:
			TWCR |= RST_INT_ENA_ACK;

			break;

		// TWSR = 0xA0 (RX: Got STOP/RSTART while being addressed as slave, TX: N/A)
		case TW_SR_STOP:
			memcpy(
				&ctx_port_handler.rx_port,
				&ctx_port_handler.rx_buffer[RX_BUF_IDX_PRT],
				RX_BUF_LEN_PRT
			);

			memcpy(
				&ctx_port_handler.rx_fid,
				&ctx_port_handler.rx_buffer[RX_BUF_IDX_FID],
				RX_BUF_LEN_FID
			);

			memcpy(
				&ctx_port_handler.rx_data,
				&ctx_port_handler.rx_buffer[RX_BUF_IDX_DAT],
				RX_BUF_LEN_DAT
			);

			port_handler[ctx_port_handler.rx_port](ctx_port_handler.rx_fid);

			TWCR |= RST_INT_ENA_ACK;

			break;

		// Slave TX (Read GrovePi)

		// TWSR = 0xA8 (RX: ADDR+R, TX: ACK)
		case TW_ST_SLA_ACK:
			ctx_port_handler.rx_tx_buffer_idx = 0;

			if (!ctx_port_handler.tx_data_valid) {
				TWDR = 0;
			}
			else {
				TWDR = ctx_port_handler.tx_buffer[ctx_port_handler.rx_tx_buffer_idx];
			}

			ctx_port_handler.rx_tx_buffer_idx++;

			TWCR |= RST_INT_ENA_ACK;

			break;

		// TWSR = 0xB8 (RX: ACK, TX: TWDR)
		case TW_ST_DATA_ACK:
			if (!ctx_port_handler.tx_data_valid) {
				TWDR = 0;
			}
			else {
				TWDR = ctx_port_handler.tx_buffer[ctx_port_handler.rx_tx_buffer_idx];
			}

			ctx_port_handler.rx_tx_buffer_idx++;

			if (ctx_port_handler.rx_tx_buffer_idx >= TX_BUF_LEN) {
				ctx_port_handler.rx_tx_buffer_idx = 0;
			}

			if (ctx_port_handler.rx_tx_buffer_idx == 0) {
				TWCR |= RST_INT_DIS_ACK;
			}
			else {
				TWCR |= RST_INT_ENA_ACK;
			}

			break;

		// TWSR = 0xC0 or 0xC8 (RX: NACK, TX: TWDR)
		case TW_ST_DATA_NACK:
		case TW_ST_LAST_DATA:
			// Reset internal data.
			ctx_port_handler.tx_data_valid = false;

			TWCR |= RST_INT_ENA_ACK;

			break;

		default:
			TWCR |= RST_INT_ENA_ACK;
	}
}
