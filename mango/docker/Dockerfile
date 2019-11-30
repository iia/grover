FROM arm32v5/debian:buster

MAINTAINER Ishraq Ibne Ashraf 'ishraq.i.ashraf@gmail.com'

# Prepapre.
USER root

# Install dependencies.
RUN apt update -y
RUN apt upgrade -y
RUN apt install \
    make \
    flex \
    bison \
    libelf1 \
    libzip4 \
    gcc-avr \
    avr-libc \
    libftdi1 \
    libudev1 \
    libftdi1-2 \
    libelf-dev \
    libusb-dev \
    libftdi-dev \
    libftdi1-dev \
    libusb-0.1-4 \
    libusb-1.0-0 \
    build-essential \
    libusb-1.0-0-dev -y

# Add local directories to the image.
ADD ./usr/ /usr/

# Set default PWD.
WORKDIR /root/src/
