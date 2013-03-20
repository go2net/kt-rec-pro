/*--------------------------------------------------------------------------*/
/**@file   dsp.h
   @brief  dspÍ·ÎÄ¼þ
   @details
   @author
   @date   2011-9-8
   @note
*/
/*----------------------------------------------------------------------------*/
#ifndef _DSP_
#define _DSP_

#include "typedef.h"

#ifdef __C51__
void dsp_set_volume(unsigned short n);
void dsp_set_sr(unsigned short n);
void dsp_set_kv(KEY_VOICE _xdata * key_cfg);
#endif

#endif