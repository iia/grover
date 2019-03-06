#include <stdint.h>

#include "i2c.h"
#include "ports.h"

void port_handler_A0(uint8_t fid) {
	FID_PORT_A0_t port_fid = (FID_PORT_A0_t)fid;

	switch (port_fid) {
		default:
			break;
	}
}

void port_handler_A1(uint8_t fid) {
	FID_PORT_A1_t port_fid = (FID_PORT_A1_t)fid;

	switch (port_fid) {
		default:
			break;
	}
}

void port_handler_A2(uint8_t fid) {
	FID_PORT_A2_t port_fid = (FID_PORT_A2_t)fid;

	switch (port_fid) {
		default:
			break;
	}
}

void port_handler_serial(uint8_t fid) {
	FID_PORT_SERIAL_t port_fid = (FID_PORT_SERIAL_t)fid;

	switch (port_fid) {
		default:
			break;
	}
}

void port_handler_D2(uint8_t fid) {
	FID_PORT_D2_t port_fid = (FID_PORT_D2_t)fid;

	switch (port_fid) {
		default:
			break;
	}
}

void port_handler_D3(uint8_t fid) {
	FID_PORT_D3_t port_fid = (FID_PORT_D3_t)fid;

	switch (port_fid) {
		default:
			break;
	}
}

void port_handler_D4(uint8_t fid) {
	FID_PORT_D4_t port_fid = (FID_PORT_D4_t)fid;

	switch (port_fid) {
		default:
			break;
	}
}

void port_handler_D5(uint8_t fid) {
	FID_PORT_D5_t port_fid = (FID_PORT_D5_t)fid;

	switch (port_fid) {
		default:
			break;
	}
}

void port_handler_D6(uint8_t fid) {
	FID_PORT_D6_t port_fid = (FID_PORT_D6_t)fid;

	switch (port_fid) {
		default:
			break;
	}
}

void port_handler_D7(uint8_t fid) {
	FID_PORT_D7_t port_fid = (FID_PORT_D7_t)fid;

	switch (port_fid) {
		default:
			break;
	}
}

void port_handler_D8(uint8_t fid) {
	FID_PORT_D8_t port_fid = (FID_PORT_D8_t)fid;

	switch (port_fid) {
		default:
			break;
	}
}

PORT_HANDLER_t port_handler[GROVEPI_PORTS] =
	{
		&port_handler_A0,
		&port_handler_A1,
		&port_handler_A2,
		&port_handler_serial,
		&port_handler_D2,
		&port_handler_D3,
		&port_handler_D4,
		&port_handler_D5,
		&port_handler_D6,
		&port_handler_D7,
		&port_handler_D8
	};
