#! /bin/bash

make -C /root/src/ clean
make -C /root/src/ all
make -C /root/src/ size
make -C /root/src/ flash
make -C /root/src/ clean
