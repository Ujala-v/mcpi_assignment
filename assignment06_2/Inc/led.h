/*
 * led.h
 *
 *  Created on: Sep 19, 2024
 *      Author: sunbeam
 */

#ifndef LED_H_
#define LED_H_

#include<stm32f4xx.h>

#define GPIO_LED GPIOD
#define GPIO_GREEN_PIN 12
#define GPIO_ORANGE_PIN 13
#define GPIO_RED_PIN 14
#define GPIO_BLUE_PIN 15

#define GPIO_LED_CLK 3

void ledinit(uint32_t pin);
void ledon(uint32_t pin);
void ledoff(uint32_t pin);
void ledblink(uint32_t pin);


#endif /* LED_H_ */
