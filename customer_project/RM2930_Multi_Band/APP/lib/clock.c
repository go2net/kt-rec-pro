/*--------------------------------------------------------------------------*/
/**@file   clock.c
   @brief  时钟配置
   @details
   @author
   @date   2010-12-13
   @note
*/
/*----------------------------------------------------------------------------*/
#include "config.h"

u8 _idata clock_in;
#if 0
/*----------------------------------------------------------------------------*/
/**@brief  P05功能设置
   @param  P05_SEL_IO:普通IO功能, P05_SEL_OSC1:输出从RTC晶振处的晶振时钟, P05_SEL_PLL
   @return 无
   @note   void P05_source_select(u8 sel)
*/
/*----------------------------------------------------------------------------*/
void P05_source_select(u8 sel)
{
    if (sel == P05_SEL_IO)								//普通IO功能
    {
        P0DIR |= BIT(5);
        P5PU &= ~(BIT(4) | BIT(5));
    }
    else if (sel == P05_SEL_OSC1)							//输出从RTC晶振处的晶振时钟
    {
        CLKCON1 |= 3;
        P5PU |= BIT(4);
        P0DIR &= ~BIT(5);
    }
    else if (sel == P05_SEL_PLL)
    {
        P5PU |= (BIT(4) | BIT(5));
        P0DIR &= ~BIT(5);
    }
}
#endif
/*----------------------------------------------------------------------------*/
/**@brief  timer 初始化
   @param  1:48M, 0:24M
   @return 无
   @note   void timer_init(u8 clk)
*/
/*----------------------------------------------------------------------------*/
#pragma disable
void timer_init(u8 clk)
{
/////rtc timer
    IP1 |= BIT(7);
    IE1 |= BIT(7);

/////timer 0
    PT0 = 1;
	if (clk == MAIN_CLK_12M)
		T0SCA = 9;
    if (clk == MAIN_CLK_24M)
        T0SCA = 10;      // 1/(2^n)分频
    else if (clk == MAIN_CLK_48M)
        T0SCA = 11;
    T0PRD = 46;
    T0CNT = 0;
    T0CON = 0x21;   //设置为TIMER模式，并将其相应的中断打开
    ET0 = 1;
////timer3
#ifndef NO_IR_REMOTE
    PT3 = 1;
	if (clk == MAIN_CLK_12M)
		T3SCA = 0x25;
    if (clk == MAIN_CLK_24M)
        T3SCA = 0x26;      // 1/(2^n)分频
    else if (clk == MAIN_CLK_48M)
        T3SCA = 0x27;
    T3CNTL = 0;
    T3CNTH = 0;
    T3PRD = 0xa1;
    T3PRD = 0x22;
    T3CON = 0x32;      //设置为TIMER模式，并将其相应的中断打开
    ET3 = 1;
#endif	
}

