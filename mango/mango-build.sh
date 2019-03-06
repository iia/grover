#! /bin/bash

docker pull iia86/mango-farmer:v1

docker run --privileged --rm -it -v $(pwd)/src/:/root/src/ iia86/mango-farmer:v1 ./scripts/./mango-build.sh
