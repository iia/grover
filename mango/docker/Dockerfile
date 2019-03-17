FROM arm32v7/ubuntu:18.04

MAINTAINER Ishraq Ibne Ashraf 'ishraq.i.ashraf@gmail.com'

# Prepapre.
USER root

# Install dependencies.
RUN apt update -y
RUN apt upgrade -y
RUN apt install \
    build-essential \
    libzip4 \
    libusb-0.1-4 \
    libusb-1.0-0 \
    libftdi1 \
    libelf1 \
    libudev1 \
    make \
    avr-libc \
    gcc-avr -y

# Add local directories to the image.
ADD ./usr/ /usr/
ADD ./etc/ /etc/

# Set default PWD.
WORKDIR /root/src/
