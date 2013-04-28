/*--------------------------------------------------------------------------*/
/**@file     iic.h
   @brief    IIC头文件
   @details
   @author
   @date   2010-12-13
   @note
*/
/*----------------------------------------------------------------------------*/

#ifndef _IIC_H_
#define _IIC_H_

#define USE_RTC_RAM       0///< 1:使用RTC内部的64个字节的RAM做记忆，掉电不能记忆；0:使用EEROM做记忆
#ifdef __C51__
#include "gpio_if.h"
#include "config.h"

//1 for RTC RAM
enum 
{
	 MEM_SD_PLAYPOINT_ID0,
	 MEM_SD_PLAYPOINT_ID0_DUMP,
	 MEM_SD_PLAYPOINT_ID1,
	 MEM_SD_PLAYPOINT_ID1_DUMP1,
	 MEM_SD_PLAYPOINT_ID1_DUMP2,
	 MEM_SD_PLAYPOINT_ID1_DUMP3, 
	 MEM_SD_PLAYPOINT_ID2,
	 MEM_SD_PLAYPOINT_ID2_DUMP1,
	 MEM_SD_PLAYPOINT_ID2_DUMP2,
	 MEM_SD_PLAYPOINT_ID2_DUMP3, 

	 MEM_USB_PLAYPOINT_ID0,
	 MEM_USB_PLAYPOINT_ID0_DUMP,
	 MEM_USB_PLAYPOINT_ID1,
	 MEM_USB_PLAYPOINT_ID1_DUMP1,
	 MEM_USB_PLAYPOINT_ID1_DUMP2,
	 MEM_USB_PLAYPOINT_ID1_DUMP3,
	 MEM_USB_PLAYPOINT_ID2,
	 MEM_USB_PLAYPOINT_ID2_DUMP1,
	 MEM_USB_PLAYPOINT_ID2_DUMP2,
	 MEM_USB_PLAYPOINT_ID2_DUMP3,
};

//1 for EEPROM
enum 
{
#if 1//(BREAK_POINT_PLAY_EN)
	 MEM_EXT_SD_PLAYPOINT_ID0,
	 MEM_EXT_SD_PLAYPOINT_ID0_DUMP,
	 MEM_EXT_USB_PLAYPOINT_ID0,
	 MEM_EXT_USB_PLAYPOINT_ID0_DUMP,
	 MEM_ACTIVE_DEV,
#else
	 MEM_ACTIVE_DEV=MEM_USB_PLAYPOINT_ID2_DUMP3,
#endif	 
	 MEM_EQ_MODE,
	 MEM_PLAY_MODE,
	 MEM_SYS_VOL,
	 MEM_SYSMODE, 
	 MEM_RADIO_FREQ_BASE,
	 MEM_FM_FRE=MEM_RADIO_FREQ_BASE,
	 MEM_AM_FRE,
	 MEM_SW0_FRE,
	 MEM_SW1_FRE,
	 MEM_SW2_FRE,
	 MEM_SW3_FRE,
	 MEM_SW4_FRE,
	 MEM_RADIO_BAND_CHAN,
	 MEM_RADIO_TOTAL_STATION_BASE,
	 MEM_RADIO_FM_TOTAL_STATION=MEM_RADIO_TOTAL_STATION_BASE,
	 MEM_RADIO_AM_TOTAL_STATION,
	 MEM_RADIO_SW0_TOTAL_STATION,
	 MEM_RADIO_SW1_TOTAL_STATION,
	 MEM_RADIO_STATION_BASE,

};

#define MEM_RADIO_STATION_MAX       50
#define MEM_RADIO_SW_STATION_MAX       100

#if 0
#if defined(IIC_GPIO_USE_P00_P01)
#define iic_data_out()    P0DIR &= ~(BIT(1));P0PU |= BIT(1) 	
#define iic_data_in()     P0DIR |= (BIT(1));P0PU |= BIT(1)	
#define iic_data_r()      P01
#define iic_data_h()      P01 = 1
#define iic_data_l()      P01 = 0

#define iic_clk_out()    P0DIR &= ~(BIT(0));P0PU |= (BIT(0))
#define iic_clk_h()      P00 = 1
#define iic_clk_l()      P00 = 0
#elif defined(IIC_GPIO_USE_P02_P03)
#define iic_data_out()    P0DIR &= ~(1<<2);P0PU |= (1<<2)
#define iic_data_in()     P0DIR |= (1<<2);P0PU |= (1<<2)
#define iic_data_r()      P02
#define iic_data_h()      P02 = 1
#define iic_data_l()      P02 = 0

#define iic_clk_out()    P0DIR &= ~(1<<3);P0PU |= (1<<3)
#define iic_clk_h()      P03 = 1
#define iic_clk_l()      P03 = 0
#else
#define iic_data_out()   P1DIR &= ~(1<<6);//P0PU |= (1<<2)
#define iic_data_in()    P1DIR |= (1<<6);P1PU |= (1<<6)
#define iic_data_r()     P16
#define iic_data_h()     P16 = 1
#define iic_data_l()     P16 = 0

#define iic_clk_out()    P1DIR &= ~(1<<7);//P0PU |= (1<<3)
#define iic_clk_h()      P17 = 1
#define iic_clk_l()      P17 = 0
#endif
#endif

#define iic_delay()      delay(15)


extern u8 read_info(u16 addr);
extern void write_info(u16 addr,u8 dat);
extern u8 read_rtc_ram(u8 addr);
extern void write_rtc_ram(u8 addr,u8 dat);

void iic_init_io(void);
void iic_start(void);
void iic_stop(void);
bool r_ack(void);
void s_ack(u8 flag);
u8 iic_revbyte_io( void );
u8 iic_revbyte( u8 para );
void iic_sendbyte_io(u8 byteI2C);
void iic_sendbyte(u8 byte);

void  iic_write(u8 chip_id,u8 iic_addr,u8 *iic_dat,u8 n);
void iic_readn(u8 chip_id,u8 iic_addr,u8 *iic_dat,u8 n);


u8 read_eerom(u16 iic_addr);
void write_eerom(u16 addr,u8 dat);
//void  eeprom_page_write_start(void);
//void  eeprom_page_write_stop(void);

u8 read_music_info(u16 addr);
void write_music_info(u16 addr,u8 dat);

#endif




#endif
