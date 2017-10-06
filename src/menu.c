#include "stm32f4xx.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include "serial.h"
#include "menu.h"
#include "timer.h"

char* Menu_Commands_Text[MENU_NUM_ITEMS] = {
    "Set ARBIDS",
    "Show ARBIDS",
    "Set buadrate",
    "Choose Attack",
};

char command[RXBUFFERSIZE + 1];
uint8_t command_len = 0;
static void handle_command();
static void setArbids();
static void showArbids();
static void setBaudrate();
static void chooseAttack();

void display_menu()
{
    for(int i = 0; i < MENU_NUM_ITEMS; i++)
    {
        printf("%d - %s\r\n", i, Menu_Commands_Text[i]);
    }
    printf("\r\n");
}

void process_menu()
{
    uint8_t read_len = read(0, &command[command_len], RXBUFFERSIZE - command_len);
    command_len += read_len;

    /* Wait to receive entire command */
    if((command_len > 0) && (command[command_len-1] == '\r'))
    {
        command[command_len] = '\0';
        printf("Command: %s\r\n", command);
        display_menu();

        handle_command();

        command_len = 0;
    }

    /* Prevent overflow */
    if(command_len >= RXBUFFERSIZE)
        command_len = 0;
}

static void handle_command()
{
    char *endptr;
    long int command_num = strtol(command, &endptr, 0);
    timer_stopInterval();

    switch(command_num)
    {
        case MENU_SET_ARBID:
            setArbids();
            break;
        case MENU_SHOW_ARBID:
            showArbids();
            break;
        case MENU_SET_BAUD:
            setBaudrate();
            break;
        case MENU_CHOOSE_ATTACK:
            chooseAttack();
            break;
        default:
            printf("No such command\r\n");
            break;
        
    }
}

/**
 * Sets the arbids to act on
 */
static void setArbids(void)
{
    printf("Unimplemented");
}

/**
 * Shows the arbids to act on
 */
static void showArbids(void)
{
    printf("Unimplemented");
}

/**
 * Shows the arbids to act on
 */
static void setBaudrate(void)
{
    printf("Unimplemented");
}

/**
 * Choose the attack to run
 */
static void chooseAttack(void)
{
    printf("Unimplemented");
}

