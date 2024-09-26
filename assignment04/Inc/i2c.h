/*
 * i2c.h
 *
 *  Created on: Sep 24, 2024
 *      Author: sunbeam
 */

#ifndef I2C_H_
#define I2C_H_

#include "stm32f4xx.h"

#define SCL_PIN			6
#define SDA_PIN			7

void I2C_Init(void);
void I2C_Start(void);
void I2C_RepeatStart(void);
void I2C_Stop(void);
void I2C_SendSlaveAddr(uint8_t slaveaddr);
void I2C_SendData(uint8_t data);
uint16_t I2C_RecvData(void);
uint16_t I2C_RecvDataNAck(void);
int I2C_IsDeviceReady(uint8_t slaveaddr);

#endif /* I2C_H_ */
