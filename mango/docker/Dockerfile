FROM arm32v7/ubuntu:18.04

MAINTAINER Ishraq Ibne Ashraf 'ishraq.i.ashraf@gmail.com'

RUN apt update -y
RUN apt upgrade -y
RUN apt install make avr-libc gcc-avr -y

ADD ./avrdude /root/
ADD ./avrdude.conf /root/etc/

WORKDIR /root/src/
