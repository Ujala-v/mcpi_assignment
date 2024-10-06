/*
 * uart.c
 *
 *  Created on: Sep 23, 2024
 *      Author: sunbeam
 */
#include"uart.h"
#include "stm32f4xx.h"
#include "system_stm32f4xx.h"

void UartInit(uint32_t baud)
{
	RCC->AHB1ENR |= BV(GPIO_CLK);
    GPIO_UART->AFR[0] |= (BV(8)|BV(9)|BV(10)|BV(12)|BV(13)|BV(14));
    GPIO_UART->AFR[0] &=~ (BV(11)|BV(15));

    GPIO_UART->MODER |= (BV((TX_PIN<<1)+1)|BV((RX_PIN<<1)+1));
    GPIO_UART->MODER &= ~(BV(TX_PIN<<1)|BV(RX_PIN<<1));

    RCC->APB1ENR |= BV(UART_CLK);
    UART->CR1 |= (BV(USART_CR1_TE_Pos)|BV(USART_CR1_RE_Pos));
    UART->CR1 &= ~(BV(USART_CR1_M_Pos)|BV(USART_CR1_OVER8_Pos));

    UART->CR2 &= ~(BV(12) | BV(13));
    if(baud == 9600)
    	UART->BRR=BRR_9600;
    else if(baud == 38400)
    	UART->BRR=BRR_38400;
    else if(baud == 115200)
    	UART->BRR = BRR_115200;
    UART->CR1 |= BV(USART_CR1_UE_Pos);
}

void UartPutc(uint8_t ch)
{
  	UART->DR=ch;
  	while((UART->SR & BV(USART_SR_TXE_Pos))==0)
  		;
}

void UartPuts(char str[])
{
	for(int i=0;str[i]!='\0';i++)
		 UartPutc((uint8_t)str[i]);
}

uint8_t UartGetc()
{
	while((UART->SR & BV(USART_SR_RXNE_Pos)) == 0)
		;
	uint8_t ch = UART->DR;
	return ch;
}

void UartGets(char str[])
{
	char ch;
	int i=0;
	do
	{
	  ch=UartGetc();
	  str[i]=ch;
	  i++;
	}while(ch!='r');
	str[i++]='\n';
	str[i]='\0';
}
