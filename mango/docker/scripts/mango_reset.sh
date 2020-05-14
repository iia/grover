#!/usr/bin/env bash

# Reset.
echo 8 | tee /sys/class/gpio/export &> /dev/null
echo out | tee /sys/class/gpio/gpio8/direction &> /dev/null
echo 1 | tee /sys/class/gpio/gpio8/value &> /dev/null
echo 8 | tee /sys/class/gpio/unexport &> /dev/null
