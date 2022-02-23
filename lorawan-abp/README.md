LoRaWAN
=======

Description
-----------

This application shows a simple use case of LoRaWAN with RIOT.

This application is using the Activation By Personalisation (ABP) procedure.

It also supports the RIOT shell (just type `help` after connecting to serial).

Usage
-----

Simply build and flash the application for a Pulga X Core V1.0 board:

    make flash term

To join a LoRaWAN network using ABP, use `make menuconfig`
inside the application and edit the configuration or edit the application
`Makefile` :

    DEVEUI ?= 0000000000000000
    APPEUI ?= 0000000000000000
    DEVADDR ?= 00000000
    APPSKEY ?= 00000000000000000000000000000000
    NWKSKEY ?= 00000000000000000000000000000000

