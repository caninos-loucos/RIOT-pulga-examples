# name of your application
APPLICATION = nimble_gatt

# Use the pulga board (nrf52840dk under the hood) by default:
BOARD ?= pulga

# default serial port
PORT ?= /dev/ttyUSB0

# This has to be the absolute path to the RIOT base directory:
RIOTBASE ?= $(CURDIR)/../../RIOT-pulga/

# Include NimBLE
USEPKG += nimble
USEMODULE += nimble_svc_gap
USEMODULE += nimble_svc_gatt

# Use automated advertising
USEMODULE += nimble_autoadv
CFLAGS += -DNIMBLE_AUTOADV_DEVICE_NAME='"NimBLE GATT Example"'
CFLAGS += -DNIMBLE_AUTOADV_START_MANUALLY=1

# Comment this out to disable code in RIOT that does safety checking
# which is not needed in a production environment but helps in the
# development process:
DEVELHELP ?= 1

# Change this to 0 show compiler invocation lines by default:
QUIET ?= 1

include $(RIOTBASE)/Makefile.include
