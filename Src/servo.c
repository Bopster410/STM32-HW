#include "servo.h"

uint8_t transform_degree(uint8_t degree)
{
  if (degree > 180)
  {
    return degree = 180;
  }

  return degree + OFFSET;
}

void rotate_servo(uint8_t degree)
{
  // Настройка рабочего хода ШИМ для поворота сервопривода
  TIM2->CCR1 = transform_degree(degree);
}

void init_servo(void)
{
  // Тактирование TIM2 и порта A
  RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
  RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;

  // General output push-pull 50MHz (PA0)
  GPIOA->CRL &= ~(GPIO_CRL_CNF0 | GPIO_CRL_MODE0);
  GPIOA->CRL |= GPIO_CRL_CNF0_1 | GPIO_CRL_MODE0;

  // Таймер в режим PWM
  // PWM mode 1 - In upcounting
  TIM2->CCMR1 |= TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1;
  // Период ШИМ 50 Гц
  TIM2->PSC = 640 - 1;
  TIM2->ARR = 2000;
  // Начальный поворот сервопривода
  rotate_servo(INIT_DEGREE);
  // Capture/compare 1 output enabled
  TIM2->CCER |= TIM_CCER_CC1E;
  // Counter Enable
  TIM2->CR1 |= TIM_CR1_CEN;
}
