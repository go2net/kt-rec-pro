/*--------------------------------------------------------------------------*/
/**@file   radio_rev.h
   @brief  dac头文件
   @details
   @author
   @date   2011-9-8
   @note
*/
/*----------------------------------------------------------------------------*/

#ifndef _RADIO_REV_
#define _RADIO_REV_

#include "config.h"
//#include "iic.h"
#if defined(K129_MODULE)
#define MAX_BAND    4
#elif defined(SW_TWO_BAND_RANGE)
#define MAX_BAND    4
#elif defined(SW_FULL_BAND_RANGE)||defined(SW_FULL_BAND_RANGE_END_AT_23MHZ)
#define MAX_BAND    3
#else
#define MAX_BAND    11
#endif
//#define MAX_FRE    1080
//#define MIN_FRE	   875
//#define MAX_CHANNL (MAX_FRE - MIN_FRE + 1)


///<**********收音选择****///////
//#define RDA5807      1
//#define CL6017G      0
//#define BK1080       0
//#define KT0830EG     0
//#define QN8035       0
#if 1//def __C51__
void radio_hdlr(void);
//void fm_rev( void );
//void dealmsgforfm(u8 msg);
//void enter_fm_rev(void);
//void scan_chan(u8 dir);
#endif

#endif
