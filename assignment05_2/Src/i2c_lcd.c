/*
 * i2c_lcd.c
 *
 *  Created on: Sep 25, 2024
 *      Author: spam
 */


#include "i2c_lcd.h"
#include "i2c.h"


void Lcd_Write4BitAndCtrl(uint8_t val)
{
   i2c_start();
   i2c_sendslaveaddress(LCD_SLAVE_ADDR_W);
   i2c_senddata(val);
   i2c_stop();
}



void Lcd_WriteByte(uint8_t rs, uint8_t val)
{
	uint8_t high = val & 0xF0, low = (val << 4) & 0xF0;
    uint8_t bvrs = (rs == LCD_CMD) ? 0: BV(LCD_RS);
    Lcd_Write4BitAndCtrl(high | bvrs | BV(LCD_EN) | BV(LCD_BL));
    DelayMs(1);
    Lcd_Write4BitAndCtrl(high | bvrs | BV(LCD_BL));

    Lcd_Write4BitAndCtrl(low | bvrs | BV(LCD_EN) | BV(LCD_BL));
    DelayMs(1);
    Lcd_Write4BitAndCtrl(low | bvrs | BV(LCD_BL));
}


int Lcd_Init()
{
	DelayMs(20);
	init_i2c();
	i2c_start();
	int ret = i2c_isdeviceready(LCD_SLAVE_ADDR_W);
	i2c_stop();
	if(!ret)
		return 0;

	Lcd_Write4BitAndCtrl(LCD_FN_SET_8BIT | BV(LCD_EN));
	__NOP();
	Lcd_Write4BitAndCtrl(LCD_FN_SET_8BIT);
	DelayMs(5);

	Lcd_Write4BitAndCtrl(LCD_FN_SET_8BIT | BV(LCD_EN));
	__NOP();
	Lcd_Write4BitAndCtrl(LCD_FN_SET_8BIT);
	DelayMs(1);

	Lcd_Write4BitAndCtrl(LCD_FN_SET_8BIT | BV(LCD_EN));
	__NOP();
	Lcd_Write4BitAndCtrl(LCD_FN_SET_8BIT);
	DelayMs(3);

	Lcd_Write4BitAndCtrl(LCD_FN_SET_4BIT | BV(LCD_EN));
	__NOP();
	Lcd_Write4BitAndCtrl(LCD_FN_SET_4BIT);
	DelayMs(3);


	// lcd initialization
	Lcd_Write4BitAndCtrl(LCD_FN_SET_4BIT_1LINES);
	DelayMs(1);
	Lcd_WriteByte(LCD_CMD, LCD_DISP_CTRL);
	DelayMs(1);
	Lcd_WriteByte(LCD_CMD, LCD_CLEAR);
	DelayMs(1);
	Lcd_WriteByte(LCD_CMD, LCD_ENTRY_MODE);
	DelayMs(1);
	Lcd_WriteByte(LCD_CMD, LCD_DISP_ON);
	DelayMs(1);
	return ret;
}


void Lcd_Puts(uint8_t line, char str[])
{
	int i;
	Lcd_WriteByte(LCD_CMD, line);
	DelayMs(1);
	for(i=0; str[i]!='\0'; i++)
		Lcd_WriteByte(LCD_DATA, str[i]);
}
