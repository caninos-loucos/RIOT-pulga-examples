# name of your application
APPLICATION = lorawan

# Use the pulga board (nrf52840dk under the hood) by default:
BOARD ?= pulga

# default serial port
PORT ?= /dev/ttyUSB0

# This has to be the absolute path to the RIOT base directory:
RIOTBASE ?= $(CURDIR)/../../RIOT-pulga/

DEVEUI ?= 282278c29f8615c5
APPEUI ?= 35bd6c8390356a66

DEVADDR ?= fdd4b1ea
NWKSKEY ?= 4036368cc6bc52dd69720689d4017980
APPSKEY ?= b251033dfc052a6e9382b83c4e2e2f2e

# Default radio driver is Semtech SX1276 (used by the B-L072Z-LRWAN1 board)
DRIVER ?= sx1272

# Default region is Europe and default band is 868MHz
LORA_REGION ?= AU915

# Include the Semtech-loramac package
USEPKG += semtech-loramac

USEMODULE += $(DRIVER)
USEMODULE += fmt

# add shell
USEMODULE += shell
USEMODULE += shell_commands
USEMODULE += ps
# include and auto-initialize all available sensors
#USEMODULE += saul_default

# Comment this out to disable code in RIOT that does safety checking
# which is not needed in a production environment but helps in the
# development process:
DEVELHELP ?= 1

# Change this to 0 show compiler invocation lines by default:
QUIET ?= 1

include $(RIOTBASE)/Makefile.include

ifndef CONFIG_KCONFIG_USEMODULE_LORAWAN
  # OTAA compile time configuration keys
  CFLAGS += -DCONFIG_LORAMAC_APP_EUI_DEFAULT=\"$(APPEUI)\"
  CFLAGS += -DCONFIG_LORAMAC_DEV_EUI_DEFAULT=\"$(DEVEUI)\"

  # ABP compile time configuration keys
  CFLAGS += -DCONFIG_LORAMAC_DEV_ADDR_DEFAULT=\"$(DEVADDR)\"
  CFLAGS += -DCONFIG_LORAMAC_NWK_SKEY_DEFAULT=\"$(NWKSKEY)\"
  CFLAGS += -DCONFIG_LORAMAC_APP_SKEY_DEFAULT=\"$(APPSKEY)\"

  CFLAGS += -DCONFIG_LORAMAC_DEFAULT_TX_MODE_UNCNF=1
  #CFLAGS += -DCONFIG_LORAMAC_DEFAULT_SYSTEM_MAX_RX_ERROR=100
endif

