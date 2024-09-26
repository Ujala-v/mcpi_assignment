/*
 * uart_cw.c
 *
 *  Created on: Sep 23, 2024
 *      Author: sunbeam
 */

#include "uart_cw.h"
volatile uint32_t flag = 0;

void UartInit(uint32_t baud){
	RCC->AHB1ENR |= BV(GPIO_CLK_EN);

	GPIO_UART->MODER |= (BV(GPIO_TX_PIN*2+1) | BV(GPIO_RX_PIN*2+1));
	GPIO_UART->MODER &= ~(BV(GPIO_TX_PIN*2) | (GPIO_RX_PIN*2));

	GPIO_UART->AFR[0] |= BV(8) | BV(9) | BV(10) |BV(12) |BV(13) |BV(14);
	GPIO_UART->AFR[0] &= ~(BV(11) | BV(15));

	// enable uart clock -- APB1ENR.17
	RCC->APB1ENR |= BV(UART_CLK_EN);
	// enable transmission and reception on uart
	UART->CR1 = (USART_CR1_TE) | (USART_CR1_RE);
	// set word length in CR1 -- M bit = 8-bit data len, Over8 = 0
	UART->CR1 &= ~((USART_CR1_M) | (USART_CR1_OVER8));
	// set stop bits in CR2 -- 1 stop bit
	UART->CR2 &= ~(USART_CR2_STOP_0 | USART_CR2_STOP_1);
	// set baud rate -- UBRR
	if(baud == 9600)
		UART->BRR = BAUD_9600;
	else if(baud == 38400)
		UART->BRR = BAUD_38400;
	else if(baud == 115200)
		UART->BRR = BAUD_115200;

	// enable USART interrupt in NVIC
	//NVIC_EnableIRQ(USART2_IRQn);
	// enable uart in CR1 -- UE bit
	UART->CR1 |= USART_CR1_UE ;

}

void SwitchInit(void){
	RCC->AHB1ENR |= BV(SWITCH_CLK_EN);

	GPIO_UART->MODER &= ~(BV(SWITCH_PIN*2) | BV(SWITCH_PIN*2+1));

	GPIO_UART->PUPDR &= ~(BV(SWITCH_PIN*2) | BV(SWITCH_PIN*2+1));

	EXTI->FTSR |= BV(SWITCH_EXTI);

	EXTI->IMR |= BV(SWITCH_EXTI);

	SYSCFG->EXTICR[0] &= ~(BV(3) |BV(2) |BV(1) |BV(0));

	NVIC_EnableIRQ(EXTI0_IRQn);

}

void UartPutch(uint32_t ch){
	UART->DR = ch;

	while((UART->SR & USART_SR_TXE) == 0)
		;
}

void EXTI0_IRQHandler(void){
	EXTI->PR |= BV(SWITCH_EXTI);

	//LedToggle(LED_GREEN_PIN);

	flag=1;
}

void UartPuts(char str[]){
	for(int i=0; str[i] != '\0'; i++)
		UartPutch((uint8_t)str[i]);
}

uint8_t UartGetch(void){
	while((UART->SR & (USART_SR_RXNE)) == 0)
		;

	char ch = UART->DR;
	return ch;
}

void UartGets(char str[]){
	char ch;
	int i = 0;
	do{
		ch = UartGetch();
		str[i] = ch;
		i++;
	}while(ch != '\r');
	str[i++] = '\n';
	str[i] = '\0';
}






















