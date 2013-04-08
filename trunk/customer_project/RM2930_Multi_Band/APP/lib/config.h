/*--------------------------------------------------------------------------*/
/**@file     config.h
   @brief    һЩ��������������
   @author
   @date   2010-12-13
   @note   AC309N
*/
/*----------------------------------------------------------------------------*/

#include "Custom_config.h"

#ifndef _CONFIG_
#define _CONFIG_

#include "AC309N.h"
#include "typedef.h"
#include "entry.h"
#include "clock.h"



#define USB_DEVICE_ENABLE		0		///���ݿͻ�ѡ�õ�bsp�⣬��Ӧ��ѡ���Ƿ��
#define RTC_ENABLE              1       ///<RTCʹ�ܣ��������Ҫʹ��RTC���ܣ��˴���0


//��ʾ��ѡ��

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
    DIS_SD_CMD_CHK = 0,	///<��������SD������״̬������£���ͣSD���߼��
    EN_SD_CMD_CHK,		///<��������SD������״̬������£��ָ�SD���߼��
    SET_SD_H_CHK,		///<��������SD������״̬������£�SD������ʱ���100MSһ��
    SET_SD_L_CHK,		///<��������SD������״̬������£�SD������ʱ���1Sһ��
}Sd_api_cmd;


#ifdef MCU_ADC_VOL_TUNER
#define FM_MODULE			3
#elif defined(RADIO_VAR_VOL_TUNE)
#define FM_MODULE			2
#else
#define FM_MODULE			1
#endif
enum
{
    MUSIC_MODE = 0,
#if FM_MODULE 
    FM_RADIO_MODE,
#endif
    AUX_MODE,
    BLUE_TOOTH_MODE,
#if RTC_ENABLE
    RTC_MODE,
#endif
    REC_MIC_MODE,
    IDLE_MODE,
#if USB_DEVICE_ENABLE
    USB_DEVICE_MODE,
#endif

};

enum{

	SYS_CLK_1M_RC,
	SYS_CLK_4M_HPRC,
	SYS_CLK_48M_PLL,
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
//����ʱ��ѡ�񣬾������clock.h   
#if defined(OSC_USE_12M)
#define INPUT_OSC_SELECT                PLL_IN_OSC1_12M// PLL_IN_HPRC//
#else
#define INPUT_OSC_SELECT                PLL_IN_OSC0_32K // PLL_IN_HPRC//
#endif
#define SHARE_32768_PERIPHERALS    0					///<�Ƿ������蹲��32768���壬0�������ã�1�����þ��壨�������ȣ�


                                       
///////work mode
#if RTC_ENABLE
#define MAX_WORK_MODE	 RTC_MODE
#else
#define MAX_WORK_MODE	 AUX_MODE
#endif

#define IDLE_WORK_MODE   REC_MIC_MODE


//���ֲ��Ź���ѡ��
#define    BREAK_POINT_PLAY_EN				1			//�Ƿ�����ϵ㲥�Ź���
#define    LAST_MEM_FILE_PLAY_EN            		0			//�Ƿ���������ļ���Ų��Ź���
//#define    ID3_TAG_EN						0
#define    FF_FR_EN                         1			//�Ƿ����������˹���
#define    FF_FR_MUSIC                      1			//�ڿ������ʱ���Ƿ���Ҫ��������

#define    BURST_OUT_POINT_SAVE_ENABLE      0			//ͻȻ�ϵ�ʹ��λ,1��Ч,3.3V��Ҫ����֧������100��F
#define    MUSIC_FADE_OUT_EN				1			//�л������ĵ���ʹ�ܣ� 1��Ч
#define    VIRTUAL_ENABLE                   0           //2/<�������ʹ�� 1��enable��0��disable��

#define   KALAOK_FUNCTION     				0		   ///<������ok����
#define   CH_MODE_SUBTRACT					0          ///<��musicģʽ�¿���������ʱ�Ƿ�Ҫ�Ѹ��������
//sd���ģʽ

#define SDMMC_CLK_MODE   1	  ///<ʹ��SD clk ��ѯģʽ
#define SDMMC_GPIO_MODE  0	  ///<ʹ�ö�����GPIO��SD���߲�ѯģʽ



#define     MP3CLK      BIT(6)
#define     SPIURCLK    BIT(4)
#define     DACCLK      BIT(6)
#define     USBCLK      BIT(0)
#define     SDCLK       BIT(5)


#endif
