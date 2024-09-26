/*
 * i2c_lcd.h
 *
 *  Created on: Sep 24, 2024
 *      Author: niralisoni
 */

#ifndef I2C_LCD_H_
#define I2C_LCD_H_

#include "i2c.h"

#define LCD_SLAVE_ADDR_W		0X4E
#define LCD_SLAVE_ADDR_R		0X4F

#define LCD_CLEAR				0X01
#define LCD_FN_SET_8BIT			0X30
#define LCD_FN_SET_4BIT			0X20
#define LCD_FN_SET_SCROLL		0X18
#define LCD_FN_SET_4BIT_1LINES_	0X20
#define LCD_DISP_CTRL			0X08
#define LCD_DISP_ON				0X0C
#define LCD_ENTRY_MODE			0X06
#define LCD_LINE1				0X80
#define LCD_LINE2				0XC0

#define LCD_RS	0
#define LCD_RW	1
#define LCD_EN	2
#define LCD_BL	3

#define LCD_CMD				0X80
#define LCD_DATA 			1

int Lcd_Init(void);
void Lcd_Write4BitAndCtrl(uint8_t val);
void Lcd_WriteByte(uint8_t rs, uint8_t val);
void Lcd_Puts(uint8_t line, char str[]);
void Lcd_shiftleft(void);

#endif /* I2C_LCD_H_ */
