The CANT project is designed to allow people to screw around with CAN easily at layers 1/2. All of the stuff that is normally handled by a CAN controller that is baked into sillicon is up for grabs.

CANT is designed to run on a STM32F4-Discovery development board. This board was chosen due to the ARM Cortex-M4s popularity and because I was already familiar with it.

## Getting started with the STM32F4-Discovery development board

The STM32F4-Discovery board has an STLink V2 debugger built in, available via the Mini-USB port. STLink V2 does not provide a serial port for communication, so currently you will need to connect a TTL serial adapter (e.g, FTDI232, CP2102) to pins PA0 (TX) and PA1 (RX) to communicate with the CANT software. Baud rate is 115200 kbps, 8N1. The USB OTG port can be programmed to provide a serial console and we will be switching to that when time permits to eliminate the extra piece of hardware.

For CAN communication, PD0 is CAN RX and PD1 is CAN TX. Conveniently the CAN peripheral can also be multiplexed to these pins, so switching from normal CAN operation to CANT operation would be possible without rewiring. This is currently not implemented. I'm using the [TI SN65HVD232](http://www.ti.com/product/sn65hvd232?qgpn=sn65hvd232) 3.3V CAN transceiver, but any 3.3V CAN Transceiver should work. Some transceivers may require some additional programming or wiring, so check that if you go with something else.

### Flashing pre-built CANT

You will need openocd installed to flash the prebuilt CANT. Connect a Mini-USB cable to the discovery board and type:

```
make flash_prebuilt
```

## Developing with CANT

To start developing on CANT, all you need is an arm-none-eabi toolcahin installed and in your path.

