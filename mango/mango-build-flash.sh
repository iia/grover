#! /bin/bash

docker pull iia86/env_build_mango:v1

docker run --privileged --rm -it -v $(pwd)/src/:/root/src/ iia86/env_build_mango:v1 ./scripts/mango-build-flash.sh
