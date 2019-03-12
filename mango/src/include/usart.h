#ifndef USART_H
#define USART_H

#define USART_DEBUG false

#define USART_BAUD 57600
#define USART_BAUD_RATE ((F_CPU) / (USART_BAUD * 16UL) - 1)

void usart_init(void);
void usart_tx_debug(char* data);

#endif // USART_H
