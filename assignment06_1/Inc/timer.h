/*
 * timer.h
 *
 *  Created on: Sep 30, 2024
 *      Author: sunbeam
 */

#ifndef TIMER_H_
#define TIMER_H_

#include "stm32f4xx.h"

#define TCLK 16000000UL
#define PR 16000

void Timer_Init(uint32_t ms);
void TIM6_DAC_IRQHandler(void);

extern volatile uint32_t count, flag;

#endif /* TIMER_H_ */
