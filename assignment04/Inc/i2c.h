/*
 * i2c.h
 *
 *  Created on: Sep 25, 2024
 *      Author: spam
 */

#ifndef I2C_H_
#define I2C_H_
#include"stm32f4xx.h"

#define GPIO_I2C			GPIOB

#define SCL_PIN				6
#define SDA_PIN				7

void init_i2c(void);
void i2c_start(void);
void i2c_stop(void);
void i2c_repeatstart(void);
void i2c_sendslaveaddress(uint8_t addr);
void i2c_senddata(uint8_t data);
uint16_t i2c_recvdata(void);
uint16_t i2c_recvdatanack(void);
int i2c_isdeviceready(uint8_t addr);


#endif /* I2C_H_ */
