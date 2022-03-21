APPLICATION ?= lora_p2p
BOARD ?= pulga
PORT ?= /dev/ttyUSB0
RIOTBASE ?= $(CURDIR)/../../RIOT-pulga/

USEMODULE += od
USEMODULE += shell
USEMODULE += shell_commands
USEMODULE += ps
USEMODULE += ztimer
USEMODULE += ztimer_sec

DRIVER ?= sx1272
CFLAGS += -DSX127X_USE_RX_SWITCH=1

USEMODULE += $(DRIVER)

include $(RIOTBASE)/Makefile.include
