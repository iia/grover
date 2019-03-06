PROJECT=mango
BUILDDIR=./build/
INCLUDEDIR=./include/

LDFLAGS=
CFLAGS=-Wall -c -Os

MCU=atmega328p
PROGRAMMER=linuxgpio

OBJECTS := $(addprefix $(BUILDDIR),$(patsubst %.c,%.o,$(wildcard *.c)))

all: builddir $(OBJECTS)
	avr-gcc \
		$(LDFLAGS) \
		-mmcu=$(MCU) \
		-DF_CPU=16000000 \
		-I$(INCLUDEDIR) \
		$(OBJECTS) \
		-o $(BUILDDIR)$(PROJECT).elf

	avr-objcopy \
		-O ihex \
		-j .data \
		-j .text \
		$(BUILDDIR)$(PROJECT).elf \
		$(BUILDDIR)$(PROJECT).hex

builddir:
	$(shell mkdir -p $(BUILDDIR))

$(BUILDDIR)%.o: %.c $(INCLUDEDIR)%.h
	avr-gcc \
		$(CFLAGS) \
		-mmcu=$(MCU) \
		-DF_CPU=16000000 \
		-I$(INCLUDEDIR) \
		$< -o $@

size:
	avr-size --mcu=$(MCU) -C $(BUILDDIR)$(PROJECT).elf

flash:
	$(shell \
		echo 8 > /sys/class/gpio/unexport; \
		echo 9 > /sys/class/gpio/unexport; \
		echo 10 > /sys/class/gpio/unexport; \
		echo 11 > /sys/class/gpio/unexport; \
		avrdude -p $(MCU) -c $(PROGRAMMER) -U lfuse:w:0xFF:m; \
		avrdude -p $(MCU) -c $(PROGRAMMER) -U hfuse:w:0xDA:m; \
		avrdude -p $(MCU) -c $(PROGRAMMER) -U efuse:w:0x05:m; \
		avrdude -p $(MCU) -c $(PROGRAMMER) -U flash:w:$(BUILDDIR)$(PROJECT).hex:a; \
		echo 8 > /sys/class/gpio/export; \
		echo out > /sys/class/gpio/gpio8/direction; \
		echo 1 > /sys/class/gpio/gpio8/value; \
		echo 8 > /sys/class/gpio/unexport)

info:
	$(shell \
		echo 8 > /sys/class/gpio/unexport; \
		echo 9 > /sys/class/gpio/unexport; \
		echo 10 > /sys/class/gpio/unexport; \
		echo 11 > /sys/class/gpio/unexport; \
		avrdude -p $(MCU) -c $(PROGRAMMER) -v; \
		echo 8 > /sys/class/gpio/export; \
		echo out > /sys/class/gpio/gpio8/direction; \
		echo 1 > /sys/class/gpio/gpio8/value; \
		echo 8 > /sys/class/gpio/unexport)

reset:
	$(shell \
		echo 8 > /sys/class/gpio/unexport; \
		echo 8 > /sys/class/gpio/export; \
		echo out > /sys/class/gpio/gpio8/direction; \
		echo 0 > /sys/class/gpio/gpio8/value; \
		sleep 2; \
		echo 1 > /sys/class/gpio/gpio8/value; \
		echo 8 > /sys/class/gpio/unexport)

clean:
	rm -rf *.o
	rm -rf *.elf
	rm -rf *.hex
	rm -rf $(BUILDDIR)
