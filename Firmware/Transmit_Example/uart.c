#include <avr/io.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <stdarg.h>
#include "uart.h"

static FILE g_uart_stream = {0};

static int uart_getc( FILE* stream )
{
    while ( (UCSR0A & _BV(RXC0)) == 0 ); /* wait for a character to be received */
    return UDR0;
}


static int uart_putc( char c, FILE* stream )
{
    while ( (UCSR0A & _BV(UDRE0)) == 0 ); /* wait for the TX buffer to be ready */
    UDR0 = c; /* put char into TX buffer */
    return 0;
}

void uart_init( uint32_t baud )
{
    /* See table 20-1 for baud rate calculations */
    uint16_t ubrr = (F_CPU / (16*baud)) - 1;

    UBRR0H = (uint8_t)(ubrr >> 8);
    UBRR0L = (uint8_t)ubrr;

    /* Disable 2x TX speed */
    UCSR0A &= ~_BV(U2X0);

    /* Enable RX and TX */
    UCSR0B = _BV(RXEN0) | _BV(TXEN0);

    /* Set 8-N-1 frame */
    UCSR0C = (3 << UCSZ00);

    /* Setup stdio */
    fdev_setup_stream( &g_uart_stream, uart_putc, uart_getc, _FDEV_SETUP_RW );
    stdin  = &g_uart_stream;
    stdout = &g_uart_stream;
    stderr = &g_uart_stream;
}

int uart_println(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    fputs("\r\n", stdout);
    va_end(args);
    return 0;
}

int uart_printf(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    //fputs("\r\n", stdout);
    va_end(args);
    return 0;
}
