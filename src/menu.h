#ifndef MENU_H
#define MENU_H

#include "stm32f4xx.h"
#include <stdint.h>

void display_menu();
void process_menu();

typedef enum
{
    MENU_SET_ARBID = 0,
    MENU_SHOW_ARBID,
    MENU_CHOOSE_ATTACK,
    MENU_SET_BAUD,
    MENU_NUM_ITEMS,
} Menu_Commands_T;

 
#endif /* MENU_H */


