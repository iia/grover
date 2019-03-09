#include "mango.h"

void debug_uart_tx_string(char* s) {
	#if DEBUG_UART == true
		/*
		NOTE:
			Tried to use this function to TX USART for debugging while in the TWI
			ISR. Even though all interrupts of the USART were disabled it still
			did not work properly(interfered with TWI hardware). Possible silicon
			bug?

			The actual reason for this is still not clear.
		*/
		while (*s != '\0') {
			while (!(UCSR0A & _BV(UDRE0))) {
				;
			}

			UDR0 = *s;
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

		UCSR0B |= (uint8_t)((_BV(TXEN0)));
		UCSR0B &= (uint8_t)(~(_BV(RXEN0) & ~(_BV(RXCIE0)) & ~(_BV(TXCIE0)) & ~(_BV(UDRIE0))));
		UCSR0C |= (_BV(UCSZ00) | _BV(UCSZ01));
	#endif
}
