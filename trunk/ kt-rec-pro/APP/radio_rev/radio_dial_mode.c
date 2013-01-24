/*--------------------------------------------------------------------------*/
/**@file    fm_receive.c
   @brief   FM接收任务模块
   @details
   @author
   @date   2011-3-7
   @note
*/
/*----------------------------------------------------------------------------*/
#include "Custom_config.h"
#include "config.h"

#if (FM_MODULE == 2)
#include "radio_rev.h"
#include "disp.h"
#include "key.h"
#include "msgfor_hot.h"
#include "main.h"
#include "radio_api.h"
#include "dac.h"
#include "rtc_api.h"
#include "eq.h"



extern bool input_number_en;
extern u8 main_menu, cur_menu, main_menu_conter;
extern u16 input_number;
extern u8 work_mode;
extern u8 _idata last_work_mode;

extern u8 fm_addr;
//extern u8 _code one_table[];
u16 frequency;                          ///<当前频点
//u8 total_channel;///<当前频道
extern  bool vol_change_en;

xd_u16 freq_regx=0;

xd_u8 sw_fm_mod=0,cur_sw_fm_band=0;
xd_u16 REG_MAX_FREQ=0,REG_MIN_FREQ=0,REG_STEP=0;
	
extern void KT_AMFMSetMode(xd_u8 AMFM_MODE);
extern xd_u8 KT_AMFMWakeUp(void); //0->Fail 1->Success
extern void KT_AMFMStandby(void);					//0->Fail 1->Success
extern xd_u8 KT_AMFMPreInit(void);			  
extern xd_u16 KT_FMGetFreq(void);
extern xd_u16 KT_AMGetFreq(void);


#if defined(SW_TWO_BAND_RANGE)
FREQ_RAGE _code radio_freq_tab[MAX_BAND]=
{
	875,		1080,	5,
	//520,		1630,	10,
	522,		1620,	9,
	3200,	17900,	10,
	17905,	25000,	10,
};
#elif defined(SW_FULL_BAND_RANGE)
FREQ_RAGE _code radio_freq_tab[MAX_BAND]=
{
	875,		1080,	5,
	//520,		1630,	10,
	522,		1620,	9,	
	3200,	25000,	10,
};
#elif defined(SW_FULL_BAND_RANGE_END_AT_23MHZ)
FREQ_RAGE _code radio_freq_tab[MAX_BAND]=
{
	875,		1080,	5,
	//520,		1630,	10,
	522,		1620,	9,	
	3200,	23000,	10,
};
#else
FREQ_RAGE _code radio_freq_tab[MAX_BAND]=
{
	875,		1080,	5,
	//520,		1630,	10,
	522,		1620,	9,		
	3200,	5200,	1,
	5210,	7300,	1,
	7310,	9400,	1,
	9410,	11500,	1,
	11510,	13800,	1,
	13810,	15800,	1,
	15810,	17900,	1,
	17910,	22000,	1,
	22010,	23000,	1,
	//23010,	25000,
};
#endif

u16 get_radio_freq()
{
	if(cur_sw_fm_band==0){
		return KT_FMGetFreq();
	}
	else{
		return KT_AMGetFreq();
	}
}
void radio_band_hdlr()
{

	REG_MAX_FREQ = radio_freq_tab[cur_sw_fm_band].MAX_FREQ;
	REG_MIN_FREQ = radio_freq_tab[cur_sw_fm_band].MIN_FREQ;

	REG_STEP=radio_freq_tab[cur_sw_fm_band].FREQ_STEP;
	
	KT_AMFMSetMode(cur_sw_fm_band);	

	delay_10ms(10);
	frequency=get_radio_freq();

	disp_port(MENU_FM_MAIN);			
#ifdef UART_ENABLE
	deg_str("radio_band_hdlr \n");
	printf_u16(cur_sw_fm_band,'B');
	printf_u16(REG_MAX_FREQ,'-');
	printf_u16(REG_MIN_FREQ,'-');
#endif
	
}
void radio_rev_hdlr( void )
{
    u8 key;

    while (1)
    {

#if defined(EXCHANGE_AUX_CHANNEL)
        dac_out_select(DAC_AMUX1, 0);
#else
        dac_out_select(DAC_AMUX0, 0);
#endif
        key = app_get_msg();

        switch (key)
        {
        case MSG_CHANGE_FM_MODE:
	     radio_band_hdlr();
	     break;        
        case MSG_CHANGE_WORK_MODE:
            return;

        case MSG_MUSIC_NEW_DEVICE_IN:							//有新设备接入
            break;

        case MSG_200MS:
			
	     freq_regx=get_radio_freq();
#ifdef UART_ENABLE
			//printf_u16(freq_regx,'F');
#endif

	     if(freq_regx!=frequency){

			frequency=freq_regx;
    			disp_port(MENU_FM_MAIN);			
	     }
	     break;		 
        case MSG_HALF_SECOND:
#if defined(USE_BAT_MANAGEMENT)			
	     bmt_hdlr();
#endif
#ifdef UART_ENABLE
		//deg_str("MSG_HALF_SECOND \n");
#endif

#ifndef LCD_BACK_LIGHT_DUMMY
	     set_brightness_fade_out();
#endif
            if (main_menu_conter < (SUB_MENU_TIME - 3))
            {
                	main_menu_conter++;
            }

            else if (cur_menu != main_menu)
            {
    			disp_port(MENU_FM_MAIN);
	     }
	     if(RECODE_WORKING == encode_status)
            {
     			disp_port(MENU_FM_MAIN);
		   //disp_port(MENU_RECWORKING); 
            }				
            break;
        default :
            ap_handle_hotkey(key);
            break;
        }
    }
}

/*----------------------------------------------------------------------------*/
/**@brief FM模式入口函数
   @param 	无
   @return  无
   @note  void fm_radio(void)
*/
/*----------------------------------------------------------------------------*/
void radio_hdlr(void)
{

#ifdef UART_ENABLE
	deg_str("fm_radio \n");
#endif

    flush_all_msg();

    amux_dsp_eq();

    SYSTEM_CLK_DIV2();

    if (KT_AMFMWakeUp()==0)
    {
		disp_port(MENU_REC_ERR);
		delay_10ms(100);
    }

    input_number_en = 1;
    vol_change_en=1;
    main_menu = MENU_FM_MAIN;
    radio_band_hdlr();

    SYSTEM_CLK_DIV4();
    set_max_vol(MAX_ANOLOG_VOL,MAX_DIGITAL_VOL);///设置最大音量

    encode_channel = REC_FM;
    encode_vol = 3;
    radio_rev_hdlr();
    main_vol_set(0, CHANGE_VOL_NO_MEM);

    KT_AMFMStandby();

    break_encode();
	
}

#endif
