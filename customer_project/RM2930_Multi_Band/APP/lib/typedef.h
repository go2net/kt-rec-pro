/*************************************************************
File: typedef.h
Author:Juntham
Discriptor:
    数据类型重定义
Version:
Date：
*************************************************************/
#ifndef _typedef_h_
#define _typedef_h_

#include "AC309N.h"

#define FALSE	0
#define TRUE    1

#define false	0
#define true    1

#define MASKROM_DATA    0x3700
#define BSP_DATA        0x3500
#define APP_DATA        0x3400

#ifdef __C51__
typedef unsigned char	u8, uint8;
typedef char			s8, int8;
typedef unsigned int	u16, uint16;
typedef signed int		s16, int16;
typedef unsigned long	u32, uint32;
typedef signed long		s32, int32;

typedef xdata unsigned char 	xd_u8, xd_uint8;
typedef xdata unsigned int		xd_u16, xd_uint16;
typedef xdata signed long		xd_u32, xd_uint32;

#define bool		bit
#define _xdata		xdata
#define _data		data
#define _idata		idata
#define _pdata		pdata
#define _bdata		bdata
#define _bit		bit
#define _sbit		sbit
#define _code		code
#define _small		small
#define _large      large


#define     BIT(n)	            (1 << (n))
#define     BitSET(REG,POS)     (REG |= (1 << (POS)))
#define     BitCLR(REG,POS)     (REG &= (~(1 << (POS))))
#define     BitXOR(REG,POS)     (REG ^= (~(1 << (POS))))
#define     BitCHK_1(REG,POS)   ((REG & (1 << (POS))) == (1 <<( POS)))
#define     BitCHK_0(REG,POS)   ((REG & (1 << (POS))) == 0x00)
#define     testBit(REG,POS)    (REG & (1 << (POS)))

#define     clrBit(x,y)         (x) &= ~(1L << (y))
#define     setBit(x,y)         (x) |= (1L << (y))

#endif
#endif