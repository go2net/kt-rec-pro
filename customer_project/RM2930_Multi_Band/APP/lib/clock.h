/*--------------------------------------------------------------------------*/
/**@file   clock.h
   @brief  时钟配置
   @details
   @author
   @date   2010-12-13
   @note
*/
/*----------------------------------------------------------------------------*/
#ifndef __CLCOK_H__
#define __CLOCK_H__


#ifdef __C51__
#include "config.h"
/*----------------------------------------------------------------------------*/
/**@brief   PLL输入时钟选择
   @param   select: 见后面的注释
   @param   share_osc: 0:不与外部设备共享晶振，1：与外部设备共享晶振(从OSC OUT处引至其它设备)
   @return  无
   @note
*/
/*----------------------------------------------------------------------------*/
void PLL_init(u8 select, u8 share_osc);

/*----------------------------------------------------------------------------*/
/**@brief   PLL输出方式选择
   @param   select: 0--选择输入时钟乘以2， 1--选择48M输出（只能是输入时钟为32K,7.6M, 12M时使用）
   @return  无
   @note
*/
/*----------------------------------------------------------------------------*/
void PLL_output(u8 select);

/*----------------------------------------------------------------------------*/
/**@brief   主时钟树选择
   @param   select: 0--选择RC，1--高速时钟，2--PLL的输出，3--32K
   @return  无
   @note
*/
/*----------------------------------------------------------------------------*/
void mainclock_select(u8 select);


/*----------------------------------------------------------------------------*/
/**@brief   系统时钟选择（给CPU及大部分外设）
   @param   select: 0--与主时钟树同频，1--主时钟频率的一半
   @return  无
   @note
*/
/*----------------------------------------------------------------------------*/
void sysclock_div2(u8 select);

/*----------------------------------------------------------------------------*/
/**@brief   解码模块时钟选择
   @param   select: 0--与主时钟树同频，1--主时钟频率的一半
   @return  无
   @note
*/
/*----------------------------------------------------------------------------*/
void decodeclock_div2(u8 select);


/*----------------------------------------------------------------------------*/
/**@brief   OTP模块时钟选择
   @param   select: 0--与主时钟树同频，1--主时钟频率的一半
   @return  无
   @note
*/
/*----------------------------------------------------------------------------*/
void otpclock_div2(u8 select);

/*----------------------------------------------------------------------------*/
/**@brief   P05输出时钟源选择
   @param   select: 0--普通IO，1--RTC处所使用的晶振, 3--PLL输出时钟，如果PLL未打开，则输出RC时钟
   @return  无
   @note	void P05_source_select(u8 select)
*/
/*----------------------------------------------------------------------------*/
void P05_source_select(u8 select);

/*----------------------------------------------------------------------------*/
/**@brief   喂狗函数
   @param   void
   @return  无
   @note   void WDT_CLEAR(void)
*/
/*----------------------------------------------------------------------------*/
extern void WDT_CLEAR(void);

/*----------------------------------------------------------------------------*/
/**@brief   使用TIMER初始化函数，可以根据不同的系统时钟做配置
   @param   clk : MAIN_CLK_24M (系统时钟使用24Mhz时的参数);MAIN_CLK_48M(系统时钟使用48Mhz时的参数)
   @return  void
   @note    void timer_init(u8 clk)
*/
/*----------------------------------------------------------------------------*/
void timer_init(u8 clk);

/*----------------------------------------------------------------------------*/
/**@brief   使用SDMMC CLK做SDMMC在线检测的函数
   @param   mode:0 普通检测， 1 SDMMC在线检测
   @return  0:IO低，1：IO高，其它：此次检测无效
   @note    u8 sdmmc_online_chk(u8 mode)
*/
/*----------------------------------------------------------------------------*/
extern u8 sdmmc_online_chk(u8 mode);

///
/*----------------------------------------------------------------------------*/
/**@brief   发送一个按键音
   @param   void
   @return  void
   @note    void fun_send_kv(void)
*/
/*----------------------------------------------------------------------------*/
extern void fun_send_kv(void);
///
/*----------------------------------------------------------------------------*/
/**@brief   发送一个闹铃音
   @param   void
   @return  void
   @note    void send_alm_voice(void)
*/
/*----------------------------------------------------------------------------*/
extern void send_alm_voice(void);
///
/*----------------------------------------------------------------------------*/
/**@brief   按键音闹钟音发送状态查询
   @param   void
   @return  1：空闲；0：繁忙
   @note   void bsp_kv_init(void)
*/
/*----------------------------------------------------------------------------*/
extern u8 kv_send_finish(void);
/*----------------------------------------------------------------------------*/
/**@brief   按键音闹钟音函数初始化
   @param   void
   @return  无
   @note   void bsp_kv_init(void)
*/
/*----------------------------------------------------------------------------*/
extern void bsp_kv_init(void);

/*----------------------------------------------------------------------------*/
/**@brief   设置模拟、数字音量的最大值，
   @param   模拟音量： anolog_vol 0~30
   @param   数字音量： digtal_vol 0~55
   @return  无
   @note   void set_max_vol(u8 anolog_vol,digtal_vol)
*/
/*----------------------------------------------------------------------------*/
extern void set_max_vol(u8 anolog_vol,digtal_vol);

/*----------------------------------------------------------------------------*/
/**@brief   芯片内部上电
   @param   无
   @return  无
   @note   void core_power_on(void)
*/
/*----------------------------------------------------------------------------*/
void core_power_on(void);

/*----------------------------------------------------------------------------*/
/**@brief  sdmmc命令检测方式的时候的使能函数,只能在命令检测方式下使用
   @param  flag:Sd_api_cmd
   @return void
   @note   void sd_chk_ctl(u8 flag)
*/
/*----------------------------------------------------------------------------*/
void sd_chk_ctl(u8 flag);

/*----------------------------------------------------------------------------*/
/**@brief  实现sdmmc IO检测功能，默认使用CMD检测
   @param  flag:0 : remove sd;1 : insert sd
   @return void
   @note   void sdmmc_chk_io(u8 flag)
*/
/*----------------------------------------------------------------------------*/
void sdmmc_chk_io(u8 flag);

u8 cmd_ctl_rec(u8 cmd,u8 dat);

void sys_clock_select(u8 select);

/*----------------------------------------------------------------------------*/
/**@brief 录音通道设置
   @param  fchannel ：REC_FM
   @                  REC_LINEIN
   @                  REC_MIC
   @return void
   @note   void dsp_recode_channel(u8 channel)
*/
/*----------------------------------------------------------------------------*/
void dsp_recode_channel(u8 channel);
/*******************************************************************************/
//APP 函数
/*******************************************************************************/
void radio_auto_pll_ctrl(void);
void radio_auto_pll_handlr(void);
void radio_auto_pll_resume(void);


#define WDT_EN()		WDTCON = 0x9D; while(WDTCON & BIT(6)); WDTCON = 0xBD			//允许复位功能，溢出时间为6.7S
//#define WDT_CLEAR()     WDTCON |= BIT(7)			//清WDT，必须在WDT溢出之前清掉WDT计数器
#define SYS_IDLE()         PCON |= BIT(6)
#ifdef UART_ENABLE
//#define SYSTEM_CLK_DIV4()  usb_suspend();CLKCON1 |= 0x80; PCON |= BIT(1);timer_init(MAIN_CLK_12M);UTBAUD = (12000000/(8 * 115200)) - 1; /*解码模式下不可使用*/
//#define SYSTEM_CLK_DIV2()  CLKCON1 &= ~0x80;PCON |= BIT(1);timer_init(MAIN_CLK_24M);UTBAUD = (24000000/(8 * 115200)) - 1;
#define SYSTEM_CLK_DIV1()  CLKCON1 &= ~0x80;PCON &= ~(BIT(1));timer_init(MAIN_CLK_48M);UTBAUD = (48000000/(8 * 115200)) - 1;
#define SYSTEM_CLK_DIV4() SYSTEM_CLK_DIV1()
#define SYSTEM_CLK_DIV2() SYSTEM_CLK_DIV1()
#else
#define SYSTEM_CLK_DIV4()  usb_suspend();CLKCON1 |= 0x80; PCON |= BIT(1);timer_init(MAIN_CLK_12M);UTBAUD = (12000000/(8 * 115200)) - 1; /*解码模式下不可使用*/
#define SYSTEM_CLK_DIV2()  CLKCON1 &= ~0x80;PCON |= BIT(1);timer_init(MAIN_CLK_24M);UTBAUD = (24000000/(8 * 115200)) - 1;
#define SYSTEM_CLK_DIV1()  CLKCON1 &= ~0x80;PCON &= ~(BIT(1));timer_init(MAIN_CLK_48M);UTBAUD = (48000000/(8 * 115200)) - 1;
#endif
#define OTP_CLK_DIV2()  PCON |= BIT(3)
#define OTP_CLK_DIV1()  PCON &= ~BIT(3)
#define DECODER_DIV1()	PCON &= ~BIT(2)
#define DECODER_DIV2()	PCON |= BIT(2)

#endif

//PLL 输入
//晶振输入时钟选择
//OSC0: RTC模块的振荡器，可接32768晶振和高速晶振
//OSC1: P00/P01上的振荡器，只能接高速晶振
#define PLL_IN_OSC1_24M      0x0			//crystal = 24M at osc1
#define PLL_IN_OSC0_32K      0x1			//crystal = 32K at osc0
#define PLL_IN_OSC0_4M       0x2			//crystal = 4M at osc0
#define PLL_IN_OSC0_12M      0x4			//crystal = 12M at osc0
#define PLL_IN_OSC1_4M       0x20			//crystal = 4M at osc1
#define PLL_IN_OSC1_12M      0x40			//crystal = 12M at osc1
#define PLL_IN_HPRC     	 0x80			//use HPRC

//系统时钟选择
#define MAIN_CLK_12M     0
#define MAIN_CLK_24M     1
#define MAIN_CLK_48M     2

#define MAIN_CLK_RC     3

//P05输出选择
#define P05_SEL_IO			0
#define P05_SEL_OSC1		1
#define P05_SEL_PLL			2

#endif
