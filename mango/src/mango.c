#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <compat/twi.h>
//#include <util/twi.h>
#include <avr/interrupt.h>

uint8_t ra;


#define GROVEPI_PORT_COUNT 11
/*
typedef struct {
	uint8_t configuration;
} GROVEPI_PORT_t;

 enum {
	 GROVEPI_PORT_INDEX_0 = 0,
	 GROVEPI_PORT_INDEX_1,
	 GROVEPI_PORT_INDEX_2,
	 GROVEPI_PORT_INDEX_3,
	 GROVEPI_PORT_INDEX_4,
	 GROVEPI_PORT_INDEX_5,
	 GROVEPI_PORT_INDEX_6,
	 GROVEPI_PORT_INDEX_7,
	 GROVEPI_PORT_INDEX_8,
	 GROVEPI_PORT_INDEX_9,
	 GROVEPI_PORT_INDEX_10
} ;

GROVEPI_PORT_t GROVEPI_PORT_0  = {.configuration = };
GROVEPI_PORT_t GROVEPI_PORT_1  = {.configuration = };
GROVEPI_PORT_t GROVEPI_PORT_2  = {.configuration = };
GROVEPI_PORT_t GROVEPI_PORT_3  = {.configuration = };
GROVEPI_PORT_t GROVEPI_PORT_4  = {.configuration = };
GROVEPI_PORT_t GROVEPI_PORT_5  = {.configuration = };
GROVEPI_PORT_t GROVEPI_PORT_6  = {.configuration = };
GROVEPI_PORT_t GROVEPI_PORT_7  = {.configuration = };
GROVEPI_PORT_t GROVEPI_PORT_8  = {.configuration = };
GROVEPI_PORT_t GROVEPI_PORT_9  = {.configuration = };
GROVEPI_PORT_t GROVEPI_PORT_10 = {.configuration = };

GROVEPI_PORT_t grovepi_ports[GROVEPI_PORT_COUNT] = {
	GROVEPI_PORT_0,
	GROVEPI_PORT_1,
	GROVEPI_PORT_2,
	GROVEPI_PORT_3,
	GROVEPI_PORT_4,
	GROVEPI_PORT_5,
	GROVEPI_PORT_6,
	GROVEPI_PORT_7,
	GROVEPI_PORT_8,
	GROVEPI_PORT_9,
	GROVEPI_PORT_10
};
*/
int main(void) {
	cli();

	TWAR = (0x42 << 1) | 1;
	TWCR = (1<<TWIE) | (1<<TWEA) | (1<<TWINT) | (1<<TWEN);

	sei();

	while(1) {
		;
	}
}

// set port config (0000 0000) i2c WRITE. doing I2C READ just after this will return NULL
// set value       (0000 0010) i2c WRITE. doing I2C READ just after this will return the value that was set
// get port config (0000 0001) i2c WRITE and then I2C READ
// get value       (0000 0011) i2c WRITE and then I2C READ

// 11 ports(requires 4 bits + 2 bits for config)

// PORT A0 (0000): GROVEPI_PORT_0
	// DIGITAL IO (0000 01 11)
	// DIGITAL IO (0000 11 01)
	// ADC        (0000 00 11)
	// ADC        (0000 11 00)

// PORT A1 (0001): GROVEPI_PORT_1
	// DIGITAL IO (0001 01 11)
	// DIGITAL IO (0001 11 01)
	// ADC        (0001 00 11)
	// ADC        (0001 11 00)

// PORT A2 (0010): GROVEPI_PORT_2
	// DIGITAL IO (0010 01 11)
	// DIGITAL IO (0010 01 11)
	// ADC        (0010 01 11)
	// ADC        (0010 01 11)

// PORT D2 (0011): GROVEPI_PORT_3
	// DIGITAL IO (0011)
	// DIGITAL IO (0011)
	// PWM (0011)

// PORT D3 (0100): GROVEPI_PORT_4
	// DIGITAL IO (0100)
	// DIGITAL IO (0100)
	// PWM (0100)

// PORT D4 (0101): GROVEPI_PORT_5
	// DIGITAL IO (0101)
	// DIGITAL IO (0101)
	// PWM (0101)

// PORT D5 (0110): GROVEPI_PORT_6
	// DIGITAL IO (0110)
	// DIGITAL IO (0110)
	// PWM (0110)
	// PWM (0110)

// PORT D6 (0111): GROVEPI_PORT_7
	// DIGITAL IO (0111)
	// DIGITAL IO (0111)
	// PWM (0111)

// PORT D7 (1000): GROVEPI_PORT_8
	// DIGITAL IO (1000)
	// DIGITAL IO (1000)

// PORT D8 (1001): GROVEPI_PORT_9
	// DIGITAL IO (1001)
	// DIGITAL IO (1001)
	// PWM (1001)

// PORT SERIAL (1010): GROVEPI_PORT_10
	// DIGITAL IO (1010)
	// DIGITAL IO (1010)
	// UART (SERIAL TX/RX) (pending) (1010)

ISR(TWI_vect) {
	cli();

	// Slave RX (Write/Configure GrovePi)
	// 0x60
	if((TWSR & 0xFC) == TW_SR_SLA_ACK) {
		TWCR |= (1<<TWIE) | (1<<TWINT) | (1<<TWEA) | (1<<TWEN);
	}
	// 0x68
	else if((TWSR & 0xFC) == TW_SR_ARB_LOST_SLA_ACK) {
		TWCR |= (1<<TWIE) | (1<<TWINT) | (1<<TWEA) | (1<<TWEN);
	}
	// 0x70
	else if((TWSR & 0xFC) == TW_SR_GCALL_ACK) {
		TWCR |= (1<<TWIE) | (1<<TWINT) | (1<<TWEA) | (1<<TWEN);
	}
	// 0x78
	else if((TWSR & 0xFC) == TW_SR_ARB_LOST_GCALL_ACK) {
		TWCR |= (1<<TWIE) | (1<<TWINT) | (1<<TWEA) | (1<<TWEN);
	}
	// 0x80
	else if((TWSR & 0xFC) == TW_SR_DATA_ACK) {
		ra=TWDR;
		TWCR |= (1<<TWIE) | (1<<TWINT) | (1<<TWEA) | (1<<TWEN);
	}
	// 0x88
	else if((TWSR & 0xFC) == TW_SR_DATA_NACK) {
		TWCR |= (1<<TWIE) | (1<<TWINT) | (1<<TWEA) | (1<<TWEN);
	}
	// 0x90
	else if((TWSR & 0xFC) == TW_SR_GCALL_DATA_ACK) {
		TWCR |= (1<<TWIE) | (1<<TWINT) | (1<<TWEA) | (1<<TWEN);
	}
	// 0x98
	else if((TWSR & 0xFC) == TW_SR_GCALL_DATA_NACK) {
		TWCR |= (1<<TWIE) | (1<<TWINT) | (1<<TWEA) | (1<<TWEN);
	}
	// 0xA0
	else if((TWSR & 0xFC) == TW_SR_STOP) {
		TWCR |= (1<<TWIE) | (1<<TWINT) | (1<<TWEA) | (1<<TWEN);
	}

	// Slave TX (Read from GrovePi)
	// 0xA8
	else if((TWSR & 0xFC) == TW_ST_SLA_ACK) {
		
		if (ra == 0x43){
			TWDR = 0x44;
		}
		else {TWDR=0x4;}
		ra=0;
		TWCR |= (1<<TWIE) | (1<<TWINT) | (1<<TWEA) | (1<<TWEN);
	}
	// 0xB0
	else if((TWSR & 0xFC) == TW_ST_ARB_LOST_SLA_ACK) {
		TWCR |= (1<<TWIE) | (1<<TWINT) | (1<<TWEA) | (1<<TWEN);
	}
	// 0xB8
	else if((TWSR & 0xFC) == TW_ST_DATA_ACK) {
		TWDR = 0x44;
		TWCR |= (1<<TWIE) | (1<<TWINT) | (1<<TWEA) | (1<<TWEN);
	}
	// 0xC0
	else if((TWSR & 0xFC) == TW_ST_DATA_NACK) {
		TWCR |= (1<<TWIE) | (1<<TWINT) | (1<<TWEA) | (1<<TWEN);
	}
	// 0xC8
	else if((TWSR & 0xFC) == TW_ST_LAST_DATA) {
		TWCR |= (1<<TWIE) | (1<<TWINT) | (1<<TWEA) | (1<<TWEN);
	}

	sei();
}
