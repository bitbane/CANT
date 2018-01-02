#ifndef MENU_H
#define MENU_H

#include "stm32h7xx.h"
#include <stdint.h>

void display_menu();
void process_menu();

typedef enum
{
    MENU_UNUSED = 0, // strtol interprets an empty string as a 0
    MENU_SET_ARBID,
    MENU_SHOW_ARBID,
    MENU_SET_BAUD,
    MENU_CHOOSE_ATTACK,
    MENU_NUM_ITEMS,
} Menu_Commands_T;


 
#endif /* MENU_H */


