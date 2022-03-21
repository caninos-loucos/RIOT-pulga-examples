## About
Test the sx1272 driver to send / receive p2p lora messages.

## Usage

This test application provides low level shell commands to interact with the
SX1272/SX1276 modules.

Once the board is flashed and you are connected via serial to the shell, use the `help`
command to display the available commands:
```
> help
help
Command              Description
---------------------------------------
setup                Initialize LoRa modulation settings
random               Get random number from sx127x
channel              Get/Set channel frequency (in Hz)
register             Get/Set value(s) of registers of sx127x
send                 Send raw payload string
listen               Start raw payload listener
reboot               Reboot the node
ps                   Prints information about running threads.
```

Once the board is booted, use `setup` to configure the basic LoRa settings:
* Bandwidth: 125kHz, 250kHz or 500kHz
* Spreading factor: between 7 and 12
* Code rate: between 5 and 8

Example:
```
> setup 125 12 5
setup: setting 125KHz bandwidth
[Info] setup: configuration set with success
```

All values are supported by both SX1272 and SX1276.

The `random ` command use the Semtech to generate a random integer value.

Example:
```
> random
random: number from sx127x: 2339536315
> random
random: number from sx127x: 863363442
```

The `channel` command allows to change/query the RF frequency channel.
The default is 868MHz for Europe, change to 915MHz for America. The frequency
is given/returned in Hz.

Example:
```
> channel set 868000000
New channel set
> channel get
Channel: 868000000
```

Use the `send` and `receive` commands in order to exchange messages between several modules.
You need first to ensure that all modules are configured the same: use `setup` and
`channel` commands to configure them correctly.

Assuming you have 2 modules, one listening and one sending messages, do the following:
* On listening module:
```
> setup 125 12 5
setup: setting 125KHz bandwidth
[Info] setup: configuration set with success
> channel set 868000000
New channel set
> listen
Listen mode set
```
* On sending module:
```
> setup 125 12 5
setup: setting 125KHz bandwidth
[Info] setup: configuration set with success
> channel set 868000000
New channel set
> send This\ is\ RIOT!
```

On the listening module, the message is captured:
```
{Payload: "This is RIOT!" (13 bytes), RSSI: 103, SNR: 240}
```
