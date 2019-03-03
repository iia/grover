#! /bin/bash

docker build -t 'mango-farmer:dockerfile' ./docker/

docker run --privileged --rm -it -v $(pwd)/src/:/root/src/ mango-farmer:dockerfile ./mango-build-flash.sh
