#! /bin/bash

docker build -t 'grover-firmware-manager:dockerfile' ./docker/

docker run --privileged -it -v $(pwd)/src/:/root/src/ grover-firmware-manager:dockerfile ./flash-mango.sh
