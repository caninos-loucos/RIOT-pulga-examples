# name of your application
APPLICATION = lorawan

# Use the pulga board (nrf52840dk under the hood) by default:
BOARD ?= pulga

PORT ?= /dev/ttyUSB0

# This has to be the absolute path to the RIOT base directory:
RIOTBASE ?= $(CURDIR)/../../RIOT-pulga/

# device tags in ns.atc.everynet.io: RIOT, example
DEVEUI ?= 62e2525867f553e3
APPEUI ?= 2dbba4e2dfa4613d
APPKEY ?= 90c7575d5b011772167e86e3a3850664

# Default radio driver is Semtech SX1276 (used by the B-L072Z-LRWAN1 board)
DRIVER ?= sx1272

# Default region is Europe and default band is 868MHz
LORA_REGION ?= AU915

# Include the Semtech-loramac package
USEPKG += semtech-loramac

USEMODULE += $(DRIVER)
USEMODULE += fmt
FEATURES_OPTIONAL += periph_rtc

# add shell
#USEMODULE += shell
#USEMODULE += shell_commands
#USEMODULE += ps
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
  CFLAGS += -DCONFIG_LORAMAC_APP_KEY_DEFAULT=\"$(APPKEY)\"
  CFLAGS += -DCONFIG_LORAMAC_APP_EUI_DEFAULT=\"$(APPEUI)\"
  CFLAGS += -DCONFIG_LORAMAC_DEV_EUI_DEFAULT=\"$(DEVEUI)\"

  #CFLAGS += -DCONFIG_LORAMAC_DEFAULT_TX_MODE_UNCNF=1
  #CFLAGS += -DCONFIG_LORAMAC_DEFAULT_SYSTEM_MAX_RX_ERROR=100
endif
