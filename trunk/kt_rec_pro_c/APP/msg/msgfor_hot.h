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

	DAC_UNMUTE,
	DAC_MUTE,
};

#ifdef __C51__
void ap_handle_hotkey(u8 msg);
void sys_dac_mute(bool mutectrl);
void sys_main_vol_setting(u8 sys_vol);
#endif

#endif
