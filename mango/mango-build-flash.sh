#! /bin/bash

docker pull iia86/mango_farmer:v1

docker run --privileged --rm -it -v $(pwd)/src/:/root/src/ iia86/mango_farmer:v1 ./scripts/mango-build-flash.sh
