#!/usr/bin/env bash

# Must be executed from /home/mango directory in the Docker container.

# Copy board support to RIOT source tree.
cp -ar ./src/RIOT ./

# Clean
make -C ./src clean

# Build and flash.
make -C ./src flash

# Reset board.
scripts/mango_reset.sh
