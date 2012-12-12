#ifndef _LCD_HT1621_DRV_H_
#define	_LCD_HT1621_DRV_H_


#define HT1621_BIT_DELAY 6
#define HT1621_INI_DELAY 60


#define HT1621_BIAS    	0x53
#define HT1621_SYSDIS  	0x00
#define HT1621_SYSEN   	0x02
#define HT1621_LCDOFF  	0x04
#define HT1621_LCDON   	0x06
#define HT1621_XTAL    	0x28
#define HT1621_RC256   	0x30
#define HT1621_TONEON  	0x12
#define HT1621_TONEOFF 0x10
#define HT1621_WDTDIS  	0x0A

#define MAX_SEG_NUM                32

#define 	DIG_A	0x01
#define 	DIG_B	0x02
#define 	DIG_C	0x04
#define 	DIG_D	0x08
#define 	DIG_E	0x10
#define 	DIG_F	0x20
#define 	DIG_G	0x40
#define 	DIG_H	0x80


#define USB_DEV_MASK	0x80
#define F_USB_DEV  		(Ht1621_buf[17])	

#define AUX_DEV_MASK	0x0000
#define F_AUX_DEV  		(Ht1621_buf[0])

#define SD_DEV_MASK	0x0040
#define F_SD_DEV		(Ht1621_buf[17])	

#define FM_DEV_MASK	0x0010
#define F_FM_DEV		(Ht1621_buf[18])	

#define AM_DEV_MASK	0x0001
#define F_AM_DEV		(Ht1621_buf[17])	


#define POINTS_MASK		0x0010
#define F_POINTS		(Ht1621_buf[21])	

#define FM_MHZ_MASK	0x0020
#define F_MHZ_DEV		(Ht1621_buf[16])	

#define AM_KHZ_MASK	0x0040
#define F_KHZ_DEV		(Ht1621_buf[16])	

#define FM_P1_MASK		0x0000
#define F_P1_DEV		(Ht1621_buf[0])	

#define SW_MHZ_MASK	0x0010
#define F_SW_MHZ_DEV	(Ht1621_buf[19])	

#define SW_P2_MASK		0x0000
#define F_P2_DEV		(Ht1621_buf[0])	


#define RTC_ICON_MASK	0x0000
#define F_RTC_ICON		(Ht1621_buf[3])

#define RTC_ALM_MASK	0x0000
#define F_RTC_ALM		(Ht1621_buf[3])	

#define RTC_PM_MASK	0x0000
#define F_RTC_PM		(Ht1621_buf[2])

#define RTC_AM_MASK	0x0000
#define F_RTC_AM		(Ht1621_buf[3])

#define REC_ICON_MASK	0x0010
#define F_REC_DEV		(Ht1621_buf[22])	

#define SPK_MUTE_MASK	0x0000
#define F_SPK_DEV		(Ht1621_buf[3])	

#define BATTERY_MASK	0x0080
#define F_BAT_ICON_BUF	(Ht1621_buf[20])	


#define TRADEMARK_MASK	0x0004
#define TRADEMARK_ICON		(Ht1621_buf[17])	

#define NUM_1BC_MASK	0x0000
#define F_NUM_1BC		(Ht1621_buf[2])	

#define REP_ALL_MASK	0x0008
#define REP_ONE_MASK	0//0x0008
#define F_REP_ALL		(Ht1621_buf[16])
#define F_REP_ONE 		(Ht1621_buf[0])

//#define L_ICON_BUF		(Ht1621_buf[4])
#define S1_ICON_MASK	0x0040
#define S1_ICON_BUF		(Ht1621_buf[20])
#define S2_ICON_MASK	0x0020
#define S2_ICON_BUF		(Ht1621_buf[20])
#define S3_ICON_MASK	0x0010
#define S3_ICON_BUF		(Ht1621_buf[20])
#define S4_ICON_MASK	0x0000
#define S4_ICON_BUF		(Ht1621_buf[20])

enum   ///<LED±êÖ¾Î»
{
	USB_ICON,
	SD_ICON,
	AUX_ICON,
	FM_ICON,
	AM_ICON,
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

void init_lcd_disp(void);
void lcd_ht1621_init(void);
void UpdateLcd_HT1621_Buf(void);
void lcd_disp_icon(u8 chardata);
void lcd_clr_icon(u8 id);
void lcd_flash_icon(u8 id);
void clr_disp_num(u8 lcd_digit);
void clr_lcd_digit(u8 lcd_num);


void Lcd_check_buf(void);

#endif
