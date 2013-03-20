#include "config.h"
#include "disp.h"
#include "lcd.h"
#include "decode.h"
#include "mp3mode.h"
#include "lcdsegment.h"

#if 0//def LCD_GPIO_DRV

xd_u16 lcd_buff[5];

u8 _code playmodestr[4][7] = 
{
	{"ALL"},
	{"FOD"},
	{"ONE"},
	{"RAN"}
};

u8 _code letter_tab[] = 
{
    0x77,0x40,0x40,0x5E,0x79,///<ABCDE
    0x71,0x40,0x76,0x06,0x40,///<FGHIJ
    0x40,0x38,0x40,0x37,0x3F,///<KLMNO
    0x73,0x40,0x50,0x40,0x40,///<PQRST
    0x3e,0x3e,0x40,0x76,0x40,///<UVWXY
    0x40,///<Z

    0x77,0x40,0x40,0x5E,0x79,///<abcde
    0x71,0x40,0x40,0x30,0x40,///<fghij
    0x40,0x38,0x40,0x54,0x3F,///<klmno
    0x73,0x40,0x50,0x40,0x40,///<pqrst
    0x3e,0x3e,0x40,0x76,0x40,///<uvwxy
    0x40///<z
};
u8 _code figure_tab[] = 
{
    0x3f,0x06,0x5b,0x4f,0x66,  ///<0~4
    0x6d,0x7d,0x07,0x7f,0x6f   ///<5~9
};

#define 	DIG_A	0x01
#define 	DIG_B	0x02
#define 	DIG_C	0x04
#define 	DIG_D	0x08
#define 	DIG_E	0x10
#define 	DIG_F	0x20
#define 	DIG_G	0x40
#define 	DIG_H	0x80
#if defined(K000_XingChuang_x821_V001)
u8 get_lcd_disbuf_offset(u8 lcd_digit)
{
	switch(lcd_digit)
	{
		case 0:return 0;
		case 1:return 2;
		case 2:return 4;
		case 3:return 6;		
	}
	return 0xFF;
}
#elif defined(K820_LHD_820_REC_V001)
u8 get_lcd_disbuf_offset(u8 lcd_digit)
{
	switch(lcd_digit)
	{
		case 0:return 5;
		case 1:return 3;
		case 2:return 1;
		case 3:return 0;		
	}
	return 0xFF;
}
#else
u8 get_lcd_disbuf_offset(u8 lcd_digit)
{
	switch(lcd_digit)
	{
		case 0:return 5;
		case 1:return 3;
		case 2:return 1;
		case 3:return 0;		
	}
	return 0xFF;
}
#endif

/*----------------------------------------------------------------------------*/
/**@brief
   @param  
   @return
   @note 
*/
/*----------------------------------------------------------------------------*/
u8 dispchar(u8 chardata,u8 offset)
{
    u16  letter_temp;
    u8 digit_idx=0;

#if defined(K000_ZhuoYue_003_V001)||defined(K000_KT_AMFM_V001)||defined(K000_XingChuang_x821_V001)


#else	
	if(offset>2)
	{
	    return 0;
	}
#endif	
	
    if((chardata>='a')&&(chardata<='z'))
    {
        chardata -= 'a';
        letter_temp = letter_tab[chardata+26];        
    }
    else if((chardata>='A')&&(chardata<='Z'))
    {
        chardata -= 'A';
        letter_temp = letter_tab[chardata];
    }
    else
    {
        return 0;
    }
 
#if defined(K000_ZhuoYue_003_V001)

	letter_temp = letter_tab[chardata];
	offset =3- offset;
	digit_idx= (offset*2);
	
	lcd_buff[0] &= ~(0x0003<<digit_idx);
	lcd_buff[1] &= ~(0x0003<<digit_idx);
	lcd_buff[2] &= ~(0x0003<<digit_idx);
	lcd_buff[3] &= ~(0x0003<<digit_idx);
	   
       lcd_buff[0] |= ((letter_temp & DIG_A)<<1)<<digit_idx;
       lcd_buff[1] |= ((letter_temp & DIG_B)|((letter_temp & DIG_F)>>5))<<digit_idx;
       lcd_buff[2] |= (((letter_temp & DIG_C)>>1)|((letter_temp & DIG_G)>>6))<<digit_idx;
       lcd_buff[3] |= (((letter_temp & DIG_D)>>2)|((letter_temp & DIG_E)>>4))<<digit_idx;
#elif defined(K000_KT_AMFM_V001)
	letter_temp = letter_tab[chardata];

	digit_idx= get_lcd_disbuf_offset(offset);
	
	lcd_buff[0] &= ~(0x0001<<digit_idx);
	lcd_buff[1] &= ~(0x0003<<digit_idx);
	lcd_buff[2] &= ~(0x0003<<digit_idx);
	lcd_buff[3] &= ~(0x0003<<digit_idx);
	   
       lcd_buff[0] |= ((letter_temp & DIG_A))<<digit_idx;
       lcd_buff[1] |= ((letter_temp & DIG_B)|((letter_temp & DIG_F)>>5))<<digit_idx;
       lcd_buff[2] |= (((letter_temp & DIG_E)>>4)|((letter_temp & DIG_G)>>5))<<digit_idx;
       lcd_buff[3] |= (((letter_temp & DIG_D)>>3)|((letter_temp & DIG_C)>>1))<<digit_idx;  
#elif defined(K000_XingChuang_x821_V001)
	letter_temp = letter_tab[chardata];

	digit_idx= get_lcd_disbuf_offset(offset);
	
	lcd_buff[0] &= ~(0x0001<<digit_idx);
	lcd_buff[1] &= ~(0x0003<<digit_idx);
	lcd_buff[2] &= ~(0x0003<<digit_idx);
	lcd_buff[3] &= ~(0x0003<<digit_idx);

       lcd_buff[0] |= ((letter_temp & DIG_A))<<digit_idx;
       lcd_buff[1] |= (((letter_temp & DIG_B)>>1)|((letter_temp & DIG_F)>>4))<<digit_idx;
       lcd_buff[2] |= (((letter_temp & DIG_C)>>2)|((letter_temp & DIG_G)>>5))<<digit_idx;
       lcd_buff[3] |= (((letter_temp & DIG_D)>>3)|((letter_temp & DIG_E)>>3))<<digit_idx;   	   
#elif defined(K820_LHD_820_V001)
	letter_temp = letter_tab[chardata];
	digit_idx= get_lcd_disbuf_offset(offset);
	   
	lcd_buff[0] &= ~(0x0003<<digit_idx);
	lcd_buff[1] &= ~(0x0003<<digit_idx);
	lcd_buff[2] &= ~(0x0003<<digit_idx);
	lcd_buff[3] &= ~(0x0001<<digit_idx);

       lcd_buff[0] |= ((letter_temp & DIG_A)|(letter_temp & DIG_B))<<digit_idx;
       lcd_buff[1] |= (((letter_temp & DIG_G)>>5)|((letter_temp & DIG_F)>>5))<<digit_idx;
       lcd_buff[2] |= (((letter_temp & DIG_C)>>1)|((letter_temp & DIG_E)>>4))<<digit_idx;
       lcd_buff[3] |= (((letter_temp & DIG_D)>>3)|((letter_temp & DIG_H)>>7))<<digit_idx;   	 	   
#else

	letter_temp = letter_tab[chardata];
	offset =3- offset;
	digit_idx= (offset*2)-1;
	
	lcd_buff[0] &= ~(0x0003<<digit_idx);
	lcd_buff[1] &= ~(0x0003<<digit_idx);
	lcd_buff[2] &= ~(0x0003<<digit_idx);
	lcd_buff[3] &= ~(0x0003<<digit_idx);
	   
       lcd_buff[0] |= (letter_temp & 0x03)<<digit_idx;
       lcd_buff[1] |= ((letter_temp & 0x60)>>5)<<digit_idx;
       lcd_buff[2] |= (((letter_temp & 0x10)>>4)|((letter_temp & 0x04)>>1))<<digit_idx;
       lcd_buff[3] |= (((letter_temp & 0x08)>>3)|((letter_temp & 0x80)>>7))<<digit_idx;
#endif	   

	return 1;
}
/*----------------------------------------------------------------------------*/
/**@brief
   @param  
   @return
   @note 
*/
/*----------------------------------------------------------------------------*/
void dispstring(u8 *str,u8 offset0)
{
#if defined(K000_ZhuoYue_003_V001)||defined(K000_KT_AMFM_V001)||defined(K000_XingChuang_x821_V001)
    u8 cnt = 3;
#else
    u8 cnt = 2;
#endif
	str = str+offset0;	
	do
	{
	    dispchar(*str,cnt);
		str++;
		
	}while((0 != *str) && cnt--);
}
/*----------------------------------------------------------------------------*/
/**@brief
   @param  
   @return
   @note 
*/
/*----------------------------------------------------------------------------*/
u8 dispNum(u8 chardata,u8 cnt)
{
    u8  figure_temp;
    u8 digit_idx_offset=0;

#if defined(K000_ZhuoYue_003_V001)	
	
	figure_temp = figure_tab[chardata];
	cnt =3- cnt;
	digit_idx_offset= (cnt*2);

	lcd_buff[0] &= ~(0x0003<<digit_idx_offset);
	lcd_buff[1] &= ~(0x0003<<digit_idx_offset);
	lcd_buff[2] &= ~(0x0003<<digit_idx_offset);
	lcd_buff[3] &= ~(0x0003<<digit_idx_offset);

       lcd_buff[0] |= ((figure_temp & DIG_A)<<1)<<digit_idx_offset;
       lcd_buff[1] |= ((figure_temp & DIG_B)|((figure_temp & DIG_F)>>5))<<digit_idx_offset;
       lcd_buff[2] |= (((figure_temp & DIG_C)>>1)|((figure_temp & DIG_G)>>6))<<digit_idx_offset;
       lcd_buff[3] |= (((figure_temp & DIG_D)>>2)|((figure_temp & DIG_E)>>4))<<digit_idx_offset;
	   
#elif defined(K000_KT_AMFM_V001)

	figure_temp = figure_tab[chardata];
	digit_idx_offset= get_lcd_disbuf_offset(cnt);

	lcd_buff[0] &= ~(0x0001<<digit_idx_offset);
	lcd_buff[1] &= ~(0x0003<<digit_idx_offset);
	lcd_buff[2] &= ~(0x0003<<digit_idx_offset);
	lcd_buff[3] &= ~(0x0003<<digit_idx_offset);

       lcd_buff[0] |= ((figure_temp & DIG_A))<<digit_idx_offset;
       lcd_buff[1] |= ((figure_temp & DIG_B)|((figure_temp & DIG_F)>>5))<<digit_idx_offset;
       lcd_buff[2] |= (((figure_temp & DIG_E)>>4)|((figure_temp & DIG_G)>>5))<<digit_idx_offset;
       lcd_buff[3] |= (((figure_temp & DIG_D)>>3)|((figure_temp & DIG_C)>>1))<<digit_idx_offset;
#elif defined(K000_XingChuang_x821_V001)

	figure_temp = figure_tab[chardata];
	digit_idx_offset= get_lcd_disbuf_offset(cnt);

	lcd_buff[0] &= ~(0x0001<<digit_idx_offset);
	lcd_buff[1] &= ~(0x0003<<digit_idx_offset);
	lcd_buff[2] &= ~(0x0003<<digit_idx_offset);
	lcd_buff[3] &= ~(0x0003<<digit_idx_offset);

       lcd_buff[0] |= ((figure_temp & DIG_A))<<digit_idx_offset;
       lcd_buff[1] |= (((figure_temp & DIG_B)>>1)|((figure_temp & DIG_F)>>4))<<digit_idx_offset;
       lcd_buff[2] |= (((figure_temp & DIG_C)>>2)|((figure_temp & DIG_G)>>5))<<digit_idx_offset;
       lcd_buff[3] |= (((figure_temp & DIG_D)>>3)|((figure_temp & DIG_E)>>3))<<digit_idx_offset;   	   
#elif defined(K820_LHD_820_V001)
	if(cnt == 3)
	{
	    if(chardata == 1)
	    {
            	F_NUM_1BC |= NUM_1BC_MASK;
	    }
	    else
	    {
            	F_NUM_1BC &= ~NUM_1BC_MASK;
	    }
	    return 1;
	}
	figure_temp = figure_tab[chardata];

	digit_idx_offset= get_lcd_disbuf_offset(cnt);

	
	lcd_buff[0] &= ~(0x0003<<digit_idx_offset);
	lcd_buff[1] &= ~(0x0003<<digit_idx_offset);
	lcd_buff[2] &= ~(0x0003<<digit_idx_offset);
	lcd_buff[3] &= ~(0x0001<<digit_idx_offset);

       lcd_buff[0] |= ((figure_temp & DIG_A)|((figure_temp & DIG_B)))<<digit_idx_offset;
       lcd_buff[1] |= (((figure_temp & DIG_G)>>5)|((figure_temp & DIG_F)>>5))<<digit_idx_offset;
       lcd_buff[2] |= (((figure_temp & DIG_C)>>1)|((figure_temp & DIG_E)>>4))<<digit_idx_offset;
       lcd_buff[3] |= (((figure_temp & DIG_D)>>3)|((figure_temp & DIG_H)>>7))<<digit_idx_offset;   	 
#else
	if(cnt == 3)
	{
	    if(chardata == 1)
	    {
            	lcd_buff[0] |= 0x01;
	    }
	    else
	    {
            	lcd_buff[0] &= ~0x01;
	    }
	    return 1;
	}
	figure_temp = figure_tab[chardata];
	cnt =3- cnt;
	digit_idx_offset= (cnt*2)-1;
	
	lcd_buff[0] &= ~(0x0003<<digit_idx_offset);
	lcd_buff[1] &= ~(0x0003<<digit_idx_offset);
	lcd_buff[2] &= ~(0x0003<<digit_idx_offset);
	lcd_buff[3] &= ~(0x0003<<digit_idx_offset);
	   
       lcd_buff[0] |= (figure_temp & 0x03)<<digit_idx_offset;
       lcd_buff[1] |= ((figure_temp & 0x60)>>5)<<digit_idx_offset;
       lcd_buff[2] |= (((figure_temp & 0x10)>>4)|((figure_temp & 0x04)>>1))<<digit_idx_offset;
       lcd_buff[3] |= (((figure_temp & 0x08)>>3)|((figure_temp & 0x80)>>7))<<digit_idx_offset;
#endif
#if 0
	printf("--00--dispNum >%x \r\n",(u16) lcd_buff[0]);
	printf("--11--dispNum >%x \r\n",(u16) lcd_buff[1]);
	printf("--22--dispNum >%x \r\n",(u16) lcd_buff[2]);
	printf("--33--dispNum >%x \r\n",(u16) lcd_buff[3]);
#endif
	
	return 1;	
}
void dispnull(void)
{
}
void Disp_Null(void)
{
    dispstring("-No",0);
}
void disp_active(void)
{
	if(device_active == BIT(SDMMC))
	{
		 F_USB_DEV &=~ USB_DEV_MASK;
		 F_SD_DEV  |= SD_DEV_MASK;
	}
	else if(device_active == BIT(USB_DISK))
	{
		 F_USB_DEV |=USB_DEV_MASK;
		 F_SD_DEV  &= ~SD_DEV_MASK;
	}

	F_FM_DEV  &= ~FM_DEV_MASK;

}
void Disp_Num(void)
{
	dispNum((u8)((cfilenum/1000)%10),3);
	dispNum((u8)((cfilenum/100)%10),2);
	dispNum((u8)((cfilenum/10)%10),1);
	dispNum(cfilenum%10,0);
}
void Disp_Filenum(void)
{
	disp_active();
	dispNum((u8)((fs_msg.fileNumber/1000)%10),3);
	dispNum((u8)((fs_msg.fileNumber/100)%10),2);
	dispNum((u8)((fs_msg.fileNumber/10)%10),1);
	dispNum(fs_msg.fileNumber%10,0);
}
void Disp_Freq(void )
{
	if(frequency > 999)
	{
		dispNum((u8)((frequency/1000)%10),3);	
	}

	dispNum((u8)((frequency/100)%10),2);
	dispNum((u8)((frequency/10)%10),1);
	dispNum(frequency%10,0);
#ifdef RADIO_AM_WM_ENABLE
	if(radio_mode){

	F_FM_DEV  |= FM_DEV_MASK;
#if defined(K000_KT_AMFM_V001)
	F_MHZ_DEV |=FM_MHZ_MASK;
	F_P1_DEV |=FM_P1_MASK;
#endif

	}
	else{

	F_KHZ_DEV |=AM_KHZ_MASK;
	SPK_ICON|=SPK_MUTE_MASK;
	}
		
#else	
	F_FM_DEV  |= FM_DEV_MASK;
#if defined(K000_KT_AMFM_V001)
	F_MHZ_DEV |=FM_MHZ_MASK;
	F_P1_DEV |=FM_P1_MASK;
#endif
#endif
	
}
/*----------------------------------------------------------------------------*/
/**@brief
   @param  
   @return
   @note 
*/
/*----------------------------------------------------------------------------*/
void Disp_Nofile(void)
{
	dispnull();
}
/*----------------------------------------------------------------------------*/
/**@brief
   @param  
   @return
   @note 
*/
/*----------------------------------------------------------------------------*/
void Disp_Waiting(void)
{
	dispnull();
}
/*----------------------------------------------------------------------------*/
/**@brief
   @param  
   @return
   @note 
*/
/*----------------------------------------------------------------------------*/
void Disp_Nodevice(void)
{
    dispnull();
}
/*----------------------------------------------------------------------------*/
/**@brief
   @param  
   @return
   @note 
*/
/*----------------------------------------------------------------------------*/
void Disp_Vol(void)
{
	dispNum((my_music_vol/10),1);
	dispNum(my_music_vol%10,0);
}
void Disp_mode_icon(void)
{
       if(play_mode == REPEAT_ONE){
		F_REP_ONE|= REP_ONE_MASK;
	}
	else if(play_mode == 0){
		F_REP_ALL|= REP_ALL_MASK;
	}
	else{
		F_REP_ONE &= ~REP_ONE_MASK;
		F_REP_ALL  &= ~REP_ALL_MASK;
	}

	F_FM_DEV  &= ~FM_DEV_MASK;
	
}
void Disp_Playmode(void)
{

}
/*----------------------------------------------------------------------------*/
/**@brief
   @param  
   @return
   @note 
*/
/*----------------------------------------------------------------------------*/
void disp_file_time(void)
{

	

}
void Disp_Pause(void)
{
}

void Disp_Play(void)
{
}
void Disp_File_Name(void)
{

}
void Disp_Stop()
{

}
#if defined(IPONE_DOCK_FUNC_ENABLE)
void Disp_IPOD(void)
{
}
#endif

/*----------------------------------------------------------------------------*/
/**@brief
   @param  
   @return
   @note 
*/
/*----------------------------------------------------------------------------*/

void Disp_Eq(void)
{

}
void Disp_USB_Slave(void)
{
}
void Disp_AUX(void)
{


}
void Disp_Error(void)
{
}

void Disp_Start(void)
{

}
void Disp_PwrOFF(void)
{

}
/*----------------------------------------------------------------------------*/
/**@brief
   @param  
   @return
   @note 
*/
/*----------------------------------------------------------------------------*/
void Disp_Power_up(void)
{

}
void Disp_CH_NO(void )
{



}
void Disp_Scan_NO(void )
{



}
void Disp_Dev_Change(u8 flag)
{


}
void Disp_CLR(void)
{

}

#endif

