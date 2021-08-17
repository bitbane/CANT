*NOTE: This is the new reCANT multipurpose CAN tool that supports 2 CAN-FD buses and firmware for multiple different
operational modes. The old version that consists of a shield for the Nucleo-H743ZI[2] dev board and firmware for
that board can be found in the old/ directory.*

The CANT project is designed to allow people to screw around with CAN easily at layers 1/2.
All of the stuff that is normally handled by a CAN controller that is baked into sillicon is up for grabs.

The reCANT hardware is a multipurpose CAN bus tool that is capable of operating in several different
modes. Modes are selected by moving the jumper on the board to the position corresponding to the desired 
operational mode. The following modes are supported:

| Number | Mode | Status |
|--------|------|--------|
| 1 | [CanCat](https://github.com/atlas0fd00m/CanCat) | Incomplete |
| 2 | CANT | Incomplete|
| 3 | SocketCAN (based on [Candlelight](https://github.com/candle-usb/candleLight_fw)) | Incomplete |
| 4 | [TruckDevil](https://github.com/LittleBlondeDevil/TruckDevil) | Incomplete |
| 5 | TBD | |
| 6 | TBD | |
| 7 | TBD | |
| 8 | TBD | |


## reCANT Hardware Description


### Flashing Software


### LEDs


## Demos

Demo videos from my talks (Original CANT board)

[![Link to 1st demo video](https://img.youtube.com/vi/g2gCfG9jTLs/0.jpg)](https://www.youtube.com/watch?v=g2gCfG9jTLs)

[![Link to 2nd demo video](https://img.youtube.com/vi/wz1S7ofVuNg/0.jpg)](https://www.youtube.com/watch?v=wz1S7ofVuNg)

Original Shmoocon Talk: 

[![Shmoocon Talk](https://img.youtube.com/vi/oS-6xDc_pP4/0.jpg)](https://www.youtube.com/watch?v=oS-6xDc_pP4)

Defcon 26 CHV Talk: 

[![Defcon 26 CHV Talk](https://img.youtube.com/vi/TRn_Rz2JIYQ/0.jpg)](https://www.youtube.com/watch?v=TRn_Rz2JIYQ)

## Developing with CANT

NOTE: Some older versions of the arm-none-eabi-gcc toolchain generate invalid opcodes with the optimizations that CANT uses. Specifically, the 4.9.3 version that ships with Ubuntu 16.04 tries to generate ARM instructions and switch to ARM mode, which the Cortex-M7 part does not support. If CANT just isn't working and you are winding up in the hardfault handler, this is likely the issue. Upgrade to a newer compiler version to fix this issue. The 7 series and newer seem to all work fine.

To start developing on CANT, all you need is an arm-none-eabi toolcahin installed and in your path.

## Assembly

For PCB design, the impedance of the USB traces is correct for FR4 board with a 0.2mm separation from the traces on the top copper plane and the ground plane on the second layer. The trace spacing is 5mil. If your PCB manufacturer has different buildpup the USB traces will need to be modified to maintain the proper impedence. 

|Ref | Qnty | Value | Description | 
|----|------|-------|-------------|
|C1, C15, C26, C27  | 4 | 1uF | C_0805 | 
|C2, C6, C7, C8, C9, C10, C12, C13, C14, C16, C17, C18, C19, C20, C21, C25, C28, C29  | 18 | 100nF | C_0805 | 
|C3  | 1 | 10uF | C_0805 | 
|C4, C5, C22, C23  | 4 | 2.2uF | C_0805 | 
|C11, C24  | 2 | 4.7uF | C_0805 | 
|D1, D3  | 2 | LED-RED | LED_0805 | 
|D2  | 1 | LED-GREEN | LED_0805 | 
|F1  | 1 | Polyfuse 6v 1A | C_0805 | 
|J1  | 1 | USB_C_Receptacle_USB2.0 | USB C Receptacle P/N GCT_USB4085 | 
|J2  | 1 | 2x8 Pin Terminal for mode selection | 2.54mm pitch 2x8 Pin Header | 
|J3  | 1 | Screw_Terminal_01x04 | 1x4 3.50mm pitch screw terminal | 
|J4  | 1 | Screw_Terminal_01x02 | 1x2 3.50mm pitch screw terminal | 
|JP1, JP2, JP3  | 3 | Jumpers | 2.54mm pitch 1x3 Pin Header | 
|P1  | 1 | SWD Connector | 2.54mm pitch 1x5 Pin Header | 
|R1, R2  | 2 | 5.1K\Omega | R_0805 | 
|R3, R4, R5  | 3 | 68\Omega | R_0805 | 
|R6  | 1 | 100K\Omega | R_0805 | 
|R7  | 1 | 10k\Omega | R_0805 | 
|R8, R9  | 2 | 120\Omega | R_0805 | 
|R10, R11, R12, R13  | 4 | 4.7K\Omega | R_0805 | 
|R14, R15  | 2 | 47\Omega | R_0805 | 
|R16  | 1 | 20K\Omega | R_0805 | 
|R17  | 1 | 8.06K\Omega | R_0805 | 
|SW1  | 1 | SW_SPST | Push Button Switch SMD:SW_SPST_PTS645 | 
|U1  | 1 | USB3343 | Package_DFN_QFN:QFN-24-1EP_4x4mm_P0.5mm_EP2.6x2.6mm | 
|U2  | 1 | LD1117S33TR | Package_TO_SOT_SMD:SOT-223 | 
|U3  | 1 | STM32H733VGTx | Package_QFP:LQFP-100_14x14mm_P0.5mm | 
|U4, U5,   | 2 | MCP2558FD-xSN | Package_SO:SOIC-8_3.9x4.9mm_P1.27mm | 
|U6, U7  | 2 | 74LVC1G66 | Package_TO_SOT_SMD:SOT-353_SC-70-5_Handsoldering | 
|U8  | 1 | SN74LVC1G14DBV | Package_TO_SOT_SMD:SOT-23-5 | 
|U9  | 1 | ST485EBDR | Package_SO:SOIC-8_3.9x4.9mm_P1.27mm | 
|U10  | 1 | DSC1001 | DSC1001:Oscillator_SMD_Microchip_DSC1001-4Pin_2.5x2.0mm | 1.7-3.3V SMD Ultra Miniature Crystal Clock Oscillator |
