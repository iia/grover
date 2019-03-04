#define I2C_ADDRESS 42

#define GROVEPI_PORTS 11

#define RX_BUF_IDX_PRT 0
#define RX_BUF_IDX_FID 1
#define RX_BUF_IDX_DAT 2

#define RX_BUF_LEN_PRT 1
#define RX_BUF_LEN_FID 1
#define RX_BUF_LEN_DAT 4

#define RX_BUF_LEN (RX_BUF_LEN_PRT + RX_BUF_LEN_FID + RX_BUF_LEN_DAT)
#define TX_BUF_LEN 6

#define RST_INT_DIS_ACK (_BV(TWINT))
#define RST_INT_ENA_ACK ((_BV(TWINT)) | (_BV(TWEA)))

#define ERR_PRT_HND_INV_DAT -1
#define ERR_PRT_HND_INV_FID -2

typedef enum {
	PORT_0_FID_0 = 0,
} PORT_0_FID_t;

typedef enum {
	PORT_1_FID_0 = 0,
} PORT_1_FID_t;

typedef enum {
	PORT_2_FID_0 = 0,
} PORT_2_FID_t;

typedef enum {
	PORT_3_FID_0 = 0,
} PORT_3_FID_t;

typedef enum {
	PORT_4_FID_0 = 0,
} PORT_4_FID_t;

typedef enum {
	PORT_5_FID_0 = 0,
} PORT_5_FID_t;

typedef enum {
	PORT_6_FID_0 = 0,
} PORT_6_FID_t;

typedef enum {
	PORT_7_FID_0 = 0,
} PORT_7_FID_t;

typedef enum {
	PORT_8_FID_0 = 0,
} PORT_8_FID_t;

typedef enum {
	PORT_9_FID_0 = 0,
} PORT_9_FID_t;

typedef enum {
	PORT_10_FID_0 = 0,
} PORT_10_FID_t;

typedef int8_t (*PORT_HANDLER_t)(uint8_t);
