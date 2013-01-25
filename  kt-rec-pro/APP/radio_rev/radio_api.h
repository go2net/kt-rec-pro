/*--------------------------------------------------------------------------*/
/**@file   fm_api.h
   @brief  FM接口函数头文件
   @details
   @author
   @date   2011-9-8
   @note
*/
/*----------------------------------------------------------------------------*/
#include "Custom_config.h"

#ifndef _RADIO_API_H_
#define _RADIO_API_H_

#include "config.h"

#ifdef __C51__

//#include "rda5807.h"
//#include "CL6017.h"
//#include "bk1080.h"
//#include "ar1019.h"
//#include "KT0830EG.h"
//#include "QN8035.h"
//#include "KT_AMFMdrv.h"

//void get_channl(u8 flag);
//bool init_fm_rev(void);
//bool set_fre(u8);
//void fm_rev_powerdown(void);
//void save_fre(u16 fre);
//void fm_module_mute(u8 flag);
//v/oid fm_set_ch(u8 db);
#endif

typedef struct{
	u16	MIN_FREQ;
	u16 	MAX_FREQ;
#if defined(RADIO_VAR_VOL_TUNE)||defined(MCU_ADC_VOL_TUNER)
	u16 	FREQ_STEP;
#endif	
}FREQ_RAGE;

enum {

	BAND_NEXT,
	BAND_PREV,
};
#define FM_CUR_FRE          0
#define FM_FRE_DEC          1
#define FM_FRE_INC			2


#endif
