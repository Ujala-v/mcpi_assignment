/*
 * switch.h
 *
 *  Created on: Sep 21, 2024
 *      Author: sunbeam
 */

#ifndef SWITCH_H_
#define SWITCH_H_

#include"stm32f4xx.h"

#define SWITCH_PORT GPIOA
#define SWITCH_PIN 0
#define SWITCH_CLK 0

#define SWITCH_EXTI 0

void SwitchInit();
void EXTI0_IRQHandler();

extern volatile uint32_t flag;

#endif /* SWITCH_H_ */
