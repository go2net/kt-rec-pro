/*--------------------------------------------------------------------------*/
/**@file   main.h
   @brief  系统主函数头文件
   @details
   @author
   @date   2011-9-8
   @note
*/
/*----------------------------------------------------------------------------*/

#ifndef __MAIN_H__
#define __MAIN_H__

#include "config.h"
#include "key.h"
#include "uart.h"
#include "lcd.h"
#include "aux_fun.h"

#ifdef __C51__
extern  void restore_music_point(void);
#endif

#endif
