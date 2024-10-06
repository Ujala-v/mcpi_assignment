/*
 * switch.c
 *
 *  Created on: Sep 21, 2024
 *      Author: sunbeam
 */

#include"switch.h"

void SwitchInit()
{
	RCC->AHB1ENR |= BV(SWITCH_EXTI);
	SWITCH_PORT->MODER &= ~(BV((SWITCH_PIN<<1)+1) | BV(SWITCH_PIN<<1));
	SWITCH_PORT->PUPDR &= ~(BV((SWITCH_PIN<<1)+1) | BV(SWITCH_PIN<<1));

	EXTI->FTSR |= BV(SWITCH_EXTI);
	EXTI->IMR |= BV(SWITCH_EXTI);

	SYSCFG->EXTICR[0] |= ~(BV(3)|BV(2)|BV(1)|BV(0));
	NVIC_EnableIRQ(EXTI0_IRQn);
}

volatile uint32_t flag =0;
void EXTI0_IRQHandler()
{
	EXTI->PR |= BV(SWITCH_EXTI);
	flag=1;
	//ledtoggle(GPIO_RED_PIN,1000);
}
