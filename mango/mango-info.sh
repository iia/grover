#!/usr/bin/env bash

docker run --privileged --rm -it -v $(pwd)/src/:/root/src/ iia86/env_build_mango:v1 ./scripts/mango-info.sh
