The CANT project is designed to allow people to screw around with CAN easily at layers 1/2.
All of the stuff that is normally handled by a CAN controller that is baked into sillicon is up for grabs.

CANT is designed to run on an ST Micro [Nucleo-H743ZI](http://www.st.com/en/evaluation-tools/nucleo-h743zi.html) 
development board. This board was chosen due to its speed (400MHz) and essentially infinite ram and flash.

## Getting started with the Nucleo-STM32H7 development board

The Nucleo-H743ZI board has an STLink V2.1 debugger built in, available via the Micro-USB port on the 
opposite side of the board from the RJ-45 jack. This port provides the serial port for communication, 
as well as the debugging interface. The serial port has a baud rate of 115200 kbps, 8N1. 

For CAN communication, PB12 is CAN RX and PB13 is CAN TX. Conveniently the CAN2 peripheral can also be 
multiplexed to these pins, so switching from normal CAN operation to CANT operation would be 
possible without rewiring. This is currently not implemented. I'm using the 
[TI SN65HVD232](http://www.ti.com/product/sn65hvd232?qgpn=sn65hvd232) 3.3V CAN transceiver, 
but any 3.3V CAN Transceiver should work. Some transceivers may require some additional 
programming or wiring, so check that if you go with something else.

Additionally, GPIO pins PA4, PA5 and PA15 are configured as GPIO outputs. I find banging on these
useful during debugging. These pins, along with the two pins for the CAN peripheral, are all located
on connector CN7, on the upper-right of the dev board if the RJ-45 connector is pointed towards you.
STs documentation contains the schematics for this board, but connector CN7 is reproduced here for
convenience:

| PIN |     |     | PIN |
|:---:|:---:|:---:|:---:|
| PC6 | 1   | 2   | PB8 |
| PB15| 3   | 4   | PB9 |
| PB13| 5   | 6   | AVDD|
| PB12| 7   | 8   | GND |
| PA15| 9   | 10  | PA5 |
| PC7 | 11  | 12  | PA6 |
| PB5 | 13  | 14  |     |
| PB3 | 15  | 16  | PD14|
| PA4 | 17  | 18  | PD15|
| PB4 | 19  | 20  | PF12|

### Flashing pre-built CANT

You will need openocd installed to flash the prebuilt CANT. At the time of this writing the latest version
of openocd (0.10.0) does not support the H743ZI, but it is supported in the openocd git repository.
Presumably support will be added in the next release of openocd. In order to flash the prebuilt CANT, type

```
make flash_prebuilt
```

## Developing with CANT

To start developing on CANT, all you need is an arm-none-eabi toolcahin installed and in your path.

