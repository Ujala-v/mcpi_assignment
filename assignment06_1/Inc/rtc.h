/*
 * rtc.h
 *
 *  Created on: Oct 1, 2024
 *      Author: sunbeam
 */

#ifndef RTC_H_
#define RTC_H_


#include "stm32f4xx.h"

typedef struct {
	uint8_t Date, Month, Year, WeekDay;
}RTC_Date;

typedef struct {
	uint8_t Hour, Minute, Second;
}RTC_Time;

void RTC_Init(RTC_Date *dt, RTC_Time *tm);
void RTC_SetDate(RTC_Date *dt);
void RTC_SetTime(RTC_Time *tm);
void RTC_GetDate(RTC_Date *dt);
void RTC_GetTime(RTC_Time *tm);


#endif /* RTC_H_ */
