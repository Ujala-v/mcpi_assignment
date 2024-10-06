/*
 * systick.c
 *
 *  Created on: Oct 2, 2024
 *      Author: sunbeam
 */


#include"systick.h"

volatile uint32_t jiffies=0;

void SysTick_Handler()
{
   jiffies++;
}

void systick_delay(uint32_t ms)
{
   uint32_t until = jiffies + ms;
   while(jiffies < until);
}
