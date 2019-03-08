#include <stdint.h>
#include <stdbool.h>
#include <avr/io.h>

#include "debug_uart.h"

void debug_uart_tx_string(char* s) {
	#if DEBUG_UART == true
		/*
		FIXME:
			Disabling I2C(TWI) here because if a string is being TXed from
			an I2C ISR handler then for some reason writing to UDR0 clears
			the I2C interrupt. Which is clearly the wrong place to clear the
			interrupt and causes I2C bus problems.

			The actual reason for this is still not clear.
		*/
		TWCR &= ~_BV(TWIE);

		while (*s != '\0') {
			while (!(UCSR0A & _BV(UDRE0))) {
				;
			}

			UDR0 = *s;
			++s;
		}

		TWCR |= _BV(TWIE);
	#endif
}

void debug_uart_init(uint32_t baud) {
	#if DEBUG_UART == true
		// TX only debug UART (8-N-1).
		uint8_t ubrr = ((F_CPU / 16) / baud) - 1;

		UBRR0H = (uint8_t)(ubrr & 0x0F00);
		UBRR0L = (uint8_t)(ubrr & 0x00FF);
		UCSR0B |= (_BV(TXEN0) & ~_BV(RXEN0) & ~_BV(RXCIE0) & ~_BV(TXCIE0) & ~_BV(UDRIE0));
		UCSR0C = (3 << UCSZ00);
	#endif
}
