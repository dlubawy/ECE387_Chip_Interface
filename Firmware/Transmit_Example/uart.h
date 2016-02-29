#ifndef uart_h_
#define uart_h_
#include <stddef.h>
#include <stdarg.h>

void uart_init( uint32_t baud );
int uart_println(const char *format, ...);
int uart_printf(const char *format, ...);

#endif
