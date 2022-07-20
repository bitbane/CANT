CC=arm-none-eabi-gcc
override CFLAGS+=-Wall -Wextra -std=c99 -fno-common -Os -mthumb -mcpu=cortex-m7 -DCPU_MIMXRT1062DVJ6A -g -Iboard -Isource -Isource/generated -Isource/MIMXRT1062DVJ6A
LD=arm-none-eabi-gcc
LDFLAGS=-TreCANT.ld -nostartfiles -Wl,-Map=build/flash.map -mcpu=cortex-m7 -mthumb --specs=nosys.specs
AS=arm-none-eabi-as
ASFLAGS=-g

ODIR=build
PERIPH_ODIR=MIMXRT1062DVJ6A

SRCS=source
GEN_SRCS=source/generated
BOARD_SRCS=board

_OBJS=usb_device_interface_0_cic_vcom.o usb_device_composite.o usb_device_descriptor.o clock_config.o dcd.o peripherals.o pin_mux.o
_PERIPH_OBJS=fsl_common.o system_MIMXRT1062.o fsl_common_arm.o fsl_clock.o fsl_os_abstraction_bm.o usb_device_class.o usb_device_cdc_acm.o usb_device_ch9.o usb_phy.o fsl_flexcan.o fsl_gpio.o fsl_lpuart.o usb_device_dci.o usb_device_ehci.o fsl_debug_console.o fsl_adapter_lpuart.o

PERIPH_OBJS = $(patsubst %,$(PERIPH_ODIR)/%,$(_PERIPH_OBJS))
_OBJS += $(PERIPH_OBJS)
_OBJS += $(_GEN_OBJS)
_OBJS += $(_BOARD_OBJS)
OBJS = $(patsubst %,$(ODIR)/%,$(_OBJS))

all: reCANT

$(ODIR)/%.o: $(SRCS)/%.c
	@mkdir -p $(@D)
	$(CC) -c -o $@ $< $(CFLAGS)

$(ODIR)/%.o: $(BOARD_SRCS)/%.c
	@mkdir -p $(@D)
	$(CC) -c -o $@ $< $(CFLAGS)

$(ODIR)/%.o: $(GEN_SRCS)/%.c
	@mkdir -p $(@D)
	$(CC) -c -o $@ $< $(CFLAGS)

$(ODIR)/$(PERIPH_ODIR)/%.o: $(SRCS)/$(PERIPH_ODIR)/src/%.c
	$(CC) -c -o $@ $< $(CFLAGS)

reCANT: $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) $(CFLAGS) -o $(ODIR)/reCANT.elf
	arm-none-eabi-objcopy -Obinary $(ODIR)/reCANT.elf $(ODIR)/reCANT.bin
	cp $(ODIR)/reCANT.elf firmware/reCANT.elf
	cp $(ODIR)/reCANT.bin	firmware/reCANT.bin

.PHONY: clean

clean:
	rm -f $(ODIR)/reCANT.* $(ODIR)/$(PERIPH_ODIR)/*.o $(ODIR)/*.o *~ core $(INCDIR)/*~ firmware/* $(ODIR)/flash.map

