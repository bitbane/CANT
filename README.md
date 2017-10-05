The CANT project is designed to allow people to screw around with CAN easily at layers 1/2. All of the stuff that is normally handled by a CAN controller that is baked into sillicon is up for grabs.

CANT is designed to run on a Kinetis FRDM-KL43z development board. This board was chosen due to the FlexIO peripheral which is used to drive the CAN tansceiver. 

## Getting started with the Kinetis FRDM-KL43z development board

[User's guide](https://www.nxp.com/docs/en/user-guide/FRDMKL43ZUG.pdf)

First thing you'll want to do on the FRDM-KL43z dev board is load the DAPLink OpenSDA application. This allows you to connect to the dev board and flash it using OpenOCD and gdb. You can download the DAPLink application [here](https://www.nxp.com/products/microcontrollers-and-processors/arm-based-processors-and-mcus/kinetis-cortex-m-mcus/developer-resources/ides-for-kinetis-mcus/opensda-serial-and-debug-adapter:OPENSDA?&tid=vanOpenSDA#FRDM-KL43Z). Current rev is 0242. Flash the new OpenSDA application following the directions in the [Quick Start Guide](https://www.nxp.com/docs/en/user-guide/FRDM-KL43Z_QSG.pdf) to enter OpenSDA Bootloader mode and drag and drop the DAPLink application into the bootloader drive that shows up on your computer.

### Flashing the default application

Connect to the dev board using OpenOCD. From the top of the CANT repository, type:

```
openocd -f frdm-kl46z.cfg
```

Open a new terminal window and change directory to the firmware/ folder, then type

```
arm-none-eabi-gdb CANT.elf
```

Once gdb has loaded, connect to the remote target and load the application as follows:

```
target remote localhost:3333
load
```

