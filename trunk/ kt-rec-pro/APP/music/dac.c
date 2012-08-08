/*--------------------------------------------------------------------------*/
/**@file   dac.h
   @brief  dac头文件
   @details
   @author
   @date   2011-5-18
   @note
*/
/*----------------------------------------------------------------------------*/
#include "dac.h"

/*----------------------------------------------------------------------------*/
/**@brief    功放Mute开关函数
   @param	 mute：Mute开关
   @return	 无
   @note     void amp_mute(bool mute)
*/
/*----------------------------------------------------------------------------*/
#include "gpio_if.h"
#if 0
#define AMP_MUTE_PORT_INIT() 	 P0DIR &= ~BIT(1);P0PU &= ~BIT(1);P0PD &= ~BIT(1)
#define AMP_MUTE_DISABLE() 	 P01 = 0
#define AMP_MUTE_ENABLE() 	 P01 = 1
#endif
#if 0
void amp_mute(bool mute)
{
    AMP_MUTE_PORT_INIT();
    if (mute==1)
    {
        AMP_MUTE_ENABLE();
    }
    else
    {
        AMP_MUTE_DISABLE();
    }
}
#endif
