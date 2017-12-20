/* Functions needed for newlib
 *
 * Just enough to get printf and friends working
 */

#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "usart.h"

extern unsigned int _heap_bottom;
extern unsigned int _heap_top;

void* _sbrk(int incr)
{
    static void *heap_end;
    void *prev_heap_end;

    if (heap_end == 0) 
    {
        heap_end = &_heap_bottom;
    }

    prev_heap_end = heap_end;
    if (heap_end + incr > (void*)&_heap_top)
    {
        return 0;
    }

    heap_end += incr;
    return (void*)prev_heap_end;
}

int _write(int file, char *ptr, int len)
{
    (void)&file;
    int num_written = 0;
    while(len > 0)
    {
        __io_putchar(*ptr++);
        len--;
        num_written++;
    }

    return num_written;
}

int _close(int file)
{
    (void)&file;
    return -1;
}

int _fstat(int file, struct stat *st)
{
    (void)&file;
    (void)st;
    return 0;
}

int _isatty(int file)
{
    (void)&file;
    return 1;
}

int _lseek(int file, int ptr, int dir)
{
    (void)&file;
    (void)&ptr;
    (void)&dir;
    return 0;
}

int _read(int file, char *ptr, int len)
{
    int bytes_read = 0;
    /* Disable the UART interrupt */
    CLEAR_BIT(USART3->CR1, USART_CR1_RXNEIE);
    
    /* Handle the case where we are reading fewer bytes than we have received */
    if(rx_counter > len)
    {
        bytes_read = len;
        memcpy(ptr, rx_buffer, len);

        for(int i = len; i < rx_counter; i++)
        {
            rx_buffer[i - len] = rx_buffer[i];
        }

        rx_counter -= len;
    }
    /* We are reading all of the bytes in the Rx_Buffer */
    else
    {
        bytes_read = rx_counter;
        memcpy(ptr, rx_buffer, rx_counter);
        rx_counter = 0;
    }

    /* Enable the UART interrupt */
    SET_BIT(USART3->CR1, USART_CR1_RXNEIE);
    (void)&file;
    return bytes_read;
}
