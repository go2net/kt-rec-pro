/*--------------------------------------------------------------------------*/
/**@file    msgfor_hot.h
   @brief   HOT 消息处理
   @details
   @author
   @date   2010-12-13
   @note
*/
/*----------------------------------------------------------------------------*/
#ifndef _MSGFOR_HOT_
#define	_MSGFOR_HOT_

#include "config.h"
#include "key.h"

enum {

	DISP_NORMAL,
	DISP_RTC_SCEN,
};

enum {

	DELAY_MUTE_500MS =1,
	DELAY_MUTE_1000MS,
	DELAY_MUTE_1500MS,
	DELAY_MUTE_2000MS,
};

enum {

	UNMUTE,
	MUTE,
};
#ifdef __C51__
void ap_handle_hotkey(u8 msg);
void set_delay_mute(u8 pa_dly_mute_time);
void ext_pa_delay_mute_hdlr(void);
#endif

#endif
