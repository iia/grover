#ifndef MANGO_H
#define MANGO_H

#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#include <avr/io.h>
#include <compat/twi.h>
#include <avr/interrupt.h>

#include "i2c.h"
#include "ports.h"
#include "debug_uart.h"

#define IDX_FID 3
#define LEN_FID 1
#define IDX_DAT 4
#define LEN_DAT 4
#define IDX_PRT_RET 2
#define LEN_PRT_RET 1
#define LEN_BUF_I2C 8

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
} CTX_MANGO_t;

extern CTX_MANGO_t ctx_mango;

#endif // MANGO_H
