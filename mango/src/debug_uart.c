#include <stdint.h>
#include <avr/io.h>

#include "debug_uart.h"

void debug_uart_tx_char(char c) {
	#if DEBUG_UART == true
		while (!(UCSR0A & _BV(UDRE0))) {
			;
		}

		UDR0 = c;
	#endif
}

void debug_uart_tx_string(char* s) {
	#if DEBUG_UART == true
		while (*s != '\0') {
			debug_uart_tx_char(*s);

			++s;
		}
	#endif
}

void debug_uart_init(uint32_t baud) {
	#if DEBUG_UART == true
		// TX only debug UART (8-N-1).
		uint8_t ubrr = ((F_CPU / 16) / baud) - 1;

		UBRR0H = (uint8_t)(ubrr & 0x0F00);
		UBRR0L = (uint8_t)(ubrr & 0x00FF);
		UCSR0B |= _BV(TXEN0);
		UCSR0C = (3 << UCSZ00);
	#endif
}
