#include "mango.h"

void usart_init() {
	/*
	USART config:
		1. 8-N-1
		2. TX only, RX disabled
		3. All USART interrupt disabled
	*/
	UBRR0H = (USART_BAUD_RATE >> 8);
	UBRR0L = USART_BAUD_RATE;

	UCSR0B |= (uint8_t)((_BV(TXEN0)));
	UCSR0B &= (uint8_t)(~(_BV(RXEN0) & ~(_BV(RXCIE0)) & ~(_BV(TXCIE0)) & ~(_BV(UDRIE0))));
	UCSR0C |= ((_BV(UCSZ00)) | (_BV(UCSZ01)));
}

void usart_tx_debug(char* data) {
	#if USART_DEBUG == true
		while (*data != '\0') {
			while (!(UCSR0A & _BV(UDRE0))) {
				;
			}

			UDR0 = *data;
			data++;
		}
	#endif
}
