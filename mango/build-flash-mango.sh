#! /bin/bash

docker build -t 'build-flash-mango:dockerfile' ./docker/

docker run --privileged -it -v $(pwd)/src/:/root/src/ build-flash-mango:dockerfile ./build-flash-mango.sh
