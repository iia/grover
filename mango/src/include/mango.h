#ifndef MANGO_H
#define MANGO_H

#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#include <avr/io.h>
#include <compat/twi.h>
#include <util/atomic.h>
#include <avr/interrupt.h>

#include "i2c.h"
#include "ports.h"
#include "usart.h"

typedef void (*TASK_I2C_ISR_RESPONSE_t)(void);

typedef struct {
	uint8_t idx_buffer;
	uint8_t buffer[LEN_BUF_I2C];
} CTX_MANGO_I2C_t;

typedef struct {
	uint8_t fid;
	uint8_t port;
	bool is_valid_data;
	uint8_t data[LEN_DAT];
} CTX_MANGO_PORT_t;

typedef struct {
	CTX_MANGO_I2C_t i2c;
	CTX_MANGO_PORT_t port;

	// Must be volatile as we assign them in the I2C ISR.
	volatile TASK_PORT_t task_port;
	volatile TASK_I2C_ISR_RESPONSE_t task_i2c_isr_response;
} CTX_MANGO_t;

extern CTX_MANGO_t ctx_mango;

#endif // MANGO_H
