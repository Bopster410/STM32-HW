#include "uart.h"

void init_usart2(void)
{
  //pa2 - tx
  //pa3 - rx
  RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;	 //тактирование порта
  RCC->APB1ENR |= RCC_APB1ENR_USART2EN ; // тактирование юсарта2
  RCC->APB2ENR |= RCC_APB2ENR_AFIOEN; // тактирование альтернативных функций
  //настройка pa2, pa3 - по умолчанию плавающий вход, не трогаем
  GPIOA->CRL |= GPIO_CRL_MODE2; //MODE = 11, Output 50MHz
  GPIOA->CRL &= ~GPIO_CRL_CNF2_0; //CNF = 00
  GPIOA->CRL |= GPIO_CRL_CNF2_1; //CNF = 10, Alternate Push-Pull
  
  //настроить скорость передачи данных:
  //Fck = 32 МГц, тк в 2 раза меньше чем на АПБ2 - 64/2=32
  //57600
  //32МГц / (16 * 57600) = 34.7 - в хексе 34 это 22, 0,7*16=11,2 - к 22 пишем целую часть C
  //итого: 0x022C
  //BRR - Baud Rate Register
  USART2->BRR = 556; //регистр с целой и дробной частью
  
  //UE - USART Enable, RE - Receiver Enable, TE - Transmitter Enable, RXNEIE - RX Not Empty Interrupt Enable
  // CR - Configuration Register
  USART2->CR1 |= USART_CR1_UE | USART_CR1_RE | USART_CR1_TE | USART_CR1_RXNEIE; 
  NVIC_EnableIRQ(USART2_IRQn); // разрешили прерывание для USART2
  NVIC_SetPriority(USART2_IRQn, 0); // выставили приоритет
}

void usart2_transmit (char *str)
{
  strcat(str, "\r\n"); //добавляем стоп биты в передаваемую строку
  
  for (uint8_t i=0; i<strlen(str); i++)
  {
    USART2->DR = str[i]; //после этой строчки начнется передача данных
    while((USART2->SR & USART_SR_TC)==0); // TC - Transmission Complete
  }
}
