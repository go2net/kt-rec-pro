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

#ifdef __C51__
void ap_handle_hotkey(u8 msg);
#endif

#endif