/*lcd segment*/
#include "config.h"

#include "lcdsegment.h"

#if(LCD_DISP == monitor)

u16 lcd_buff[5]={0};


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
void clear_lcd_disp_buf(void)
{
	lcd_buff[0] =0x0000;
	lcd_buff[1] =0x0000;
	lcd_buff[2] =0x0000;
	lcd_buff[3] =0x0000;
	lcd_buff[4] =0x0000;
}
#if 0
void lcd_backlight_ctrl(bool on)
{
	P0DIR &=~(BIT(4));P0PU|= (BIT(4)); 

	if(!on){
    		LCD_BACKLIGHT_HIGH();
	}
	else{
    		LCD_BACKLIGHT_LOW();
	}

}
#endif
/*----------------------------------------------------------------------------*/
/**@brief    数码管状态位显示
   @param	 id：要显示的状态位
   @return	 无
   @note     void led_disp_icon(u8 id)
*/
/*----------------------------------------------------------------------------*/
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
	case FM_ICON:
		
		F_MHZ_DEV |=FM_MHZ_MASK;
		
#if defined(NEW_DH_LCD_MODULE_SM5858)
		F_P1_DEV |=FM_P1_MASK;
#elif defined(NEW_DH_107_105_104_LCD_MODULE)
		F_P1_DEV |=FM_P1_MASK;
		F_FM_DEV |=FM_DEV_MASK;
#endif		
		break;
	case AM_ICON:
#if defined(NEW_DH_107_105_104_LCD_MODULE)
		F_AM_DEV |=AM_DEV_MASK;
#endif		
		F_KHZ_DEV |=AM_KHZ_MASK;
		break;
	case SW_ICON:
		F_SW_MHZ_DEV |=SW_MHZ_MASK;
#if defined(NEW_DH_LCD_MODULE_SM5901)
		F_P1_DEV |=FM_P1_MASK;
#elif defined(NEW_DH_LCD_MODULE_SM5858)
		F_P2_DEV |=SW_P2_MASK;
#elif defined(NEW_DH_107_105_104_LCD_MODULE)
		F_P2_DEV |=SW_P2_MASK;
		F_SW_DEV |=SW_DEV_MASK;
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

/*----------------------------------------------------------------------------*/
/**@brief    LED闪烁设置
   @param	 id：状态位
   @return	 无
   @note     void led_flash_icon(u8 id)
*/
/*----------------------------------------------------------------------------*/
u8  xdata lcd_flash_icon_id=NONE_ICON;
u8 xdata lcd_flash_timer=0;
void lcd_flash_icon(u8 id)
{
    lcd_flash_icon_id = id;	
}
void lcd_clr_flash_icon()
{
	lcd_flash_icon_id =0xFF;
}
/*----------------------------------------------------------------------------*/
/**@brief    LED闪烁设置
   @param	 flag：闪烁的数据位
   @return	 无
   @note     void led_flash_section(u8 flag)
*/
/*----------------------------------------------------------------------------*/
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
	case FM_ICON:

		F_MHZ_DEV &=~FM_MHZ_MASK;

#if defined(NEW_DH_LCD_MODULE_SM5858)
		F_P1_DEV &=~FM_P1_MASK;
#elif defined(NEW_DH_107_105_104_LCD_MODULE)
		F_P1_DEV &=~FM_P1_MASK;
		F_FM_DEV &=~FM_DEV_MASK;
#endif		
		break;
	case AM_ICON:
#if defined(NEW_DH_107_105_104_LCD_MODULE)
		F_AM_DEV &=~AM_DEV_MASK;
#endif		
		
		F_KHZ_DEV &=~AM_KHZ_MASK;
		break;
	case SW_ICON:
		F_SW_MHZ_DEV &=~SW_MHZ_MASK;
#if defined(NEW_DH_LCD_MODULE_SM5901)
		F_P1_DEV &=~FM_P1_MASK;
#elif defined(NEW_DH_LCD_MODULE_SM5858)
		F_P2_DEV &=~SW_P2_MASK;
#elif defined(NEW_DH_107_105_104_LCD_MODULE)
		F_P2_DEV &=~SW_P2_MASK;
		F_SW_DEV &=~SW_DEV_MASK;
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
    	seg_init();
    	com_init();
	LCD_BACKLIGHT_INIT();
	LCD_BACKLIGHT_ON();
}
/*----------------------------------------------------------------------------*/
/**@brief    LED 亮度设置
   @param	 br:亮度数值
   @return	 无
   @note     void led_set_brightness(u8 br)
*/
/*----------------------------------------------------------------------------*/
//void seg_lcd_set_brightness(u8 br)
//{
#if 0
    if (br > 16)
        return;
    if (br == 16)
        PWM4CON = 0;
    else
        PWM4CON = br | 0xd0;
#endif
//}
/*----------------------------------------------------------------------------*/
/**@brief    LED 字符显示
   @param	 chardata：字符数据
   @return	 无
   @note     void led_putchar(u8 chardata,u8 loc)
*/
/*----------------------------------------------------------------------------*/
#if defined(K129_MODULE00000000000000000000)
u8 _code lcd_disbuf_offset[4] ={0,2,4,6};
void align_lcd_disp_buff(u8 offset,u8 letter_data)
{
	u8 digit_idx=offset;
	
	digit_idx= lcd_disbuf_offset[offset];

	lcd_buff[1] &= ~(0x0002<<digit_idx);
	lcd_buff[2] &= ~(0x0003<<digit_idx);
	lcd_buff[3] &= ~(0x0003<<digit_idx);
	lcd_buff[4] &= ~(0x0003<<digit_idx);

       lcd_buff[1] |= ((letter_data & DIG_A)<<1)<<digit_idx;
       lcd_buff[2] |= (((letter_data & DIG_B))|((letter_data & DIG_F)>>5))<<digit_idx;
       lcd_buff[3] |= (((letter_data & DIG_C)>>1)|((letter_data & DIG_G)>>6))<<digit_idx;
       lcd_buff[4] |= (((letter_data & DIG_D)>>2)|((letter_data & DIG_E)>>4))<<digit_idx;   	 
}
#elif defined(JF_168_LCD_MODULE)
u8 _code lcd_disbuf_offset[4] ={6,4,2,0};
void align_lcd_disp_buff(u8 offset,u8 letter_data)
{
	u8 digit_idx=offset;
	
	digit_idx= lcd_disbuf_offset[offset];

	lcd_buff[1] &= ~(0x0003<<digit_idx);
	lcd_buff[2] &= ~(0x0003<<digit_idx);
	lcd_buff[3] &= ~(0x0003<<digit_idx);
	lcd_buff[4] &= ~(0x0001<<digit_idx);

       lcd_buff[1] |= ((letter_data & DIG_A)|((letter_data & DIG_F)>>4))<<digit_idx;
       lcd_buff[2] |= (((letter_data & DIG_B)>>1)|((letter_data & DIG_G)>>5))<<digit_idx;
       lcd_buff[3] |= (((letter_data & DIG_C)>>2)|((letter_data & DIG_E)>>3))<<digit_idx;
       lcd_buff[4] |= (((letter_data & DIG_D)>>3))<<digit_idx;   	 	 
}
#elif defined(NEW_DH_107_105_104_LCD_MODULE)||defined(JF_168_LCD_MODULE)
u8 _code lcd_disbuf_offset[4] ={6,4,2,0};
void align_lcd_disp_buff(u8 offset,u8 letter_data)
{
	u8 digit_idx=offset;
	
	digit_idx= lcd_disbuf_offset[offset];

	lcd_buff[1] &= ~(0x0003<<digit_idx);
	lcd_buff[2] &= ~(0x0003<<digit_idx);
	lcd_buff[3] &= ~(0x0003<<digit_idx);
	lcd_buff[4] &= ~(0x0001<<digit_idx);

       lcd_buff[1] |= ((letter_data & DIG_A)|((letter_data & DIG_F)>>4))<<digit_idx;
       lcd_buff[2] |= (((letter_data & DIG_B)>>1)|((letter_data & DIG_G)>>5))<<digit_idx;
       lcd_buff[3] |= (((letter_data & DIG_C)>>2)|((letter_data & DIG_E)>>3))<<digit_idx;
       lcd_buff[4] |= (((letter_data & DIG_D)>>3))<<digit_idx;   	 	 
}
#elif defined(NEW_DH_LCD_MODULE_SM5858)
u8 _code lcd_disbuf_offset[4] ={0,5,3,1};
void align_lcd_disp_buff(u8 offset,u8 letter_data)
{
	u8 digit_idx=offset;
	
	digit_idx= lcd_disbuf_offset[offset];
	
	if(digit_idx==0)
	{
		 lcd_buff[2]&=~0x0080;
		 lcd_buff[3]&=~0x0080;
	        lcd_buff[4]&=~0x0080;
			
		 if((letter_data == LCD_NUMBER[1])){
			lcd_buff[2]|=0x0080;
			lcd_buff[3]|=0x0080;
		    }
		    else if((letter_data == LCD_NUMBER[2])){
			lcd_buff[4]|=0x0080;
			lcd_buff[3]|=0x0080;
		   }	
	   	return;
	}
	else{
		
		lcd_buff[4] &= ~(0x0001<<digit_idx);
		lcd_buff[3] &= ~(0x0003<<digit_idx);
		lcd_buff[2] &= ~(0x0003<<digit_idx);
		lcd_buff[1] &= ~(0x0003<<digit_idx);

	       lcd_buff[4] |= ((letter_data & DIG_A))<<digit_idx;
	       lcd_buff[3] |= (((letter_data & DIG_B)>>1)|((letter_data & DIG_F)>>4))<<digit_idx;
	       lcd_buff[2] |= (((letter_data & DIG_C)>>2)|((letter_data & DIG_G)>>5))<<digit_idx;
	       lcd_buff[1] |= (((letter_data & DIG_D)>>3)|((letter_data & DIG_E)>>3))<<digit_idx; 
	}	   
}
#elif defined(NEW_DH_LCD_MODULE_SM5901)
u8 _code lcd_disbuf_offset[4] ={0,1,3,5};
void align_lcd_disp_buff(u8 offset,u8 letter_data)
{
	u8 digit_idx=offset;
	
	digit_idx= lcd_disbuf_offset[offset];

	if(digit_idx==0)
	{
		 lcd_buff[2]&=~0x0001;
		 lcd_buff[3]&=~0x0001;
	        lcd_buff[4]&=~0x0001;
			
		 if((letter_data == LCD_NUMBER[1])){
			lcd_buff[2]|=0x0001;
			lcd_buff[3]|=0x0001;
		    }
		    else if((letter_data == LCD_NUMBER[2])){
			lcd_buff[4]|=0x0001;
			lcd_buff[3]|=0x0001;
		   }	
	   	return;
	}
	else{		
		lcd_buff[4] &= ~(0x0002<<digit_idx);
		lcd_buff[3] &= ~(0x0003<<digit_idx);
		lcd_buff[2] &= ~(0x0003<<digit_idx);
		lcd_buff[1] &= ~(0x0003<<digit_idx);

	       lcd_buff[4] |= ((letter_data & DIG_A)<<1)<<digit_idx;
	       lcd_buff[3] |= (((letter_data & DIG_B))|((letter_data & DIG_F)>>5))<<digit_idx;
	       lcd_buff[2] |= (((letter_data & DIG_C)>>1)|((letter_data & DIG_G)>>6))<<digit_idx;
	       lcd_buff[1] |= (((letter_data & DIG_D)>>2)|((letter_data & DIG_E)>>4))<<digit_idx;   	 
	}
}
#else
u8 _code lcd_disbuf_offset[4] ={7,5,3,1};
void align_lcd_disp_buff(u8 offset,u8 letter_data)
{
	u8 digit_idx=offset;
	
	digit_idx= lcd_disbuf_offset[offset];

	lcd_buff[4] &= ~(0x0001<<digit_idx);
	lcd_buff[3] &= ~(0x0003<<digit_idx);
	lcd_buff[2] &= ~(0x0003<<digit_idx);
	lcd_buff[1] &= ~(0x0003<<digit_idx);

       lcd_buff[4] |= ((letter_data & DIG_A))<<digit_idx;
       lcd_buff[3] |= (((letter_data & DIG_B)>>1)|((letter_data & DIG_F)>>4))<<digit_idx;
       lcd_buff[2] |= (((letter_data & DIG_C)>>2)|((letter_data & DIG_G)>>5))<<digit_idx;
       lcd_buff[1] |= (((letter_data & DIG_D)>>3)|((letter_data & DIG_E)>>3))<<digit_idx;   	 
}
#endif
void clr_lcd_digit(u8 lcd_num)
{
	align_lcd_disp_buff(lcd_num,0x00);
}
void led_putchar(u8 chardata,u8 loc)
{
    loc += 0;
    if ((chardata < ' ') || (chardata > '~'))
    {
        return;
    }
    if ((chardata >= '0') && (chardata <= '9'))
    {
          align_lcd_disp_buff(loc,LCD_NUMBER[chardata - '0']);
    }
    else if ((chardata >= 'a') && (chardata <= 'z'))
    {
         align_lcd_disp_buff(loc,LCD_SMALL_LETTER[chardata - 'a']);
    }
    else if ((chardata >= 'A') && (chardata <= 'Z'))
    {
         align_lcd_disp_buff(loc,LCD_LARGE_LETTER[chardata - 'A']);
    }
    else if (chardata == ':')
    {
        lcd_disp_icon(COL_ICON);
    }

}
#if defined(USE_BAT_MANAGEMENT)
extern void Bat_icon_chk(void);
#endif
void seg_lcd_disp_scan(void)
{
    static xd_u8 cnt = 0;
    xd_u8 temp;
    static bool flash;
#if defined(USE_BAT_MANAGEMENT)
    Bat_icon_chk();
#endif
    TRADEMARK_ICON |=TRADEMARK_MASK;

    update_disp_icon();

    lcd_flash_timer++;
    if (lcd_flash_timer == 220)
    {
        lcd_flash_timer = 0;
        flash = !flash;
    }
    if (flash)
    {
        lcd_clr_icon(lcd_flash_icon_id);   
    }
    else
    {
        lcd_disp_icon(lcd_flash_icon_id); 
    }
	
    temp = cnt>>1;
    close_com(temp);
    if(cnt & 0x01){
	  seg07_port(lcd_buff[temp]);
	  seg8_port( ( ((lcd_buff[temp]&0x0100)>0)?1:0 ) );
	  clr_com(temp);
    }
    else
   {                            
	  seg07_port(~lcd_buff[temp]); 	  
	  seg8_port(( ((lcd_buff[temp]&0x0100)>0)?0:1 ));
	  set_com(temp);
   }

   cnt++;
   if(cnt>9)cnt = 0;
}
#endif


