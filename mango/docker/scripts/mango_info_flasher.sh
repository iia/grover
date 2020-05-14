#!/usr/bin/env bash

# Must be executed from /home/mango directory in the Docker container.

# Get flasher info.
avrdude -c linuxspi -p m328p -P /dev/spidev0.1 -v

# Wait.
sleep 0.5

# Reset.
echo 8 | tee /sys/class/gpio/export &> /dev/null
echo out | tee /sys/class/gpio/gpio8/direction &> /dev/null
echo 1 | tee /sys/class/gpio/gpio8/value &> /dev/null
echo 8 | tee /sys/class/gpio/unexport &> /dev/null
