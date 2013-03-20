/*--------------------------------------------------------------------------*/
/**@file    rtc_ui.h
   @brief   RTC用户界面操作
   @details
   @author
   @date   2011-7-5
   @note
*/
/*----------------------------------------------------------------------------*/

#ifndef	_RTC_UI_H_
#define _RTC_UI_H_

#include "config.h"
#include "lcd.h"
#include "rtc_api.h"

#ifdef __C51__

void curr_time_plus(void);
void curr_time_minus(void);
void alm_time_plus(void);
void alm_time_minus(void);
u8 alm_request_choose(void);
#endif

#define RTC_END_COLUMN 128

#define RTC_YEAR_COORDINATE		(RTC_END_COLUMN - 10*8)/2 + 0
#define RTC_MONTH_COORDINATE	(RTC_END_COLUMN - 10*8)/2 + 40
#define RTC_DAY_COORDINATE		(RTC_END_COLUMN - 10*8)/2 + 64
#define RTC_HOUR_COORDINATE		(RTC_END_COLUMN - 10*8)/2 + 0
#define RTC_MIN_COORDINATE		(RTC_END_COLUMN - 10*8)/2 + 24
#define RTC_SEC_COORDINATE		(RTC_END_COLUMN - 10*8)/2 + 48

#define ALM_ICON_COORDINATE 	1*8
#define ALM_SW_COORDINATE		8*8//(RTC_END_COLUMN - 12*8)/2 +
#define ALM_HOUR_COORDINATE		8*8//(RTC_END_COLUMN - 12*8)/2 +
#define ALM_MIN_COORDINATE		(8*8+24)//(RTC_END_COLUMN - 12*8)/2 +

#define ALM_Y_COORDINATE		(RTC_END_COLUMN - 10*8)/2 + 0
#define ALM_N_COORDINATE 		(RTC_END_COLUMN - 10*8)/2 + 64
/*
#define ALM_MON_COORDINATE		(RTC_END_COLUMN - 12*8)/2 +
#define ALM_TUE_COORDINATE		(RTC_END_COLUMN - 12*8)/2 +
#define ALM_WED_COORDINATE		(RTC_END_COLUMN - 12*8)/2 +
#define ALM_THU_COORDINATE		(RTC_END_COLUMN - 12*8)/2 +
#define ALM_FRI_COORDINATE		(RTC_END_COLUMN - 12*8)/2 +
#define ALM_SAT_COORDINATE		(RTC_END_COLUMN - 12*8)/2 +
#define ALM_SUN_COORDINATE		(RTC_END_COLUMN - 12*8)/2 +
*/
#endif