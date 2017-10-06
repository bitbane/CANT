CC=arm-none-eabi-gcc
CFLAGS=-Wall -Wextra -std=c99 -fno-common -Ofast -mthumb -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DUSE_STDPERIPH_DRIVER
CFLAGS+=-Isrc -Isrc/CMSIS/Include -Isrc/STM32F4xx -Isrc/STM32F4xx_StdPeriph_Driver/inc -Isrc/STM32F4xx_mic
LD=arm-none-eabi-gcc
LDFLAGS=-TCANT.ld -nostartfiles -Wl,-Map=build/flash.map
AS=arm-none-eabi-as
ASFLAGS=-g

ODIR=build
LDIR=lib
SRCS=src

PERIPH_ODIR=STM32F4xx_StdPeriph_Driver

_OBJS=startup_stm32f40_41xxx.o main.o system_stm32f4xx.o stm32f4xx_it.o serial.o bsp.o menu.o timer.o can.o
_PERIPH_OBJS=stm32f4xx_gpio.o stm32f4xx_rcc.o misc.o stm32f4xx_usart.o stm32f4xx_rng.o stm32f4xx_tim.o stm32f4xx_exti.o stm32f4xx_syscfg.o

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

$(ODIR)/startup_stm32f40_41xxx.o: $(SRCS)/STM32F4xx/startup_stm32f40_41xxx.s
	$(AS) src/STM32F4xx/startup_stm32f40_41xxx.s -o $@ $(ASFLAGS)

$(ODIR)/%.o: $(SRCS)/%.c
	$(CC) -c -o $@ $< $(CFLAGS)

$(ODIR)/$(PERIPH_ODIR)/%.o: $(SRCS)/$(PERIPH_ODIR)/src/%.c
	$(CC) -c -o $@ $< $(CFLAGS)

CANT: $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) $(CFLAGS) -o $(ODIR)/CANT.elf

.PHONY: clean

clean:
	rm -f $(ODIR)/CANT.* $(ODIR)/*.o $(ODIR)/STM32F4xx/*.o $(ODIR)/STM32F4xx_StdPeriph_Driver/*.o *~ core $(INCDIR)/*~ firmware/*

