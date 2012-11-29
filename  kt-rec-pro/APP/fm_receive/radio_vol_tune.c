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

#include "fm_rev.h"

#if (FM_MODULE == 2)
#include "disp.h"
#include "key.h"
#include "msgfor_hot.h"
#include "main.h"
#include "fm_api.h"
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
u8 fre_channel; 			///<总台数
//u8 total_channel;///<当前频道
extern  bool vol_change_en;
extern u8 eq_mode;
extern u8 _xdata decode_buffer[];
#ifdef FAST_STICK_TUNE_FUNC
extern xd_u8 fast_step_cnt;
#endif


bool freq_step_flag=0;

xd_u8 sw_fm_mod=0,cur_sw_fm_band=0;
xd_u16 REG_MAX_FREQ=0,REG_MIN_FREQ=0;

xd_u8 am_adj_timer=0;
	
extern void KT_AMFMSetMode(xd_u8 AMFM_MODE);
extern void KT_FMTune(xd_u16 Frequency);
extern void KT_AMTune(xd_u16 Frequency);
extern xd_u8 KT_AMFMWakeUp(void); //0->Fail 1->Success
extern void KT_AMFMStandby(void);					//0->Fail 1->Success
extern xd_u8 KT_AMFMPreInit(void);			  
extern void KT_AMFMMute(void);


#if defined(SW_TWO_BAND_RANGE)
FREQ_RAGE _code radio_freq_tab[MAX_BAND]=
{
	875,		1080,
	520,		1630,
	3200,	17900,
	17905,	25000,
};
#elif defined(SW_FULL_BAND_RANGE)
FREQ_RAGE _code radio_freq_tab[MAX_BAND]=
{
	875,		1080,
	520,		1630,
	3200,	25000,
};
#elif defined(SW_FULL_BAND_RANGE_END_AT_23MHZ)
FREQ_RAGE _code radio_freq_tab[MAX_BAND]=
{
	875,		1080,
	520,		1630,
	3200,	23000,
};
#else
FREQ_RAGE _code radio_freq_tab[MAX_BAND]=
{
	875,		1080,
	520,		1630,
	3200,	5200,
	5210,	7300,
	7310,	9400,
	9410,	11500,
	11510,	13800,
	13810,	15800,
	15810,	17900,
	17910,	22000,
	22010,	23000,
	//23010,	25000,
};
#endif

void radio_band_hdlr()
{
	REG_MAX_FREQ = radio_freq_tab[cur_sw_fm_band].MAX_FREQ;
	REG_MIN_FREQ = radio_freq_tab[cur_sw_fm_band].MIN_FREQ;

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
        
        case MSG_CHANGE_WORK_MODE:
            return;
        case MSG_MUSIC_NEW_DEVICE_IN:							//有新设备接入
            //work_mode = MUSIC_MODE;
            break;
            //return;
        case MSG_200MS:

	     break;		 
        case MSG_HALF_SECOND:
#if defined(USE_BAT_MANAGEMENT)			
	     bmt_hdlr();
#endif

	     set_brightness_fade_out();
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
	uart_init();
	deg_str("fm_radio \n");
#endif

    flush_all_msg();

    amux_dsp_eq();

    SYSTEM_CLK_DIV2();

    if (KT_AMFMWakeUp()==0)
    {
#if 0
    	   work_mode = MUSIC_MODE;
	   return;
#endif
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
