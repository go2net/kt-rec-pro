/*--------------------------------------------------------------------------*/
/**@file     rtc_api.h
   @brief    RTC接口函数头文件
   @details
   @author
   @date   2011-9-8
   @note
*/
/*----------------------------------------------------------------------------*/

#ifndef	_RTC_API_H_
#define _RTC_API_H_

#include "typedef.h"
#include "device.h"
#include "rtc_operation.h"

#ifdef __C51__

#define IRTC_CSEN IRTCON|=BIT(0)
#define IRTC_CSDIS IRTCON&=~BIT(0)

#define MAX_ALARM 1

void write_rtc(RTC_TIME *curr_time_rtc);
void read_rtc(RTC_TIME *curr_time_rtc);
void write_alm(RTC_TIME *curr_time_alm);
void read_alm(RTC_TIME *curr_time_alm);
void reset_rtc_ram(void);
void alm_check(void);
void alm_sw(u8 flag);
//void set_rtc_power(u8 sw);
ALM_TIME find_next_alm_info(const ALM_TIME *alm_info);
ALM_TIME deal_multi_alarm(void);
void write_next_alm_sec(void);
void rtc_init(void);
void rtc_reset(void);
void chk_date_err(void);
void save_alarm_info(void);
void load_alarm_info(void);
void alarm_on_mode(void);
u8 alm_msg_convert(u8 key);
void close_alarm(void);
bool alarm_on(void);
#endif

#define WRITE_RTC_SEC 			0x50
#define READ_RTC_SEC  			0x40
#define WRITE_RTC_ALM 			0x38
#define READ_RTC_ALM  			0x39

#endif