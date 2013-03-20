/*--------------------------------------------------------------------------*/
/**@file     diskio.h
   @brief    disk io header file
   @details
   @author
   @date   2011-3-30
   @note
*/
/*----------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------
/  PFF - Low level disk interface modlue include file    (C)ChaN, 2009
/-----------------------------------------------------------------------*/

#ifndef _DISKIO

#include "typedef.h"

#ifdef __C51__
#define __keil 1
#else
#define __keil 0
#endif

#ifdef WIN32
#define __win 1
#else
#define __win 0
#endif

#if __keil | __win
/* Status of Disk Functions */
typedef u8	DSTATUS;


/* Results of Disk Functions */
typedef enum
{
    RES_OK = 0,		/* 0: Function succeeded */
    RES_ERROR,		/* 1: Disk error */
    RES_NOTRDY,		/* 2: Not ready */
    RES_PARERR		/* 3: Invalid parameter */
} DRESULT;

#endif
/*---------------------------------------*/
/* Prototypes for disk control functions */

#define STA_NOINIT		0x01	/* Drive not initialized */
#define STA_NODISK		0x02	/* No medium in the drive */

#define _DISKIO
#endif
