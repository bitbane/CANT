#ifndef CAN_H
#define CAN_H

#include "stm32h7xx.h"
#include <stdint.h>

extern volatile uint32_t attack_arbid;

void can_init(void);
void can_poll(void);
void can_sync(void);
void can_timer_stop();
void setCanBaudrate(long int baud);

/* Attacks */
void remove_attack();
void install_arbid_killer();
void install_data_replacer();
void install_overload_frame();
void install_bus_short();
void install_nack_attack();

#endif /* TIMER_H */

