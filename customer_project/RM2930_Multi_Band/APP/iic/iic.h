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

//#include "config.h"

#define USE_RTC_RAM       0///< 1:使用RTC内部的64个字节的RAM做记忆，掉电不能记忆；0:使用EEROM做记忆

#ifdef __C51__

#include "gpio_if.h"

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


extern u8 read_info(u8 addr);
extern void write_info(u8 addr,u8 dat);
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


u8 read_eerom(u8 iic_addr);
void write_eerom(u8 addr,u8 dat);
void  eeprom_page_write_start(void);
void  eeprom_page_write_stop(void);
#endif





#define MEM_FM_CHANNL            0
#define MEM_FRE            0
#define MEM_CHAN		   1
#define MEM_CHANNL         2
#define MEM_VOL_BAND         6
#define MEM_FM_LEN         26//28

#define MEM_ACTIVE_DEV     29



#define MEM_SD_PLAYPOINT_ID0   30// 32
#define MEM_SD_PLAYPOINT_ID1   32//	36
#define MEM_SD_PLAYPOINT_ID2   36// 40

#define MEM_EQ_MODE        40
#define MEM_PLAY_MODE      41
#define MEM_PLAY_MODE_REC  42
#define MEM_VOL            43
#define MEM_SYSMODE        44
#define MEM_USB_PLAYPOINT_ID0   46//48
#define MEM_USB_PLAYPOINT_ID1	48//52
#define MEM_USB_PLAYPOINT_ID2   52//56




#define MEM_ALARM_0_HOUR  	60
#define MEM_ALARM_0_MIN	  	61



#define MEM_REC_SD_PLAYPOINT_ID0   70// 72
#define MEM_REC_SD_PLAYPOINT_ID1   72//	76
#define MEM_REC_SD_PLAYPOINT_ID2   76// 80

#define MEM_REC_USB_PLAYPOINT_ID0   86//48
#define MEM_REC_USB_PLAYPOINT_ID1	88//82
#define MEM_REC_USB_PLAYPOINT_ID2   92//86

#define MEM_REC_D_VALUE (MEM_REC_SD_PLAYPOINT_ID0 - MEM_SD_PLAYPOINT_ID0)

//#define MEM_ALARM_0_DAYS	62
//#define MEM_ALARM_1_HOUR  62
//#define MEM_ALARM_1_MIN	  63
//#define MEM_ALARM_2_HOUR  64
//#define MEM_ALARM_2_MIN	  65
//#define MEM_ALARM_3_HOUR  66
//#define MEM_ALARM_3_MIN	  67
//#define MEM_ALARM_4_HOUR  68
//#define MEM_ALARM_4_MIN	  69
//#define MEM_ALARM_ALL_SW  70	///<按位存储闹钟开关状态
#define EEPROM_SIGN			127		 ///<用作EEPROM识别位
#endif
