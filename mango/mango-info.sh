#!/usr/bin/env bash

docker run --privileged --rm -it -v $(pwd)/src/:/root/src/ iia86/env_build_mango:v2 ./scripts/mango-info.sh
