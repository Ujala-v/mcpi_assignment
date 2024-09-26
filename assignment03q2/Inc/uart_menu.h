	/*
 * uart_cw.h
 *
 *  Created on: Sep 23, 2024
 *Author: sunbeam
 */

#ifndef UART_MENU_H_
#define UART_MENU_H_

#include "stm32f4xx.h"
//extern volatile uint32_t flag;

#define UART 			USART2

#define GPIO_UART 		GPIOA
#define GPIO_TX_PIN 	2
#define GPIO_RX_PIN 	3

#define GPIO_CLK_EN 	0
#define UART_CLK_EN 	17

#define BAUD_9600 		0x683
#define BAUD_38400		0x1A1
#define BAUD_115200		0x8B

void SwitchInit(void);
void UartInit(uint32_t baud);
void UartPutch(uint32_t ch);
void UartPuts(char str[]);
uint8_t UartGetch(void);
void UartGets(char str[]);


#endif /* UART_MENU_H_ */
