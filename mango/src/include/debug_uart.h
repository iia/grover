#ifndef DEBUG_UART_H
#define DEBUG_UART_H

#define DEBUG_UART true

void debug_uart_tx_string(char* s);
void debug_uart_init(uint32_t baud);

#endif // DEBUG_UART_H
