/*--------------------------------------------------------------------------*/
/**@file   my_printf.c
   @brief    格式化输出
   @details
   @author
   @date   2011-3-7
   @note
*/
/*----------------------------------------------------------------------------*/
#include "my_printf.h"
#include "config.h"
#if ((monitor == DISP_LED5X7)||(LCD_DISP == monitor)||(LCD_DRV_DISP == monitor))

extern void led_putchar(u8 chardata,u8 loc);
u8 _xdata aa[4];
/*----------------------------------------------------------------------------*/
/**@brief    显示字符串
   @param	 * str：字符串地址 ，loc:数据位置
   @return	 无
   @note     void printf_str(u8 *str,u8 loc)
*/
/*----------------------------------------------------------------------------*/
void printf_str(u8 *str,u8 loc)
{
    u8 c;
    while (1)
    {
        c = *str++;
        if (c == '\0')
            break;
        led_putchar(c,loc++);
    }
}

/*----------------------------------------------------------------------------*/
/**@brief    数字转换
   @param	 dat：转换数字
   @return	 无
   @note     void number_ascii(u16 dat)
*/
/*----------------------------------------------------------------------------*/
void number_ascii(u16 dat)
{
    aa[0] = dat%10 + '0';
    aa[1] = (dat/10)%10 + '0';
    aa[2] = (dat/100)%10 + '0';
    aa[3] = (dat/1000)%10 + '0';
}

/*----------------------------------------------------------------------------*/
/**@brief    数字显示
   @param	 dat：转换数字，loc：数字开始位置 ，len：数字长度
   @return	 无
   @note     void number_ascii(u16 dat)
*/
/*----------------------------------------------------------------------------*/
void printf_num(u16 dat,u8 loc,u8 len)
{
    if((!len) || (len>4))
    {
        return;
    }
    number_ascii(dat);
    do
    {
        led_putchar(aa[--len],loc++);
    }
    while(len);
}

#endif
