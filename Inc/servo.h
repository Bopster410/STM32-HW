#ifndef SERVO_H
#define SERVO_H

#include "stm32f1xx.h"

#define OFFSET 50
#define INIT_DEGREE 0

// Инициализировать работу сервопривода
void init_servo(void);

// Преобразовать угла поворота в значение для TIM2_CCR1
uint8_t transform_degree(uint8_t degree);

// Повернуть сервопривод
void rotate_servo(uint8_t degree);

#endif /* SERVO_H */
