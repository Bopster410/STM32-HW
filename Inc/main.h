#ifndef MAIN_H_
#define MAIN_H_

#include "stm32f1xx.h"
#include "uart.h"
#include "clk.h"
#include "servo.h"

// Считывание буфера Rx и выполнение команды
void execute_command(void);

#endif /* MAIN_H_ */
