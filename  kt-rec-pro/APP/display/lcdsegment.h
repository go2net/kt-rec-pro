
#include "config.h"
#if(LCD_DISP == monitor)

#ifndef _LCDSEGMENT_H_
#define _LCDSEGMENT_H_

/*
COM1 P30
COM2 P31
COM3 P32
COM4 P33
SEG0~7   P10~P17
SEG8     P34
*/
#define 	DIG_A	0x01
#define 	DIG_B	0x02
#define 	DIG_C	0x04
#define 	DIG_D	0x08
#define 	DIG_E	0x10
#define 	DIG_F	0x20
#define 	DIG_G	0x40
#define 	DIG_H	0x80
#ifdef __C51__

#if 0
#define play_led_seg_out() P0DIR &= ~0x80;P0PU |= 0x80;
#endif


#if defined(K820_LHD_820_REC_V001)
#define   com_init()      P3PU |= (0x0F);P3PD |= (0x0F)
#define   close_com(n)    com_init();P3DIR |= (0x0F);P3DIR &= ~(1<<(n))
    
#define	set_com(n)      P3 |= (1<<(n))
#define   clr_com(n)       P3 &= ~(1<<(n)) 
	
#define   seg_init()      P1DIR =0;P3DIR &= ~(1<<4)//;P3PU &= ~(1<<4);P3PD &= ~(1<<4)
#define   seg07_port(n)   	P1 = n
#define   seg8_port(n)	P34 = n
#define   bklt_init()	  P3DIR &= ~(1<<0);P3 |= (1<<0);

#elif defined(K129_MODULE0000000000000000000000000)

#define   com_init()      P3PU |= (0x1F);P3PD |= (0x1F)
#define   close_com(n)    com_init();P3DIR |= (0x1F);P3DIR &= ~(1<<(n))
    
#define	set_com(n)      P3 |= (1<<(n))
#define   clr_com(n)       P3 &= ~(1<<(n)) 
	
#define   seg_init()      	P1DIR = 0;P0DIR &= ~(BIT(2));P0PU &= ~(BIT(2))//;P3PD &= ~(BIT(4))
#define   seg07_port(n)   	P1 = n

#else

#define   com_init()      P3PU |= (0x1F);P3PD |= (0x1F)
#define   close_com(n)    com_init();P3DIR |= (0x1F);P3DIR &= ~(1<<(n))
    
#define	set_com(n)      P3 |= (1<<(n))
#define   clr_com(n)       P3 &= ~(1<<(n)) 
	
#define   seg_init()      	P1DIR = 0;P0DIR &= ~(BIT(2));P0PU &= ~(BIT(2))//;P3PD &= ~(BIT(4))
#define   seg07_port(n)   	P1 = n
#define   seg8_port(n)	P02 = n
//#define   bklt_init()	  	//P3DIR &= ~(1<<0);P3 |= (1<<0);
#endif

#define  LCD_BACKLIGHT_INIT()	  P0DIR &=~(BIT(4));P0PU|= (BIT(4))
#define LCD_BACKLIGHT_ON()		P04 =0;
#define LCD_BACKLIGHT_OFF()		P04 =1;

#endif

enum {

	USB_ICON,
	SD_ICON,
	AUX_ICON,
	FM_MHZ_ICON,
	AM_KHZ_ICON,
	SW_ICON,
	REC_ICON,
	REP_1_ICON,
	REP_ALL_ICON,
	COL_ICON,
	MUTE_ICON,
	
	BAT_ICON,
	BAT_S1_ICON,
	BAT_S2_ICON,
	BAT_S3_ICON,
	BAT_S4_ICON,

	NONE_ICON,
};

#if defined(K129_MODULE000000000000000)

#define USB_DEV_MASK	0x0004
#define F_USB_DEV  		(lcd_buff[1])	

#define AUX_DEV_MASK	0x0000
#define F_AUX_DEV  		(lcd_buff[1])

#define SD_DEV_MASK	0x0004
#define F_SD_DEV		(lcd_buff[1])	

#define FM_DEV_MASK	0x0000
#define F_FM_DEV		(lcd_buff[1])	

#define POINTS_MASK		0x0010
#define F_POINTS		(lcd_buff[1])	

#define FM_MHZ_MASK	0x0024
#define F_MHZ_DEV		(lcd_buff[0])	

#define AM_KHZ_MASK	0x0082
#define F_KHZ_DEV		(lcd_buff[0])	

#define FM_P1_MASK		0x0000
#define F_P1_DEV		(lcd_buff[3])	

#define SW_MHZ_MASK	0x0001
#define F_SW_DEV		(lcd_buff[1])	


#define RTC_ICON_MASK	0x0000
#define F_RTC_ICON		(lcd_buff[3])

#define RTC_ALM_MASK	0x0000
#define F_RTC_ALM		(lcd_buff[3])	

#define RTC_PM_MASK	0x0000
#define F_RTC_PM		(lcd_buff[2])

#define RTC_AM_MASK	0x0000
#define F_RTC_AM		(lcd_buff[3])

#define REC_ICON_MASK	0x0040
#define F_REC_DEV		(lcd_buff[1])	

#define SPK_MUTE_MASK	0x0040
#define F_SPK_DEV		(lcd_buff[0])	

#define BATTERY_MASK	0x00000
#define F_BAT_ICON_BUF	(lcd_buff[0])	


#define TRADEMARK_MASK	0x0000
#define TRADEMARK_ICON		(lcd_buff[0])	

#define NUM_1BC_MASK	0x0000
#define F_NUM_1BC		(lcd_buff[2])	

#define REP_ALL_MASK	0//0x0004
#define REP_ONE_MASK	0//0x0008
#define F_REP_ALL		(lcd_buff[4])
#define F_REP_ONE 		(lcd_buff[0])

//#define L_ICON_BUF		(lcd_buff[4])
#define S1_ICON_MASK	0x0000
#define S1_ICON_BUF		(lcd_buff[0])
#define S2_ICON_MASK	0x0000
#define S2_ICON_BUF		(lcd_buff[0])
#define S3_ICON_MASK	0x0000
#define S3_ICON_BUF		(lcd_buff[0])
#define S4_ICON_MASK	0x0000
#define S4_ICON_BUF		(lcd_buff[0])

#elif defined(JF_168_LCD_MODULE)
#define USB_DEV_MASK	0x0080
#define F_USB_DEV  		(lcd_buff[0])	

#define AUX_DEV_MASK	0x0100
#define F_AUX_DEV  		(lcd_buff[0])

#define SD_DEV_MASK	0x0080
#define F_SD_DEV		(lcd_buff[4])	

#define FM_DEV_MASK	0x0100
#define F_FM_DEV		(lcd_buff[2])	

#define AM_DEV_MASK	0x0100
#define F_AM_DEV		(lcd_buff[3])	

#define SW_DEV_MASK	0x0100
#define F_SW_DEV		(lcd_buff[4])	

#define POINTS_MASK		0x0008
#define F_POINTS		(lcd_buff[4])	

#define FM_MHZ_MASK	0x0040
#define F_MHZ_DEV		(lcd_buff[0])	

#define AM_KHZ_MASK	0x0010
#define F_KHZ_DEV		(lcd_buff[0])	

#define SW_MHZ_MASK	0x0040
#define F_SW_MHZ_DEV	(lcd_buff[0])	

#define FM_P1_MASK		0x0002
#define F_P1_DEV		(lcd_buff[4])	

#define SW_P2_MASK		0x0020
#define F_P2_DEV		(lcd_buff[4])	

#define RTC_ICON_MASK	0x0000
#define F_RTC_ICON		(lcd_buff[3])

#define RTC_ALM_MASK	0x0000
#define F_RTC_ALM		(lcd_buff[4])	

#define RTC_PM_MASK	0x0000
#define F_RTC_PM		(lcd_buff[2])

#define RTC_AM_MASK	0x0000
#define F_RTC_AM		(lcd_buff[3])

#define REC_ICON_MASK	0x0000
#define F_REC_DEV		(lcd_buff[4])	

#define SPK_MUTE_MASK	0x0080
#define F_SPK_DEV		(lcd_buff[0])	

#define BATTERY_MASK	0x0000
#define F_BAT_ICON_BUF	(lcd_buff[0])	


#define TRADEMARK_MASK	0x0000
#define TRADEMARK_ICON		(lcd_buff[0])	

#define NUM_1BC_MASK	0x0000
#define F_NUM_1BC		(lcd_buff[2])	

#define REP_ALL_MASK	0x0000
#define REP_ONE_MASK	0x004
#define F_REP_ALL		(lcd_buff[4])
#define F_REP_ONE 		(lcd_buff[0])

//#define L_ICON_BUF		(lcd_buff[4])
#define S1_ICON_MASK	0x0000
#define S1_ICON_BUF		(lcd_buff[0])
#define S2_ICON_MASK	0x0000
#define S2_ICON_BUF		(lcd_buff[0])
#define S3_ICON_MASK	0x0000
#define S3_ICON_BUF		(lcd_buff[0])
#define S4_ICON_MASK	0x0000
#define S4_ICON_BUF		(lcd_buff[0])

#define FIGURE_NUM	4
#elif defined(NEW_DH_107_105_104_LCD_MODULE)

#define USB_DEV_MASK	0x0080
#define F_USB_DEV  		(lcd_buff[0])	

#define AUX_DEV_MASK	0x0100
#define F_AUX_DEV  		(lcd_buff[0])

#define SD_DEV_MASK	0x0080
#define F_SD_DEV		(lcd_buff[4])	

#define FM_DEV_MASK	0x0100
#define F_FM_DEV		(lcd_buff[2])	

#define AM_DEV_MASK	0x0100
#define F_AM_DEV		(lcd_buff[3])	

#define SW_DEV_MASK	0x0100
#define F_SW_DEV		(lcd_buff[4])	

#define POINTS_MASK		0x0008
#define F_POINTS		(lcd_buff[4])	

#define FM_MHZ_MASK	0x0040
#define F_MHZ_DEV		(lcd_buff[0])	

#define AM_KHZ_MASK	0x0010
#define F_KHZ_DEV		(lcd_buff[0])	

#define SW_MHZ_MASK	0x0040
#define F_SW_MHZ_DEV	(lcd_buff[0])	

#define FM_P1_MASK		0x0002
#define F_P1_DEV		(lcd_buff[4])	

#define SW_P2_MASK		0x0020
#define F_P2_DEV		(lcd_buff[4])	

#define RTC_ICON_MASK	0x0000
#define F_RTC_ICON		(lcd_buff[3])

#define RTC_ALM_MASK	0x0000
#define F_RTC_ALM		(lcd_buff[4])	

#define RTC_PM_MASK	0x0000
#define F_RTC_PM		(lcd_buff[2])

#define RTC_AM_MASK	0x0000
#define F_RTC_AM		(lcd_buff[3])

#define REC_ICON_MASK	0x0000
#define F_REC_DEV		(lcd_buff[4])	

#define SPK_MUTE_MASK	0x0080
#define F_SPK_DEV		(lcd_buff[0])	

#define BATTERY_MASK	0x0000
#define F_BAT_ICON_BUF	(lcd_buff[0])	


#define TRADEMARK_MASK	0x0000
#define TRADEMARK_ICON		(lcd_buff[0])	

#define NUM_1BC_MASK	0x0000
#define F_NUM_1BC		(lcd_buff[2])	

#define REP_ALL_MASK	0x0000
#define REP_ONE_MASK	0x004
#define F_REP_ALL		(lcd_buff[4])
#define F_REP_ONE 		(lcd_buff[0])

//#define L_ICON_BUF		(lcd_buff[4])
#define S1_ICON_MASK	0x0000
#define S1_ICON_BUF		(lcd_buff[0])
#define S2_ICON_MASK	0x0000
#define S2_ICON_BUF		(lcd_buff[0])
#define S3_ICON_MASK	0x0000
#define S3_ICON_BUF		(lcd_buff[0])
#define S4_ICON_MASK	0x0000
#define S4_ICON_BUF		(lcd_buff[0])

#define FIGURE_NUM	4
#elif defined(NEW_DH_LCD_MODULE_SM5901)

#define USB_DEV_MASK	0x0001
#define F_USB_DEV  		(lcd_buff[1])	

#define AUX_DEV_MASK	0x0000
#define F_AUX_DEV  		(lcd_buff[0])

#define SD_DEV_MASK	0x0002
#define F_SD_DEV		(lcd_buff[4])	

#define FM_DEV_MASK	0x0000
#define F_FM_DEV		(lcd_buff[1])	


#define POINTS_MASK		0x0008
#define F_POINTS		(lcd_buff[0])	

#define FM_MHZ_MASK	0x0080
#define F_MHZ_DEV		(lcd_buff[0])	

#define AM_KHZ_MASK	0x0080
#define F_KHZ_DEV		(lcd_buff[1])	

#define FM_P1_MASK		0x0002
#define F_P1_DEV		(lcd_buff[0])	

#define SW_MHZ_MASK	0x0080
#define F_SW_DEV		(lcd_buff[2])	


#define RTC_ICON_MASK	0x0000
#define F_RTC_ICON		(lcd_buff[3])

#define RTC_ALM_MASK	0x0000
#define F_RTC_ALM		(lcd_buff[3])	

#define RTC_PM_MASK	0x0000
#define F_RTC_PM		(lcd_buff[2])

#define RTC_AM_MASK	0x0000
#define F_RTC_AM		(lcd_buff[3])

#define REC_ICON_MASK	0x0080
#define F_REC_DEV		(lcd_buff[4])	

#define SPK_MUTE_MASK	0x0080
#define F_SPK_DEV		(lcd_buff[3])	

#define BATTERY_MASK	0x0040
#define F_BAT_ICON_BUF	(lcd_buff[0])	


#define TRADEMARK_MASK	0x0100
#define TRADEMARK_ICON		(lcd_buff[0])	

#define NUM_1BC_MASK	0x0000
#define F_NUM_1BC		(lcd_buff[2])	

#define REP_ALL_MASK	0//0x0004
#define REP_ONE_MASK	0//0x0008
#define F_REP_ALL		(lcd_buff[4])
#define F_REP_ONE 		(lcd_buff[0])

//#define L_ICON_BUF		(lcd_buff[4])
#define S1_ICON_MASK	0x0010
#define S1_ICON_BUF		(lcd_buff[0])
#define S2_ICON_MASK	0x0004
#define S2_ICON_BUF		(lcd_buff[0])
#define S3_ICON_MASK	0x0001
#define S3_ICON_BUF		(lcd_buff[0])
#define S4_ICON_MASK	0x0000
#define S4_ICON_BUF		(lcd_buff[0])

#elif defined(NEW_DH_LCD_MODULE_SM5858)

#define USB_DEV_MASK	0x0080
#define F_USB_DEV  		(lcd_buff[1])	

#define AUX_DEV_MASK	0x0000
#define F_AUX_DEV  		(lcd_buff[0])

#define SD_DEV_MASK	0x0040
#define F_SD_DEV		(lcd_buff[4])	

#define FM_DEV_MASK	0x0000
#define F_FM_DEV		(lcd_buff[1])	


#define POINTS_MASK		0x0010
#define F_POINTS		(lcd_buff[0])	

#define FM_MHZ_MASK	0x0001
#define F_MHZ_DEV		(lcd_buff[2])	

#define AM_KHZ_MASK	0x0001
#define F_KHZ_DEV		(lcd_buff[1])	

#define FM_P1_MASK		0x0004
#define F_P1_DEV		(lcd_buff[0])	

#define SW_MHZ_MASK	0x0001
#define F_SW_DEV		(lcd_buff[0])	

#define SW_P2_MASK		0x0040
#define F_P2_DEV		(lcd_buff[0])	


#define RTC_ICON_MASK	0x0000
#define F_RTC_ICON		(lcd_buff[3])

#define RTC_ALM_MASK	0x0000
#define F_RTC_ALM		(lcd_buff[3])	

#define RTC_PM_MASK	0x0000
#define F_RTC_PM		(lcd_buff[2])

#define RTC_AM_MASK	0x0000
#define F_RTC_AM		(lcd_buff[3])

#define REC_ICON_MASK	0x0001
#define F_REC_DEV		(lcd_buff[4])	

#define SPK_MUTE_MASK	0x0001
#define F_SPK_DEV		(lcd_buff[3])	

#define BATTERY_MASK	0x0002
#define F_BAT_ICON_BUF	(lcd_buff[0])	


#define TRADEMARK_MASK	0x0100
#define TRADEMARK_ICON		(lcd_buff[0])	

#define NUM_1BC_MASK	0x0000
#define F_NUM_1BC		(lcd_buff[2])	

#define REP_ALL_MASK	0//0x0004
#define REP_ONE_MASK	0//0x0008
#define F_REP_ALL		(lcd_buff[4])
#define F_REP_ONE 		(lcd_buff[0])

//#define L_ICON_BUF		(lcd_buff[4])
#define S1_ICON_MASK	0x0008
#define S1_ICON_BUF		(lcd_buff[0])
#define S2_ICON_MASK	0x0020
#define S2_ICON_BUF		(lcd_buff[0])
#define S3_ICON_MASK	0x0080
#define S3_ICON_BUF		(lcd_buff[0])
#define S4_ICON_MASK	0x0080
#define S4_ICON_BUF		(lcd_buff[0])
#else

#define USB_DEV_MASK	0x0100
#define F_USB_DEV  		(lcd_buff[4])	

#define AUX_DEV_MASK	0x0100
#define F_AUX_DEV  		(lcd_buff[0])

#define SD_DEV_MASK	0x0040
#define F_SD_DEV		(lcd_buff[4])	

#define FM_DEV_MASK	0x0000
#define F_FM_DEV		(lcd_buff[1])	


#define POINTS_MASK		0x0010
#define F_POINTS		(lcd_buff[0])	

#define FM_MHZ_MASK	0x0005
#define F_MHZ_DEV		(lcd_buff[0])	

#define AM_KHZ_MASK	0x0001
#define F_KHZ_DEV		(lcd_buff[1])	

#define FM_P1_MASK		0x0000
#define F_P1_DEV		(lcd_buff[3])	

#define SW_MHZ_MASK	0x0041
#define F_SW_DEV		(lcd_buff[0])	


#define RTC_ICON_MASK	0x0000
#define F_RTC_ICON		(lcd_buff[3])

#define RTC_ALM_MASK	0x0000
#define F_RTC_ALM		(lcd_buff[3])	

#define RTC_PM_MASK	0x0000
#define F_RTC_PM		(lcd_buff[2])

#define RTC_AM_MASK	0x0000
#define F_RTC_AM		(lcd_buff[3])

#define REC_ICON_MASK	0x0001
#define F_REC_DEV		(lcd_buff[4])	

#define SPK_MUTE_MASK	0x0001
#define F_SPK_DEV		(lcd_buff[2])	

#define BATTERY_MASK	0x0002
#define F_BAT_ICON_BUF	(lcd_buff[0])	


#define TRADEMARK_MASK	0x0000
#define TRADEMARK_ICON		(lcd_buff[0])	

#define NUM_1BC_MASK	0x0000
#define F_NUM_1BC		(lcd_buff[2])	

#define REP_ALL_MASK	0//0x0004
#define REP_ONE_MASK	0//0x0008
#define F_REP_ALL		(lcd_buff[4])
#define F_REP_ONE 		(lcd_buff[0])

//#define L_ICON_BUF		(lcd_buff[4])
#define S1_ICON_MASK	0x0008
#define S1_ICON_BUF		(lcd_buff[0])
#define S2_ICON_MASK	0x0020
#define S2_ICON_BUF		(lcd_buff[0])
#define S3_ICON_MASK	0x0080
#define S3_ICON_BUF		(lcd_buff[0])
#define S4_ICON_MASK	0x0080
#define S4_ICON_BUF		(lcd_buff[0])
#endif

void init_lcd_disp(void);
void seg_lcd_disp_scan(void);
void lcd_disp_icon(u8 id);
void lcd_clr_icon(u8 id);
void lcd_flash_icon(u8 id);
void lcd_backlight_ctrl(bool on);

//void seg_lcd_set_brightness(u8 br);
void led_putchar(u8 chardata,u8 loc);
void clr_lcd_digit(u8 lcd_num);

#endif

#endif
