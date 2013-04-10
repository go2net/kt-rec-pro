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

bool radio_device_init(void);
void radio_device_standby(void);

void radio_info_pre_init(void);

void set_radio_freq(u8 mode);
bool radio_band_scan(u8 mode);
void radio_all_scan_stop(void);
void radio_band_switcher(void);
void radio_freq_auto_align(void);



#endif


typedef struct _RADIO_MODE_VAR
{
    u16 wFreq;          ///<当前频点
    u16 wFreqUpLimit;          
    u16 wFreqDownLimit;          
    u8  bCurBand; 	
    u8  bTuneStep; 	
    u8  bCurChannel; 	
    u8  bTotalChannel;  
}RADIO_MODE_VAR;


typedef struct{
	u16	MIN_FREQ;
	u16 	MAX_FREQ;
#if 1//defined(RADIO_VAR_VOL_TUNE)||defined(MCU_ADC_VOL_TUNER)
	u8	FREQ_STEP;
#endif	
}FREQ_RAGE;

enum {

	BAND_NEXT,
	BAND_PREV,
};
enum {

	RADIO_SCAN_STOP,
	RADIO_SCAN_NEXT,
	RADIO_SCAN_PREV,
	RADIO_SCAN_ALL,	
};


enum {
	
	 RADIO_CUR_FRE,
	 RADIO_FRE_DEC,
	 RADIO_FRE_INC,
};


#define SEMI_AUTO_SCAN_KEY_UP		MSG_MUSIC_FF_START
#define SEMI_AUTO_SCAN_KEY_DOWN	MSG_MUSIC_FR_START


#endif
