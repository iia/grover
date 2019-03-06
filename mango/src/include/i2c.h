#ifndef I2C_H
#define I2C_H

#include <stdbool.h>

#define I2C_ADDRESS 42
#define RST_INT_DIS_ACK (_BV(TWINT))
#define RST_INT_ENA_ACK ((_BV(TWINT)) | (_BV(TWEA)))

#define RX_BUF_IDX_PRT 0
#define RX_BUF_IDX_FID 1
#define RX_BUF_IDX_DAT 2
#define RX_BUF_LEN_PRT 1
#define RX_BUF_LEN_FID 1
#define RX_BUF_LEN_DAT 4
#define RX_TX_BUF_LEN 6

struct {
	uint8_t rx_fid;
	uint8_t rx_port;
	bool rx_tx_data_valid;
	uint8_t rx_tx_buffer_idx;
	uint8_t rx_tx_buffer[RX_TX_BUF_LEN];
	uint8_t rx_data[RX_BUF_LEN_DAT];
} ctx_port_handler;

void i2c_init(uint8_t i2c_address);

#endif // I2C_H
