/*
 * timer.h
 *
 *  Created on: Oct 1, 2024
 *      Author: sunbeam
 */

#ifndef TIMER_H_
#define TIMER_H_

#include"stm32f4xx.h"

#define TCLK 16000000UL
#define PR 16000

void TimerInit();
void TimerDelay(uint32_t ms);


#endif /* TIMER_H_ */
