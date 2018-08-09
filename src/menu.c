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
    "End Attack",
};

char* Attack_Commands_Text[ATTACK_NUM_ITEMS] = {
    "",
    "Bus Killer - constantly transmit arbid 0",
    "Data Replacer - replace the data sent with the configured arbid with the supplied data",
    "Overload Inserter - Send specified number of overload frames after each message",
    "Bus Short - Short CANH and CANL (aka \"Cyber-Paperclip Mode\")",
    "NACK Attack - kill the ACK response"
};

static void handle_command();
static void setArbids();
static void showArbids();
static void setBaudrate();
static void chooseAttack();

void display_menu()
{
    write_string("\r\n? - Help\r\n");
    for(int i = 1; i < MENU_NUM_ITEMS; i++)
    {
        printf("%d - %s\r\n", i, Menu_Commands_Text[i]);
    }
    write_string("\r\nCANT>");
}

void process_menu()
{
    /* Wait to receive entire command */
    if((rx_counter > 0) && (rx_buffer[rx_counter - 1] == '\r'))
    {
        rx_buffer[rx_counter - 1] = '\0';
        if(rx_buffer[0] == '?')
        {
            /* Disable the interrupt, reset the rx_counter */
            CLEAR_BIT(USART3->CR1, USART_CR1_RXNEIE);
            rx_counter = 0;
            SET_BIT(USART3->CR1, USART_CR1_RXNEIE);
            display_menu();
        }
        else
            handle_command();
    }
}

static void handle_command()
{
    char *endptr;
    long int command_num = strtol((char *)rx_buffer, &endptr, 0);

    /* Disable the interrupt, reset the rx_counter */
    CLEAR_BIT(USART3->CR1, USART_CR1_RXNEIE);
    rx_counter = 0;
    SET_BIT(USART3->CR1, USART_CR1_RXNEIE);

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
        case MENU_STOP_ATTACK:
            remove_attack();
            break;
        default:
            write_string("No such command\r\n");
            break;
        
    }
    write_string("\r\nCANT>");
}

/**
 * Sets the arbids to act on
 */
static void setArbids(void)
{
    write_string("Enter arbid: 0x");
    attack_arbid = read_hex();
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
    long int baud;

    write_string("Enter baudrate in BPS: ");
    baud = read_int();

    /* Start the CAN sync */
    setCanBaudrate(baud);
    printf("Baud rate: %ld BPS\r\n", baud);
    can_sync();
}

/**
 * Choose the attack to run
 */
static void chooseAttack(void)
{
    long int command_num;
    remove_attack();
    for(int i = 1; i < ATTACK_NUM_ITEMS; i++)
    {
        printf("%d - %s\r\n", i, Attack_Commands_Text[i]);
    }
    write_string("\r\nCANT ATTACK>");

    command_num = read_int();

    switch(command_num)
    {
        case ATTACK_UNUSED:
            break;
        case ATTACK_BUS_KILLER:
            install_arbid_killer();
            write_string("Installing bus killer\r\n");
            break;
        case ATTACK_DATA_REPLACER:
            install_data_replacer();
            write_string("Installing data replacer\r\n");
            break;
        case ATTACK_OVERLOAD_FRAMES:
            install_overload_frame();
            write_string("Installing the overload attack\r\n");
            break;
        case ATTACK_BUS_SHORT:
            install_bus_short();
            write_string("Installing the bus short attack\r\n");
            break;
        case ATTACK_NACK:
            install_nack_attack();
            write_string("Installing the NACK Attack\r\n");
            break;
        default:
            write_string("No such Attack\r\n");
            break;
    }
}


