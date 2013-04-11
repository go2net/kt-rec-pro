/*--------------------------------------------------------------------------*/
/**@file     fm_receive_api.c
   @brief    FM任务应用接口
   @details
   @author
   @date   2011-3-7
   @note
*/
/*----------------------------------------------------------------------------*/

#include "Custom_config.h"

#include "dac.h"
#include "radio_api.h"
#include "radio_rev.h"
#include "KT_radio_drv.h"
#include "msgfor_hot.h"

RADIO_MODE_VAR  radio_band;

#if (FM_MODULE == 1)

//xd_u8 am_adj_timer=0;
xd_u8 scan_mode=RADIO_SCAN_STOP;
bool freq_step_flag=0;

extern bool input_number_en;
extern  bool vol_change_en;
extern  bool sys_mute_flag;
extern xd_u8 fast_step_cnt;

extern u8 KT_FMValidStation(u16 Frequency);
extern u8 KT_AMValidStation(u16 Frequency);
extern u8 KT_SMValidStation(u16 Frequency);
extern void KT_AMFMSetMode(u8 AMFM_MODE);
extern void KT_FMTune(u16 Frequency);
extern void KT_AMTune(u16 Frequency);
extern u8 KT_AMFMWakeUp(void); //0->Fail 1->Success
extern void KT_AMFMStandby(void);					//0->Fail 1->Success
extern void KT_AMFMMute(void);
extern void KT_Mute_Ctrl(bool m_f);
extern void load_band_info(u8 cur_band);

#if defined(SW_TWO_BAND_RANGE)
FREQ_RAGE _code radio_freq_tab[MAX_BAND]=
{
	8750,	10800, 	10,
	520,		1630, 	10,
	3200,	17900, 	5,
	17905,	25000,	5,
};
#elif defined(SW_TWO_BAND_RANGE_FOR_CUSTOMER_JIN_FENG)
FREQ_RAGE _code radio_freq_tab[MAX_BAND]=
{
	8750,	10800,	10,
	520,		1630,	10,
	3500,	7800,	5,
	8000,	20500,	5,
};
#elif defined(SW_FULL_BAND_RANGE)
FREQ_RAGE _code radio_freq_tab[MAX_BAND]=
{
	8750,	10800,	10,
	520,		1630,	10,
	3200,	25000,	1,
};
#elif defined(SW_FULL_BAND_RANGE_END_AT_23MHZ)
FREQ_RAGE _code radio_freq_tab[MAX_BAND]=
{
	8750,	10800,	10,
	520,		1630,	10,
	3200,	23000,	5,
};
#else
FREQ_RAGE _code radio_freq_tab[MAX_BAND]=
{
	8750,	10800,	10,
	520,		1630,	10,
	3200,	5200,	5,
	5210,	7300,	5,
	7310,	9400,	5,
	9410,	11500,	5,
	11510,	13800,	5,
	13810,	15800,	5,
	15810,	17900,	5,
	17910,	22000,	5,
	22010,	23000,	5,
	//23010,	25000,
};
#endif

bool radio_device_init(void)
{
	return (KT_AMFMWakeUp());
}
void radio_device_standby(void)
{
    	KT_AMFMStandby();
}

void radio_info_pre_init(void)
{
	if(radio_band.bCurBand>((sizeof(radio_freq_tab)/6)-1)){
		
		radio_band.bCurBand = FM_MODE;
	}
	radio_band.wFreqUpLimit = radio_freq_tab[radio_band.bCurBand].MAX_FREQ;
	radio_band.wFreqDownLimit = radio_freq_tab[radio_band.bCurBand].MIN_FREQ;
	radio_band.bTuneStep  = radio_freq_tab[radio_band.bCurBand].FREQ_STEP;
	

	if (radio_band.wFreq > radio_band.wFreqUpLimit)
        	radio_band.wFreq = radio_band.wFreqDownLimit;
	
    	if (radio_band.wFreq < radio_band.wFreqDownLimit)
        	radio_band.wFreq =radio_band.wFreqDownLimit;

    disp_port(MENU_RADIO_MAIN);			
    scan_mode = RADIO_SCAN_STOP;
}

#ifdef SAVE_BAND_FREQ_INFO
void save_radio_freq(u16 radio_freq,u8 ch)
{
	xd_u8 freq_reg=0;
	
	ch=ch<<1;
	freq_reg =(u8)radio_freq&(0x00FF);
	write_info(MEM_FM_CHANNL +ch , freq_reg);

	freq_reg =(u8)(radio_freq>>8);
	write_info(MEM_FM_CHANNL +ch+1, freq_reg);
}
u16 read_radio_freq(u8 ch)
{
	xd_u16 freq_reg=0;
	
	ch=ch<<1;

	freq_reg = read_info(MEM_FM_CHANNL +ch+1);
	freq_reg=freq_reg<<8;
	freq_reg |= read_info(MEM_FM_CHANNL +ch);
	return freq_reg;	
}
#endif

void set_radio_freq(u8 mode)
{
   	xd_u16 freq_step =0;
#ifndef LCD_BACK_LIGHT_DUMMY				   
    	set_brightness_all_on();
#endif

#if defined(FAST_STICK_TUNE_FUNC)

	 if(fast_step_cnt==0){
		fast_step_cnt=1;
	 }

    	if(radio_band.bCurBand<SW_MODE){

		if(fast_step_cnt<6)				
			freq_step = (radio_band.bTuneStep*fast_step_cnt);
		else if(fast_step_cnt<12)				
			freq_step = (radio_band.bTuneStep*fast_step_cnt*5);
    	}
	else{
		
		if(fast_step_cnt<6)				
			freq_step = (radio_band.bTuneStep*fast_step_cnt);
		else if(fast_step_cnt<12)				
			freq_step = (radio_band.bTuneStep*fast_step_cnt*10);
		else
			freq_step = (radio_band.bTuneStep*fast_step_cnt*20);
	}
#if 0
	if(fast_step_cnt>3){
		am_adj_timer=2;
	}
#endif

#endif
	
    if (mode == RADIO_FRE_INC)
    {
        radio_band.wFreq=radio_band.wFreq+freq_step;
    }
    else if (mode == RADIO_FRE_DEC)
    {
        radio_band.wFreq=radio_band.wFreq-freq_step;
    }
	
    if (radio_band.wFreq > radio_band.wFreqUpLimit)
        radio_band.wFreq = radio_band.wFreqUpLimit;
	
    if (radio_band.wFreq < radio_band.wFreqDownLimit)
        radio_band.wFreq =radio_band.wFreqDownLimit;

    if(radio_band.bCurBand==0){

#ifdef FM_SOFTMUTE
		KT_FM_SOFTMUTE(radio_band.wFreq);
#else
		KT_FMTune(radio_band.wFreq);
#endif

    }
    else{

#ifdef AM_SOFTMUTE
		KT_AM_SOFTMUTE(radio_band.wFreq);
#else
		KT_AMTune(radio_band.wFreq);
#endif

    }
	
    disp_port(MENU_RADIO_MAIN);			

#ifdef SAVE_BAND_FREQ_INFO	
    save_radio_freq(radio_band.wFreq,radio_band.bCurBand);
#endif
    flush_all_msg();
#ifdef SEMI_AUTO_SCAN_FUNC
    if(scan_mode!=RADIO_SCAN_STOP){
		radio_all_scan_stop();
    }
#endif
	
}

void radio_band_switcher(void)
{

#if 1
	if(radio_band.bCurBand>((sizeof(radio_freq_tab)/6)-1)){
		
		radio_band.bCurBand = FM_MODE;
	}
#endif	
	radio_band.wFreqUpLimit= radio_freq_tab[radio_band.bCurBand].MAX_FREQ;
	radio_band.wFreqDownLimit = radio_freq_tab[radio_band.bCurBand].MIN_FREQ;
	radio_band.bTuneStep= radio_freq_tab[radio_band.bCurBand].FREQ_STEP;
	
#ifdef SAVE_BAND_FREQ_INFO	
	radio_band.wFreq= read_radio_freq(radio_band.bCurBand);
	if (radio_band.wFreq > radio_band.wFreqUpLimit)
        	radio_band.wFreq = radio_band.wFreqDownLimit;
    	if (radio_band.wFreq < radio_band.wFreqDownLimit)
        	radio_band.wFreq =radio_band.wFreqDownLimit;
#endif

#ifdef USE_VALIDSTATION_CHECK
	load_band_info(radio_band.bCurBand);
#endif
    	disp_port(MENU_RADIO_MAIN);

	KT_AMFMSetMode(radio_band.bCurBand);

	set_radio_freq(RADIO_CUR_FRE);
}


#ifdef SEMI_AUTO_SCAN_FUNC
bool radio_get_validstation(u16 freq)
{
    if(radio_band.bCurBand==FM_MODE){
	return KT_FMValidStation(freq);
    }
    else if(radio_band.bCurBand==MW_MODE){
	return KT_AMValidStation(freq);
    }
    else{
	return KT_SMValidStation(freq);
    }
}

xd_u8 radio_scan_safeguard=0;
xd_u16 freq_reg_stop=0;

void radio_freq_auto_align(void)
{
	if(radio_band.bCurBand == MW_MODE){
		
		radio_band.wFreq = radio_band.wFreq -((radio_band.wFreq-radio_band.wFreqDownLimit)%radio_band.bTuneStep);
	}
}
void radio_all_scan_stop(void)
{
       radio_scan_safeguard=0;
	input_number_en = 1;
       vol_change_en=1;	
	sys_dac_mute(DAC_UNMUTE);
	scan_mode = RADIO_SCAN_STOP;
    	set_radio_freq(RADIO_CUR_FRE);			
}
bool radio_band_scan(u8 mode)
{
    bool res;

    input_number_en = 0;
    vol_change_en=0;	
    //adkey_activated=1;	  
    radio_scan_safeguard=3;
		
    dac_mute_control(1,1);
	
    if(mode == RADIO_SCAN_NEXT)
    {
        radio_band.wFreq=radio_band.wFreq+radio_band.bTuneStep;
		
	 if (radio_band.wFreq > radio_band.wFreqUpLimit)
	     radio_band.wFreq = radio_band.wFreqDownLimit;		

	 if(freq_reg_stop ==radio_band.wFreq ){

    		set_radio_freq(RADIO_CUR_FRE);			
	 	return 1;
	 }
    }
    else if (mode == RADIO_SCAN_PREV)
    {
        radio_band.wFreq=radio_band.wFreq-radio_band.bTuneStep;
		
	 if (radio_band.wFreq < radio_band.wFreqDownLimit)
	      radio_band.wFreq =radio_band.wFreqUpLimit;	

	 if(freq_reg_stop ==radio_band.wFreq ){

    		set_radio_freq(RADIO_CUR_FRE);			
	 	return 1;
	 }
    }
    else{
		
        radio_band.wFreq=radio_band.wFreq+radio_band.bTuneStep;
		
	 if(radio_band.wFreq > radio_band.wFreqUpLimit){
	     	radio_band.wFreq = radio_band.wFreqDownLimit;
		radio_band.bTotalChannel=radio_band.bTotalChannel-1;						  				
		//restore_station_from_epprom((RADIO_STATION_CURR|1));
		return 1;
	 }
    }

    disp_port(MENU_RADIO_MAIN);
		
    res = radio_get_validstation(radio_band.wFreq);

    //disp_port(MENU_RADIO_MAIN);			

    if (res)						//找到一个台
    {
#ifdef DEBUG_FM    	
	printf(" ---->KT  VALID  %d  \r\n ",(u16)radio_band.bTotalChannel);
	printf(" ---->OK OK   \r\n ");
	printf(" \r\n   \r\n ");
#endif
#if 0

       	if(mode==RADIO_SCAN_ALL){
				
#ifdef SAVE_BAND_FREQ_INFO	
			//mem_radio_info(RADIO_SAVE_STATION,&radio_band.wFreq,radio_band.bTotalChannel);
			//mem_radio_info(RADIO_SAVE_STATION_SUM,&radio_band.wFreq,0);
#endif
			dac_mute_control(0,1);
			disp_port(MENU_RADIO_SCAN_STATION);
			delay_10ms(100);
			if(radio_band.bTotalChannel ==MEM_RADIO_STATION_MAX){
				restore_station_from_epprom((RADIO_STATION_CURR|1));		
			}
			else{
				radio_band.bTotalChannel++;
			}
			dac_mute_control(1,1);
       	}
		else
#endif			
		{
       		scan_mode = RADIO_SCAN_STOP;
		}
#ifdef SAVE_BAND_FREQ_INFO	
    		save_radio_freq(radio_band.wFreq,radio_band.bCurBand);
#endif
		return true;            		
    }
	
    return false;
}
#endif





#endif

