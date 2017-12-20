#include "stm32h7xx.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include "usart.h"
#include "menu.h"
#include "can.h"

char* Menu_Commands_Text[MENU_NUM_ITEMS] = {
    "Set ARBIDS",
    "Show ARBIDS",
    "Set buadrate",
    "Choose Attack",
};

char command[RX_BUFFER_SIZE + 1];
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
    uint8_t read_len = read(0, &command[command_len], RX_BUFFER_SIZE - command_len);
    command_len += read_len;

    /* Wait to receive entire command */
    if((command_len > 0) && (command[command_len-1] == '\r'))
    {
        command[command_len] = '\0';
        printf("Command: %s\r\n", command);

        handle_command();

        command_len = 0;
        display_menu();
    }

    /* Prevent overflow */
    if(command_len >= RX_BUFFER_SIZE)
        command_len = 0;
}

static void handle_command()
{
    char *endptr;
    long int command_num = strtol(command, &endptr, 0);

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
    printf("Unimplemented\r\n");
}

/**
 * Shows the arbids to act on
 */
static void showArbids(void)
{
    printf("Unimplemented\r\n");
}

/**
 * Shows the arbids to act on
 */
static void setBaudrate(void)
{
    uint8_t read_len = 0;
    uint8_t command_len = 0;
    long int baud;

    printf("Enter baudrate in BPS\r\n");
    while(command_len == 0 || command[command_len - 1] != '\r')
    {
        read_len = read(0, &command[command_len], RX_BUFFER_SIZE - command_len);
        command_len += read_len;

        /* Prevent overflow */
        if(command_len >= RX_BUFFER_SIZE)
            command_len = 0;
    }

    baud = strtol(command, NULL, 0);
    setCanBaudrate(baud);
    printf("Baud rate: %ld BPS\r\n", baud);
    can_sync();
}

/**
 * Choose the attack to run
 */
static void chooseAttack(void)
{
    printf("Unimplemented\r\n");
}

