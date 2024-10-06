/*
 * i2c_lcd.h
 *
 *  Created on: Sep 25, 2024
 *      Author: spam
 */


#ifndef I2C_LCD_H_
#define I2C_LCD_H_

#include "i2c.h"

#define LCD_SLAVE_ADDR_W	0x4E
#define LCD_SLAVE_ADDR_R	0x4F
//#define LCD_SLAVE_ADDR_W	0x7E
//#define LCD_SLAVE_ADDR_R	0x7F

#define LCD_CLEAR		0x01
#define LCD_FN_SET_8BIT	0x30
#define LCD_FN_SET_4BIT	0x20
#define LCD_FN_SET_4BIT_2LINES	0x28
#define LCD_FN_SET_4BIT_1LINES	0x20
#define LCD_DISP_CTRL	0x08
#define LCD_DISP_ON		0x0C
#define LCD_ENTRY_MODE	0x06


#define LCD_LINE1		0x80
#define LCD_LINE2		0xC0

#define LCD_DISP_SHIFT_LEFT 0x18
#define LCD_DISP_SHIFT_RIGHT 0x1C

#define LCD_RS	0
#define LCD_RW	1
#define LCD_EN	2
#define LCD_BL	3

#define LCD_CMD		0x80
#define LCD_DATA	1


int Lcd_Init(void);
void Lcd_Write4BitAndCtrl(uint8_t val);
void Lcd_WriteByte(uint8_t rs, uint8_t val);
void Lcd_Puts(uint8_t line, char str[]);

#endif /* I2C_LCD_H_ */

