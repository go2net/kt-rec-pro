/*--------------------------------------------------------------------------*/
/**@file    led.c
   @brief   4λLED����
   @details
   @author
   @date   2010-12-13
   @note
*/
/*----------------------------------------------------------------------------*/
#include "config.h"
#include "led.h"
#include "uart.h"
#if 0//(monitor == DISP_LED5X7)

#define LED_SBUF_IDX		4
#define LED0_STATUS          LED_BUFF[LED_SBUF_IDX]
#define LED0_FLASH_STATUS    LED_FLASH[LED_SBUF_IDX]



_xdata u8 LED_BUFF[5];   ///<LED�Դ�
_idata u8 LED_FLASH[5];
/*
u8 _code led_icon[] =    ///<LED��־λ
{
    LED0_FM,
    LED0_USB,
    LED0_SD,
    LED0_MP3,
    LED0_2POINT,
	LED0_PLAY,
	LED0_PAUSE,
};
*/
#define LED_MINUS     0x40

u8 _code LED_NUMBER[10] =
{
    0x3f,0x06,0x5b,0x4f,0x66,  ///<0~4
    0x6d,0x7d,0x07,0x7f,0x6f   ///<5~9
};

u8 _code LED_LARGE_LETTER[26] =
{
    0x77,0x40,0x39,0x3f,0x79,///<ABCDE
    0x71,0x40,0x76,0x06,0x40,///<FGHIJ
    0x40,0x38,0x40,0x37,0x3f,///<KLMNO
    0x73,0x40,0x50,0x6d,0x40,///<PQRST
    0x3e,0x3e,0x40,0x76,0x40,///<UVWXY
    0x40///<Z
};

u8 _code LED_SMALL_LETTER[26] =
{
    0x77,0x7c,0x58,0x5e,0x79,///<abcde
    0x71,0x40,0x40,0x40,0x40,///<fghij
    0x40,0x38,0x40,0x54,0x5c,///<klmno
    0x73,0x67,0x50,0x40,0x40,///<pqrst
    0x3e,0x3e,0x40,0x40,0x40,///<uvwxy
    0x40///<z
};
/*----------------------------------------------------------------------------*/
/**@brief    ���LED BUFF������LED��ʾλ����Ϊ1
   @param	 ��
   @return	 ��
   @note     void clear_led(void)
*/
/*----------------------------------------------------------------------------*/
void clear_led(void)
{
    LED_BUFF[0] = 0;	  /* ǧλ */
    LED_BUFF[1] = 0;	  /* ��λ */
    LED_BUFF[2] = 0;	  /* ʮλ */
    LED_BUFF[3] = 0;	  /* ��λ */
    LED_BUFF[4] = 0;	  /* ״̬λ */
    LED_FLASH[0] = 0;
    LED_FLASH[1] = 0;
    LED_FLASH[2] = 0;
    LED_FLASH[3] = 0;
    LED_FLASH[4] = 0;
}

/*----------------------------------------------------------------------------*/
/**@brief    �����״̬λ��ʾ
   @param	 id��Ҫ��ʾ��״̬λ
   @return	 ��
   @note     void led_disp_icon(u8 id)
*/
/*----------------------------------------------------------------------------*/
void led_disp_icon(u8 id)
{
    LED0_STATUS |= id;	
}

/*----------------------------------------------------------------------------*/
/**@brief    LED��˸����
   @param	 id��״̬λ
   @return	 ��
   @note     void led_flash_icon(u8 id)
*/
/*----------------------------------------------------------------------------*/
void led_flash_icon(u8 id)
{
    LED0_FLASH_STATUS |= id;	
}

/*----------------------------------------------------------------------------*/
/**@brief    LED��˸����
   @param	 flag����˸������λ
   @return	 ��
   @note     void led_flash_section(u8 flag)
*/
/*----------------------------------------------------------------------------*/
void led_flash_section(u8 flag)
{
	if(flag!= LED_SBUF_IDX)
	{
	    LED_FLASH[flag]=0xff;
	}	
}

/*----------------------------------------------------------------------------*/
/**@brief    LED ��ʾ��ʼ��
   @param	 ��
   @return	 ��
   @note     void init_led_disp(void)
*/
/*----------------------------------------------------------------------------*/
void init_led_disp(void)
{
#ifndef NO_LED_DISPLAY
    clear_led();
    led_com_out();
    led_seg_out();
#endif	
}

/*----------------------------------------------------------------------------*/
/**@brief    LED ��������
   @param	 br:������ֵ
   @return	 ��
   @note     void led_set_brightness(u8 br)
*/
/*----------------------------------------------------------------------------*/
void led_set_brightness(u8 br)
{
    if (br > 16)
        return;
    if (br == 16)
        PWM4CON = 0;
    else
        PWM4CON = br | 0xd0;
}

/*----------------------------------------------------------------------------*/
/**@brief    LED �ַ���ʾ
   @param	 chardata���ַ�����
   @return	 ��
   @note     void led_putchar(u8 chardata,u8 loc)
*/
/*----------------------------------------------------------------------------*/
void led_putchar(u8 chardata,u8 loc)
{
    loc += 0;
    if ((chardata < ' ') || (chardata > '~'))
    {
        return;
    }
    if ((chardata >= '0') && (chardata <= '9'))
    {
        LED_BUFF[loc] = LED_NUMBER[chardata - '0'];
    }
    else if ((chardata >= 'a') && (chardata <= 'z'))
    {
        LED_BUFF[loc] = LED_SMALL_LETTER[chardata - 'a'];
    }
    else if ((chardata >= 'A') && (chardata <= 'Z'))
    {
        LED_BUFF[loc] = LED_LARGE_LETTER[chardata - 'A'];
    }
    else if (chardata == ':')
    {
        LED0_STATUS |= LED0_2POINT;
    }
    else if (chardata == ' ')
    {

    }
    else if (chardata == '-')
    {
        LED_BUFF[loc] = LED_MINUS;
    }
}

/*----------------------------------------------------------------------------*/
/**@brief    LEDɨ�躯��
   @param
   @return
   @note     void disp_scan(void)
*/
/*----------------------------------------------------------------------------*/
void disp_scan(void)
{
#ifndef NO_LED_DISPLAY
    static xd_u8 cnt;
    static xd_u8 counter;
    static bool flash;

    xd_u8 com, seg;


    counter++;
    if (counter == 250)
    {
        counter = 0;
        flash = !flash;
    }

    if (flash)
    {
        seg = LED_BUFF[cnt] ^ LED_FLASH[cnt];   
    }
    else
    {
        seg = LED_BUFF[cnt]; 
    }
    com = BIT(cnt); 
    /**/
    LED_COM &= ~0x1f;
    LED_COM_MASK &= ~0x1f;
    LED_SEG |= 0x7f;			 //��LED COM SEG

    LED_SEG &= ~seg;
    LED_COM |= com;
    LED_COM_MASK |= com;
    cnt = (cnt >= 4)?( 0 ): (cnt+1);
#endif	
}
#else
//void disp_scan(void)
//{
//}
#endif
