/*--------------------------------------------------------------------------*/
/**@file    rtc_mode.h
   @brief   RTC任务模块头文件
   @details
   @author
   @date   2011-9-8
   @note
*/
/*----------------------------------------------------------------------------*/

#ifndef	_RTC_MODE_H_
#define _RTC_MODE_H_

#include "config.h"
#include "msgfor_hot.h"
#include "dac.h"
//#include "ADKEY.h"
#include "rtc_api.h"
#include "rtc_ui.h"

#ifdef __C51__

enum
{
    RTC_DISPLAY = 0,
    RTC_SETTING,
    ALARM_SETTING,
};
void rtc_disp_hdlr(void);
void rtc_fun(void);
#endif

#define	MSG_RTC_SETTING	  	MSG_NEXT_PLAYMODE
#define	MSG_RTC_NEXT	  	MSG_MUSIC_NEXT_EQ
#define	MSG_RTC_PREV	  	MSG_MUSIC_PP
#define	MSG_RTC_PLUS	  	MSG_MUSIC_NEXT_FILE
#define MSG_RTC_PLUS_HOLD	MSG_MUSIC_FF
#define	MSG_RTC_MINUS	  	MSG_MUSIC_PREV_FILE
#define MSG_RTC_MINUS_HOLD	MSG_MUSIC_FR

#endif
