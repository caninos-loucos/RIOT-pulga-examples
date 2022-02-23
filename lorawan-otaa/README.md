LoRaWAN
=======

**Note**: this example is not fully working yet.

Description
-----------

This application shows a simple use case of LoRaWAN with RIOT.

By using the real time clock and low-power capabilities of a board, this
application shows how to program a LoRaWAN Class A device using RIOT.

This application is using the Over-The-Air Activation procedure.

Usage
-----

Simply build and flash the application for a Pulga X Core V1.0 board:

    make flash term

To join a LoRaWAN network using OTAA activation, use `make menuconfig`
inside the application and edit the configuration or edit the application
`Makefile` :

    DEVEUI ?= 0000000000000000
    APPEUI ?= 0000000000000000
    APPKEY ?= 00000000000000000000000000000000

