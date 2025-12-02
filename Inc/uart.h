#ifndef UART_H
#define UART_H

#include <string.h>
#include "stm32f1xx.h"

// Инициализировать модуль USART2
void init_usart2(void);

// Передать данные по UART
void usart2_transmit (char *str);

#endif /* UART_H */
