/*--------------------------------------------------------------------------*/
/**@file   get_music_file.h
   @brief  获取文件头文件
   @details
   @author
   @date   2011-9-8
   @note
*/
/*----------------------------------------------------------------------------*/

#ifndef  _MSGFOR_MP3_
#define  _MSGFOR_MP3_

#ifdef __C51__
#include "config.h"

enum
{
    GET_FILE_OK = 0,			        //找到文件序号
    GET_DEVICE_END,						//已经播放到设备结束
    GET_DEVICE_HEAD						//已经播放到设备开头
};

u8 fs_get_filenum(u8 playmode, u8 searchMode);
#endif

#define GET_NEXT_FILE       0
#define GET_PREV_FILE       1
#define GET_PLAY_FILE       2


#endif