/*
 * uart.h
 *
 *  Created on: Sep 23, 2024
 *      Author: sunbeam
 */

#ifndef UART_H_
#define UART_H_

#include"stm32f4xx.h"

#define UART USART2
#define GPIO_UART GPIOA
#define GPIO_CLK   0
#define UART_CLK  17
#define TX_PIN 2
#define RX_PIN 3

#define BRR_9600 0x683
#define BRR_38400 0x1A1
#define BRR_115200 0x8B

void UartInit(uint32_t baud);
void UartPuts(char str[]);
void UartPutc(uint8_t ch);

void UartGets(char str[]);
uint8_t UartGetc();


#endif /* UART_H_ */
