CC=arm-none-eabi-gcc
CFLAGS=-Wall -Wextra -std=c99 -fno-common -Os -mthumb -mcpu=cortex-m7 -DSTM32H743xx -g
CFLAGS+=-Isrc -Isrc/STM32H7xx_Nucleo_144
LD=arm-none-eabi-gcc
LDFLAGS=-TCANT.ld -nostartfiles -Wl,-Map=build/flash.map -mcpu=cortex-m7 -mthumb
AS=arm-none-eabi-as
ASFLAGS=-g

ODIR=build
LDIR=lib
SRCS=src

PERIPH_ODIR=STM32H7xx_Nucleo_144

_OBJS=startup_stm32h743xx.o main.o system_stm32h7xx.o stm32h7xx_it.o gpio.o can.o menu.o usart.o bsp.o
_PERIPH_OBJS=stm32h7xx_hal_cortex.o stm32h7xx_hal.o stm32h7xx_hal_rcc.o stm32h7xx_hal_rcc_ex.o stm32h7xx_hal_gpio.o stm32h7xx_hal_uart_ex.o stm32h7xx_hal_uart.o stm32h7xx_hal_dma.o stm32h7xx_hal_tim.o stm32h7xx_hal_tim_ex.o stm32h7xx_nucleo_144.o

PERIPH_OBJS = $(patsubst %,$(PERIPH_ODIR)/%,$(_PERIPH_OBJS))
_OBJS += $(PERIPH_OBJS)
OBJS = $(patsubst %,$(ODIR)/%,$(_OBJS))

all: CANT

flash_prebuilt: firmware/CANT.elf
	scripts/flash_prebuilt.py

flash: CANT
	scripts/flash.py

debug:
	scripts/debug.py

flash_and_debug: CANT
	scripts/flash_and_debug.py

$(ODIR)/startup_stm32h743xx.o: $(SRCS)/startup_stm32h743xx.s
	@mkdir -p $(@D)
	$(AS) src/startup_stm32h743xx.s -o $@ $(ASFLAGS)

$(ODIR)/%.o: $(SRCS)/%.c
	@mkdir -p $(@D)
	$(CC) -c -o $@ $< $(CFLAGS)

$(ODIR)/$(PERIPH_ODIR)/%.o: $(SRCS)/$(PERIPH_ODIR)/src/%.c
	$(CC) -c -o $@ $< $(CFLAGS)

CANT: $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) $(CFLAGS) -o $(ODIR)/CANT.elf
	cp $(ODIR)/CANT.elf firmware/CANT.elf

.PHONY: clean

clean:
	rm -f $(ODIR)/CANT.* $(ODIR)/STM32H7xx_Nucleo_144/*.o $(ODIR)/*.o *~ core $(INCDIR)/*~ firmware/* $(ODIR)/flash.map

