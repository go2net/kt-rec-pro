
#ifndef _KT_AMFMDRV_H_
#define _KT_AMFMDRV_H_

#include "iic.h"
//#include "typedef.h"

#define KTAMw_address 		0x6A
#define KTAMr_address 		0x6B

//#define LONG_ANTENNA				// Turn on only if the length of antenna exceeds 2m
//#define SEEK_WITH_SNR				// Turn on only if SNR double check is required in SEEK process
//#define DISABLE_FAST_GAIN_UP
//#define LOWFM_MODE
//#define MANUAL_SEPARATION				 
//#define AM_SOFTMUTE
//#define FM_SOFTMUTE
//#define AM_GAIN
//#define AUDIO_LEVEL_BOOST
//#define FM_HIGHLEVER_RF_SIGAL_INPUT
//#define AM_ABC
//#define AM_SOFTMUTE_AFCMODE

//#define KT0913
#define KT0915

#define X32P768K					//32.768KHz crystal
//#define R32P768K					//32.768KHz reference clock
//#define X38K						//38KHz crystal
//#define R38K						//38KHz reference clock
//#define R7P6M						//7.6MHz reference clock
//#define R12M						//12MHz reference clock
//#define R13M						//13MHz reference clock
//#define R24M						//24MHz reference clock
//#define R26M						//26MHz reference clock
//#define R12288KHz					//12.288MHz reference clock

#ifdef X32P768K
	#define C32P768K
#endif
#ifdef R32P768K
	#define C32P768K
#endif

#define FM_100KHz_STEP			10
#define FM_1MHz_STEP			100
#define AM_1KHz_STEP			1
#define AM_2KHz_STEP			2
#define AM_9KHz_STEP			9
#define AM_100KHz_STEP			100

#define FM_SEEK_UP_LIMIT			10800
#define FM_SEEK_DOWN_LIMIT		8600
#define FM_BAND_TOP				10900
#ifdef LOWFM_MODE
#define FM_BAND_BOTTOM			3200
#else
#define FM_BAND_BOTTOM			6400
#endif

#define MW_SEEK_UP_LIMIT			1710
#define MW_SEEK_DOWN_LIMIT		504
#define MW_BAND_TOP				1710
#define MW_BAND_BOTTOM			504

#define SW_SEEK_UP_LIMIT			32000
#define SW_SEEK_DOWN_LIMIT		1600
#define SW_BAND_TOP				32000
#define SW_BAND_BOTTOM			1600

#define SW1_TOP_LIMIT 			2495
#define SW1_BOTTOM_LIMIT 		2300

#define SW2_TOP_LIMIT 			3400
#define SW2_BOTTOM_LIMIT 		3200

#define SW3_TOP_LIMIT 			4000
#define SW3_BOTTOM_LIMIT 		3900

#define SW4_TOP_LIMIT 			5600
#define SW4_BOTTOM_LIMIT 		4750

#define SW5_TOP_LIMIT 			6200
#define SW5_BOTTOM_LIMIT 		5900

#define SW6_TOP_LIMIT 			7350
#define SW6_BOTTOM_LIMIT 		7100

#define SW7_TOP_LIMIT 			9900
#define SW7_BOTTOM_LIMIT 		9400

#define SW8_TOP_LIMIT 			12100
#define SW8_BOTTOM_LIMIT 		11600

#define SW9_TOP_LIMIT 			13870
#define SW9_BOTTOM_LIMIT 		13570

#define SW10_TOP_LIMIT 			15800
#define SW10_BOTTOM_LIMIT 		15100

#define SW11_TOP_LIMIT 			17900
#define SW11_BOTTOM_LIMIT 		17480

#define SW12_TOP_LIMIT 19100
#define SW12_BOTTOM_LIMIT 18850

#define SW13_TOP_LIMIT 21850
#define SW13_BOTTOM_LIMIT 21450

#define SW14_TOP_LIMIT 26100
#define SW14_BOTTOM_LIMIT 24670


#define FM_AFCTH_PREV 0			//Range from 0 to 127
#define FM_AFCTH 15				//Range from 0 to 127
#define FM_AFCTH_NEXT 0			//Range from 0 to 127

#define MW_AFCTH_PREV 6			//Range from 128 to 127
#define MW_AFCTH 4				//Range from 128 to 127
#define MW_AFCTH_NEXT 6			//Range from 128 to 127

#define SW_AFCTH_PREV 12		//Range from 128 to 127
#define SW_AFCTH 6				//Range from 128 to 127
#define SW_AFCTH_NEXT 12		//Range from 128 to 127


#define BAND_NUM	17

typedef enum {	

	FM_MODE=0,
	MW_MODE,
	SW_MODE,
	SW1_MODE,
	SW2_MODE,
	SW3_MODE,
	SW4_MODE,
	SW5_MODE,
	SW6_MODE,
	SW7_MODE,
	SW8_MODE,
	SW9_MODE,
	SW10_MODE,
	SW11_MODE,
	SW12_MODE,
	SW13_MODE,
	SW14_MODE
}Band_Mode;

typedef struct 
{
	u8 		Band;						// 频段
#if 0	
	u16			Band_Top;					//	tune台频段上门限
	u16			Band_Bottom;				//	tune台频段下门限
	u16			Seek_Up_Limit;				//	seek频段上门限
	u16			Seek_Down_Limit;			//	seek频段下门限
	u8			Min_Step;					//
	u8			Max_Step;					//
	u8			Seek_Step;					// SeekFromCurrentCh 函数用的频率步进
	u8			ValidStation_Step;			// ValidStation 函数用的频率步进
	u8			AFCTH_Prev;					//
	u8			AFCTH;						//
	u8			AFCTH_Next;					// 
#endif	
}Str_Band;
  

#define INIT_FAIL_TH 3

#define SEEKUP 1
#define SEEKDOWN 0

#define TST_TH 0x2800
#define FM_SNR_TH 0x40
#define AM_TUNING_LIGHT_TH 30
#define SEPARATION_POINT -91
#define BLEND_POINT -97

xd_u8 KT_AMFMPreInit(void);
xd_u8  KT_AMFMInit(void);
void KT_AMFMStandby(void);
xd_u8 KT_AMFMWakeUp(void);
xd_u8 KT_AMFMVolumeSet(xd_u8 vol);
void KT_AMFMMute(void);
xd_u8 KT_AMFMUnMute(void);
void KT_AMFMSetMode(xd_u8 AMFM_MODE);
xd_u8 KT_AMSetBW(xd_u8 AMBW);
void KT_AMTune(xd_u16 Frequency);
void KT_FMTune(xd_u16 Frequency);

//xd_u8 KT_FMReadRSSI(char *RSSI);
//xd_u8 KT_AMReadRSSI(char *RSSI);

//char KT_FMGetAFC(xd_u16 Frequency);
//char KT_AMGetAFC(void);

//xd_u8 KT_FMSeekFromCurrentCh(xd_u16 seekDir, xd_u16 *Frequency);
//xd_u8 KT_FMValidStation(xd_u16 Frequency);

//xd_u8 KT_AMSeekFromCurrentCh(xd_u16 seekDir, xd_u16 *Frequency);
//xd_u8 KT_AMValidStation(xd_u16 Frequency);
//xd_u8 KT_AMFMSeekFromCurrentCh(xd_u16 seekDir, xd_u16 *Frequency);   //     seekDir: 0-->seek down 1-->seek up

//xd_u16 KT_AMGetFreq(void);
//xd_u16 KT_FMGetFreq(void);
//xd_u8 KT_FMGetST(void);
//xd_u8 KT_FMGetSNR(void);

#ifdef AM_SOFTMUTE
void KT_AM_SOFTMUTE(xd_u16 Frequency);
void KT_AM_SOFTMUTE_SETTING(xd_u8 SMUTEA, xd_u8 SMUTER, xd_u8 AM_SMTH, xd_u8 VOLUMET);
#endif

#ifdef FM_SOFTMUTE
void KT_FM_SOFTMUTE(xd_u16 Frequency);
void KT_FM_SOFTMUTE_SETTING(xd_u8 SMUTEA, xd_u8 SMUTER, xd_u8 FM_SMTH, xd_u8 VOLUMET);
#endif

bit KT_AM_TUNING_LIGHT(void);
bit KT_FM_TUNING_LIGHT(void);
bit KT_FM_ST_Indicator(void);

#ifdef AM_SOFTMUTE_AFCMODE
//void KT_AM_SOFTMUTE_AFCMODE(bit Valid);
void KT_AM_SOFTMUTE_AFCMODE(void);
void KT_AM_AFC_VolumeSet(xd_u8 afc);			//Input: 0~128
#endif

void KT_Bus_Write(xd_u8 Register_Address, xd_u16 Word_Data);
xd_u16 KT_Bus_Read(xd_u8 Register_Address);

#endif

