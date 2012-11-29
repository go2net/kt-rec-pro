/*--------------------------------------------------------------------------*/
/**@file   main.c
   @brief  系统主函数
   @details
   @author
   @date   2011-9-8
   @note
*/
/*----------------------------------------------------------------------------*/
#include "Custom_config.h"

#include "config.h"

#include "main.h"
#include "disp.h"
#include "fm_rev.h"
#include "led.h"
#include "music.h"
#include "device.h"
#include "dac.h"
#include "msgfor_usb.h"
#include "clock.h"
#include "disp.h"
#include "rtc_mode.h"
#include "lcdsegment.h"

extern u8 _idata clock_in;
extern u8 given_device;
extern u16 given_file_number;
extern bool vol_change_en;
extern bool sys_pwr_flag,sys_mute_flag;

extern u8 eq_mode;
extern u8 play_mode;

extern bool pc_connect, udisk_connect, sdmmc_connect;
extern u8 _xdata win_buffer[];
//extern u8 _xdata alm_cnt;
//u8 _code one_table[] = {0,1,1,2,1,2,2,3,1,2,2,3,2,3,3,4};

bool input_number_en;				///<是否允许数字键输入功能
//bool change_eq_en;					///<是否允许改变EQ的设置
u8 work_mode;						///<工作模式变量
//u8 _idata last_work_mode;			///<RTC 闹钟前的工作模式
//bool aux_online;					///<AUX在线状态
//bool kv_flag;						///<按键音的发送标记

u8  main_menu;						///<记录各种不同模式下的主界面
u8  cur_menu;        				///<当前界面
u8  main_menu_conter;				///<离开主界面的时间
//bool flash_en;						///<显示闪动允许
//u8 bright_counter;
extern bool iic_busy; ///<iic繁忙标记
extern void KT_AMFMStandby(void);					//0->Fail 1->Success
#ifdef JOG_STICK_FUNC	 
extern void JogDetect(void);
#endif
#if defined(USE_LCD_DRV_HT1621)
extern void lcd_ht1621_init(void);
#endif
/*----------------------------------------------------------------------------*/
/**@brief  Line In检测函数
   @param  无
   @return 无
   @note   void aux_check(void)
*/
/*----------------------------------------------------------------------------*/
#if 0
static void aux_check(void)
{
    static u8 aux_cnt_online;

    if(iic_busy)return;

    P0DIR |= BIT(7); //linein check port
    P0PU |= BIT(7);
    //_nop_();
    //_nop_();
    //_nop_();
    if (P07)
    {
        aux_cnt_online = 0;

        if (aux_online)
        {
            put_msg_lifo(MSG_AUX_OUT);
            aux_online = 0;
        }
    }
    else
    {
        aux_cnt_online++;
        if (aux_cnt_online > 50)
        {
            if (!aux_online)
            {
                put_msg_lifo(MSG_AUX_IN);
                aux_online = 1;
            }
        }
    }
    //P0DIR &= ~BIT(7); //linein check port

}
#endif
#if 0
/*----------------------------------------------------------------------------*/
/**@brief   使用独立的GPIO检测SD card在线
   @param   void
   @return  void
   @note    void sdmmc_detect(void)
*/
/*----------------------------------------------------------------------------*/
void sdmmc_detect(void)
{
    static u8 sdmmc_cnt_online;
    P3DIR |= BIT(3); //linein check port
    P3PU |= BIT(3);
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    if (P33)
    {
        sdmmc_cnt_online = 0;
        sdmmc_chk_io(0);
    }
    else
    {
        if (sdmmc_cnt_online<51)
        {
            sdmmc_cnt_online++;
        }
        if (sdmmc_cnt_online > 50)
        {
            sdmmc_chk_io(1);
        }
        else
        {
            sdmmc_chk_io(0xff);
        }
    }
}
#endif 
/*----------------------------------------------------------------------------*/
/**@brief  RTC中断服务程序
   @param  无
   @return 无
   @note   void rtcisr(void)
*/
/*----------------------------------------------------------------------------*/
#if 0
void rtcisr(void)
{
    //PSW = 0x08;
    //DPCON = 0x0;
#if BURST_OUT_POINT_SAVE_ENABLE
    burst_out_break_point_save();
#endif

}
#endif





/*----------------------------------------------------------------------------*/
/**@brief  RTC中断服务程序
   @param  无
   @return 无
   @note   void rtcisr(void)
*/
/*----------------------------------------------------------------------------*/
void timer0isr(void)
{
    static xd_u8 counter0, counter1;

    PSW = 0x08;
    DPCON = 0x0;
    T0CON &= ~BIT(7);			//clear pending
#ifdef LCD_GPIO_DRV
   seg_lcd_disp_scan();
#else
   //disp_scan();
#endif
    adc_scan();
    counter0++;
    usb_polling();

#ifdef JOG_STICK_FUNC	 
    JogDetect();
#endif

    if ((counter0 % 5) == 0)			//10ms
    {
        dec_delay_counter();
//#if SDMMC_CMD_MODE
//        sd_online_check();
//#if SDMMC_CLK_MODE
        sdmmc_online_chk(1);
//#elif SDMMC_GPIO_MODE
        //sdmmc_detect();
//#endif
        keyScan();
    }

//    if ((counter0 % 50) == 0)
//    {
//        put_msg_fifo(MSG_100MS);
//    }
    if ((counter0 % 100) == 0)
    {
    	 ad_mod_sel_hdlr();
        put_msg_fifo(MSG_200MS);
        counter0 = 0;
    }
    counter1++;
    if ((counter1 % 250) == 0)
    {
        put_msg_fifo(MSG_HALF_SECOND);
        counter1 = 0;
    }
#if 0//RTC_ENABLE
    if (IRTCON & BIT(7))
    {
        alm_cnt = 1;
        last_work_mode = work_mode;
        put_msg_lifo(MSG_ALM_ON);
    }
#endif
}

/*----------------------------------------------------------------------------*/
/**@brief  系统共用信息的初始化
   @param  无
   @return 无
   @note   void sys_info_init(void)
*/
/*----------------------------------------------------------------------------*/
static void sys_info_init(void)
{
 //   u8 tmp;

#if 0
#if (DEFAULT_VOL>0)
	tmp = MAX_MAIN_VOL;
#else
    tmp = read_info(MEM_VOL);

    if ((tmp > MAX_MAIN_VOL) || (tmp == 0))              //每次开机时，不要超过最大音量的一半，以免开机音量过大
    {
       // tmp = MAX_MAIN_VOL/2;
        tmp = 20;
    }
#endif
#endif
	//tmp = MAX_MAIN_VOL;

    dac_init(MAX_MAIN_VOL);
    delay_10ms(50);										//等待,检测USB,SD在线状态
    //init_rec_name();
    //restore_music_point();
#if 0
#if RTC_ENABLE
    if (work_mode != RTC_MODE)
#endif
    {
    	device_check();
#if USB_DEVICE_ENABLE
        if (pc_connect)
            work_mode = USB_DEVICE_MODE;
        else if (udisk_connect || sdmmc_connect)
            work_mode = MUSIC_MODE;
#else
       // if (udisk_connect || sdmmc_connect)
       //     work_mode = MUSIC_MODE;
#endif
    }
#endif

}
/*----------------------------------------------------------------------------*/
/**@brief  系统主函数
   @param  无
   @return 无
   @note   void main(void)
*/
/*----------------------------------------------------------------------------*/

void sys_init(void)
{
#if defined(UART_ENABLE)
    uart_init();
    deg_str("power on\n");
#endif

    core_power_on();
    OTP_CLK_DIV2();
    DECODER_DIV2();
    SYSTEM_CLK_DIV4();
#if (NO_DISP != monitor)
    init_display();
#endif
    sd_speed_init(0,100);

//#if SDMMC_CMD_MODE
//    sd_chk_ctl(SET_SD_H_CHK);
//#endif
    init_port_sd();
    //kv_init(); ///按键音初始化函数

#if RTC_ENABLE
    rtc_init();			//RTC初始化，检测是否闹钟开机
    //{
        //work_mode = RTC_MODE;
    //}
#else
    {
        u8 rtc_reg = read_rtc_reg();
        if (rtc_reg & BIT(7))					//检测是否掉电
        {
            rtc_reg &= ~BIT(7); 				//清零PDFLAG
            write_rtc_reg(rtc_reg);
#if USE_RTC_RAM
            reset_rtc_ram();
#endif
        }
    }
#endif
    key_init();
    bsp_init();
    //interrupt_init(15, rtcisr);
    interrupt_init(3, timer3isr);
    interrupt_init(0, timer0isr);
    enable_interrupt();
   /// flashled(3);
}
#if 1
void idle_mode(void)
{
    u8 key;
//deg_str("idle_mode \n");

    //dac_out_select(DAC_MUSIC, 0);
    //clear_all_event();
    KT_AMFMStandby();

    flush_all_msg();
    disp_port(MENU_POWER_OFF);
    input_number_en=0;
    vol_change_en=0;

   while (1)
    {
        key = app_get_msg();

        switch (key)
        {
        case MSG_CHANGE_WORK_MODE:
	     clear_all_event();
    	     flush_all_msg();
            return;

        case MSG_MUSIC_NEW_DEVICE_IN:							//有新设备接入
	  //put_msg_lifo(MSG_CHANGE_WORK_MODE);		
	 	break;
        default:
            ap_handle_hotkey(key);        
            break;
        }
    }
}
#endif
void main(void)
{
#if defined(USE_LCD_DRV_HT1621)
    lcd_ht1621_init();
#endif
    work_mode = MUSIC_MODE;
    //amp_mute(1);
    clock_in = T0CNT;									//输入时钟,define in clock.h
    //WDT_EN();
    sys_init();
    AMUX_P2IE_SET(AMUX1_IE);
    sys_info_init();
    clear_all_event();
    flush_all_msg();
    set_brightness_all_on();
#if (DISP_VER!=0)
    if(ADKEY_PORT==0){

	disp_port(MENU_VER);
	delay_10ms(80);
    }
#endif	
    delay_10ms(10);
    ///*
    while (1)
    {
        switch (work_mode)
        {
        case MUSIC_MODE:
            music_decode();
            break;
#if USB_DEVICE_ENABLE
        case USB_DEVICE_MODE:
            usb_audio_massstorage();
            break;
#endif     

#if FM_MODULE                     
        case FM_RADIO_MODE:
            radio_hdlr();
            break;
#endif
        //case AUX_MODE:
            //aux_fun();
          //  break;

#if RTC_ENABLE
        //case RTC_MODE:
            //rtc_fun();
         //   break;        
#endif
        case REC_MIC_MODE:
            rec_mic_fun();
            break;
			
        case IDLE_MODE:
            idle_mode();	
	     sys_mute_flag =0;
	     dac_mute_control(0,1);					//调节音量时，自动UNMUTE
    	     //set_brightness_all_on();
            break;		
        default:
            work_mode = MUSIC_MODE;
            break;
        }
        //write_info(MEM_SYSMODE ,work_mode);
    }
    //*/
}
