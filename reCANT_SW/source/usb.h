#ifndef __USB_H__
#define __USB_H__

#define RX_BUFFER_SIZE 64
#define TX_BUFFER_SIZE 64
extern volatile uint8_t rx_buffer[RX_BUFFER_SIZE];
extern volatile uint8_t rx_counter;

void USB_Init();
void usb_serial_task();

int __io_putchar(int ch);
int __sfputc_r(int ch);
void write_string(char *s);
void write_int(uint32_t n);
long read_int();
long read_hex();
char read_char();
char read_char_nb();
int _write(int file, char *ptr, int len);


#endif

