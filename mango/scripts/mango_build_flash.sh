#!/usr/bin/env bash

# Must be executed from the Mango source root.

docker run \
--rm \
--tty \
--interactive \
--user mango \
--device /dev/spidev0.1:/dev/spidev0.1 \
--volume /dev:/dev \
--volume /sys:/sys \
--volume $(pwd)/src:/home/mango/src/ \
--volume $(pwd)/docker/scripts:/home/mango/scripts \
$(cat ./docker/docker_image) \
./scripts/mango_build_flash.sh

if [ $? -ne 0 ]
then
    echo -e "\nMaybe not executed from the Mango source root?\n"
else
    echo -e "\n[BUILD FLASH: OK]\n"
fi
