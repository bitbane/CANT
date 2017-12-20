#ifndef CAN_H
#define CAN_H

#include "stm32h7xx.h"
#include <stdint.h>

void can_init(void);
void can_poll(void);
void can_sync(void);
void can_timer_stop();
void setCanBaudrate(long int baud);

#endif /* TIMER_H */

