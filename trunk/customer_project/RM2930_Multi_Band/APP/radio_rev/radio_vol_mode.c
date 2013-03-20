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

#include "radio_rev.h"

#if (FM_MODULE == 3)
#include "disp.h"
#include "key.h"
#include "msgfor_hot.h"
#include "main.h"
#include "radio_api.h"
#include "dac.h"
#include "rtc_api.h"
#include "eq.h"
#include "KT_radio_drv.h"



extern bool input_number_en;
extern u8 main_menu, cur_menu, main_menu_conter;
extern u16 input_number;
extern u8 work_mode;
extern u8 _idata last_work_mode;

u16 frequency;                          ///<当前频点

extern  bool vol_change_en;
extern u8 eq_mode;
extern u8 _xdata decode_buffer[];
extern u8 adc_tuner_volt;


//bool freq_step_flag=0;

#ifdef AUTO_PLAY_RADIO_REC_FILE
bool auto_play_radio_rec=0;
#endif

u16 freq_last=0;
bool band_select_en=0;
xd_u8 sw_band_div=0;

xd_u8 sw_fm_mod=0,cur_sw_fm_band=0;
xd_u16 REG_MAX_FREQ=0,REG_MIN_FREQ=0,REG_STEP=0;
	
extern void KT_AMFMSetMode(xd_u8 AMFM_MODE);
extern void KT_FMTune(xd_u16 Frequency);
extern void KT_AMTune(xd_u16 Frequency);
extern xd_u8 KT_AMFMWakeUp(void); //0->Fail 1->Success
extern void KT_AMFMStandby(void);					//0->Fail 1->Success
extern void KT_AMFMMute(void);
extern void sw_auto_gain_hdlr(void);



FREQ_RAGE _code radio_freq_tab[]=
{
	875,		1080,	1,
	522,		1620,	9,
	3200,	4450,	5,
	4450,	5700,	5,
	5700,	6950,	5,
	6950,	8200,	5,
	8200,	9450,	5,
	9450,	10700,	5,
	10700,	11950,	5,
	11950,	13200,	5,
	13200,	14450,	5,
	14450,	15700,	5,
	15700,	16950,	5,
	16950,	18200,	5,
	18200,	19450,	5,
	19450,	20700,	5,
};

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
#ifndef LCD_BACK_LIGHT_DUMMY				   
    set_brightness_all_on();
#endif
		
    if (frequency > REG_MAX_FREQ)
        frequency = REG_MAX_FREQ;
	
    if (frequency < REG_MIN_FREQ)
        frequency =REG_MIN_FREQ;

    if(cur_sw_fm_band==0){

		KT_FMTune(frequency*10);
    }
    else{
		KT_AMTune(frequency);
    }
	
    disp_port(MENU_FM_MAIN);			

#if 0//def SAVE_BAND_FREQ_INFO	
    save_radio_freq(frequency,cur_sw_fm_band);
#endif
}

void band_select_hdlr(u8 key)
{
	if(!band_select_en)return;
		band_select_en = 0;
		
	if(key==BAND_NEXT){

		sw_band_div++;
		if(sw_band_div>(((sizeof(radio_freq_tab))/6)-1)){
			sw_band_div = 2;
		}
     		//printf_u16((((sizeof(radio_freq_tab))/6)-2),'A');
     		//printf_u16(sw_band_div,'A');

	}
	else{

		if(sw_band_div>2){
			sw_band_div--;
		}
		else{
			sw_band_div = (u8)(((sizeof(radio_freq_tab))/6)-1);
		}
     		//printf_u16((((sizeof(radio_freq_tab))/6)-2),'M');
		// printf_u16(sw_band_div,'M');

	}

	delay_10ms(20);
	put_msg_fifo(MSG_CHANGE_FM_MODE);

}
void mcu_vol_tuner_hdlr()
{
	u8 tune_step=0;
	
	if(cur_sw_fm_band == 0){

		if(adc_tuner_volt>20){
			tune_step = adc_tuner_volt-20;
		}
	}
	else if(cur_sw_fm_band == 1){
		tune_step = adc_tuner_volt/2;
	}
	else{
		tune_step = adc_tuner_volt;
	}

	freq_last = (tune_step*REG_STEP)+REG_MIN_FREQ;

	if(freq_last > REG_MAX_FREQ){

		freq_last = REG_MAX_FREQ;
	}

     //	printf_u16(adc_tuner_volt,'V');

	if(freq_last != frequency){
#if 0
	     	printf_u16(freq_last,'L');
	     	printf_u16(frequency,'F');
#endif			
		frequency = freq_last;
    		set_radio_freq(FM_CUR_FRE);
	}
}

void radio_band_hdlr()
{
	u8 band_reg=0;
	if(cur_sw_fm_band ==SW_MODE){
		
		band_select_en = 1;
			
		if(sw_band_div>(((sizeof(radio_freq_tab))/6)-1)){
			sw_band_div = 2;
		}		

		if(sw_band_div<2){
			sw_band_div = 2;
		}		

		band_reg = sw_band_div;
    		save_radio_freq(sw_band_div,MEM_VOL_BAND);
		//printf_u16(sw_band_div,'B');			
	}
	else{

		band_select_en = 0;	
		band_reg = cur_sw_fm_band;
	}

	//printf_u16(cur_sw_fm_band,'B');

	REG_STEP = radio_freq_tab[band_reg].FREQ_STEP;
	REG_MAX_FREQ = radio_freq_tab[band_reg].MAX_FREQ;
	REG_MIN_FREQ = radio_freq_tab[band_reg].MIN_FREQ;
	
#if 0//def SAVE_BAND_FREQ_INFO	
	frequency = read_radio_freq(sw_band_div);
	if (frequency > REG_MAX_FREQ)
        	frequency = REG_MIN_FREQ;
    	if (frequency < REG_MIN_FREQ)
        	frequency =REG_MIN_FREQ;
#endif

	KT_AMFMSetMode(cur_sw_fm_band);	

	frequency = 0;
	mcu_vol_tuner_hdlr();

    	//set_radio_freq(FM_CUR_FRE);
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

    //set_radio_freq(FM_CUR_FRE);
	mcu_vol_tuner_hdlr();

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
        case MSG_200MS:
	     mcu_vol_tuner_hdlr();
	     break;        
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
        case MSG_MUSIC_NEXT_FILE:
		//freq_step_flag=1;
        case MSG_FM_NEXT_STEP:
		band_select_hdlr(BAND_NEXT);
    		//set_radio_freq(FM_FRE_INC);
		//disp_port(MENU_FM_MAIN);
		break;
	 case MSG_MUSIC_FR:
	 case MSG_MUSIC_PREV_FILE:
        case MSG_FM_PREV_STEP:
		band_select_hdlr(BAND_PREV);
    	     //set_radio_freq(FM_FRE_DEC);
	    //disp_port(MENU_FM_MAIN);			
	     break;		 
        case MSG_HALF_SECOND:
#if defined(USE_BAT_MANAGEMENT)			
	     bmt_hdlr();
#endif

#if 1
		sw_auto_gain_hdlr();
#endif
#ifndef LCD_BACK_LIGHT_DUMMY
	     set_brightness_fade_out();
#endif
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

    sw_band_div = read_radio_freq(MEM_VOL_BAND);
	
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
