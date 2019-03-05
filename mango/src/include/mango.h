#define I2C_ADDRESS 42

#define DEBUG_UART true

#define GROVEPI_PORTS 11

#define RX_BUF_IDX_PRT 0
#define RX_BUF_IDX_FID 1
#define RX_BUF_IDX_DAT 2

#define RX_BUF_LEN_PRT 1
#define RX_BUF_LEN_FID 1
#define RX_BUF_LEN_DAT 4

#define RX_TX_BUF_LEN 6

#define RST_INT_DIS_ACK (_BV(TWINT))
#define RST_INT_ENA_ACK ((_BV(TWINT)) | (_BV(TWEA)))

// FID return values.
#define FID_RET_OK           0
#define FID_RET_ERR_INV_FID -1
#define FID_RET_ERR_INV_DAT -2

typedef enum {
	FID_PORT_A0_CH0_ = 0x01,
	FID_PORT_A0_CH1_ = 0x02
} FID_PORT_A0_t;

typedef enum {
	FID_PORT_A1_CH0_ = 0x01,
	FID_PORT_A1_CH1_ = 0x02
} FID_PORT_A1_t;

typedef enum {
	FID_PORT_A2_CH0_ = 0x01,
	FID_PORT_A2_CH1_ = 0x02
} FID_PORT_A2_t;

typedef enum {
	FID_PORT_SERIAL_CH0_ = 0x01,
	FID_PORT_SERIAL_CH1_ = 0x02
} FID_PORT_SERIAL_t;

typedef enum {
	FID_PORT_D2_CH0_ = 0x01,
	FID_PORT_D2_CH1_ = 0x02
} FID_PORT_D2_t;

typedef enum {
	FID_PORT_D3_CH0_ = 0x01,
	FID_PORT_D3_CH1_ = 0x02
} FID_PORT_D3_t;

typedef enum {
	FID_PORT_D4_CH0_ = 0x01,
	FID_PORT_D4_CH1_ = 0x02
} FID_PORT_D4_t;

typedef enum {
	FID_PORT_D5_CH0_ = 0x01,
	FID_PORT_D5_CH1_ = 0x02
} FID_PORT_D5_t;

typedef enum {
	FID_PORT_D6_CH0_ = 0x01,
	FID_PORT_D6_CH1_ = 0x02
} FID_PORT_D6_t;

typedef enum {
	FID_PORT_D7_CH0_SET_DIN     = 0x01,
	FID_PORT_D7_CH0_SET_DOU     = 0x02,
	FID_PORT_D7_CH0_SET_DIN_PUP = 0x03,
	FID_PORT_D7_CH0_GET_DIR     = 0x04,
	FID_PORT_D7_CH0_GET_VAL     = 0x05,
	FID_PORT_D7_CH0_GET_PUP     = 0x07,
	FID_PORT_D7_CH1_SET_DIN     = 0x08,
	FID_PORT_D7_CH1_SET_DOU     = 0x09,
	FID_PORT_D7_CH1_SET_DIN_PUP = 0x0A,
	FID_PORT_D7_CH1_GET_DIR0    = 0x0B,
	FID_PORT_D7_CH1_GET_VAL     = 0x0C,
	FID_PORT_D7_CH1_GET_PUP     = 0x0D
} FID_PORT_D7_t;

typedef enum {
	FID_PORT_D8_CH0_ = 0x01,
	FID_PORT_D8_CH1_ = 0x02
} FID_PORT_D8_t;

typedef void (*PORT_HANDLER_t)(uint8_t);
