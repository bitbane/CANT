CC=arm-none-eabi-gcc
override CFLAGS+=-Wall -Wextra -std=c99 -fno-common -Os -mthumb -mabi=aapcs -mcpu=cortex-m7 -mfloat-abi=hard -DCPU_MIMXRT1062DVJ6A -DXIP_EXTERNAL_FLASH=1 -DXIP_BOOT_HEADER_ENABLE=1 -DCFG_TUSB_MCU=OPT_MCU_MIMXRT -D__ARMVFP__=0 -D__ARMFPV5__=0 -g -Iboard -Isource -Isource/MIMXRT1062DVJ6A -Wno-unused-parameter -fdata-sections -ffunction-sections -fsingle-precision-constant -fno-strict-aliasing
LD=arm-none-eabi-gcc
LDFLAGS=-Wl,-T,reCANT.ld -Wl,-Map=build/flash.map -Wl,--defsym,__stack_size__=0x800 -Wl,-cref -Wl,-gc-sections -Wl,--start-group -lgcc -lm -lnosys -lc -Wl,--end-group -mcpu=cortex-m7 -mthumb -mfpu=fpv5-d16 --specs=nosys.specs --specs=nano.specs
AS=arm-none-eabi-gcc
ASFLAGS=-c

ODIR=build
PERIPH_ODIR=MIMXRT1062DVJ6A

SRCS=source
GEN_SRCS=source/generated
BOARD_SRCS=board

_OBJS=startup_MIMXRT1062.o clock_config.o dcd.o peripherals.o pin_mux.o main.o board.o
_PERIPH_OBJS=fsl_common.o system_MIMXRT1062.o fsl_common_arm.o fsl_clock.o fsl_os_abstraction_bm.o fsl_flexcan.o fsl_gpio.o fsl_lpuart.o fsl_adapter_lpuart.o teensy41_flexspi_nor_config.o fsl_flexspi_nor_boot.o

PERIPH_OBJS = $(patsubst %,$(PERIPH_ODIR)/%,$(_PERIPH_OBJS))
_OBJS += $(PERIPH_OBJS)
_OBJS += $(_GEN_OBJS)
_OBJS += $(_BOARD_OBJS)
OBJS = $(patsubst %,$(ODIR)/%,$(_OBJS))

all: reCANT

$(ODIR)/startup_MIMXRT1062.o: $(SRCS)/startup_MIMXRT1062.S
	@mkdir -p $(@D)
	$(AS) $(SRCS)/startup_MIMXRT1062.S -o $@ $(ASFLAGS)

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
	arm-none-eabi-objcopy -Oihex $(ODIR)/reCANT.elf $(ODIR)/reCANT.hex
	cp $(ODIR)/reCANT.elf firmware/reCANT.elf
	cp $(ODIR)/reCANT.bin	firmware/reCANT.bin
	cp $(ODIR)/reCANT.hex	firmware/reCANT.hex

.PHONY: clean

clean:
	rm -f $(ODIR)/reCANT.* $(ODIR)/$(PERIPH_ODIR)/*.o $(ODIR)/*.o *~ core $(INCDIR)/*~ firmware/* $(ODIR)/flash.map

