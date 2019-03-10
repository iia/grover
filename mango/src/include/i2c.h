#ifndef I2C_H
#define I2C_H

#define I2C_ADDRESS 42

#define IDX_FID 3
#define LEN_FID 1
#define IDX_DAT 4
#define LEN_DAT 4
#define IDX_PRT_RET 2
#define LEN_PRT_RET 1
#define LEN_BUF_I2C 8

void i2c_init(uint8_t i2c_address);
void i2c_load_response(int8_t ret, uint8_t fid, uint8_t* data);

#endif // I2C_H
