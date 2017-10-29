#ifndef SERIAL_H
#define SERIAL_H

#include "stm32f4xx.h"
#include <stdint.h>

#define RXBUFFERSIZE   0x20
extern uint8_t Rx_Buffer[RXBUFFERSIZE];
extern __IO uint16_t Rx_Counter;

void serial_init(void);
int __io_putchar(int ch);

#endif /* SERIAL_H */

