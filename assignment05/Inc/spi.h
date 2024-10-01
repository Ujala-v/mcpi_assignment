/*
Author: Nilesh Ghule <nilesh@sunbeaminfo.com>
Course: PG-DESD @ Sunbeam Infotech
Date: Sep 25, 2024
*/

#ifndef SPI_H_
#define SPI_H_

#include "stm32f4xx.h"

// SPI1 -- GPIOA (Alt Fn 5)
#define SPI_SCLK_PIN	5
#define SPI_MISO_PIN	6
#define SPI_MOSI_PIN	7

// CS -- GPIOE
#define SPI_CS_PIN		3

void SPI_Init(void);
void SPI_CS_Enable(void);
void SPI_CS_Disable(void);
uint16_t SPI_Transmit(uint16_t val);
uint16_t SPI_Receive(void);

#endif /* SPI_H_ */
