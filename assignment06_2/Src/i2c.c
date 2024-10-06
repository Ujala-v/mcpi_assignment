/*
Author: Nilesh Ghule <nilesh@sunbeaminfo.com>
Course: PG-DESD @ Sunbeam Infotech
Date: Sep 24, 2024
*/

#include "i2c.h"

void I2C_Init(void) {
	// PB6, PB7 -- GPIO Init -- MODER, AFRL, PUPDR, CLKEN
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
	GPIOB->MODER |= (BV(SCL_PIN*2+1) | BV(SDA_PIN*2+1));
	GPIOB->MODER &= ~(BV(SCL_PIN*2) | BV(SDA_PIN*2));
    GPIOB->PUPDR &= ~(BV(SCL_PIN*2+1) | BV(SDA_PIN*2+1) | BV(SCL_PIN*2) | BV(SDA_PIN*2)); // no pull-up/down
    // choose AF4 for I2C1 in Alternate Function registers
    GPIOB->AFR[0] |= BV(30) | BV(26);
    GPIOB->AFR[0] &= ~(BV(31) | BV(29) | BV(28) | BV(27) | BV(25) | BV(24));

	// I2C1 Init -- CR1, CR2, CCR, TRISE, CLKEN
    RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;
    // reset and clear reg
    I2C1->CR1 = I2C_CR1_SWRST;
    I2C1->CR1 = 0;
    // set pclk in CR2 (16 MHz)
    I2C1->CR2 |= 16;
    // set i2c bitrate to 100KHz (std mode)
    I2C1->CCR &= ~I2C_CCR_FS; // change mode to standard mode
    I2C1->CCR |= 80;			// CCR = Ton / Tpclk = 5 / 0.0625 = 80
    // standard mode Max Trise = 1000 ns
    // set Trise = Max Trise / Tpclk = 1000 / 62.5 = 17
    I2C1->TRISE |= 17;
    // Enable Ack
    I2C1->CR1 |= I2C_CR1_ACK;
    // Enable I2C
    I2C1->CR1 |= I2C_CR1_PE;
}

void I2C_Start(void) {
	// CR1 -- send start bit
    I2C1->CR1 |= I2C_CR1_START;
	// SR1 -- poll for SB (start bit sent)
    while(!(I2C1->SR1 & I2C_SR1_SB));
}
void I2C_RepeatStart(void) {
	I2C_Start();
}
void I2C_Stop(void) {
	// CR1 -- send stop bit
    I2C1->CR1 |= I2C_CR1_STOP;
    // SR2 -- poll for bus to be release
    while(!(I2C1->SR2 & I2C_SR2_BUSY));
}
void I2C_SendSlaveAddr(uint8_t slaveAddr) {
	// DR -- write slave addr in data regr
    I2C1->DR = slaveAddr;
	// SR1 -- poll for addr is transferred
    while (!(I2C1->SR1 & I2C_SR1_ADDR));
    // dummy read to clear flags
    (void)I2C1->SR1;
    (void)I2C1->SR2;
}
void I2C_SendData(uint8_t data) {
	// SR1 -- wait while previous data is not transmitted
	while (!(I2C1->SR1 & I2C_SR1_TXE));
	// DR -- write data in data regr
    I2C1->DR = data;
	// SR1 -- poll for BTF is transferred
    while (!(I2C1->SR1 & I2C_SR1_BTF));
}
uint16_t I2C_RecvData(void) {
	I2C1->CR1 |= I2C_CR1_ACK | I2C_CR1_POS;
	// wait until receive buffer is not empty
	while (!(I2C1->SR1 & I2C_SR1_RXNE));
	// read content and clear flags
	uint16_t val = I2C1->DR;
	return val;
}

uint16_t I2C_RecvDataNAck(void) {
	I2C1->CR1 &= ~(I2C_CR1_ACK | I2C_CR1_POS);
	// wait until receive buffer is not empty
	while (!(I2C1->SR1 & I2C_SR1_RXNE));
	// read content and clear flags
	uint16_t val = I2C1->DR;
	return val;
}

int I2C_IsDeviceReady(uint8_t slaveAddr) {
	// DR -- write slave addr in data regr
    I2C1->DR = slaveAddr;
	// SR1 -- poll for addr is transferred
    while (!(I2C1->SR1 & I2C_SR1_ADDR));
    // dummy read to clear flags
    (void)I2C1->SR1;
    (void)I2C1->SR2;
    return 1;
}


