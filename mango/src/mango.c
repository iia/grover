#define F_CPU 16000000UL

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
	bool rx_tx_data_valid;
	uint8_t rx_tx_buffer_idx;
	uint8_t rx_tx_buffer[RX_TX_BUF_LEN];
	uint8_t rx_data[RX_BUF_LEN_DAT];
} ctx_port_handler;

static void port_handler_A0(uint8_t fid) {
	FID_PORT_A0_t port_fid = (FID_PORT_A0_t)fid;

	switch (port_fid) {
		default:
			break;
	}
}

static void port_handler_A1(uint8_t fid) {
	FID_PORT_A1_t port_fid = (FID_PORT_A1_t)fid;

	switch (port_fid) {
		default:
			break;
	}
}

static void port_handler_A2(uint8_t fid) {
	FID_PORT_A2_t port_fid = (FID_PORT_A2_t)fid;

	switch (port_fid) {
		default:
			break;
	}
}

static void port_handler_serial(uint8_t fid) {
	FID_PORT_SERIAL_t port_fid = (FID_PORT_SERIAL_t)fid;

	switch (port_fid) {
		default:
			break;
	}
}

static void port_handler_D2(uint8_t fid) {
	FID_PORT_D2_t port_fid = (FID_PORT_D2_t)fid;

	switch (port_fid) {
		default:
			break;
	}
}

static void port_handler_D3(uint8_t fid) {
	FID_PORT_D3_t port_fid = (FID_PORT_D3_t)fid;

	switch (port_fid) {
		default:
			break;
	}
}

static void port_handler_D4(uint8_t fid) {
	FID_PORT_D4_t port_fid = (FID_PORT_D4_t)fid;

	switch (port_fid) {
		default:
			break;
	}
}

static void port_handler_D5(uint8_t fid) {
	FID_PORT_D5_t port_fid = (FID_PORT_D5_t)fid;

	switch (port_fid) {
		default:
			break;
	}
}

static void port_handler_D6(uint8_t fid) {
	FID_PORT_D6_t port_fid = (FID_PORT_D6_t)fid;

	switch (port_fid) {
		default:
			break;
	}
}

static void port_handler_D7(uint8_t fid) {
	FID_PORT_D7_t port_fid = (FID_PORT_D7_t)fid;

	switch (port_fid) {
		default:
			break;
	}
}

static void port_handler_D8(uint8_t fid) {
	FID_PORT_D8_t port_fid = (FID_PORT_D8_t)fid;

	switch (port_fid) {
		default:
			break;
	}
}

static void i2c_init(uint8_t i2c_address) {
	TWAR = (i2c_address << 1); // Disable general call.
	TWCR |= _BV(TWIE) | _BV(TWEA) | _BV(TWINT) | _BV(TWEN);
}

static void debug_uart_init(uint32_t baud) {
	#if DEBUG_UART == true
		// TX only debug UART (8-N-1).
		uint8_t ubrr = ((F_CPU / 16) / baud) - 1;

		UBRR0H = (uint8_t)(ubrr & 0x0F00);
		UBRR0L = (uint8_t)(ubrr & 0x00FF);
		UCSR0B |= _BV(TXEN0);
		UCSR0C = (3 << UCSZ00);
	#endif
}

static void debug_uart_tx_char(char c) {
	#if DEBUG_UART == true
		while (!(UCSR0A & _BV(UDRE0))) {
			;
		}

		UDR0 = c;
	#endif
}

static void debug_uart_tx_string(char* s) {
	#if DEBUG_UART == true
		while (*s != '\0') {
			debug_uart_tx_char(*s);

			++s;
		}
	#endif
}

static PORT_HANDLER_t port_handler[GROVEPI_PORTS] =
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

ISR(TWI_vect) {
	switch((TWSR & 0xFC)) {
		// Slave RX (Write GrovePi).

		// TWSR = 0x60 (RX: START+ADDR+W, TX: ACK).
		case TW_SR_SLA_ACK:
			ctx_port_handler.rx_tx_buffer_idx = 0;
			ctx_port_handler.rx_tx_data_valid = false;
			TWCR |= RST_INT_ENA_ACK;

			break;

		// TWSR = 0x80 (Got TW_SR_SLA_ACK previously) (RX: DATA, TX: ACK).
		case TW_SR_DATA_ACK:
			if (ctx_port_handler.rx_tx_buffer_idx == RX_TX_BUF_LEN - 1) {
				ctx_port_handler.rx_tx_buffer[ctx_port_handler.rx_tx_buffer_idx] = TWDR;
				TWCR |= RST_INT_DIS_ACK;
			}
			else {
				ctx_port_handler.rx_tx_buffer[ctx_port_handler.rx_tx_buffer_idx] = TWDR;
				ctx_port_handler.rx_tx_buffer_idx++;
				TWCR |= RST_INT_ENA_ACK;
			}

			break;

		// TWSR = 0x88 (Got TW_SR_SLA_ACK previously) (RX: DATA, TX: NACK).
		case TW_SR_DATA_NACK:
			ctx_port_handler.rx_tx_buffer_idx = 0;
			TWCR |= RST_INT_DIS_ACK;

			break;

		// TWSR = 0xA0 (RX: Got STOP/RSTART while being addressed as slave, TX: N/A).
		case TW_SR_STOP:
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
			if (ctx_port_handler.rx_tx_buffer_idx == RX_TX_BUF_LEN - 1) {
				TWDR = ctx_port_handler.rx_tx_buffer[ctx_port_handler.rx_tx_buffer_idx];
				TWCR |= RST_INT_DIS_ACK;
			}
			else {
				TWDR = ctx_port_handler.rx_tx_buffer[ctx_port_handler.rx_tx_buffer_idx];
				ctx_port_handler.rx_tx_buffer_idx++;
				TWCR |= RST_INT_ENA_ACK;
			}

			break;

		// TWSR = 0xC0 or 0xC8 (RX: NACK, TX: TWDR).
		case TW_ST_DATA_NACK:
		case TW_ST_LAST_DATA:
			// Reset internal data.
			ctx_port_handler.rx_tx_buffer_idx = 0;
			ctx_port_handler.rx_tx_data_valid = false;

			TWCR |= RST_INT_ENA_ACK;

			break;

		default:
			TWCR |= RST_INT_DIS_ACK;
	}
}
