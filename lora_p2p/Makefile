APPLICATION ?= lora_p2p
BOARD ?= pulga
PORT ?= /dev/ttyUSB0
RIOTBASE ?= $(CURDIR)/../../RIOT-pulga/

ifeq (1,$(IS_SENDER))
CFLAGS += -DIS_SENDER=1
endif

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
