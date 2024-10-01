/*
Author: Nilesh Ghule <nilesh@sunbeaminfo.com>
Course: PG-DESD @ Sunbeam Infotech
Date: Sep 25, 2024
*/

#ifndef ACCEL_H_
#define ACCEL_H_

#include "spi.h"
#include "stm32f4xx.h"

#define LIS_CR4_ADDR	0x20
#define LIS_STATUS_ADDR	0x27
#define LIS_XL_ADDR		0x28
#define LIS_XH_ADDR		0x29
#define LIS_YL_ADDR		0x2A
#define LIS_YH_ADDR		0x2B
#define LIS_ZL_ADDR		0x2C
#define LIS_ZH_ADDR		0x2D

#define LIS_CR4_XEN		BV(0)
#define LIS_CR4_YEN		BV(1)
#define LIS_CR4_ZEN		BV(2)
#define LIS_CR4_XY_EN	(LIS_CR4_XEN | LIS_CR4_YEN)
#define LIS_CR4_XYZ_EN	(LIS_CR4_XEN | LIS_CR4_YEN | LIS_CR4_ZEN)

#define LIS_CR4_RATE_25	BV(6)

#define LIS_SR_XDA		BV(0)
#define LIS_SR_YDA		BV(1)
#define LIS_SR_ZDA		BV(2)
#define LIS_SR_XYZDA	BV(3)

// Functions to Write or Read registers
void SPI_WriteIO(uint8_t regr, uint8_t data[], uint8_t size);
void SPI_ReadIO(uint8_t regr, uint8_t data[], uint8_t size);

typedef struct {
	int16_t x;
	int16_t y;
	int16_t z;
} LIS_Data;

// LIS3DSH Functions
// LIS Initialization = Enable axes and Set data rate
void LIS_Init(void);
// LIS Poll = Check if new data (X, Y, Z reading) is available
int LIS_IsDataAvail(void); // LIS_DRdy
// LIS Read = Get X, Y, Z axis data from Accel
LIS_Data LIS_GetData(void);

#endif /* ACCEL_H_ */
