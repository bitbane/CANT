#include "stm32h7xx.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include "usart.h"
#include "menu.h"
#include "can.h"

char* Menu_Commands_Text[MENU_NUM_ITEMS] = {
    "", // strtol interprets the empty string as a 0
    "Set ARBID",
    "Show ARBIDS",
    "Set buadrate",
    "Choose Attack",
};

char command[RX_BUFFER_SIZE + 1];
static uint8_t command_len = 0;
static void handle_command();
static void setArbids();
static void showArbids();
static void setBaudrate();
static void chooseAttack();

void display_menu()
{
    write_string("? - Help\r\n");
    for(int i = 1; i < MENU_NUM_ITEMS; i++)
    {
        printf("%d - %s\r\n", i, Menu_Commands_Text[i]);
    }
    write_string("\r\nCANT>");
}

void process_menu()
{
    uint8_t read_len = read(0, &command[command_len], RX_BUFFER_SIZE - command_len);
    command_len += read_len;

    /* Wait to receive entire command */
    if((command_len > 0) && (command[command_len-1] == '\r'))
    {
        command[command_len] = '\0';
        if(command[0] == '?')
            display_menu();
        else
            handle_command();
        command_len = 0;
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
        case MENU_UNUSED:
            break;
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
            write_string("No such command\r\n");
            break;
        
    }
    write_string("CANT>");
}

/**
 * Sets the arbids to act on
 */
static void setArbids(void)
{
    uint8_t read_len = 0;
    uint8_t cmd_len = 0;

    write_string("Enter arbid: 0x");
    while(cmd_len == 0 || command[cmd_len - 1] != '\r')
    {
        read_len = read(0, &command[cmd_len], RX_BUFFER_SIZE - cmd_len);
        cmd_len += read_len;

        /* Prevent overflow */
        if(cmd_len >= RX_BUFFER_SIZE)
            cmd_len = 0;
    }

    attack_arbid = strtol(command, NULL, 16);
    printf("Attacking 0x%lx\r\n", attack_arbid);
}

/**
 * Shows the arbids to act on
 */
static void showArbids(void)
{
    printf("Currently attacking 0x%lx\r\n", attack_arbid);
}

/**
 * Sets the CAN baud rate
 */
static void setBaudrate(void)
{
    uint8_t read_len = 0;
    uint8_t cmd_len = 0;
    long int baud;

    write_string("Enter baudrate in BPS: ");
    while(cmd_len == 0 || command[cmd_len - 1] != '\r')
    {
        read_len = read(0, &command[cmd_len], RX_BUFFER_SIZE - cmd_len);
        cmd_len += read_len;

        /* Prevent overflow */
        if(cmd_len >= RX_BUFFER_SIZE)
            cmd_len = 0;
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

