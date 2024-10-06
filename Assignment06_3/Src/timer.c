/*
 * timer.c
 *
 *  Created on: Oct 1, 2024
 *      Author: sunbeam
 */


#include"timer.h"

void TimerInit(uint32_t ms)
{
	RCC->APB1ENR |= RCC_APB1ENR_TIM7EN;
	TIM7->PSC = (PR-1);
	uint32_t cnt = (TCLK / 1000)*ms/PR;
	TIM7->ARR = (cnt-1);
    TIM7->CNT = 0;
    TIM7->DIER |= TIM_DIER_UIE;
    NVIC_EnableIRQ(TIM7_IRQn);
    TIM7->CR1 |= TIM_CR1_CEN;
}

volatile int count=0;
void TIM7_IRQHandler()
{
	//while((TIM7->SR & TIM_SR_UIF));
	if(TIM7->SR & TIM_SR_UIF)
	{
		TIM7->SR &= ~TIM_SR_UIF;
		count++;
	}
}
