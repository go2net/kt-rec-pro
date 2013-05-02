/*--------------------------------------------------------------------------*/
/**@file   my_adkey.h
   @brief  AD��������
   @details
   @author
   @date   2010-12-13
   @note
*/
/*----------------------------------------------------------------------------*/
#include "Custom_config.h"

#ifndef	_MY_ADKEY_H_
#define _MY_ADKEY_H_

#if defined(JK_JF_689_MODULE)||defined(JK_JF_933_MODULE)||defined(JK_JF_168_MODULE)
#define MUSIC_ADKEY_SHORT_00		NO_MSG
#define MUSIC_ADKEY_SHORT_01		NO_MSG
#define MUSIC_ADKEY_SHORT_02		MSG_NEXT_PLAYMODE
#define MUSIC_ADKEY_SHORT_03		MSG_REC_KEY
#define MUSIC_ADKEY_SHORT_04		MSG_DEVICE_MODE
#define MUSIC_ADKEY_SHORT_05		MSG_MUSIC_NEXT_EQ
#define MUSIC_ADKEY_SHORT_06		MSG_NEXT_WORKMODE
#define MUSIC_ADKEY_SHORT_07		MSG_MUSIC_NEXT_FILE
#define MUSIC_ADKEY_SHORT_08		MSG_MUSIC_PREV_FILE
#define MUSIC_ADKEY_SHORT_09		MSG_MUSIC_PP

#define MUSIC_ADKEY_LONG_00		NO_MSG
#define MUSIC_ADKEY_LONG_01		NO_MSG
#define MUSIC_ADKEY_LONG_02		NO_MSG
#define MUSIC_ADKEY_LONG_03		MSG_DEL_CURR_FILE
#define MUSIC_ADKEY_LONG_04		NO_MSG
#define MUSIC_ADKEY_LONG_05		NO_MSG
#define MUSIC_ADKEY_LONG_06		MSG_TIME_SETTING
#define MUSIC_ADKEY_LONG_07		MSG_MUSIC_FF_START
#define MUSIC_ADKEY_LONG_08		MSG_MUSIC_FR_START
#define MUSIC_ADKEY_LONG_09		MSG_REC_PLAY


#define MUSIC_ADKEY_HOLD_00		NO_MSG
#define MUSIC_ADKEY_HOLD_01		NO_MSG
#define MUSIC_ADKEY_HOLD_02		NO_MSG
#define MUSIC_ADKEY_HOLD_03		NO_MSG
#define MUSIC_ADKEY_HOLD_04		NO_MSG
#define MUSIC_ADKEY_HOLD_05		NO_MSG
#define MUSIC_ADKEY_HOLD_06		NO_MSG
#define MUSIC_ADKEY_HOLD_07		MSG_MUSIC_FF
#define MUSIC_ADKEY_HOLD_08		MSG_MUSIC_FR
#define MUSIC_ADKEY_HOLD_09		NO_MSG

#define MUSIC_ADKEY_L_UP_00		NO_MSG
#define MUSIC_ADKEY_L_UP_01		NO_MSG
#define MUSIC_ADKEY_L_UP_02		NO_MSG
#define MUSIC_ADKEY_L_UP_03		NO_MSG
#define MUSIC_ADKEY_L_UP_04		NO_MSG
#define MUSIC_ADKEY_L_UP_05		NO_MSG
#define MUSIC_ADKEY_L_UP_06		NO_MSG
#define MUSIC_ADKEY_L_UP_07		MSG_MUSIC_FFR_DONE
#define MUSIC_ADKEY_L_UP_08		MSG_MUSIC_FFR_DONE
#define MUSIC_ADKEY_L_UP_09		NO_MSG

#elif defined(JK_FT_770_MODULE)

#define MUSIC_ADKEY_SHORT_00		NO_MSG
#define MUSIC_ADKEY_SHORT_01		NO_MSG
#define MUSIC_ADKEY_SHORT_02		MSG_NEXT_PLAYMODE
#define MUSIC_ADKEY_SHORT_03		MSG_REC_KEY
#define MUSIC_ADKEY_SHORT_04		MSG_REC_PLAY
#define MUSIC_ADKEY_SHORT_05		MSG_MUSIC_NEXT_EQ
#define MUSIC_ADKEY_SHORT_06		MSG_NEXT_WORKMODE
#define MUSIC_ADKEY_SHORT_07		MSG_MUSIC_NEXT_FILE
#define MUSIC_ADKEY_SHORT_08		MSG_MUSIC_PREV_FILE
#define MUSIC_ADKEY_SHORT_09		MSG_MUSIC_PP

#define MUSIC_ADKEY_LONG_00		NO_MSG
#define MUSIC_ADKEY_LONG_01		NO_MSG
#define MUSIC_ADKEY_LONG_02		NO_MSG
#define MUSIC_ADKEY_LONG_03		MSG_DEL_CURR_FILE
#define MUSIC_ADKEY_LONG_04		NO_MSG
#define MUSIC_ADKEY_LONG_05		NO_MSG
#define MUSIC_ADKEY_LONG_06		MSG_TIME_SETTING
#define MUSIC_ADKEY_LONG_07		MSG_MUSIC_FF
#define MUSIC_ADKEY_LONG_08		MSG_MUSIC_FR
#define MUSIC_ADKEY_LONG_09		NO_MSG


#define MUSIC_ADKEY_HOLD_00		NO_MSG
#define MUSIC_ADKEY_HOLD_01		NO_MSG
#define MUSIC_ADKEY_HOLD_02		NO_MSG
#define MUSIC_ADKEY_HOLD_03		NO_MSG
#define MUSIC_ADKEY_HOLD_04		NO_MSG
#define MUSIC_ADKEY_HOLD_05		NO_MSG
#define MUSIC_ADKEY_HOLD_06		NO_MSG
#define MUSIC_ADKEY_HOLD_07		MSG_MUSIC_FF
#define MUSIC_ADKEY_HOLD_08		MSG_MUSIC_FR
#define MUSIC_ADKEY_HOLD_09		NO_MSG

#define MUSIC_ADKEY_L_UP_00		NO_MSG
#define MUSIC_ADKEY_L_UP_01		NO_MSG
#define MUSIC_ADKEY_L_UP_02		NO_MSG
#define MUSIC_ADKEY_L_UP_03		NO_MSG
#define MUSIC_ADKEY_L_UP_04		NO_MSG
#define MUSIC_ADKEY_L_UP_05		NO_MSG
#define MUSIC_ADKEY_L_UP_06		NO_MSG
#define MUSIC_ADKEY_L_UP_07		MSG_MUSIC_FFR_DONE
#define MUSIC_ADKEY_L_UP_08		MSG_MUSIC_FFR_DONE
#define MUSIC_ADKEY_L_UP_09		NO_MSG
#elif defined(JK_FT_780_MODULE)

#define MUSIC_ADKEY_SHORT_00		NO_MSG
#define MUSIC_ADKEY_SHORT_01		NO_MSG
#define MUSIC_ADKEY_SHORT_02		MSG_NEXT_PLAYMODE
#define MUSIC_ADKEY_SHORT_03		MSG_REC_KEY
#define MUSIC_ADKEY_SHORT_04		MSG_REC_PLAY
#define MUSIC_ADKEY_SHORT_05		MSG_MUSIC_NEXT_EQ
#define MUSIC_ADKEY_SHORT_06		MSG_NEXT_WORKMODE
#define MUSIC_ADKEY_SHORT_07		MSG_MUSIC_NEXT_FILE
#define MUSIC_ADKEY_SHORT_08		MSG_MUSIC_PREV_FILE
#define MUSIC_ADKEY_SHORT_09		MSG_MUSIC_PP

#define MUSIC_ADKEY_LONG_00		NO_MSG
#define MUSIC_ADKEY_LONG_01		NO_MSG
#define MUSIC_ADKEY_LONG_02		NO_MSG
#define MUSIC_ADKEY_LONG_03		MSG_DEL_CURR_FILE
#define MUSIC_ADKEY_LONG_04		NO_MSG
#define MUSIC_ADKEY_LONG_05		NO_MSG
#define MUSIC_ADKEY_LONG_06		MSG_TIME_SETTING
#define MUSIC_ADKEY_LONG_07		MSG_MUSIC_FF
#define MUSIC_ADKEY_LONG_08		MSG_MUSIC_FR
#define MUSIC_ADKEY_LONG_09		NO_MSG


#define MUSIC_ADKEY_HOLD_00		NO_MSG
#define MUSIC_ADKEY_HOLD_01		NO_MSG
#define MUSIC_ADKEY_HOLD_02		NO_MSG
#define MUSIC_ADKEY_HOLD_03		NO_MSG
#define MUSIC_ADKEY_HOLD_04		NO_MSG
#define MUSIC_ADKEY_HOLD_05		NO_MSG
#define MUSIC_ADKEY_HOLD_06		NO_MSG
#define MUSIC_ADKEY_HOLD_07		MSG_MUSIC_FF
#define MUSIC_ADKEY_HOLD_08		MSG_MUSIC_FR
#define MUSIC_ADKEY_HOLD_09		NO_MSG

#define MUSIC_ADKEY_L_UP_00		NO_MSG
#define MUSIC_ADKEY_L_UP_01		NO_MSG
#define MUSIC_ADKEY_L_UP_02		NO_MSG
#define MUSIC_ADKEY_L_UP_03		NO_MSG
#define MUSIC_ADKEY_L_UP_04		NO_MSG
#define MUSIC_ADKEY_L_UP_05		NO_MSG
#define MUSIC_ADKEY_L_UP_06		NO_MSG
#define MUSIC_ADKEY_L_UP_07		MSG_MUSIC_FFR_DONE
#define MUSIC_ADKEY_L_UP_08		MSG_MUSIC_FFR_DONE
#define MUSIC_ADKEY_L_UP_09		NO_MSG

#else
#define MUSIC_ADKEY_SHORT_00		MSG_VOL_UP
#define MUSIC_ADKEY_SHORT_01		MSG_VOL_DOWN
#define MUSIC_ADKEY_SHORT_02		NO_MSG
#define MUSIC_ADKEY_SHORT_03		MSG_REC_KEY
#define MUSIC_ADKEY_SHORT_04		MSG_REC_PLAY
#define MUSIC_ADKEY_SHORT_05		MSG_MUSIC_NEXT_EQ
#define MUSIC_ADKEY_SHORT_06		MSG_NEXT_WORKMODE
#define MUSIC_ADKEY_SHORT_07		MSG_MUSIC_NEXT_FILE
#define MUSIC_ADKEY_SHORT_08		MSG_MUSIC_PREV_FILE
#define MUSIC_ADKEY_SHORT_09		MSG_MUSIC_PP

#define MUSIC_ADKEY_LONG_00		NO_MSG
#define MUSIC_ADKEY_LONG_01		NO_MSG
#define MUSIC_ADKEY_LONG_02		NO_MSG
#define MUSIC_ADKEY_LONG_03		MSG_DEL_CURR_FILE
#define MUSIC_ADKEY_LONG_04		NO_MSG
#define MUSIC_ADKEY_LONG_05		NO_MSG
#define MUSIC_ADKEY_LONG_06		MSG_TIME_SETTING
#define MUSIC_ADKEY_LONG_07		MSG_MUSIC_FF
#define MUSIC_ADKEY_LONG_08		MSG_MUSIC_FR
#define MUSIC_ADKEY_LONG_09		NO_MSG


#define MUSIC_ADKEY_HOLD_00		MSG_VOL_UP
#define MUSIC_ADKEY_HOLD_01		MSG_VOL_DOWN
#define MUSIC_ADKEY_HOLD_02		NO_MSG
#define MUSIC_ADKEY_HOLD_03		NO_MSG
#define MUSIC_ADKEY_HOLD_04		NO_MSG
#define MUSIC_ADKEY_HOLD_05		NO_MSG
#define MUSIC_ADKEY_HOLD_06		NO_MSG
#define MUSIC_ADKEY_HOLD_07		MSG_MUSIC_FF
#define MUSIC_ADKEY_HOLD_08		MSG_MUSIC_FR
#define MUSIC_ADKEY_HOLD_09		NO_MSG

#define MUSIC_ADKEY_L_UP_00		NO_MSG
#define MUSIC_ADKEY_L_UP_01		NO_MSG
#define MUSIC_ADKEY_L_UP_02		NO_MSG
#define MUSIC_ADKEY_L_UP_03		NO_MSG
#define MUSIC_ADKEY_L_UP_04		NO_MSG
#define MUSIC_ADKEY_L_UP_05		NO_MSG
#define MUSIC_ADKEY_L_UP_06		NO_MSG
#define MUSIC_ADKEY_L_UP_07		MSG_MUSIC_FFR_DONE
#define MUSIC_ADKEY_L_UP_08		MSG_MUSIC_FFR_DONE
#define MUSIC_ADKEY_L_UP_09		NO_MSG
#if 0
//3 FM ADKEY
#define FM_ADKEY_SHORT_00		NO_MSG
#define FM_ADKEY_SHORT_01		NO_MSG
#define FM_ADKEY_SHORT_02		NO_MSG
#define FM_ADKEY_SHORT_03		MSG_REC_KEY
#define FM_ADKEY_SHORT_04		NO_MSG
#define FM_ADKEY_SHORT_05		NO_MSG
#define FM_ADKEY_SHORT_06		NO_MSG
#define FM_ADKEY_SHORT_07		MSG_FM_NEXT_STEP
#define FM_ADKEY_SHORT_08		MSG_FM_PREV_STEP
#define FM_ADKEY_SHORT_09		NO_MSG

#define FM_ADKEY_LONG_00		NO_MSG
#define FM_ADKEY_LONG_01		NO_MSG
#define FM_ADKEY_LONG_02		NO_MSG
#define FM_ADKEY_LONG_03		NO_MSG
#define FM_ADKEY_LONG_04		NO_MSG
#define FM_ADKEY_LONG_05		NO_MSG
#define FM_ADKEY_LONG_06		NO_MSG	
#define FM_ADKEY_LONG_07		NO_MSG
#define FM_ADKEY_LONG_08		NO_MSG
#define FM_ADKEY_LONG_09		NO_MSG	

#define FM_ADKEY_HOLD_00		NO_MSG
#define FM_ADKEY_HOLD_01		NO_MSG
#define FM_ADKEY_HOLD_02		NO_MSG
#define FM_ADKEY_HOLD_03		NO_MSG
#define FM_ADKEY_HOLD_04		NO_MSG
#define FM_ADKEY_HOLD_05		NO_MSG
#define FM_ADKEY_HOLD_06		NO_MSG
#define FM_ADKEY_HOLD_07		NO_MSG
#define FM_ADKEY_HOLD_08		NO_MSG
#define FM_ADKEY_HOLD_09		NO_MSG

#define FM_ADKEY_L_UP_00		NO_MSG
#define FM_ADKEY_L_UP_01		NO_MSG	
#define FM_ADKEY_L_UP_02		NO_MSG
#define FM_ADKEY_L_UP_03		NO_MSG
#define FM_ADKEY_L_UP_04		NO_MSG
#define FM_ADKEY_L_UP_05		NO_MSG
#define FM_ADKEY_L_UP_06		NO_MSG
#define FM_ADKEY_L_UP_07		NO_MSG
#define FM_ADKEY_L_UP_08		NO_MSG
#define FM_ADKEY_L_UP_09		NO_MSG

#endif
#endif



#endif

