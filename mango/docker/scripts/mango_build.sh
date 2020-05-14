#!/usr/bin/env bash

# Must be executed from /home/mango directory in the Docker container.

# Copy board support to RIOT source tree.
cp -ar ./src/RIOT ./

# Build.
make -C ./src clean
make -C ./src
