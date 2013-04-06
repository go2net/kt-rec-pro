/*--------------------------------------------------------------------------*/
/**@file   clock.c
   @brief  ʱ������
   @details
   @author
   @date   2010-12-13
   @note
*/
/*----------------------------------------------------------------------------*/
#include "config.h"
#include "radio_rev.h"

u8 _idata clock_in;
#ifdef FM_SYS_RUN_RC
u8 cur_sys_clk;
/*----------------------------------------------------------------------------*/
/**@brief  ����ϵͳʱ��
   @param  	1:SYS_CLK_1M_RC, 2: SYS_CLK_48M_PLL, 3:SYS_CLK_4M_HPRC	
   @return ��
   @note   void mainclock_select(u8 select)
*/
/*----------------------------------------------------------------------------*/
void sys_pll_select(u8 select)
{
	if ((select == SYS_CLK_1M_RC)&&(cur_sys_clk != SYS_CLK_1M_RC))
	{
		usb_suspend();
		cur_sys_clk = SYS_CLK_1M_RC;	
		PCON = 0x08;
		CLKCON1 &= ~(BIT(4));				//OSC_SEL PLL_SEL 32K_SEL
		CLKCON1 &= ~(BIT(5));
		CLKCON1 &= ~(BIT(6));
		_nop_();_nop_();_nop_();
		_nop_();_nop_();
		CLKCON0 = BIT(0);//(BIT(2)|BIT(0));		//RC_EN	  
		CLKCON1	= 0;
	}
	else if ((select == SYS_CLK_48M_PLL)&&(cur_sys_clk != SYS_CLK_48M_PLL))
	{
		cur_sys_clk	= SYS_CLK_48M_PLL;
		PCON = 0x08;	
    		CLKCON1 = 0;
		delay(10);
    		CLKCON0 = 0x1;	   	
		CLKCON0 |= BIT(2) | BIT(4);
		delay(20000);                  //wait PLL stable
		CLKCON1 = BIT(5);							
	}
	else if ((select == SYS_CLK_4M_HPRC)&&(cur_sys_clk != SYS_CLK_4M_HPRC))
	{
		usb_suspend();
		cur_sys_clk	= SYS_CLK_4M_HPRC;	   
		PCON = 0x08;
		CLKCON0 |= BIT(5);
		CLKCON1 &= ~(BIT(4));						//OSC_SEL PLL_SEL 32K_SEL
		CLKCON1 &= ~(BIT(5));
		CLKCON1 &= ~(BIT(6));
		_nop_();_nop_();_nop_();_nop_();_nop_();
		_nop_();_nop_();_nop_();_nop_();_nop_();
//		CLKCON1 = 0;
		_nop_();_nop_();_nop_();_nop_();_nop_();
		_nop_();_nop_();_nop_();_nop_();_nop_();
			 
///��HPRC����ʹ��HPRC/2��Ϊϵͳ��ʱ��,HPRC����ֵΪ3M
		CLKCON0 = BIT(0)|BIT(3)| BIT(5);//Rc Enable��OSC2X_EN��HPRC_EN		 BIT(2)|
	
		CLKCON1 = BIT(3)|BIT(2);	//BIT(2);//  	x  3M
//		CLKCON1 = BIT(3);		    //6M
		
		CLKCON1 |= BIT(4);			//PLL SEL
	    delay(1000);
	}
}
extern u8 scan_mode;
extern bool adkey_activated;
u8 radio_pll_delay_timer=0;
u8 radio_pll_setting=0;
void radio_auto_pll_ctrl(void)
{
	if((adkey_activated)||(scan_mode != RADIO_SCAN_STOP)){

		radio_pll_delay_timer =6;
		adkey_activated =0;
		if(radio_pll_setting!=SYS_CLK_48M_PLL){
			radio_pll_setting =SYS_CLK_48M_PLL;
	              //sys_pll_select(SYS_CLK_48M_PLL);
			//SYSTEM_CLK_DIV4();				  
    			 //printf(" --->SYS_CLK_48M_PLL \r\n");
		}		
	}
	else{

		if(radio_pll_delay_timer==0){
			if(radio_pll_setting!=SYS_CLK_4M_HPRC){
				radio_pll_setting =SYS_CLK_4M_HPRC;
    			  	//printf(" --->SYS_CLK_4M_HPRC \r\n");
	                     sys_pll_select(SYS_CLK_4M_HPRC);
				timer_init(MAIN_CLK_RC);
			}
		}
       }
}
void radio_auto_pll_handlr(void)
{
	if(radio_pll_delay_timer>0)radio_pll_delay_timer--;
}
void radio_auto_pll_resume(void)
{
	sys_pll_select(SYS_CLK_48M_PLL);
	SYSTEM_CLK_DIV4();
}
#endif

#if 0
/*----------------------------------------------------------------------------*/
/**@brief  P05��������
   @param  P05_SEL_IO:��ͨIO����, P05_SEL_OSC1:�����RTC���񴦵ľ���ʱ��, P05_SEL_PLL
   @return ��
   @note   void P05_source_select(u8 sel)
*/
/*----------------------------------------------------------------------------*/
void P05_source_select(u8 sel)
{
    if (sel == P05_SEL_IO)								//��ͨIO����
    {
        P0DIR |= BIT(5);
        P5PU &= ~(BIT(4) | BIT(5));
    }
    else if (sel == P05_SEL_OSC1)							//�����RTC���񴦵ľ���ʱ��
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
/**@brief  timer ��ʼ��
   @param  1:48M, 0:24M
   @return ��
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
        T0SCA = 10;      // 1/(2^n)��Ƶ
    else if (clk == MAIN_CLK_48M)
        T0SCA = 11;
    else if (clk == MAIN_CLK_RC)
        T0SCA = 8;
    T0PRD = 46;
    T0CNT = 0;
    T0CON = 0x21;   //����ΪTIMERģʽ����������Ӧ���жϴ�
    ET0 = 1;
////timer3
#ifndef NO_IR_REMOTE
    PT3 = 1;
	if (clk == MAIN_CLK_12M)
		T3SCA = 0x25;
    if (clk == MAIN_CLK_24M)
        T3SCA = 0x26;      // 1/(2^n)��Ƶ
    else if (clk == MAIN_CLK_48M)
        T3SCA = 0x27;
    T3CNTL = 0;
    T3CNTH = 0;
    T3PRD = 0xa1;
    T3PRD = 0x22;
    T3CON = 0x32;      //����ΪTIMERģʽ����������Ӧ���жϴ�
    ET3 = 1;
#endif	
}

