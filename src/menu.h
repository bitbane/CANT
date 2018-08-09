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
    MENU_STOP_ATTACK,
    MENU_NUM_ITEMS,
} Menu_Commands_T;

typedef enum
{
    ATTACK_UNUSED = 0, // strtol interprets an empty string as a 0
    ATTACK_BUS_KILLER,
    ATTACK_DATA_REPLACER,
    ATTACK_OVERLOAD_FRAMES,
    ATTACK_BUS_SHORT,
    ATTACK_NACK,
    ATTACK_NUM_ITEMS,
} Attack_Commands_T;


 
#endif /* MENU_H */


