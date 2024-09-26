/*
 * led.c
 *
 *  Created on: Sep 19, 2024
 *      Author: spam
 */
#include"led.h"

void  led_init(uint32_t pin)
{
  RCC->AHB1ENR |= BV(GPIO_LED_AHBENR);
  GPIO_LED->MODER &= ~(BV((pin<<1) + 1));
  GPIO_LED->MODER |= (BV(pin<<1));
  GPIO_LED->OTYPER &= ~BV(13);
  GPIO_LED->OSPEEDR &= ~(BV((pin<<1) +1) | (BV(pin<<1)));
  GPIO_LED->PUPDR &= ~(BV((pin<<1) +1) | (BV(pin<<1)));

}

void led_on(uint32_t pin)
{
	GPIO_LED->ODR |= BV(pin);
}

void led_off(uint32_t pin)
{
	GPIO_LED->ODR &= ~BV(pin);
}

void ledblink(uint32_t pin, uint32_t delay )
{

	led_on(pin);
	DelayMs(delay);
	led_off(pin);
}
