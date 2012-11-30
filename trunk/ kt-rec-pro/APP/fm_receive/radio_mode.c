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

#if (FM_MODULE == 1)
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

u16 frequency;                          ///<当前频点

extern  bool vol_change_en;
extern u8 eq_mode;
extern u8 _xdata decode_buffer[];
#ifdef FAST_STICK_TUNE_FUNC
extern xd_u8 fast_step_cnt;
#endif


bool freq_step_flag=0;

xd_u8 sw_fm_mod=0,cur_sw_fm_band=0;
xd_u16 REG_MAX_FREQ=0,REG_MIN_FREQ=0,REG_STEP;

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
   xd_u8 freq_step =0;
   
    set_brightness_all_on();
#if defined(FAST_STICK_TUNE_FUNC)

	  // EA =0;
	    if(fast_step_cnt==0){
			fast_step_cnt=1;
	    }
		
	    if(cur_sw_fm_band==0){
			
			freq_step =1*fast_step_cnt; 
	    }
	    else if(cur_sw_fm_band==1){

			if(freq_step_flag){
				freq_step = 10;
				freq_step_flag=0;				
			}
			else{
				freq_step = 1*fast_step_cnt;
			}
	    }
	    else{
			if(freq_step_flag==1){
				freq_step = 10;
				freq_step_flag=0;				
			}
			else{				
				freq_step = 5*fast_step_cnt;
			}
	   }

#if 1

	if(fast_step_cnt>3){
		am_adj_timer=2;
	}
#endif
	//EA =1;		
#else
    if(cur_sw_fm_band==0){
		
		freq_step =1; 
    }
    else if(cur_sw_fm_band==1){
		if(freq_step_flag){
			freq_step_flag=0;			
			freq_step = 10;
		}
		else{
			freq_step = 1;
		}
    }
    else{
	
		freq_step = 5;
    }	
#endif
	
    if (mode == FM_FRE_INC)
    {
        frequency=frequency+freq_step;
    }
    else if (mode == FM_FRE_DEC)
    {
        frequency=frequency-freq_step;
    }
	
    if (frequency > REG_MAX_FREQ)
        frequency = REG_MAX_FREQ;
	
    if (frequency < REG_MIN_FREQ)
        frequency =REG_MIN_FREQ;

    if(cur_sw_fm_band==0){

		KT_FMTune(frequency*10);
    }
    else{

		if(am_adj_timer<2)	
			KT_AMTune(frequency);
		//else
		//	KT_AMFMMute();
    }
    disp_port(MENU_FM_MAIN);			

#ifdef SAVE_BAND_FREQ_INFO	
    save_radio_freq(frequency,cur_sw_fm_band);
#endif
}
void radio_band_hdlr()
{
	REG_MAX_FREQ = radio_freq_tab[cur_sw_fm_band].MAX_FREQ;
	REG_MIN_FREQ = radio_freq_tab[cur_sw_fm_band].MIN_FREQ;
#ifdef SAVE_BAND_FREQ_INFO	
	frequency = read_radio_freq(cur_sw_fm_band);
	if (frequency > REG_MAX_FREQ)
        	frequency = REG_MIN_FREQ;
    	if (frequency < REG_MIN_FREQ)
        	frequency =REG_MIN_FREQ;
#endif
	KT_AMFMSetMode(cur_sw_fm_band);	

    	set_radio_freq(FM_CUR_FRE);
}
/*----------------------------------------------------------------------------*/
/**@brief  获取FM任务的信息
   @param  无
   @return 无
   @note   void enter_fm_rev(void)
*/
/*----------------------------------------------------------------------------*/
//void enter_fm_rev(void)
//{
   // frequency = read_info(MEM_FRE);
   // if (frequency > (1085-875))
   // {
        //frequency = MIN_FRE;
 //   }
    //else
  //  {
        //frequency += MIN_FRE;
  //  }
   // radio_band_hdlr();
    //set_radio_freq(FM_CUR_FRE);
//}
/*----------------------------------------------------------------------------*/
/**@brief  FM任务函数
   @param  无
   @return 无
   @note   void fm_rev( void )
*/
/*----------------------------------------------------------------------------*/
void radio_rev_hdlr( void )
{
    u8 key;

    set_radio_freq(FM_CUR_FRE);

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
            //work_mode = MUSIC_MODE;
            break;
            //return;
        case MSG_MUSIC_FF:
	 	am_adj_timer=2;			
        case MSG_MUSIC_NEXT_FILE:
		freq_step_flag=1;
        case MSG_FM_NEXT_STEP:
    		set_radio_freq(FM_FRE_INC);
		//disp_port(MENU_FM_MAIN);
		break;
	 case MSG_MUSIC_FR:
	 	am_adj_timer=2;
	 case MSG_MUSIC_PREV_FILE:
		freq_step_flag=1;	 	
        case MSG_FM_PREV_STEP:
    	     set_radio_freq(FM_FRE_DEC);
	    //disp_port(MENU_FM_MAIN);			
	     break;		 
        case MSG_HALF_SECOND:
#if defined(USE_BAT_MANAGEMENT)			
	     bmt_hdlr();
#endif

#if 1
    	 if(cur_sw_fm_band>0){

		     if(am_adj_timer>0){
				am_adj_timer--;
				if(am_adj_timer==0){
			    		set_radio_freq(FM_CUR_FRE);
				}
		     }
	     }
#endif		 
	     set_brightness_fade_out();
            if (main_menu_conter < (SUB_MENU_TIME - 3))
            {
                	main_menu_conter++;
            }
#ifdef FM_FREQ_NUM_KEY_INPUT			
            else if (cur_menu == MENU_INPUT_NUMBER)			//数字输入模式
            {
            		if(cur_sw_fm_band>1){
				input_number = input_number*10;
			}
            	 	if ((input_number <= REG_MAX_FREQ) && (input_number >=REG_MIN_FREQ)){

		        	frequency =input_number;
			    	set_radio_freq(FM_CUR_FRE);
			}
			else{
	     			disp_port(MENU_REC_ERR);
			}
            }	
#endif			
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
   // disp_port(MENU_FM_MAIN);
    SYSTEM_CLK_DIV4();
    set_max_vol(MAX_ANOLOG_VOL,MAX_DIGITAL_VOL);///设置最大音量
	//dac_out_select(DAC_AMUX1, 0);
    encode_channel = REC_FM;
    encode_vol = 3;
    radio_rev_hdlr();
    main_vol_set(0, CHANGE_VOL_NO_MEM);

    KT_AMFMStandby();
    //fm_rev_powerdown();
    //P05_source_select(P05_SEL_IO);
    break_encode();
	
}

#endif
