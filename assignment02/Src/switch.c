/*
 * switch.c
 *
 *  Created on: Sep 21, 2024
 *      Author: spam
 */


#include "switch_inter.h"

void SwitchInit(void)
{

	GPIO_SWITCH->MODER &= BV((GPIO_SWITCH_PIN>>1) +1);
	GPIO_SWITCH->MODER |= BV(GPIO_SWITCH_PIN>>1);

	GPIO_SWITCH->PUPDR &= ~(((GPIO_SWITCH_PIN>>1) +1) | (GPIO_SWITCH_PIN>>1));

	//Interrupt initialization
	EXTI->FTSR |= BV(SWITCH_EXTI);
	EXTI->IMR |= BV(SWITCH_EXTI);
	SYSCFG->EXTICR[0] = ~(BV(3) | BV(2) | BV(1) | BV(0));
	NVIC_EnableIRQ(EXTI0_IRQn);
}
volatile uint32_t switch_flag = 0;

void EXTI0_IRQHandler(void)
{

EXTI->PR |= BV(SWITCH_EXTI);
  switch_flag = 1;
}
