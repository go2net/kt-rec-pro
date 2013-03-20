/*--------------------------------------------------------------------------*/
/**@file     uart.h
   @brief    ´®¿Ú´òÓ¡Çý¶¯
   @details
   @author
   @date   2011-4-26
   @note
*/
/*----------------------------------------------------------------------------*/
#ifndef _UART_
#define _UART_

#include "config.h"

#ifdef __C51__
void uart_init(void);
void putbyte (char c);
//void printf_buf(u8 _xdata *buf, u16 len);
void printf_u8(u8 dat);

void deg_str(u8 *p);
void printf_u32(u32 dat);
void printf_u16(u16,u8);
#endif

#endif