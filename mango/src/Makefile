PROJECT=mango

LDFLAGS=
CFLAGS=-Wall -c -Ofast
BUILDDIR=./build/

MCU=atmega328p
PROGRAMMER=linuxgpio

all: builddir
	avr-gcc $(CFLAGS) -mmcu=$(MCU) -I./include $(PROJECT).c -o $(BUILDDIR)$(PROJECT).o
	avr-gcc $(LDFLAGS) -mmcu=$(MCU) -I./include $(BUILDDIR)$(PROJECT).o -o $(BUILDDIR)$(PROJECT).elf
	avr-objcopy -O ihex -j .data -j text $(BUILDDIR)$(PROJECT).elf $(BUILDDIR)$(PROJECT).hex

flash:
	$(shell \
		avrdude -p $(MCU) -c $(PROGRAMMER) -U flash:w:$(BUILDDIR)$(PROJECT).hex:a; \
		echo 8 > /sys/class/gpio/export && \
		echo out > /sys/class/gpio/gpio8/direction && \
		echo 1 > /sys/class/gpio/gpio8/value && \
		echo 8 > /sys/class/gpio/unexport)


size:
	avr-size --mcu=$(MCU) -C $(BUILDDIR)$(PROJECT).elf

builddir:
	$(shell mkdir -p $(BUILDDIR))

info:
	$(shell \
		avrdude -p $(MCU) -c $(PROGRAMMER) -v; \
		echo 8 > /sys/class/gpio/export && \
		echo out > /sys/class/gpio/gpio8/direction && \
		echo 1 > /sys/class/gpio/gpio8/value && \
		echo 8 > /sys/class/gpio/unexport)

clean:
	rm -rf *.o
	rm -rf *.elf
	rm -rf *.hex
	rm -rf $(BUILDDIR)
