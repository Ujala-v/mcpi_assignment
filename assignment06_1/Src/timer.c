/*
 * timer.c
 *
 *  Created on: Sep 30, 2024
 *      Author: sunbeam
 */


#include "timer.h"



void Timer_Init(uint32_t ms){
	//Enable Timer APB clock
	RCC->APB1ENR |= RCC_APB1ENR_TIM6EN;

//set timer clock
	TIM6->PSC=(PR-1);

//Calculate number of clocks to count(cnt)
	uint32_t cnt =(TCLK/1000) * ms/PR;
//set CNT in ARR
	TIM6-> ARR=(cnt-1);
//Reset timer counter to 0
	TIM6->CNT = 0;
//Enable timer interrupt in DIER
	TIM6->DIER |= TIM_DIER_UIE;
//NVIC ENable
	NVIC_EnableIRQ(TIM6_DAC_IRQn);

//start timer in CR1
	TIM6->CR1 |= TIM_CR1_CEN;

}


uint32_t volatile  count=0, flag=0;

void TIM6_DAC_IRQHandler(void){

	// CHECK IF UIF flag is set
	if(TIM6->SR & TIM_SR_UIF){

		TIM6->SR &= ~TIM_SR_UIF;

		count++;
		flag=1;


	}
}
