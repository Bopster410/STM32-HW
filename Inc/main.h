/*
 * main.h
 *
 *  Created on: Oct 31, 2025
 *      Author: dmitr
 */

#ifndef MAIN_H_
#define MAIN_H_

#define SET_INDICATOR(digit) GPIOC->ODR = GPIOC->ODR == 0 ? 0 : digit
#define INDICATOR_SWAP(digit)	GPIOC->ODR = GPIOC->ODR == 0 ? digit : 0;
#include "stm32f1xx.h"
void delay(uint32_t delay_value);

#endif /* MAIN_H_ */
