/*--------------------------------------------------------------------------*/
/**@file     msgfor_usb.c
   @brief    usb 从机任务模块
   @details
   @author
   @date   2011-3-7
   @note
*/
/*----------------------------------------------------------------------------*/

/* msgfor usb */

#include "msgfor_usb.h"
#include "dac.h"
#include "eq.h"
#include "rtc_api.h"
#include "rtc_ui.h"

#if USB_DEVICE_ENABLE

extern u8 eq_mode;
extern u8  main_menu_conter;
extern bool input_number_en;
extern u8 cur_menu;
extern u8  main_menu;
extern u8 work_mode;
//extern u8 _idata last_work_mode;
extern bool pc_connect;
//extern bool vol_change_en;
//extern bool key_voice_en;

extern u8 device_check(void);
extern u8 _xdata alm_cnt;

u8 _xdata alm_request_cnt;		  ///<闹钟的请求界面的CNT

/*----------------------------------------------------------------------------*/
/**@brief   usb hid 命令接口函数
   @param   Audio_Flag ：  hid 命令
   @return  无
   @note    void usb_hid_control(u8 Audio_Flag)
*/
/*----------------------------------------------------------------------------*/
void usb_hid_control(u8 Audio_Flag)
{
    usb_hid_key(Audio_Flag);
    usb_hid_key(0);
}
/*----------------------------------------------------------------------------*/
/**@brief   闹钟请求界面下作消息转换
   @param   key：系统消息
   @return  无
   @note    u8 alm_request_msg_convert(u8 key)
*/
/*----------------------------------------------------------------------------*/
u8 alm_request_msg_convert(u8 key)
{
    switch (key)
    {
    case MSG_MUSIC_NEXT_EQ:
        return MSG_REQUEST_N;
    case MSG_NEXT_PLAYMODE:
        return MSG_REQUEST_Y;
    case MSG_HALF_SECOND:
        return key;
    default:
        return NO_MSG;
    }
}
/*----------------------------------------------------------------------------*/
/**@brief   usb 从机任务 主循环函数
   @param   无
   @return  无
   @note    void usb_device(void)
*/
/*----------------------------------------------------------------------------*/
void usb_device(void)
{
    u8 key;
	u8 connect_counter = 0;
	bool usb_con = 0;

    while (1)
    {
#if ((USB_DEVICE_CFG & USB_MASS) == USB_MASS)
        UFI_massstorage();
#endif
#if ((USB_DEVICE_CFG & USB_SPEAKER) == USB_SPEAKER)
//        key_voice_en=1;
        dac_out_select(DAC_MUSIC, 0);
#endif

        key = app_get_msg();
        if (alm_request_cnt)
        {
            key = alm_request_msg_convert(key);
        }
        switch (key)
        {

#if ((USB_DEVICE_CFG & USB_SPEAKER) == USB_SPEAKER)


            /*  case MSG_MUSIC_NEXT_EQ:
                  eq_mode++;
                  if (eq_mode > CLASSIC)
                  {
                      eq_mode = NORMAL;
                  }
                  //set_dsp_eq(eq_mode);
              	set_eq(eq_mode);
                  disp_port(MENU_SET_EQ);
                  break;	 */

        case MSG_PC_MUTE:
            dac_mute_control(1,1);
            break;
        case MSG_PC_UNMUTE:
            dac_mute_control(0,1);
            break;
#else
        case MSG_VOL_UP:
            break;

        case MSG_VOL_DOWN:
            break;
#endif


#if ((USB_DEVICE_CFG & USB_HID) == USB_HID)
        case MSG_MUSIC_PP:
            //Usb_Audio_Mute_Ctl();
            usb_hid_control(USB_AUDIO_PP);
            break;

        case MSG_MUSIC_NEXT_FILE:
            usb_hid_control(USB_AUDIO_NEXTFILE);
            break;

        case MSG_MUSIC_PREV_FILE:
            usb_hid_control(USB_AUDIO_PREFILE);
            break;

#endif

        case MSG_USB_PC_OUT:
            work_mode = MUSIC_MODE;
            return;

        case MSG_HALF_SECOND:
			if (!usb_con)
			{
				connect_counter++;
				if(USBCON0 & BIT(6))
					usb_con = 1;
				else if (connect_counter > 4)
					return;
			}
            //printf("alm_request_cnt:%u,main_menu_conter:%u\n",(u16)alm_request_cnt,(u16)main_menu_conter);
#if 0//RTC_ENABLE
            if (alm_request_cnt)
            {
                alm_request_cnt++;
                disp_port(MENU_ALM_REQUEST);
                if (alm_request_cnt > 60)
                {
                    alm_request_cnt = 0;
                    work_mode = RTC_MODE;
                    put_msg_lifo(MSG_CHANGE_WORK_MODE);
                }
                break;
            }
#endif
            set_brightness_fade_out();
            if (main_menu_conter < SUB_MENU_TIME)
            {
                main_menu_conter++;
            }
            else if (cur_menu != main_menu)
            {
                cur_menu = main_menu;
                disp_port(cur_menu);
            }
            break;
#if 0//RTC_ENABLE
        case MSG_CHANGE_WORK_MODE:
            if (alm_cnt)
            {
                return;
            }
            break;

        case MSG_REQUEST_Y:
            alm_request_cnt = 0;
            work_mode = RTC_MODE;
            put_msg_lifo(MSG_CHANGE_WORK_MODE);
            break;
        case MSG_REQUEST_N:
            alm_request_cnt = 0;
            close_alarm();
            main_menu_conter = SUB_MENU_TIME;
            break;
        case MSG_ALM_ON:
            alm_request_cnt = 1;
            write_next_alm_sec();
            disp_port(MENU_ALM_REQUEST);
            break;
#endif

        default :
            ap_handle_hotkey(key);
            break;
        }

    }

}
/*----------------------------------------------------------------------------*/
/**@brief   usb 从机任务 入口函数
   @param   无
   @return  无
   @note    void usb_audio_massstorage(void)
*/
/*----------------------------------------------------------------------------*/
void usb_audio_massstorage(void)
{
    device_check();
    if (pc_connect)
    {
        input_number_en = 0;
        //vol_change_en=1;
        //sd_speed_init(0, 100);
        main_menu = MENU_USBDEV_MAIN;
        disp_port(MENU_USBDEV_MAIN);
        usb_config(USB_DEVICE_CFG);
        write_protect_set(0);                           //不使用写保护功能,如果需要，请根据卡座写保护的状态改变配置
        SYSTEM_CLK_DIV1();
        init_usb_device_hardware();
        //key_table_sel(0);
        flush_all_msg();
#if ((USB_DEVICE_CFG & USB_SPEAKER) == USB_SPEAKER)
        set_eq(eq_mode);
#endif
        alm_request_cnt = 0;
        set_max_vol(MAX_ANOLOG_VOL,MAX_DIGITAL_VOL);///设置最大音量
        usb_device();
#if ((USB_DEVICE_CFG & USB_SPEAKER) == USB_SPEAKER)
        main_vol_set(0, CHANGE_VOL_NO_MEM);
#endif
        IE1 &= ~BIT(1);
        P3PU &= ~BIT(6);
    }
    else
    {
        work_mode++;
    }
}

#endif





