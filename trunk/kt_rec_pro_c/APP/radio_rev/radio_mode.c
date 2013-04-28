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

#if (FM_MODULE == 1)
#include "disp.h"
#include "key.h"
#include "msgfor_hot.h"
#include "main.h"
#include "radio_api.h"
#include "dac.h"
#include "rtc_api.h"
#include "eq.h"
#include "KT_radio_drv.h"


extern RADIO_MODE_VAR  radio_band;

extern bool input_number_en;
extern xd_u8 main_menu, cur_menu, main_menu_conter;
extern xd_u16 input_number;
extern u8 work_mode;
extern xd_u8 scan_mode;
//extern xd_u8 am_adj_timer;
extern xd_u8 radio_scan_safeguard;
extern u8 _idata last_work_mode;
extern  bool vol_change_en;
extern  bool freq_step_flag;
extern  bool sys_mute_flag;
extern  xd_u16 freq_reg_stop;
extern  xd_u8 sys_main_vol;

xd_u8 sw_fm_mod=0;
extern void sw_auto_gain_hdlr(void);

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


   put_msg_lifo(MSG_RADIO_DEVICE_INIT);

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
        case MSG_RADIO_DEVICE_INIT:

	     set_adc_mode_protect(PROTECT);
	     if(radio_device_init()==0){
    			disp_port(MENU_REC_ERR);			
			delay_10ms(20);
	     }
	     else{
		   radio_band_switcher();		 	
		   set_radio_freq(RADIO_CUR_FRE);
    		   SYSTEM_CLK_DIV4();
		   dac_mute_control(0,1);	   	   
		   sys_dac_mute(DAC_UNMUTE);
    		   set_max_vol(MAX_ANOLOG_VOL,MAX_DIGITAL_VOL);///设置最大音量
	     }
	     set_adc_mode_protect(UNPROTECT);
            main_vol_set(sys_main_vol, CHANGE_VOL_MEM);
		 
	     flush_all_msg();						  	 
	     break;
		 
        case MSG_CHANGE_RADIO_MODE:
	     set_adc_mode_protect(PROTECT);			
	     radio_band_switcher();
	     set_adc_mode_protect(UNPROTECT);
	     break;
        case MSG_CHANGE_WORK_MODE:
            return;
        case MSG_MUSIC_NEW_DEVICE_IN:							//有新设备接入
            break;
			
#ifdef SEMI_AUTO_SCAN_FUNC

        case MSG_RADIO_SCAN_ALL:	
		if(scan_mode == RADIO_SCAN_STOP){

			input_number_en = 0;
    			vol_change_en=0;				
			radio_band.bTotalChannel =1;
	              scan_mode = RADIO_SCAN_ALL;			
	     		radio_band.wFreq = radio_band.wFreqDownLimit-radio_band.bTuneStep;	
            		put_msg_lifo(MSG_RADIO_SCAN_RUNNING);
		}
		else{

			if((scan_mode == RADIO_SCAN_NEXT)||(scan_mode == RADIO_SCAN_PREV)){
				freq_reg_stop = radio_band.wFreq;
				radio_freq_auto_align();					
	            		put_msg_lifo(MSG_RADIO_SCAN_RUNNING);
			}
			else{
	    			flush_all_msg();
				radio_all_scan_stop();  
			}
		}			
		break;
        case MSG_RADIO_SCAN_RUNNING:
			   	
		if (radio_band_scan(scan_mode))
	       {
	             	if(scan_mode==RADIO_SCAN_STOP){
		    		flush_all_msg();						  	
				radio_all_scan_stop();
                    		break;							 
			}
		}
            	put_msg_fifo(MSG_RADIO_SCAN_RUNNING);
		break;		
        case SEMI_AUTO_SCAN_KEY_UP:			
            	scan_mode = RADIO_SCAN_NEXT;		
            	put_msg_lifo(MSG_RADIO_SCAN_ALL);
		break;
        case SEMI_AUTO_SCAN_KEY_DOWN:			
            	scan_mode = RADIO_SCAN_PREV;		
            	put_msg_lifo(MSG_RADIO_SCAN_ALL);
		break;	
#endif
        case MSG_MUSIC_NEXT_FILE:
		freq_step_flag=1;
        case MSG_FM_NEXT_STEP:
    		set_radio_freq(RADIO_FRE_INC);
		break;
	 case MSG_MUSIC_PREV_FILE:
		freq_step_flag=1;	 	
        case MSG_FM_PREV_STEP:
    	     set_radio_freq(RADIO_FRE_DEC);
	     break;		 
        case MSG_HALF_SECOND:
#if defined(USE_BAT_MANAGEMENT)			
	     bmt_hdlr();
#endif

#if 0
    	 if(radio_band.bCurBand>0){

		     if(am_adj_timer>0){
				am_adj_timer--;
				if(am_adj_timer==0){
			    		set_radio_freq(FM_CUR_FRE);
				}
		     }
	     }
#endif		 
#if 1
		if(scan_mode == RADIO_SCAN_STOP)
			sw_auto_gain_hdlr();
#endif

#ifdef SEMI_AUTO_SCAN_FUNC
		if(scan_mode != RADIO_SCAN_STOP){
				
			if(radio_scan_safeguard>0){
				radio_scan_safeguard--;
				if(radio_scan_safeguard==1){
	            			put_msg_lifo(MSG_RADIO_SCAN_RUNNING);
				}
			}
		}
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
            		if(radio_band.bCurBand>1){
				input_number = input_number*10;
			}
            	 	if ((input_number <= radio_band.wFreqUpLimit) && (input_number >=radio_band.wFreqDownLimit)){

		        	radio_band.wFreq =input_number;
			    	set_radio_freq(RADIO_CUR_FRE);
			}
			else{
	     			disp_port(MENU_REC_ERR);
			}
            }	
#endif			
            else if (cur_menu != main_menu)
            {
    			disp_port(MENU_RADIO_MAIN);
	     }
	     if(RECODE_WORKING == encode_status)
            {
     			disp_port(MENU_RADIO_MAIN);
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
void radio_rev_init()
{
#ifdef UART_ENABLE
	uart_init();
	deg_str("fm_radio \n");
#endif
    	dac_mute_control(1,1);	   
    	amux_dsp_eq();
    	SYSTEM_CLK_DIV2();

#if 0
   	 if (KT_AMFMWakeUp()==0)
    	{
#if 0
    	   work_mode = MUSIC_MODE;
	   return;
#endif
   	}
#endif
       sys_mute_flag=0;
    	input_number_en = 1;
#ifdef NO_VOL_TUNE_FUNC	
    	vol_change_en=0;
#else		
    	vol_change_en=1;
#endif
    	main_menu = MENU_RADIO_MAIN;

    	radio_info_pre_init();
		
    	encode_channel = REC_FM;
    	encode_vol = 3;
	
}
void radio_rev_exit(void)
{
    	main_vol_set(0, CHANGE_VOL_NO_MEM);
	radio_device_standby();
	break_encode();
}
void radio_main_hdlr(void)
{
    	radio_rev_init();
    	radio_rev_hdlr();
    	radio_rev_exit();
}
#endif
