PROJECT=mango

LDFLAGS=
CFLAGS=-c -Os
BUILDDIR=./build/

MCU=atmega328p
PROGRAMMER=linuxspi
PORT=/dev/spidev0.1

all: builddir
	avr-gcc $(CFLAGS) -mmcu=$(MCU) $(PROJECT).c -o $(BUILDDIR)$(PROJECT).o
	avr-gcc $(LDFLAGS) -mmcu=$(MCU) $(BUILDDIR)$(PROJECT).o -o $(BUILDDIR)$(PROJECT).elf
	avr-objcopy -O ihex -j .data -j text $(BUILDDIR)$(PROJECT).elf $(BUILDDIR)$(PROJECT).hex

size:
	avr-size --mcu=$(MCU) -C $(BUILDDIR)$(PROJECT).elf

flash:
	/root/avrdude -p $(MCU) -c $(PROGRAMMER) -P $(PORT) -U flash:w:$(BUILDDIR)$(PROJECT).hex:a
	echo 8 > /sys/class/gpio/export
	echo out > /sys/class/gpio/gpio8/direction
	echo 1 > /sys/class/gpio/gpio8/value
	echo 8 > /sys/class/gpio/unexport

builddir:
	$(shell mkdir -p $(BUILDDIR))

clean:
	rm -rf *.o
	rm -rf *.elf
	rm -rf *.hex
	rm -rf $(BUILDDIR)
