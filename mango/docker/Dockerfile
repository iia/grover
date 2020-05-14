FROM raspbian/stretch:latest

MAINTAINER Ishraq Ibne Ashraf 'ishraq.i.ashraf@gmail.com'

# Switch to the root user.
USER root

# Create a non-root user.
RUN useradd -ms /bin/bash mango

# Install dependencies.
RUN apt-get update -y
RUN apt-get upgrade -y
RUN apt-get install \
git \
unzip \
avrdude \
gcc-avr \
python3 \
avr-libc \
build-essential -y

# Copy custom files.
COPY ./etc/avrdude.conf /etc/avrdude.conf

# Switch to non-root user.
USER mango

# Get RIOT OS source.
WORKDIR /home/mango/
RUN git clone -b 2020.04-branch --depth=1 https://github.com/RIOT-OS/RIOT.git

# Set SUID of executables.
USER root

RUN chmod u+s /usr/bin/tee
RUN chmod u+s /usr/bin/avrdude

# Switch back to the normal user.
USER mango

# Set working directory.
WORKDIR /home/mango/
