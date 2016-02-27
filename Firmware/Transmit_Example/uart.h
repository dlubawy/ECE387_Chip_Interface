#ifndef uart_h_
#define uart_h_
#include <stddef.h>
#include <stdarg.h>

int uart_print(const char *format, ...);
int uart_receive(char *buff, size_t sz);
int uart_receivec(char line[], int i);

#endif
