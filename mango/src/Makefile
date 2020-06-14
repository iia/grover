APPLICATION = mango

BOARD ?= grovepi-v3

RIOTBASE ?= $(CURDIR)/../RIOT

FEATURES_REQUIRED += periph_i2c

# Comment this out to disable code in RIOT that does
# safety checking which is not needed in a production
# environment but helps in the development process.
DEVELHELP ?= 1

# Change this to 0 show compiler invocation lines by default.
QUIET ?= 0

INCLUDES += -I$(CURDIR)/include

include $(RIOTBASE)/Makefile.include
