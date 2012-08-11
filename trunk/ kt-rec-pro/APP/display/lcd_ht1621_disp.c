
#include "config.h"


#if defined(USE_LCD_DRV_HT1621)
#include "lcd_ht1621_drv.h"

u8 lcd_flash_char;		  ///<LED闪烁数字位
u8 lcd_flash_icon_id;		  ///<LED闪烁状态位
u8 xdata lcd_flash_timer=0;


extern xd_u8 Ht1621_buf[MAX_SEG_NUM];


u16 _code LCD_NUMBER[10] =
{
    0xA28A,0x0088,0x9292,0x909A,0x3098,  ///<0~4
    0xB01A,0xB21A,0x8088,0xB29A,0xB09A   ///<5~9
};

u16 _code LCD_LARGE_LETTER[26] =
{
    0xB298,0x321A,0xA202,0x129A,0xB212,///<ABCDE
    0xB210,0xA21A,0x3298,0xC006,0x008A,///<FGHIJ
    0x4844,0x2202,0x22EC,0xA288,0xA28A,///<KLMNO
    0xB290,0xB098,0xBB90,0xB01A,0xC004,///<PQRST
    0x228A,0x08A8,0x6E88,0x0C60,0x309A,///<UVWXY
    0x8442///<Z
};

u16 _code LCD_SMALL_LETTER[26] =
{
    0xB298,0x321A,0xA202,0x129A,0xB212,///<ABCDE
    0xB210,0xA21A,0x3298,0xC006,0x008A,///<FGHIJ
    0x4844,0x2202,0x22EC,0xA288,0xA28A,///<KLMNO
    0xB290,0xB098,0xBB90,0xB01A,0xC004,///<PQRST
    0x228A,0x08A8,0x6E88,0x0C60,0x309A,///<UVWXY
    0x8442///<Z
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
void disp_buf_align(u8 lcd_digit,u16 buf_data)
{
	u8 digit_num=0;
	//digit_num =align_lcd_digit[lcd_digit];
	Ht1621_buf[digit_num] |=(u8)(buf_data>>8);
	Ht1621_buf[digit_num+1]|=(u8)(buf_data&0x00FF);
}
void clr_lcd_digit(u8 lcd_num)
{
	u8 digit_num=0;
	//digit_num =align_lcd_digit[lcd_digit];
	Ht1621_buf[digit_num] =0x00;
	Ht1621_buf[digit_num+1]=0x00;
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
	clear_lcd_disp_buf();
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
		F_MHZ_DEV |=FM_MHZ_MASK;
#if defined(NEW_DH_LCD_MODULE_SM5858)
		F_P1_DEV |=FM_P1_MASK;
#endif		
		break;
	case AM_KHZ_ICON:
		F_KHZ_DEV |=AM_KHZ_MASK;
		break;
	case SW_ICON:
		F_SW_DEV |=SW_MHZ_MASK;
#if defined(NEW_DH_LCD_MODULE_SM5901)
		F_P1_DEV |=FM_P1_MASK;
#elif defined(NEW_DH_LCD_MODULE_SM5858)
		F_P2_DEV |=SW_P2_MASK;
#endif			
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
//	case BAT_S4_ICON:
//		S1_ICON_BUF |=S4_ICON_MASK;
//		break;		
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
		F_MHZ_DEV &=~FM_MHZ_MASK;
		break;
#if defined(NEW_DH_LCD_MODULE_SM5858)
		F_P1_DEV &=~FM_P1_MASK;
#endif
	case AM_KHZ_ICON:
		F_KHZ_DEV &=~AM_KHZ_MASK;
		break;
	case SW_ICON:
		F_SW_DEV &=~SW_MHZ_MASK;
#if defined(NEW_DH_LCD_MODULE_SM5901)
		F_P1_DEV &=~FM_P1_MASK;
#elif defined(NEW_DH_LCD_MODULE_SM5858)
		F_P2_DEV &=~SW_P2_MASK;
#endif			
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
    //set_lcd_icon_buf(LCD_ST_ICON);
   //printf("digit : %x   -->   %c  \r\n",(u16)loc,chardata);
    if ((chardata < ' ') || (chardata > '~') || (loc > 7))
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
        //set_lcd_icon_buf(LCD_2DOT_ICON);
    }
    else if (chardata == ' ')
    {
        loc++;
    }
    else if (chardata == '-')
    {
        //Ht1621_buf[loc++] = LCD0_MINUS;
    }
}
void Lcd_check_buf()
{
#if 0
	static char cnt='0';
	disp_buf_clear();

	cnt++;
	if(cnt>'9')cnt='0';
	//loc++;
	if(loc>7)loc=0;
	//lcd_putchar('A');
	disp_buf_align(0,LCD_LARGE_LETTER[0]);
	//Ht1621_buf[0]=LCD_LARGE_LETTER[0];
	//Ht1621_buf[1]=LCD_LARGE_LETTER[0];
#endif
	
}
#endif

