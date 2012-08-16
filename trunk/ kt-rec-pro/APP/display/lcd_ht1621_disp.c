
#include "config.h"


#if defined(USE_LCD_DRV_HT1621)
#include "lcd_ht1621_drv.h"

u8 lcd_flash_char;		  ///<LED闪烁数字位
u8 lcd_flash_icon_id;		  ///<LED闪烁状态位
u8 xdata lcd_flash_timer=0;


extern xd_u8 Ht1621_buf[MAX_SEG_NUM];


u8 _code LCD_NUMBER[10] =
{
    0x3f,0x06,0x5b,0x4f,0x66,  ///<0~4
    0x6d,0x7d,0x07,0x7f,0x6f   ///<5~9
};

u8 _code LCD_LARGE_LETTER[26] =
{
    0x77,0x40,0x39,0x3f,0x79,///<ABCDE
    0x71,0x40,0x76,0x06,0x40,///<FGHIJ
    0x40,0x38,0x40,0x37,0x3f,///<KLMNO
    0x73,0x40,0x50,0x6d,0x40,///<PQRST
    0x3e,0x3e,0x40,0x76,0x40,///<UVWXY
    0x40///<Z
};

u8 _code LCD_SMALL_LETTER[26] =
{
    0x77,0x7c,0x58,0x5e,0x79,///<abcde
    0x71,0x40,0x40,0x40,0x40,///<fghij
    0x40,0x38,0x40,0x54,0x5c,///<klmno
    0x73,0x67,0x50,0x40,0x40,///<pqrst
    0x3e,0x3e,0x40,0x40,0x40,///<uvwxy
    0x40///<z
};
/*----------------------------------------------------------------------------*/
/**@brief    清空LED BUFF函数，LED显示位置设为1
   @param	 无
   @return	 无
   @note     void clear_led(void)
*/
/*----------------------------------------------------------------------------*/
void clear_lcd_disp_buf(void)
{
	my_memset(&Ht1621_buf[0], 0x0, (MAX_SEG_NUM));
	//loc=0;
}
u8 _code align_lcd_digit[4]={18,19,21,22};
void disp_buf_align(u8 lcd_digit,u8 buf_data)
{
	//u8 digit_num=0;
	//digit_num =align_lcd_digit[lcd_digit];
	
	Ht1621_buf[align_lcd_digit[lcd_digit]] &=~(0xEF);
       Ht1621_buf[align_lcd_digit[lcd_digit]] |= ((buf_data & DIG_A)<<3)|((buf_data & DIG_B)<<1)|((buf_data & DIG_C)>>1)|((buf_data & DIG_D)>>3);
       Ht1621_buf[align_lcd_digit[lcd_digit]] |= ((buf_data & DIG_E)<<1)|((buf_data & DIG_F)<<2)|((buf_data & DIG_G));
}
void clr_lcd_digit(u8 lcd_num)
{
	u8 digit_num=0;
	digit_num =align_lcd_digit[lcd_num];
	Ht1621_buf[digit_num] &=~(0xEF);
}
void clr_all_num()
{
	u8 i;
	for(i=0;i<8;i++){
		clr_lcd_digit(i);
	}
}
/*----------------------------------------------------------------------------*/
/**@brief    LED 显示初始化
   @param	 无
   @return	 无
   @note     void init_led_disp(void)
*/
/*----------------------------------------------------------------------------*/
void init_lcd_disp(void)
{
	//clear_lcd_disp_buf();
	lcd_ht1621_init();
}
void lcd_disp_icon(u8 id)
{
    switch(id)
    {
	case USB_ICON:
		F_USB_DEV |=USB_DEV_MASK;
		break;
	case SD_ICON:
		F_SD_DEV |=SD_DEV_MASK;
		break;
	case REC_ICON:
		F_REC_DEV |=REC_ICON_MASK;
		break;	
#if 0		
	case AUX_ICON:
		F_AUX_DEV |=AUX_DEV_MASK;
		break;
#endif		
	case FM_MHZ_ICON:
		F_FM_DEV |=FM_DEV_MASK;
		F_MHZ_DEV |=FM_MHZ_MASK;	
		break;
	case AM_KHZ_ICON:
		F_KHZ_DEV |=AM_KHZ_MASK;
		break;
	case SW_ICON:
		F_SW_DEV |=SW_MHZ_MASK;
		F_MHZ_DEV |=FM_MHZ_MASK;	
		break;				
	case REP_1_ICON:
		F_REP_ONE|=REP_ONE_MASK;
		break;
	case REP_ALL_ICON:
		F_REP_ALL |=REP_ALL_MASK;
		break;
	case COL_ICON:
		F_POINTS |=POINTS_MASK;
		break;		
	case MUTE_ICON:
		F_SPK_DEV |=SPK_MUTE_MASK;
		break;
#if defined(USE_BAT_MANAGEMENT)		
	case BAT_ICON:
		F_BAT_ICON_BUF |=BATTERY_MASK;
		break;	
	case BAT_S1_ICON:
		S1_ICON_BUF |=S1_ICON_MASK;
		break;	
	case BAT_S2_ICON:
		S1_ICON_BUF |=S2_ICON_MASK;
		break;	
	case BAT_S3_ICON:
		S1_ICON_BUF |=S3_ICON_MASK;
		break;	
#endif		

    }
}
void lcd_clr_icon(u8 id)
{

    switch(id)
    {
	case USB_ICON:
		F_USB_DEV &=~USB_DEV_MASK;
		break;
	case SD_ICON:
		F_SD_DEV &=~SD_DEV_MASK;
		break;
	case REC_ICON:
		F_REC_DEV &=~REC_ICON_MASK;
		break;		
#if 0		
	case AUX_ICON:
		F_AUX_DEV &=~AUX_DEV_MASK;
		break;
#endif		
	case FM_MHZ_ICON:
		F_FM_DEV &=~FM_DEV_MASK;
		F_MHZ_DEV &=~FM_MHZ_MASK;
		break;

	case AM_KHZ_ICON:
		F_KHZ_DEV &=~AM_KHZ_MASK;
		break;
	case SW_ICON:
		F_SW_DEV &=~SW_MHZ_MASK;
		F_MHZ_DEV &=~FM_MHZ_MASK;		
		break;			
	case REP_1_ICON:
		F_REP_ONE&=~REP_ONE_MASK;
		break;
	case REP_ALL_ICON:
		F_REP_ALL &=~REP_ALL_MASK;
		break;
	case COL_ICON:
		F_POINTS &=~POINTS_MASK;
		break;
	case MUTE_ICON:
		F_SPK_DEV &=~SPK_MUTE_MASK;
		break;	
#if defined(USE_BAT_MANAGEMENT)
	case BAT_ICON:
		F_BAT_ICON_BUF &=~BATTERY_MASK;
		break;	
	case BAT_S1_ICON:
		S1_ICON_BUF &=~S1_ICON_MASK;
		break;	
	case BAT_S2_ICON:
		S1_ICON_BUF &=~S2_ICON_MASK;
		break;	
	case BAT_S3_ICON:
		S1_ICON_BUF &=~S3_ICON_MASK;
		break;
#endif		
    }
}
void lcd_flash_icon(u8 id)
{
    lcd_flash_icon_id = id;	
}
void lcd_clr_flash_icon()
{
	lcd_flash_icon_id =0xFF;
}
/*----------------------------------------------------------------------------*/
/**@brief    LED 字符显示
   @param	 chardata：字符数据
   @return	 无
   @note     void led_puchar(u8 chardata)
*/
/*----------------------------------------------------------------------------*/
void led_putchar(u8 chardata,u8 loc)
{
   //printf("digit : %x   -->   %c  \r\n",(u16)loc,chardata);
   TRADEMARK_ICON |=TRADEMARK_MASK;
	
    if ((chardata < ' ') || (chardata > '~'))
    {
        return;
    }
    if ((chardata >= '0') && (chardata <= '9'))
    {
        disp_buf_align(loc++,(LCD_NUMBER[chardata - '0']));
    }
    else if ((chardata >= 'a') && (chardata <= 'z'))
    {
	  disp_buf_align(loc++,((LCD_SMALL_LETTER[chardata - 'a'])));
    }
    else if ((chardata >= 'A') && (chardata <= 'Z'))
    {
    	  disp_buf_align(loc++,(LCD_LARGE_LETTER[chardata - 'A']));
    }
    else if (chardata == ':')
    {
        lcd_disp_icon(COL_ICON);
    }
}
#if defined(USE_BAT_MANAGEMENT)
extern void Bat_icon_chk(void);
#endif

void Lcd_check_buf()
{
#if defined(USE_BAT_MANAGEMENT)
	Bat_icon_chk();
#endif
#if 0
	static char cnt='0';
	clear_lcd_disp_buf();

	//cnt++;
	//led_putchar('0',0);
	//led_putchar('1',1);
	//led_putchar('2',2);
	//led_putchar('3',3);
	Ht1621_buf[16]=0x01;

#endif
	
}
#endif

