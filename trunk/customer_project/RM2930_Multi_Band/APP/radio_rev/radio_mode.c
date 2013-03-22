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



extern bool input_number_en;
extern u8 main_menu, cur_menu, main_menu_conter;
extern u16 input_number;
extern u8 work_mode;
extern u8 _idata last_work_mode;

RADIO_MODE_VAR _data radio_band;

extern  bool vol_change_en;
extern xd_u8 P2IE_REG;

extern u8 _xdata decode_buffer[];

extern xd_u8 fast_step_cnt;

u8 scan_mode=RADIO_SCAN_STOP;

#if defined(FAST_STICK_TUNE_FUNC)
bool freq_step_flag=0;
#endif

#ifdef AUTO_PLAY_RADIO_REC_FILE
bool auto_play_radio_rec=0;
#endif

xd_u8 am_adj_timer=0;
#ifdef USE_VALIDSTATION_CHECK
extern Str_Band  Current_Band;
extern xd_u8 KT_FMValidStation(xd_u16 Frequency);
extern xd_u8 KT_AMValidStation(xd_u16 Frequency);
extern xd_u8 KT_SMValidStation(xd_u16 Frequency);
extern void KT_Mute_Ctrl(bool m_f);
void load_band_info(u8 cur_band);
#endif
	
extern void KT_AMFMSetMode(xd_u8 AMFM_MODE);
extern void KT_FMTune(xd_u16 Frequency);
extern void KT_AMTune(xd_u16 Frequency);
extern xd_u8 KT_AMFMWakeUp(void); //0->Fail 1->Success
extern void KT_AMFMStandby(void);					//0->Fail 1->Success
extern void KT_AMFMMute(void);
extern void sw_auto_gain_hdlr(void);


#if defined(SW_TWO_BAND_RANGE)
FREQ_RAGE _code radio_freq_tab[MAX_BAND]=
{
	8750,	10800, 10,
	520,		1630,   10,
	3200,	17900,  5,
	17905,	25000,  5,
};
#elif defined(SW_TWO_BAND_RANGE_FOR_CUSTOMER_JIN_FENG)
FREQ_RAGE _code radio_freq_tab[MAX_BAND]=
{
	8750,	10800,10,
	520,		1630,  10,
	3500,	7800,   5,
	8000,	20500, 5,
};
#elif defined(SW_FULL_BAND_RANGE)
FREQ_RAGE _code radio_freq_tab[MAX_BAND]=
{
	8750,	10800, 10,
	520,		1630,   10,
	3200,	25000,  5,
};
#elif defined(SW_FULL_BAND_RANGE_END_AT_23MHZ)
FREQ_RAGE _code radio_freq_tab[MAX_BAND]=
{
	8750,	10800, 10,
	520,		1630,   10,
	3200,	23000,  5,
};
#else
FREQ_RAGE _code radio_freq_tab[MAX_BAND]=
{
	8750,	10800,   10,
	520,		1630,     10,
	3200,	5200,     5,
	5210,	7300,     5,
	7310,	9400,     5,
	9410,	11500,    5,
	11510,	13800,    5,
	13810,	15800,    5,
	15810,	17900,    5,
	17910,	22000,    5,
	22010,	23000,    5,
	//23010,	25000,
};
#endif

#ifdef SAVE_BAND_FREQ_INFO
#if 0
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
void mem_radio_info(RADIO_STORE_CMD SAVE_CMD,u16 *RADIO_DATA,u8 RADIO_VALID_CH)
{
	u16 read_reg=0;
	u16 save_reg=0;
	
	switch(SAVE_CMD)
	{
//4 READ HANDLR	
	 case RADIO_READ_FREQ:
		if(radio_band.bCurBand<=MW_MODE ){	 	
	 		read_reg = read_info(MEM_RADIO_FREQ_BASE +radio_band.bCurBand);

		}
		else{
	 		read_reg = read_info(MEM_RADIO_FREQ_BASE +(radio_band.bCurBand-1)*2);
			read_reg=read_reg<<8;
	 		read_reg |= read_info(MEM_RADIO_FREQ_BASE +(radio_band.bCurBand-1)*2+1);
		}
		*RADIO_DATA = (read_reg*radio_band.bTuneStep)+radio_band.wFreqDownLimit;
	 	break;
	 case RADIO_READ_BAND:
	 	*RADIO_DATA = read_info(MEM_RADIO_BAND_CHAN);	 	
	 	break;
	 case RADIO_READ_STATION_SUM:
	 	*RADIO_DATA = read_info(MEM_RADIO_FM_TOTAL_STATION+(radio_band.bCurBand));	 	
	 	break;	 	
	 case RADIO_READ_STATION:
		if(radio_band.bCurBand<=MW_MODE ){	 	
			read_reg = read_info(MEM_RADIO_STATION_BASE+(radio_band.bCurBand*MEM_RADIO_STATION_MAX)+RADIO_VALID_CH);	
		}
		else{			
			read_reg = read_info(MEM_RADIO_STATION_BASE+(radio_band.bCurBand*MEM_RADIO_STATION_MAX)+RADIO_VALID_CH*2);	
			read_reg=read_reg<<8;
			read_reg = read_info(MEM_RADIO_STATION_BASE+(radio_band.bCurBand*MEM_RADIO_STATION_MAX)+RADIO_VALID_CH*2+1);	
		}
		*RADIO_DATA = (read_reg*radio_band.bTuneStep)+radio_band.wFreqDownLimit;
	 	break;	 	


//4 SAVE HANDLR		
	 case RADIO_SAVE_FREQ:
	 	save_reg = ((*RADIO_DATA - radio_band.wFreqDownLimit)/radio_band.bTuneStep);
		if(radio_band.bCurBand<=MW_MODE ){	 	
			write_info((MEM_RADIO_FREQ_BASE +radio_band.bCurBand), (u8)save_reg);
		}
		else{
			write_info((MEM_RADIO_FREQ_BASE +(radio_band.bCurBand-1)*2+1), (u8)(save_reg&0x00FF));
			write_info((MEM_RADIO_FREQ_BASE +(radio_band.bCurBand-1)*2), (u8)((save_reg&0xFF00)>>8));
		}	 		
		printf_u16(save_reg,'S');
		
	 	break;	 	
	 case RADIO_SAVE_BAND:
		write_info((MEM_RADIO_BAND_CHAN), (u8)save_reg);
	 	break;	 	
	 case RADIO_SAVE_STATION_SUM:
		write_info((MEM_RADIO_TOTAL_STATION_BASE+(radio_band.bCurBand)), (u8)save_reg);
	 	break;	
	 case RADIO_SAVE_STATION:
		save_reg =(*RADIO_DATA - radio_band.wFreqDownLimit)/radio_band.bTuneStep;
		if(radio_band.bCurBand<=MW_MODE ){	 	
			write_info((MEM_RADIO_STATION_BASE+(radio_band.bCurBand*MEM_RADIO_STATION_MAX)+RADIO_VALID_CH), (u8)save_reg);
		}	
		else{
			write_info((MEM_RADIO_STATION_BASE+(radio_band.bCurBand*MEM_RADIO_STATION_MAX)+RADIO_VALID_CH*2), (u8)((save_reg&0xFF00)>>8));
			write_info((MEM_RADIO_STATION_BASE+(radio_band.bCurBand*MEM_RADIO_STATION_MAX)+RADIO_VALID_CH*2+1), (u8)(save_reg&0x00FF));
		}
		
	 	break;	 	
	}

	//printf_u16(SAVE_CMD,'C');
	//printf_u16((*RADIO_DATA),'V');
}
#endif
void set_radio_freq(u8 mode)
{
#if defined(FAST_STICK_TUNE_FUNC)
   	   xd_u8 freq_step =0;

	  // EA =0;
	    if(fast_step_cnt==0){
			fast_step_cnt=1;
	    }
		
	    if(radio_band.bCurBand==0){
			
			freq_step =1*fast_step_cnt; 
	    }
	    else if(radio_band.bCurBand==1){

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

    if(radio_band.bCurBand==0){
		
    }
    else if(radio_band.bCurBand==1){

#if 0		
		if(freq_step_flag){
			freq_step_flag=0;
			// speed up
		}
		else{
		}
#endif		
    }
    else{
		
    }	
#endif


#ifndef LCD_BACK_LIGHT_DUMMY				   
    set_brightness_all_on();
#endif
	
    if (mode == FM_FRE_INC)
    {
        radio_band.wFreq=radio_band.wFreq+radio_band.bTuneStep;
    }
    else if (mode == FM_FRE_DEC)
    {
        radio_band.wFreq=radio_band.wFreq-radio_band.bTuneStep;
    }
	
    if (radio_band.wFreq > radio_band.wFreqUpLimit)
        radio_band.wFreq = radio_band.wFreqDownLimit;
	
    if (radio_band.wFreq < radio_band.wFreqDownLimit)
        radio_band.wFreq =radio_band.wFreqUpLimit;

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
		if(am_adj_timer<2)	
			KT_AMTune(radio_band.wFreq);
#endif

    }
    disp_port(MENU_FM_MAIN);			

#ifdef SAVE_BAND_FREQ_INFO	
    mem_radio_info(RADIO_SAVE_FREQ,&radio_band.wFreq,0);
#endif
}
void radio_band_hdlr()
{	
	if(radio_band.bCurBand>((sizeof(radio_freq_tab)/6)-1))
		radio_band.bCurBand = FM_MODE;
	
	radio_band.wFreqUpLimit = radio_freq_tab[radio_band.bCurBand].MAX_FREQ;
	radio_band.wFreqDownLimit = radio_freq_tab[radio_band.bCurBand].MIN_FREQ;
	radio_band.bTuneStep  = radio_freq_tab[radio_band.bCurBand].FREQ_STEP;
	
#ifdef SAVE_BAND_FREQ_INFO	
    	mem_radio_info(RADIO_SAVE_BAND,&radio_band.bCurBand,0);

    	mem_radio_info(RADIO_READ_FREQ,&radio_band.wFreq,0);
    	mem_radio_info(RADIO_READ_STATION_SUM,&radio_band.bTotalChannel,0);

	if (radio_band.wFreq > radio_band.wFreqUpLimit)
        	radio_band.wFreq = radio_band.wFreqDownLimit;
	
    	if (radio_band.wFreq < radio_band.wFreqDownLimit)
        	radio_band.wFreq =radio_band.wFreqDownLimit;
#endif

#ifdef USE_VALIDSTATION_CHECK
	load_band_info(radio_band.bCurBand);
#endif

	KT_AMFMSetMode(radio_band.bCurBand);	

    	set_radio_freq(FM_CUR_FRE);
}

#ifdef SEMI_AUTO_SCAN_FUNC

bool radio_get_validstation(u16 freq)
{
    if(radio_band.bCurBand==0){
	return KT_FMValidStation(freq);
    }
    else if(radio_band.bCurBand==1){
	return KT_AMValidStation(freq);
    }
    else{
	return KT_SMValidStation(freq);
    }

}
#define SEMI_AUTO_SCAN_KEY_UP		MSG_RADIO_SCAN_ALL_UP
#define SEMI_AUTO_SCAN_KEY_DOWN	MSG_RADIO_SCAN_ALL_DOWN
bool radio_band_scan(u8 mode)
{
    bool res;
	
    if(mode == RADIO_SCAN_NEXT)
    {
        radio_band.wFreq=radio_band.wFreq+radio_band.bTuneStep;
		
	 if (radio_band.wFreq > radio_band.wFreqUpLimit)
	     radio_band.wFreq = radio_band.wFreqDownLimit;		
    }
    else if (mode == RADIO_SCAN_PREV)
    {
        radio_band.wFreq=radio_band.wFreq-radio_band.bTuneStep;
		
	 if (radio_band.wFreq < radio_band.wFreqDownLimit)
	      radio_band.wFreq =radio_band.wFreqUpLimit;		
    }
		
    res = radio_get_validstation(radio_band.wFreq);

    disp_port(MENU_FM_MAIN);			

    if (res)						//找到一个台
    {
       // fm_module_mute(0);
       	if(mode==RADIO_SCAN_ALL){
#ifdef SAVE_BAND_FREQ_INFO	
			mem_radio_info(RADIO_SAVE_STATION,&radio_band.wFreq,radio_band.bTotalChannel++);
			mem_radio_info(RADIO_SAVE_STATION_SUM,&radio_band.bTotalChannel,0);
#endif
       	}
#ifdef SAVE_BAND_FREQ_INFO	
    		mem_radio_info(RADIO_SAVE_FREQ,&radio_band.wFreq,0);
#endif
		return true;            		
    }
	
    return false;
}
#endif

/*----------------------------------------------------------------------------*/
/**@brief  FM任务函数
   @param  无
   @return 无
   @note   void fm_rev( void )
*/
/*----------------------------------------------------------------------------*/
void radio_rev_init(void)
{

    key_table_sel(SYS_RADIO_KEY_TABLE);
    input_number_en = 1;
    vol_change_en=1;
    encode_channel = REC_FM;
    encode_vol = 3;
	
    main_menu = MENU_FM_MAIN;
	
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

    mem_radio_info(RADIO_READ_BAND,&radio_band.bCurBand,0);
    radio_band_hdlr();
    SYSTEM_CLK_DIV4();
    set_max_vol(MAX_ANOLOG_VOL,MAX_DIGITAL_VOL);///设置最大音量
}
void radio_rev_end_handlr(void)
{
    main_vol_set(0, CHANGE_VOL_NO_MEM);
    KT_AMFMStandby();
    break_encode();
}
void radio_rev_hdlr( void )
{
    u8 key;

    	set_radio_freq(FM_CUR_FRE);
		
#ifdef FORCE_AUX_GPIO_TO_GROUND_IMPROVE_CROSSTALK

#if defined(EXCHANGE_AUX_CHANNEL)

	P2IE_REG &=~((BIT(6)|BIT(7)));
	P2IE_REG |= ((BIT(4)|BIT(5)));
	P2PD &= ~((BIT(6)|BIT(7)));
	P2PD |= ((BIT(4)|BIT(5)));
	P2 &=~((BIT(4)|BIT(5)));
	P2IE_reg_OverWrite();	
#else 
	P2IE_REG &=~((BIT(4)|BIT(5)));
	P2IE_REG |= ((BIT(6)|BIT(7)));
	
	P2PD &= ~((BIT(4)|BIT(5)));
	P2PD |= ((BIT(6)|BIT(7)));
	P2 &=~((BIT(6)|BIT(7)));
#endif	
	P2IE_reg_OverWrite();	
#endif	
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
	        case MSG_CHANGE_RADIO_MODE:
    		    flush_all_msg();
            	     scan_mode = RADIO_SCAN_STOP;		
		     radio_band.bCurBand++;
		     radio_band_hdlr();
		     break;
	        case MSG_CHANGE_WORK_MODE:
	            return;
	        case MSG_MUSIC_NEW_DEVICE_IN:							//有新设备接入
	            //work_mode = MUSIC_MODE;
	            break;
#ifdef SEMI_AUTO_SCAN_FUNC
               case MSG_RADIO_SCAN_ALL:
			radio_band.bTotalChannel =0;
	              scan_mode = RADIO_SCAN_ALL;			
	     		radio_band.wFreq = radio_band.wFreqDownLimit;	
            		put_msg_lifo(MSG_RADIO_SCAN);
			break;
               case MSG_RADIO_SCAN:
			   	
		      if (radio_band_scan(scan_mode))
	             {
	             	      if(scan_mode==RADIO_SCAN_ALL){
					if(radio_band.bTotalChannel>MEM_RADIO_STATION_MAX){
    		    				flush_all_msg();
		                     	scan_mode = RADIO_SCAN_STOP;
						break;
					}
	             	      }
			      else{
		                     scan_mode = RADIO_SCAN_STOP;
	                    		break;
				}
			}
            	       put_msg_fifo(MSG_RADIO_SCAN);
			break;	
			
	        case SEMI_AUTO_SCAN_KEY_UP:			
            		scan_mode = RADIO_SCAN_NEXT;		
            		put_msg_lifo(MSG_RADIO_SCAN);
			break;
	        case SEMI_AUTO_SCAN_KEY_DOWN:			
            		scan_mode = RADIO_SCAN_PREV;		
            		put_msg_lifo(MSG_RADIO_SCAN);
			break;	
#endif
	        case MSG_RADIO_NEXT_STEP:
    		    	flush_all_msg();
	    		set_radio_freq(FM_FRE_INC);
			break;
	        case MSG_RADIO_PREV_STEP:
    		    	flush_all_msg();
		    	set_radio_freq(FM_FRE_DEC);
		       break;		 
	        case MSG_HALF_SECOND:
#if defined(USE_BAT_MANAGEMENT)			
		     bmt_hdlr();
#endif

#if 1
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
	            		if(radio_band.bCurBand>1){
					input_number = input_number*10;
				}
	            	 	if ((input_number <= radio_band.wFreqUpLimit) && (input_number >=radio_band.wFreqDownLimit)){

			        	radio_band.wFreq =input_number;
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
	
    radio_rev_init();

    radio_rev_hdlr();

    radio_rev_end_handlr();
}

#endif
