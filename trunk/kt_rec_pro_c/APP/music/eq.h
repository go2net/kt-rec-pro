/*--------------------------------------------------------------------------*/
/**@file     eq.h
   @brief    音效头文件
   @details
   @author
   @date   2010-12-13
   @note
*/
/*----------------------------------------------------------------------------*/
#ifndef _EQ_H_
#define _EQ_H_

#ifdef __C51__
#include "config.h"

#define DECODE_EQ       0
#define DSP_EQ          1
#define EQ_WORK_USE  DSP_EQ//DECODE_EQ//

enum
{
    NORMAL = 0,
    POP,
    ROCK,
    JAZZ,
    CLASSIC,
};

void set_decode_eq(u8 n);
void set_dsp_eq(u8 n);
void amux_dsp_eq(void);
void set_eq(u8 n);
#endif

#endif