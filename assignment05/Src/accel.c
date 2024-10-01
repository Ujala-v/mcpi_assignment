/*
Author: Nilesh Ghule <nilesh@sunbeaminfo.com>
Course: PG-DESD @ Sunbeam Infotech
Date: Sep 25, 2024
*/

#include "accel.h"

void SPI_WriteIO(uint8_t regr, uint8_t data[], uint8_t size) {
	// enable slave
	SPI_CS_Enable();
	// send regr address (internal address) : MSB=0
	regr &= ~BV(7);
	SPI_Transmit(regr);
	// write multiple bytes of data
	for(int i=0; i<size; i++)
		SPI_Transmit(data[i]);
	// disable slave
	SPI_CS_Disable();
}

void SPI_ReadIO(uint8_t regr, uint8_t data[], uint8_t size) {
	// enable slave
	SPI_CS_Enable();
	// send regr address (internal address) : MSB=1
	regr |= BV(7);
	SPI_Transmit(regr);
	// read multiple bytes of data
	for(int i=0; i<size; i++)
		data[i] = SPI_Receive();
	// disable slave
	SPI_CS_Disable();
}


// LIS Initialization = Enable axes and Set data rate
void LIS_Init(void) {
	// initialize spi
	SPI_Init();
	DelayMs(3);
	// enable axes and set data rate
	uint8_t config = LIS_CR4_RATE_25 | LIS_CR4_XYZ_EN;
	SPI_WriteIO(LIS_CR4_ADDR, &config, 1);
}

// LIS Poll = Check if new data (X, Y, Z reading) is available
int LIS_IsDataAvail(void) {
	uint8_t status;
	do {
		// read status regr value
		SPI_ReadIO(LIS_STATUS_ADDR, &status, 1);
		// repeat until data is avail
	} while(!(status & LIS_SR_XYZDA));
	return 1;
}

// LIS Read = Get X, Y, Z axis data from Accel
LIS_Data LIS_GetData(void) {
	uint8_t data[2];
	LIS_Data val;
	// read x axis reading
	SPI_ReadIO(LIS_XL_ADDR, data, 2); // data[0]=L, data[1]=H
	val.x = ((uint16_t)data[1] << 8) | data[0];
	// read y axis reading
	SPI_ReadIO(LIS_YL_ADDR, data, 2); // data[0]=L, data[1]=H
	val.y = ((uint16_t)data[1] << 8) | data[0];
	// read z axis reading
	SPI_ReadIO(LIS_ZL_ADDR, data, 2); // data[0]=L, data[1]=H
	val.z = ((uint16_t)data[1] << 8) | data[0];
	return val;
}






