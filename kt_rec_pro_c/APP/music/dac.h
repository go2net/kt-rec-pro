/*--------------------------------------------------------------------------*/
/**@file   dac.h
   @brief  dac头文件
   @details
   @author
   @date   2011-9-8
   @note
*/
/*----------------------------------------------------------------------------*/
#ifndef _DAC_H_
#define _DAC_H_

#include "config.h"

#ifdef __C51__
#define AMUX0_IE		0xCF
#define AMUX1_IE        0x3F
#define AMUX_P2IE_SET(x)		P2IE = x			//设置 AMUX通道
/*----------------------------------------------------------------------------*/
/**@brief    获取数字音量或主音量
   @param    mode：通道
   @return   无
   @note     u8 get_dac_vol(u8 mode)
*/
/*----------------------------------------------------------------------------*/
u8 get_dac_vol(u8 mode);
/*----------------------------------------------------------------------------*/
/**@brief    关DAC
   @param    mode: 0 不高阻， 1：高阻
   @return   无
   @note     void dac_off(u8 mode)
*/
/*----------------------------------------------------------------------------*/
void dac_off(u8 mode);
/*----------------------------------------------------------------------------*/
/**@brief    DAC mute控制函数
   @param    mute：1：enable mute；0：disable mute
   @param    mode：1：马上生效，0：在调用dac_out_select()时延时生效
   @return   无
   @note     void dac_mute_control(u8 mute)
*/
/*----------------------------------------------------------------------------*/
void dac_mute_control(u8 mute,u8 mode);
/*----------------------------------------------------------------------------*/
/**@brief    DAC mute状态切换 mute <->unmute
   @param    无
   @return   指针位置
   @note     bool dac_mute_toggle(void)
*/
/*----------------------------------------------------------------------------*/
bool dac_mute_toggle(void);
/*----------------------------------------------------------------------------*/
/**@brief    DAC 通道选择
   @param    sel：选择的通道
   @return   无
   @note     void dac_channel_sel(u8 sel)
*/
/*----------------------------------------------------------------------------*/
void dac_channel_sel(u8 sel);
/*----------------------------------------------------------------------------*/
/**@brief    DAC 输出通道选择
   @param    channel：选择的通道
   @param    mode：是否为静音模式
   @return   无
   @note     void dac_out_select(u8 channle, u8 mode)
*/
/*----------------------------------------------------------------------------*/
void dac_out_select(u8 channle, u8 mode);
/*----------------------------------------------------------------------------*/
/**@brief    DAC 初始化
   @param    m_vol：主音量
   @param    mode：是否为静音模式
   @return   无
   @note     void dac_init(u8 m_vol)
*/
/*----------------------------------------------------------------------------*/
void dac_init(u8 m_vol);
/*----------------------------------------------------------------------------*/
/**@brief    打开DAC
   @param    mode 0:不打开VCOMO， 1：打开VCOMO
   @return   无
   @note     void dac_on1(u8 mode)
*/
/*----------------------------------------------------------------------------*/
void dac_on1(u8 mode);
/*----------------------------------------------------------------------------*/
/**@brief    主音量设置
   @param    vol：主音量
   @param    mode：设置模式
   @return   无
   @note     u8 main_vol_set(u8 vol, u8 mode)
*/
/*----------------------------------------------------------------------------*/
u8 main_vol_set(u8 vol, u8 mode);

/*----------------------------------------------------------------------------*/
/**@brief    功放Mute
   @param    是否打开功放mute
   @return   无
   @note     void amp_mute(bool mute)
*/
/*----------------------------------------------------------------------------*/
void amp_mute(bool mute);

#endif


////u8 main_vol_set(u8 vol, u8 mode)中，mode说明
#define CHANGE_VOL_NO_MEM   0
#define CHANGE_VOL_MEM   	1
#define SET_USE_CURRENT_VOL 2
#define CHANGE_VOL_INC      3
#define CHANGE_VOL_DEC      4

#define CHANGE_VOL_PEND     0x10
#define CHANGE_VOL_NO_PEND  0x0

#define TRACK_ALL    0 
#define TRACK_RIGHT  1 
#define TRACK_LEFT   2

#define REC_FM     		0x00 
#define REC_LINEIN 		0x01
#define REC_MIC			0x02 

//////通道选择
#define DAC_AMUX0			0
#define DAC_AMUX1			1
#define DAC_MUSIC			2

///最大音量
#define MAX_DIGITAL_VOL 	30
#define MAX_ANOLOG_VOL 		30
#define MAX_MAIN_VOL        30

#endif