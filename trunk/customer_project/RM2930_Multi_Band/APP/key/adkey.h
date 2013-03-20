/*--------------------------------------------------------------------------*/
/**@file   adkey.h
   @brief  AD按键定义
   @details
   @author
   @date   2010-12-13
   @note
*/
/*----------------------------------------------------------------------------*/
#ifndef	_ADKEY_H_
#define _ADKEY_H_
#include "my_adkey.h"
/************ADKEY GROUP 1****************/
#if 1
#define ADKEY1			(0xf000)
#define ADKEY1_0		(0xf000)
#define ADKEY1_1		(0xf000)
#define ADKEY1_2		0xd400
#define ADKEY1_3		0xb080
#define ADKEY1_4		0x9040
#define ADKEY1_5		0x7000
#define ADKEY1_6		0x4DC0
#define ADKEY1_7		0x2D40
#define ADKEY1_8		(0x1F80)/2
#else
#define ADKEY1			(0xff40-0xe840)/2+0xe840
#define ADKEY1_0		(0xe800-0xd1c0)/2+0xd1c0
#define ADKEY1_1		(0xd140-0xb2c0)/2+0xb2c0
#define ADKEY1_2		(0xb2c0-0x99c0)/2+0x99c0
#define ADKEY1_3		(0x9980-0x85c0)/2+0x85c0
#define ADKEY1_4		(0x8540-0x67c0)/2+0x67c0
#define ADKEY1_5		(0x66c0-0x4ac0)/2+0x4ac0
#define ADKEY1_6		(0x49c0-0x3740)/2+0x3740
#define ADKEY1_7		(0x3700-0x1e80)/2+0x1e80
#define ADKEY1_8		(0x1e40-0x0)/2+0x0
#endif

u16 _code adkey1_check_table[] = {ADKEY1_0, ADKEY1_1, ADKEY1_2, ADKEY1_3, ADKEY1_4, ADKEY1_5, ADKEY1_6, ADKEY1_7, ADKEY1_8,};

//
#define ADKEY1_MUSIC_SHORT		\
                                				/*00*/    MUSIC_ADKEY_SHORT_00,\
							    	/*01*/    MUSIC_ADKEY_SHORT_01,\
								/*02*/    MUSIC_ADKEY_SHORT_02,\
								/*03*/    MUSIC_ADKEY_SHORT_03,\
								/*04*/    MUSIC_ADKEY_SHORT_04,\
								/*05*/    MUSIC_ADKEY_SHORT_05,\
								/*06*/    MUSIC_ADKEY_SHORT_06,\
								/*07*/    MUSIC_ADKEY_SHORT_07,\
								/*08*/    MUSIC_ADKEY_SHORT_08,\
								/*09*/    MUSIC_ADKEY_SHORT_09,

#define ADKEY1_MUSIC_LONG		\
                                				/*00*/    MUSIC_ADKEY_LONG_00,\
                                				/*01*/    MUSIC_ADKEY_LONG_01,\
								/*02*/    MUSIC_ADKEY_LONG_02,\
								/*03*/    MUSIC_ADKEY_LONG_03,\
								/*04*/    MUSIC_ADKEY_LONG_04,\
								/*05*/    MUSIC_ADKEY_LONG_05,\
								/*06*/    MUSIC_ADKEY_LONG_06,\
								/*07*/    MUSIC_ADKEY_LONG_07,\
								/*08*/    MUSIC_ADKEY_LONG_08,\
								/*09*/    MUSIC_ADKEY_LONG_09,


#define ADKEY1_MUSIC_HOLD		\
                                				/*00*/    MUSIC_ADKEY_HOLD_00,\
                                				/*01*/    MUSIC_ADKEY_HOLD_01,\
								/*02*/    MUSIC_ADKEY_HOLD_02,\
								/*03*/    MUSIC_ADKEY_HOLD_03,\
								/*04*/    MUSIC_ADKEY_HOLD_04,\
								/*05*/    MUSIC_ADKEY_HOLD_05,\
								/*06*/    MUSIC_ADKEY_HOLD_06,\
								/*07*/    MUSIC_ADKEY_HOLD_07,\
								/*08*/    MUSIC_ADKEY_HOLD_08,\
								/*09*/    MUSIC_ADKEY_HOLD_09,

#define ADKEY1_MUSIC_LONG_UP	\
                                				/*00*/    MUSIC_ADKEY_L_UP_00,\
                                				/*01*/    MUSIC_ADKEY_L_UP_01,\
								/*02*/    MUSIC_ADKEY_L_UP_02,\
								/*03*/    MUSIC_ADKEY_L_UP_03,\
								/*04*/    MUSIC_ADKEY_L_UP_04,\
								/*05*/    MUSIC_ADKEY_L_UP_05,\
								/*06*/    MUSIC_ADKEY_L_UP_06,\
								/*07*/    MUSIC_ADKEY_L_UP_07,\
								/*08*/    MUSIC_ADKEY_L_UP_08,\
								/*09*/    MUSIC_ADKEY_L_UP_09,

const u8 _code adkey1_msg_music_table[4][10] =				//Music模式下的遥控转换表
{
    /*短按*/	    {ADKEY1_MUSIC_SHORT},
    /*长按*/		{ADKEY1_MUSIC_LONG},
    /*连按*/		{ADKEY1_MUSIC_HOLD},
    /*长按抬起*/	{ADKEY1_MUSIC_LONG_UP},
};

#if 0
//
#define ADKEY1_FM_SHORT			\
								/*00*/    FM_ADKEY_SHORT_00,\
							    	/*01*/    FM_ADKEY_SHORT_01,\
								/*02*/    FM_ADKEY_SHORT_02,\
								/*03*/    FM_ADKEY_SHORT_03,\
								/*04*/    FM_ADKEY_SHORT_04,\
								/*05*/    FM_ADKEY_SHORT_05,\
								/*06*/    FM_ADKEY_SHORT_06,\
								/*07*/    FM_ADKEY_SHORT_07,\
								/*08*/    FM_ADKEY_SHORT_08,\
								/*09*/    FM_ADKEY_SHORT_09,

#define ADKEY1_FM_LONG			\
								/*00*/    FM_ADKEY_LONG_00,\
                               	 			/*01*/    FM_ADKEY_LONG_01,\
								/*02*/    FM_ADKEY_LONG_02,\
								/*03*/    FM_ADKEY_LONG_03,\
								/*04*/    FM_ADKEY_LONG_04,\
								/*05*/    FM_ADKEY_LONG_05,\
								/*06*/    FM_ADKEY_LONG_06,\
								/*07*/    FM_ADKEY_LONG_07,\
								/*08*/    FM_ADKEY_LONG_08,\
								/*09*/    FM_ADKEY_LONG_09,

#define ADKEY1_FM_HOLD			\
								/*00*/    FM_ADKEY_HOLD_00,\
                                				/*01*/    FM_ADKEY_HOLD_01,\
								/*02*/    FM_ADKEY_HOLD_02,\
								/*03*/    FM_ADKEY_HOLD_03,\
								/*04*/    FM_ADKEY_HOLD_04,\
								/*05*/    FM_ADKEY_HOLD_05,\
								/*06*/    FM_ADKEY_HOLD_06,\
								/*07*/    FM_ADKEY_HOLD_07,\
								/*08*/    FM_ADKEY_HOLD_08,\
								/*09*/    FM_ADKEY_HOLD_09,


#define ADKEY1_FM_LONG_UP		\
								/*00*/    FM_ADKEY_L_UP_00,\
                                				/*01*/    FM_ADKEY_L_UP_01,\
								/*02*/    FM_ADKEY_L_UP_02,\
								/*03*/    FM_ADKEY_L_UP_03,\
								/*04*/    FM_ADKEY_L_UP_04,\
								/*05*/    FM_ADKEY_L_UP_05,\
								/*06*/    FM_ADKEY_L_UP_06,\
								/*07*/    FM_ADKEY_L_UP_07,\
								/*08*/    FM_ADKEY_L_UP_08,\
								/*09*/    FM_ADKEY_L_UP_09,

const u8 _code adkey1_msg_fm_table[4][10] =				//Music模式下的遥控转换表
{
    /*短按*/	    {ADKEY1_FM_SHORT},
    /*长按*/		{ADKEY1_FM_LONG},
    /*连按*/		{ADKEY1_FM_HOLD},
    /*长按抬起*/	{ADKEY1_FM_LONG_UP},
};
#endif
#endif


