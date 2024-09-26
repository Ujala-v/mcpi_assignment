/*
 * uart_cw.c
 *
 *  Created on: Sep 23, 2024
 *      Author: sunbeam
 */

#include <uart_menu.h>


void UartInit(uint32_t baud){
	RCC->AHB1ENR |= BV(GPIO_CLK_EN);

	GPIO_UART->MODER |= (BV(GPIO_TX_PIN*2+1) | BV(GPIO_RX_PIN*2+1));
	GPIO_UART->MODER &= ~(BV(GPIO_TX_PIN*2) | (GPIO_RX_PIN*2));

	GPIO_UART->AFR[0] |= BV(8) | BV(9) | BV(10) |BV(12) |BV(13) |BV(14);
	GPIO_UART->AFR[0] &= ~(BV(11) | BV(15));


	RCC->APB1ENR |= BV(UART_CLK_EN);

	UART->CR1 = (USART_CR1_TE) | (USART_CR1_RE);

	UART->CR1 &= ~((USART_CR1_M) | (USART_CR1_OVER8));

	UART->CR2 &= ~(USART_CR2_STOP_0 | USART_CR2_STOP_1);

	if(baud == 9600)
		UART->BRR = BAUD_9600;
	else if(baud == 38400)
		UART->BRR = BAUD_38400;
	else if(baud == 115200)
		UART->BRR = BAUD_115200;

	UART->CR1 |= USART_CR1_UE ;

}

void UartPutch(uint32_t ch){
	UART->DR = ch;

	while((UART->SR & USART_SR_TXE) == 0)
		;
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






















