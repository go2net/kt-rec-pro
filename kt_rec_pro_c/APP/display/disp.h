/*--------------------------------------------------------------------------*/
/**@file   disp.h
   @brief    显示模块头文件
   @details
   @author
   @date   2010-12-13
   @note
*/
/*----------------------------------------------------------------------------*/
#ifndef   _DISP_H_
#define  _DISP_H_

#include "config.h"
#include "my_printf.h"

#ifdef __C51__

enum
{
    MENU_NULL = 0,
    MENU_VER= 0,
    MENU_PLAY,
    MENU_PAUSE,
    MENU_MAIN_VOL,
    MENU_EQ,
    MENU_POWER_UP,
    MENU_POWER_OFF,
    MENU_PLAYMODE,
    MENU_NOFILE,
    MENU_NODEVICE,
    MENU_DEL_FIL,
    MENU_PLAY_TIME,
    MENU_FILENUM,
    MENU_INPUT_NUMBER,
    MENU_WAIT,
    MENU_USBDEV_MAIN,
    MENU_MUSIC_MAIN,
    MENU_RADIO_MAIN,
    MENU_RADIO_DISP_FRE,
    MENU_RADIO_FIND_STATION,
    MENU_RADIO_CHANNEL,
    MENU_USBREMOVE,
    MENU_SDREMOVE,
    MENU_SCAN_DISK,
    MENU_AUX,
    MENU_RTC,
    MENU_RTC_PWD,
    MENU_ALM_UP,
    MENU_ALM_SET,
    MENU_ALM_REQUEST,
	MENU_REC_MAIN ,
	MENU_REC_ERR,
    MENU_SET_EQ,
    MENU_SET_PLAY_MODE,
    MENU_RECWORKING,
    MENU_REC,
	MENU_REC_PAUSE,
    MENU_BLUE_TOOTH_MAIN,
    MENU_200MS_REFRESH = 0x80,
    MENU_100MS_REFRESH,

    MENU_HALF_SEC_REFRESH,
    MENU_POWER_DOWN,
};

enum
{
    PLED_OFF= 0,
    PLED_ON,
    PLED_SPARK_V_FAST,
    PLED_SPARK_FAST,
    PLED_SPARK_NOR,
    PLED_SPARK_SLOW,
};

void disp_power_on(void);
void disp_fm_freq(void);
void disp_input_number(u16 num);
void disp_main_vol(u8 vol);
void update_disp_icon();



void disp_music_play_time(void);
void disp_music_format(void);
void disp_roll_ctrl(u8 mode);
void disp_main_menu_refresh(void);
void disp_eq(void);

void init_display(void);

void disp_flash_icon(u8 id);

void disp_rec_working(void);

#ifdef PLAY_STATUS_LED_FUNC
void play_status_led_init();
void set_play_status_led_spark(u8 speed);
void play_status_led_hdlr();
#endif

#endif

#define SUB_MENU_TIME         (1*6)

#endif
