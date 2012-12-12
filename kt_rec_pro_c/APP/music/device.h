/*--------------------------------------------------------------------------*/
/**@file    DEVICE.h
   @brief   设备控制接口
   @details
   @author
   @date   2010-12-13
   @note
*/
/*----------------------------------------------------------------------------*/
#ifndef __DEVICE_H__
#define __DEVICE_H__

#ifdef __C51__
#include "config.h"

u8 find_device(u8);
u8 device_init(void);
void write_file_info(u8);

/*----------------------------------------------------------------------------*/
/**@brief   检测当前活动的设备
   @param   无
   @return  0：当前活动的设备不在线：其他：当前活动的设备
   @note    u8 device_check(void)
*/
/*----------------------------------------------------------------------------*/
u8 device_check(void);

enum
{
    NO_DEVICE = 0,
    DEVICE_SDMMC0 = 1,
    //DEVICE_SDMMC1,
    DEVICE_UDISK = 2,
    DEVICE_SDMMC0_REC = 0x41,
    DEVICE_UDISK_REC = 0x42,
    DEVICE_AUTO_NEXT = 0x81,
    DEVICE_AUTO_PREV = 0x82,
    MAX_PLAY_DEVICE = 2,

};

enum
{
    FIND_DEV_OK      = 0,				//成功找到设备
    DEFINE_DEV_WKING,					//指定设备已经被选中,正在播放
    ONLY_ONE_DEVICE,  					//只有一个设备,并已经选中，无法选择下一个设备
    NO_DEFINE_DEV,    					//指定设备未找到
    DEV_INIT_ERR,     					//找到设备，但初始化失败
    NO_EFFECTIVE_DEV,					//无有效可以使用的设备
    NO_DEV_ONLINE,    					//无在线设备
};
#endif


/////

#define VIRTUAL_DEVICE  (DEVICE_SDMMC0_REC & (~DEVICE_SDMMC0))


#if VIRTUAL_ENABLE
    #define MAX_DEVICE 4
#else
    #define MAX_DEVICE 2
#endif
#endif