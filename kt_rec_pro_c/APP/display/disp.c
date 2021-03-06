/*--------------------------------------------------------------------------*/
/**@file   DISP.C
   @brief    显示模块
   @details
   @author
   @date   2011-3-7
   @note
*/
/*----------------------------------------------------------------------------*/
#include "Custom_config.h"
#include "config.h"

#include "disp.h"
#include "uart.h"
#if (monitor != NO_DISP)


#include "lcd.h"
#include "led.h"

#if defined(USE_LCD_DRV_HT1621)
#include "lcd_ht1621_drv.h"
#else
#include "lcdsegment.h"
#endif

#include "resource.h"
#include "my_printf.h"
#include "lcd.h"
#include "led.h"
#include "device.h"
#include "dac.h"
#include "rtc_mode.h"
#include "gpio_if.h"
#include "radio_api.h"

extern RADIO_MODE_VAR  radio_band;

extern xd_u16 input_number;
extern u8 _bdata device_online;

extern u16 given_file_number;
extern u8 device_active;
extern u8 eq_mode;
extern u8 play_mode;
extern u8 music_type;
extern DECODER_MSG _xdata *dec_msg;
extern FSAPIMSG _pdata fs_msg;
extern u8 _xdata rtc_coordinate;
extern u8 work_mode;
extern u8 _idata last_work_mode;
extern xd_u8 rtc_setting_flag;

extern xd_u8  main_menu;			///<记录各种不同模式下的主界面
extern xd_u8  cur_menu;        	///<当前界面
extern xd_u8  main_menu_conter;	///<离开主界面的时间
extern bool flash_en;			///<显示闪动允许
extern u8 bright_counter;		///<显示亮度调整延时
extern u8 play_status;	
extern xd_u8 sys_main_vol;	

u8 led_flag;
xd_u8  clock_points=0;

extern void clear_lcd_disp_buf(void);
void disp_play_mode_icon(void);

extern u16 lcd_buff[5];

/*----------------------------------------------------------------------------*/
/**@brief  显示在线和闪烁活动设备符号
   @param  无
   @return 无
   @note   void disp_device(void)
*/
/*----------------------------------------------------------------------------*/
void disp_device(void)
{
	if((device_active & (~VIRTUAL_DEVICE)) == DEVICE_SDMMC0)
	{
	    	lcd_disp_icon(SD_ICON);

		//if(RECODE_WORKING == encode_status)
	    	//	lcd_flash_icon(SD_ICON);
	}
	else if((device_active & (~VIRTUAL_DEVICE)) == DEVICE_UDISK)
	{
	    lcd_disp_icon(USB_ICON);

		//if(RECODE_WORKING == encode_status)
		//    lcd_flash_icon(USB_ICON);
	}

	if(encode_status==RECODE_WORKING)
	{
	    lcd_flash_icon(REC_ICON);
	}
	else	 if(encode_status==RECODE_PAUSE)
	{
	    lcd_disp_icon(REC_ICON);
#ifdef DISP_PAU_STR		
    	    printf_str("PAU",1);
#else
	    printf_str("PAUS",0);//my_printf("OFF ");
#endif	    
           lcd_clr_icon(COL_ICON);
	}

}



//////////////////////////////////////////////////////////////////////////////////

/*----------------------------------------------------------------------------*/
/**@brief  设置亮度
   @param  无
   @return 无
   @note   void set_brightness(void)
*/
/*----------------------------------------------------------------------------*/
#if 0
void set_brightness(u8 br)
{
#if(LCD_DISP == monitor)

#else
  // led_set_brightness(br);
#endif
}
#endif
/*----------------------------------------------------------------------------*/
/**@brief  设置亮度渐暗
   @param  无
   @return 无
   @note   void set_brightness_fade_out(void)
*/
/*----------------------------------------------------------------------------*/
#ifndef LCD_BACK_LIGHT_DUMMY
xd_u8 backlight_timer=0;
void set_brightness_fade_out(void)
{
    if (backlight_timer >0)
    {
            backlight_timer--;
	 return;
    }
    LCD_BACKLIGHT_OFF();
}

/*----------------------------------------------------------------------------*/
/**@brief  设置亮度全亮
   @param  无
   @return 无
   @note   void set_brightness_all_on(void)
*/
/*----------------------------------------------------------------------------*/
void set_brightness_all_on(void)
{
    backlight_timer = 120;
    LCD_BACKLIGHT_ON();
    //set_brightness(16);
    //bright_counter = 0;
}
#endif    

/*----------------------------------------------------------------------------*/
/**@brief  显示初始化
   @param  无
   @return 无
   @note   void init_display(void)
*/
/*----------------------------------------------------------------------------*/
void init_display(void)
{
    	init_lcd_disp();
 //   disp_power_on();
    	LCD_BACKLIGHT_ON();
#ifdef PLAY_STATUS_LED_FUNC
	play_status_led_init(); 
#endif
}


/////////////////////////////////////////////////////////////////////////////////

/*----------------------------------------------------------------------------*/
/**@brief  显示开机上电的界面
   @param  无
   @return 无
   @note   void disp_power_on(void)
*/
/*----------------------------------------------------------------------------*/
#if 0
void disp_power_on(void)
{
#if(LCD_DISP == monitor)
        printf_str(" HI",0);//my_printf("%X\x0HI--");
#else
        printf_str("HI--",0);//my_printf("%X\x0HI--");
#endif
}

#endif
/*----------------------------------------------------------------------------*/
/**@brief  显示关机界面
   @param  无
   @return 无
   @note   void disp_power_off(void)
*/
/*----------------------------------------------------------------------------*/
void disp_power_off(void)
{
    //printf_str("OFF ",0);//my_printf("OFF ");
      clear_lcd_disp_buf();
      LCD_BACKLIGHT_OFF();
}
void disp_no_device(void)
{
    printf_str(" NO",0);//my_printf("OFF ");
}
void disp_del_file(void)
{
    printf_str(" del",0);//my_printf("OFF ");
}

/*----------------------------------------------------------------------------*/
/**@brief  显示FM主界面
   @param  无
   @return 无
   @note   void disp_fm_main(void)
*/
/*----------------------------------------------------------------------------*/


void disp_radio_main(void)
{
	u16 freq=0;

	if(radio_band.bCurBand==0){
		freq =radio_band.wFreq/10;
	 	lcd_disp_icon(FM_ICON);		
	}
	else if(radio_band.bCurBand==1){
		freq =radio_band.wFreq;
	 	lcd_disp_icon(AM_ICON);
	}
	else{
		freq =radio_band.wFreq/10;

#if defined(DISP_SW2_ICON)
		if(radio_band.bCurBand==3){
	 		lcd_disp_icon(SW2_ICON);		
		}
		else
#endif		
	 	lcd_disp_icon(SW_ICON);		

	}
	
    if(freq > 999)
    {
        printf_num(freq,0,4);
    }	
    else if(freq > 99)
    {
        printf_num(freq,1,3);
    }
    else{

        printf_num(freq,2,2);
    }

#ifdef DISP_ACTIVE_REC_DEVICE_AT_RADIO_MODE
	if((encode_status==RECODE_WORKING)||(encode_status==RECODE_PAUSE)){
		
		if((device_active & (~VIRTUAL_DEVICE)) == DEVICE_SDMMC0)
		{
		    	lcd_disp_icon(SD_ICON);
		}
		else if((device_active & (~VIRTUAL_DEVICE)) == DEVICE_UDISK)
		{
		    lcd_disp_icon(USB_ICON);
		}
	}
#endif	
}


/*----------------------------------------------------------------------------*/
/**@brief  显示FM频点
   @param  无
   @return 无
   @note   void disp_fm_freq(void)
*/
/*----------------------------------------------------------------------------*/
#if 0//FM_MODULE
void disp_fm_freq(void)
{
    disp_fm_main();
}
#endif
/*----------------------------------------------------------------------------*/
/**@brief  显示搜索到的FM频道
   @param  无
   @return 无
   @note   void disp_fm_find_station(void)
*/
/*----------------------------------------------------------------------------*/
#if 0//FM_MODULE
void disp_fm_find_station(void)
{
    led_putchar('P',1);
    printf_num(fre_channel,2,2);//my_printf("%c P%02b%m", fre_channel, LED_FM_ICON);
    delay_10ms(50);

}
#endif
/*----------------------------------------------------------------------------*/
/**@brief  显示FM频道
   @param  无
   @return 无
   @note   void disp_fm_channel(void)
*/
/*----------------------------------------------------------------------------*/
#if 0//FM_MODULE
void disp_fm_channel(void)
{
    led_putchar('P',1);
    printf_num(fre_channel,2,2);

}
#endif
/*----------------------------------------------------------------------------*/
/**@brief  显示输入数字
   @param  num:数值
   @return 无
   @note   void disp_input_number(u16 num)
*/
/*----------------------------------------------------------------------------*/
void disp_input_number(u16 num)
{
    printf_num(num,0,4);      
    disp_device();
}

/*----------------------------------------------------------------------------*/
/**@brief  显示主音量
   @param  vol:显示的音量值
   @return 无
   @note   void disp_main_vol(u8 vol)
*/
/*----------------------------------------------------------------------------*/
void disp_main_vol()
{
    //sys_main_vol = vol;
    led_putchar('U',1);
    printf_num(sys_main_vol,2,2);

}
/*----------------------------------------------------------------------------*/
/**@brief  显示音频播放时间，总时间
   @param  无
   @return 无
   @note   void disp_music_play_time(void)
*/
/*----------------------------------------------------------------------------*/
void disp_music_play_time(void)
{
    u16 play_time;
    u8 min,sec;

    play_time = dec_msg->play_time;
    min = play_time / 60;
    sec = play_time % 60;
//	printf_u16(play_time,'t');
#if 1//((monitor == DISP_LED5X7)||(LCD_DISP == monitor))
    printf_num(sec,2,2);
    printf_num(min,0,2);
    led_putchar(':',0);
#endif
    // disp_play_mode();
}

/*----------------------------------------------------------------------------*/
/**@brief  显示音频文体格式
   @param  无
   @return 无
   @note   void disp_music_format(voids)
*/
/*----------------------------------------------------------------------------*/
#if 0
void disp_music_format(void)
{
    if (music_type == IS_WAV)
    {
    }
    else if (music_type == IS_WMA)
    {
    }
}
#endif
/*----------------------------------------------------------------------------*/
/**@brief  显示 MUSIC主界面
   @param  无
   @return 无
   @note   void diso_music_main(void)
*/
/*----------------------------------------------------------------------------*/
void disp_music_main(void)
{
    	disp_music_play_time();
	disp_device();

#if defined(DISP_PLAY_ICON)	
	lcd_disp_icon(PLAY_ICON);
#endif
	disp_play_mode_icon();
}
/*----------------------------------------------------------------------------*/
/**@brief  显示 EQ
   @param  无
   @return 无
   @note   void disp_eq(void)
*/
/*----------------------------------------------------------------------------*/
void disp_eq(void)
{
	printf_str("Eq",1);
    	printf_num(eq_mode,3,1);
}
/*----------------------------------------------------------------------------*/
/**@brief  显示 播放模式
   @param  无
   @return 无
   @note   void disp_play_mode(void)
*/
/*----------------------------------------------------------------------------*/
#ifdef PLAY_MODE_IN_USE
void disp_play_mode_icon(void)
{
	if(play_mode==REPEAT_ALL){

		lcd_disp_icon(REP_ALL_ICON);
	}
	else{
		lcd_disp_icon(REP_1_ICON);
	}
}
void disp_play_mode(void)
{
#if VIRTUAL_ENABLE	
    if(device_active & VIRTUAL_DEVICE)
    {
	if(play_mode_rec==REPEAT_ALL){
		lcd_disp_icon(REP_ALL_ICON);
	}
	else if(play_mode_rec==REPEAT_ONE){
		lcd_disp_icon(REP_1_ICON);
	}
    }
    else
#else		
    {
	if(play_mode==REPEAT_ALL){
#ifdef DISP_PLAY_MODE_STR
#if defined(NEW_DH_228_LCD_MODULE_SM5901)
		    printf_str("ALL",1);
#else
		    printf_str("ALL",1);
#endif
#endif
	}
	else if(play_mode==REPEAT_ONE){

#ifdef DISP_PLAY_MODE_STR
#if defined(NEW_DH_228_LCD_MODULE_SM5901)
		    printf_str("ONE",1);
#else
		    printf_str("ONE",1);
#endif		
#endif		
	}
    }
#endif

	disp_play_mode_icon();
}
#endif
/*----------------------------------------------------------------------------*/
/**@brief  刷新音乐显示主界面
   @param  无
   @return 无
   @note   无
*/
/*----------------------------------------------------------------------------*/
//void disp_main_menu_refresh(void)
//{
//       disp_music_main();
//}
/*----------------------------------------------------------------------------*/
/**@brief 显示音乐模式下的暂停界面
   @param 	void
   @return  void
   @note  void disp_music_pause(void)
*/
/*----------------------------------------------------------------------------*/
void disp_music_pause(void)
{
    disp_music_play_time();

    disp_device();
#if defined(DISP_PAU_STR)
    printf_str("PAU",1);
    lcd_clr_icon(COL_ICON);
#elif defined(DISP_PAUSE_ICON)
    lcd_disp_icon(PAUSE_ICON);
    lcd_disp_icon(COL_ICON);
#else
    printf_str("PAUS",0);
    lcd_clr_icon(COL_ICON);
#endif	

}
/*----------------------------------------------------------------------------*/
/**@brief 显示扫描设备界面
   @param 	void
   @return  void
   @note  void disp_scan_disk(void)
*/
/*----------------------------------------------------------------------------*/
void disp_scan_disk(void)
{
    printf_str(" Lod",0);
}

#if RTC_ENABLE

extern RTC_TIME _xdata curr_time;

/*----------------------------------------------------------------------------*/
/**@brief 显示当前时间界面
   @param 	void
   @return  void
   @note  void disp_curr_time(void)

*/
/*----------------------------------------------------------------------------*/
void disp_curr_time(void)
{
    printf_num(curr_time.min,2,2);
    printf_num(curr_time.hour,0,2);

#ifdef DISP_ACTIVE_DEVICE_WHEN_TIME_DISPLAY
    if(play_status == MAD_PLAY)
	    disp_device();
#endif

    if(clock_points==1){

		clock_points =0;
		led_putchar(':',0xFF);		
    }
    else{
		
		clock_points =1;
		
		if(rtc_setting_flag>0){

			if(rtc_coordinate==3){
    				clr_lcd_digit(0);
    				clr_lcd_digit(1);
			}
			else if(rtc_coordinate==4){
    				clr_lcd_digit(2);
    				clr_lcd_digit(3);			
			}
			led_putchar(':',0xFF);		
    		}
   }
}
#endif
/*----------------------------------------------------------------------------*/
/**@brief 	录音出错界面显示
   @param 	void
   @return  void
   @note  	void disp_rec_err(void)
*/
/*----------------------------------------------------------------------------*/
void disp_rec_err(void)
{
    printf_str(" ERR",0);
    //delay_10ms(100);
}
/*----------------------------------------------------------------------------*/
/**@brief 	录音时间显示
   @param 	void
   @return  void
   @note  	void disp_rec_time(void)
*/
/*----------------------------------------------------------------------------*/
void disp_rec_time(void)
{
    u16 encoder_time;
    u8 min,sec;

    encoder_time = encode_time();
    min = encoder_time / 60;
    sec = encoder_time % 60;

    printf_num(sec,2,2);
    printf_num(min,0,2);
    led_putchar(':',0xFF);
}
/*----------------------------------------------------------------------------*/
/**@brief 	录音工作界面显示
   @param 	void
   @return  void
   @note  	void disp_rec_working(void)
*/
/*----------------------------------------------------------------------------*/
void disp_rec_working(void)
{
	disp_rec_time();
	disp_device();
}
/*----------------------------------------------------------------------------*/
/**@brief 	录音开始界面显示
   @param 	void
   @return  void
   @note  	void disp_rec(void)
*/
/*----------------------------------------------------------------------------*/
#if 0
void disp_rec(void)
{
    printf_str("REC",1);
    disp_device();
}
#endif
/*----------------------------------------------------------------------------*/
/**@brief 	录音暂停显示
   @param 	void
   @return  void
   @note  	void disp_rec_err(void)
*/
/*----------------------------------------------------------------------------*/
#if 0

void disp_rec_pause(void)
{
	disp_rec_time();
	disp_device();
}
#endif

extern bool sys_mute_flag;
void update_disp_icon()
{
    if(work_mode != IDLE_MODE){
		
	    lcd_clr_icon(MUTE_ICON);

	     if(sys_mute_flag){
			lcd_disp_icon(MUTE_ICON);
	    }
    }	
#ifdef DISP_REC_ICON_WHEN_RECORDING
	if(encode_status==RECODE_WORKING)
	{
	    lcd_flash_icon(REC_ICON);
	}
	else if(encode_status==RECODE_PAUSE){

	    	lcd_clr_flash_icon();
		lcd_disp_icon(REC_ICON);
	}	
#endif
#if defined(USE_LCD_DRV_HT1621)
	UpdateLcd_HT1621_Buf();
#endif

#ifdef PLAY_STATUS_LED_FUNC
	play_status_led_hdlr();
#endif
}
#if (DISP_VER!=0)
void disp_version(void)
{
    led_putchar('U',1);
    printf_num(DISP_VER,2,2);
}
#endif
/*----------------------------------------------------------------------------*/
/**@brief 显示界面集中处理
   @param 	void
   @return  void
   @note  void disp_port(u8 menu)
*/
/*----------------------------------------------------------------------------*/
void disp_port(u8 menu)
{
   
    if (menu < 0x80)							//显示场景切换，整个显示均会更新
    {

      	 clear_lcd_disp_buf();

        cur_menu = menu;
        main_menu_conter = 0;

        if (menu != MENU_INPUT_NUMBER)
            input_number = 0;

        switch (menu)
        {
#if (DISP_VER!=0)
        case MENU_VER:
            disp_version();
            break;
#endif			
        case MENU_PAUSE:
            disp_music_pause();
            break;

        case MENU_SCAN_DISK:
            disp_scan_disk();
            break;

        case MENU_MAIN_VOL:
            disp_main_vol();
            break;

        case MENU_FILENUM:
            disp_input_number(fs_msg.fileNumber);
            break;

        case MENU_MUSIC_MAIN:
            disp_music_main();
            break;

        case MENU_INPUT_NUMBER:
            disp_input_number(input_number);
            break;

        case MENU_RADIO_MAIN:
            disp_radio_main();
            break;
        
        case MENU_POWER_OFF:
            disp_power_off();
            break;
        case MENU_NODEVICE:
            disp_no_device();
            break;
#if 1			
        case MENU_DEL_FIL:
            disp_del_file();
            break;				
#endif			
      //  case MENU_FM_DISP_FRE:
     //       disp_fm_main();
     //       break;

	case MENU_REC_ERR:
		disp_rec_err();
		break;

	//case MENU_REC_MAIN:
	//	disp_music_main();
	//	break;

	case MENU_SET_EQ:
            disp_eq();
            break;
#ifdef PLAY_MODE_IN_USE
        case MENU_SET_PLAY_MODE:
            disp_play_mode();
            break;
#endif
        case MENU_RECWORKING:
            disp_rec_working();
            break;
#if 0
        case MENU_REC:
            disp_rec();
            break;
#endif			
#if 0
	 case MENU_REC_PAUSE:
		disp_rec_pause();
		break;
#endif
#if USB_DEVICE_ENABLE
        case MENU_USBDEV_MAIN:
            disp_usb_device();
            break;
#endif

#if RTC_ENABLE
        case MENU_RTC:
            disp_curr_time();
            break;

#if USB_DEVICE_ENABLE
        case MENU_ALM_REQUEST:
            disp_alm_request();
            break;
#endif
#endif
        }
    }
    else												//局部显示替换和更新
    {

      		switch (menu)
        	{
        		case MENU_HALF_SEC_REFRESH:
	       		disp_music_main();
            			break;

        }
    }
	update_disp_icon();
}

#ifdef PLAY_STATUS_LED_FUNC
xd_u8 playled_spark=0;
xd_u16 led_spark_div=0;
void play_status_led_init()
{
	PLAY_LED_GPIO_INIT();
	set_play_status_led_spark(PLED_ON);
}
void set_p_led_port(bool led_level)
{
	if(led_level){
		PLAY_LED_ON();
	}
	else{
		PLAY_LED_OFF();
	}
}
void set_play_status_led_spark(u8 speed)
{
	playled_spark=speed;
}
void play_status_led_hdlr()
{
	static bool pled_bit=0;
	if(PLED_OFF == playled_spark){
		PLAY_LED_OFF();
	}
	else if(PLED_ON== playled_spark){
		PLAY_LED_ON();
	}
	else if(PLED_SPARK_NOR== playled_spark){

		led_spark_div++;
		if((led_spark_div)==500){
			led_spark_div=0;
			pled_bit=~pled_bit;
		}
		set_p_led_port(pled_bit);
	}	
}
#endif


#endif

