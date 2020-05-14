#ifndef BOARD_COMMON_H
#define BOARD_COMMON_H

#include "cpu.h"

#ifdef __cplusplus
extern "C" {
#endif

#define STDIO_UART_BAUDRATE (9600U)

#define CPU_ATMEGA_CLK_SCALE_INIT CPU_ATMEGA_CLK_SCALE_DIV1

#define XTIMER_WIDTH   (16)
#define XTIMER_HZ      (250000UL)
#define XTIMER_BACKOFF (40)


#define CONFIG_ZTIMER_USEC_TYPE  ZTIMER_TYPE_PERIPH_TIMER
#define CONFIG_ZTIMER_USEC_DEV   (TIMER_DEV(0))
#define CONFIG_ZTIMER_USEC_FREQ  (250000LU)
#define CONFIG_ZTIMER_USEC_WIDTH (16)

void board_init(void);

#ifdef __cplusplus
}
#endif

#endif /* BOARD_COMMON_H */
