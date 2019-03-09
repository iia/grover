#ifndef I2C_H
#define I2C_H

#include <stdbool.h>

#define I2C_ADDRESS 42
#define RST_INT_DIS_ACK (_BV(TWINT) & ~_BV(TWEA))
#define RST_INT_ENA_ACK (_BV(TWINT) | _BV(TWEA))

#define IDX_FID 3
#define LEN_FID 1
#define IDX_DAT 4
#define LEN_DAT 4
#define IDX_PRT_RET 2
#define LEN_PRT_RET 1

#define LEN_BUF_I2C 8

struct {
	uint8_t fid;
	uint8_t port;
	bool is_valid_data;
	uint8_t idx_buffer;
	uint8_t data[LEN_DAT];
	uint8_t buffer[LEN_BUF_I2C];
} ctx_port_handler;

void i2c_init(uint8_t i2c_address);

#endif // I2C_H
