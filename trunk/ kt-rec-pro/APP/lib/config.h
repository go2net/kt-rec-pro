/*--------------------------------------------------------------------------*/
/**@file     config.h
   @brief    一些基本参数的配置
   @author
   @date   2010-12-13
   @note   AC309N
*/
/*----------------------------------------------------------------------------*/

//#define UART_ENABLE
#ifdef UART_ENABLE
#define USE_UART_P24_P25
#endif

#define MUTE_CTRL_LEVEL_NORMAL
//#define REC_PLAY_KEY_BREAK_POINT
//#define DEFAULT_VOL		0

//#define IIC_GPIO_USE_P00_P01
//#define IIC_GPIO_USE_P02_P03
//#define EXCHANGE_AUX_CHANNEL
//#define CUSTOM_DEFINED_FOLDER
//#define NO_LED_DISPLAY
//#define NEW_DH_LCD_MODULE_SM5901
//#define NEW_DH_LCD_MODULE_SM5858


#define JK_HT_998_MODULE
//#define JK_SZ_S900_MODULE
//#define JK_JF_168_MODULE
//#define JK_DH_105_104_MODULE
//#define JK289_MODULE
//#define K129_MODULE
//#define JK299_MODULE



#if defined(JK_HT_998_MODULE)

#define NEW_DH_LCD_MODULE_SM5858

#ifdef NEW_DH_LCD_MODULE_SM5858
#define DISP_PAU_STR
#endif

#define SW_FULL_BAND_RANGE_END_AT_23MHZ

#define REC_PLAY_KEY_BREAK_POINT
#define FM_FREQ_NUM_KEY_INPUT

#define IIC_GPIO_USE_P00_P01
#define MUTE_PORT_USE_P03

#define REPEAT_MODE_USE_ONE_ALL

#define EXCHANGE_AUX_CHANNEL
#define USE_BAT_MANAGEMENT
#define DEFAULT_VOL		MAX_MAIN_VOL
#define LCD_GPIO_DRV
#define NO_AUX_CHANNEL
#define SAVE_BAND_FREQ_INFO
#define JOG_STICK_FUNC
#define FAST_STICK_TUNE_FUNC


#define CHARGER_DETECT_INDICATOR

#define DC_CHARGER_DET_SHARE_IIC
#define USE_GPIO_MEASURE_VOLT

#define PLAY_MODE_IN_USE
#define REPEAT_MODE_USE_ONE_ALL
#define DISP_PLAY_MODE_STR
#endif

#if defined(JK_JF_168_MODULE)

#define JF_168_LCD_MODULE

#define SW_TWO_BAND_RANGE
#define REC_PLAY_KEY_BREAK_POINT
#define FM_FREQ_NUM_KEY_INPUT

#define IIC_GPIO_USE_P00_P01
#define MUTE_PORT_USE_P03

#define REPEAT_MODE_USE_ONE_ALL

#define EXCHANGE_AUX_CHANNEL
#define DEFAULT_VOL		MAX_MAIN_VOL
#define LCD_GPIO_DRV
#define NO_AUX_CHANNEL
#define SAVE_BAND_FREQ_INFO
#define JOG_STICK_FUNC
#define FAST_STICK_TUNE_FUNC

//#define USE_BAT_MANAGEMENT
//#define CHARGER_DETECT_INDICATOR
//#define DC_CHARGER_DET_SHARE_IIC
//#define USE_GPIO_MEASURE_VOLT
#define PLAY_STATUS_LED_FUNC


#define PLAY_MODE_IN_USE
#define REPEAT_MODE_USE_ONE_ALL
#define DISP_PLAY_MODE_STR
#endif



#if defined(JK_DH_105_104_MODULE)

#define NEW_DH_107_105_104_LCD_MODULE

#define SW_TWO_BAND_RANGE
#define REC_PLAY_KEY_BREAK_POINT
#define FM_FREQ_NUM_KEY_INPUT

#define IIC_GPIO_USE_P00_P01
#define MUTE_PORT_USE_P03

#define REPEAT_MODE_USE_ONE_ALL

#define EXCHANGE_AUX_CHANNEL
#define DEFAULT_VOL		MAX_MAIN_VOL
#define LCD_GPIO_DRV
#define NO_AUX_CHANNEL
#define SAVE_BAND_FREQ_INFO
#define JOG_STICK_FUNC
#define FAST_STICK_TUNE_FUNC


//#define USE_BAT_MANAGEMENT
//#define CHARGER_DETECT_INDICATOR
//#define DC_CHARGER_DET_SHARE_IIC
//#define USE_GPIO_MEASURE_VOLT

#define PLAY_MODE_IN_USE
#define REPEAT_MODE_USE_ONE_ALL
#define DISP_PLAY_MODE_STR
#endif


#if defined(JK_SZ_S900_MODULE)

#define NEW_DH_LCD_MODULE_SM5858

#ifdef NEW_DH_LCD_MODULE_SM5858
#define DISP_PAU_STR
#endif

#define SW_TWO_BAND_RANGE
#define REC_PLAY_KEY_BREAK_POINT
#define FM_FREQ_NUM_KEY_INPUT

#define IIC_GPIO_USE_P00_P01
#define MUTE_PORT_USE_P03

#define REPEAT_MODE_USE_ONE_ALL

#define EXCHANGE_AUX_CHANNEL
#define USE_BAT_MANAGEMENT
#define DEFAULT_VOL		MAX_MAIN_VOL
#define LCD_GPIO_DRV
#define NO_AUX_CHANNEL
#define CHARGER_DETECT_INDICATOR
#define SAVE_BAND_FREQ_INFO
#define JOG_STICK_FUNC
#define FAST_STICK_TUNE_FUNC

#define DC_CHARGER_DET_SHARE_IIC
#define USE_GPIO_MEASURE_VOLT

#define PLAY_MODE_IN_USE
#define REPEAT_MODE_USE_ONE_ALL
#define DISP_PLAY_MODE_STR
#endif

#if defined(JK299_MODULE)

#define USE_LCD_DRV_HT1621
#define DISP_REC_ICON_WHEN_RECORDING
#define REC_PLAY_KEY_BREAK_POINT
#define FM_FREQ_NUM_KEY_INPUT

#define IIC_GPIO_USE_P00_P01
#define MUTE_PORT_USE_P03

#define EXCHANGE_AUX_CHANNEL

#define DEFAULT_VOL		MAX_MAIN_VOL
#define NO_AUX_CHANNEL
#define SAVE_BAND_FREQ_INFO
#define JOG_STICK_FUNC
#define FAST_STICK_TUNE_FUNC


#define REPEAT_MODE_USE_ONE_ALL
#define PLAY_MODE_IN_USE

#define USE_BAT_MANAGEMENT
#define DC_CHARGER_DET_SHARE_IIC
#define USE_GPIO_MEASURE_VOLT
#define CHARGER_DETECT_INDICATOR

#endif

#if defined(K129_MODULE)

#define NEW_DH_LCD_MODULE_SM5901

#define DISP_PAU_STR

#define SW_TWO_BAND_RANGE

#define REC_PLAY_KEY_BREAK_POINT
#define FM_FREQ_NUM_KEY_INPUT

#define IIC_GPIO_USE_P00_P01
#define MUTE_PORT_USE_P03

#define REPEAT_MODE_USE_ONE_ALL

#define EXCHANGE_AUX_CHANNEL
#define USE_BAT_MANAGEMENT
#define DEFAULT_VOL		MAX_MAIN_VOL
#define LCD_GPIO_DRV
#define NO_AUX_CHANNEL
#define SAVE_BAND_FREQ_INFO
#define JOG_STICK_FUNC
#define FAST_STICK_TUNE_FUNC


#define CHARGER_DETECT_INDICATOR

#define DC_CHARGER_DET_SHARE_IIC
#define USE_GPIO_MEASURE_VOLT

#define PLAY_MODE_IN_USE
#define REPEAT_MODE_USE_ONE_ALL
#define DISP_PLAY_MODE_STR
#endif

#if defined(JK289_MODULE)

#define NEW_DH_LCD_MODULE_SM5858

#ifdef NEW_DH_LCD_MODULE_SM5858
#define DISP_PAU_STR
#endif

#define REC_PLAY_KEY_BREAK_POINT
#define FM_FREQ_NUM_KEY_INPUT

#define IIC_GPIO_USE_P00_P01
#define MUTE_PORT_USE_P03

#define REPEAT_MODE_USE_ONE_ALL

#define EXCHANGE_AUX_CHANNEL
#define USE_BAT_MANAGEMENT
#define DEFAULT_VOL		MAX_MAIN_VOL
#define LCD_GPIO_DRV
#define NO_AUX_CHANNEL
#define SAVE_BAND_FREQ_INFO
#define JOG_STICK_FUNC
#define FAST_STICK_TUNE_FUNC


#define CHARGER_DETECT_INDICATOR

#define DC_CHARGER_DET_SHARE_IIC
#define USE_GPIO_MEASURE_VOLT

#define PLAY_MODE_IN_USE
#define REPEAT_MODE_USE_ONE_ALL
#define DISP_PLAY_MODE_STR
#endif





#ifndef _CONFIG_
#define _CONFIG_

#include "AC309N.h"
#include "typedef.h"
#include "entry.h"
#include "clock.h"



#define USB_DEVICE_ENABLE		0		///根据客户选用的bsp库，对应地选择是否打开
#define RTC_ENABLE              1       ///<RTC使能，如果不需要使用RTC功能，此处填0


//显示屏选择

#define DISP_LED5X7           1
#define DLED				  2
#define NO_DISP				  3
#define LCD_DISP				  4
#define LCD_DRV_DISP		5

#ifdef LCD_GPIO_DRV
#define monitor       LCD_DISP
#elif defined(USE_LCD_DRV_HT1621)
#define monitor      	LCD_DRV_DISP
#endif
#ifdef __C51__
#include "intrins.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "encode.h"

typedef enum
{
    DIS_SD_CMD_CHK = 0,	///<在命令检测SD卡在线状态的情况下，暂停SD在线检测
    EN_SD_CMD_CHK,		///<在命令检测SD卡在线状态的情况下，恢复SD在线检测
    SET_SD_H_CHK,		///<在命令检测SD卡在线状态的情况下，SD不在线时检测100MS一次
    SET_SD_L_CHK,		///<在命令检测SD卡在线状态的情况下，SD不在线时检测1S一次
}Sd_api_cmd;




#define FM_MODULE			1

enum
{
    MUSIC_MODE = 0,
#if USB_DEVICE_ENABLE
    USB_DEVICE_MODE,
#endif

#if FM_MODULE 
    FM_RADIO_MODE,
#endif

    AUX_MODE,
#if RTC_ENABLE
    RTC_MODE,
#endif
    REC_MIC_MODE,
    IDLE_MODE,
};



//    void flashled(u8 fre);
//    void disp_dled(void);
//    void dled_ctl(u8 flag);
//    extern void set_brightness(u8 br);
extern void set_brightness_fade_out(void);
extern void set_brightness_all_on(void);
extern void disp_port(u8 menu);

#endif
                               //(PLL_IN_OSC0_32K | PLL_IN_OSC0_4M | PLL_IN_OSC0_12M | PLL_IN_OSC1_4M | PLL_IN_OSC1_12M | PLL_IN_HPRC)//
//输入时钟选择，具体请见clock.h   
#if defined(OSC_USE_12M)
#define INPUT_OSC_SELECT                PLL_IN_OSC1_12M// PLL_IN_HPRC//
#else
#define INPUT_OSC_SELECT                PLL_IN_OSC0_32K // PLL_IN_HPRC//
#endif
#define SHARE_32768_PERIPHERALS    0					///<是否与外设共用32768晶体，0：不共用，1：共用晶体（如收音等）


                                       
///////work mode
#if RTC_ENABLE
#define MAX_WORK_MODE	 RTC_MODE
#else
#define MAX_WORK_MODE	 AUX_MODE
#endif

#define IDLE_WORK_MODE   REC_MIC_MODE


//音乐播放功能选择
#define    BREAK_POINT_PLAY_EN				0			//是否允许断点播放功能
#define    LAST_MEM_FILE_PLAY_EN            1			//是否允许记忆文件序号播放功能
//#define    ID3_TAG_EN						0
#define    FF_FR_EN                         1			//是否允许快进快退功能
#define    FF_FR_MUSIC                      1			//在快进快退时，是否需要听到声音

#define    BURST_OUT_POINT_SAVE_ENABLE      0			//突然断电使能位,1有效,3.3V需要电容支持至少100μF
#define    MUSIC_FADE_OUT_EN				1			//切换歌曲的淡出使能， 1有效
#define    VIRTUAL_ENABLE                   0           //2/<虚拟设别使能 1：enable；0：disable；

#define   KALAOK_FUNCTION     				0		   ///<开卡拉ok功能
#define   CH_MODE_SUBTRACT					0          ///<在music模式下开了扩音机时是否要把歌曲声相减
//sd检测模式

#define SDMMC_CLK_MODE   1	  ///<使用SD clk 查询模式
#define SDMMC_GPIO_MODE  0	  ///<使用独立的GPIO做SD在线查询模式



#define     MP3CLK      BIT(6)
#define     SPIURCLK    BIT(4)
#define     DACCLK      BIT(6)
#define     USBCLK      BIT(0)
#define     SDCLK       BIT(5)


#endif
