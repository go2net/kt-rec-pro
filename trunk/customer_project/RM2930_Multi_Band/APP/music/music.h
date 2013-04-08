/*--------------------------------------------------------------------------*/
/**@file   music.h
   @brief  music头文件
   @details
   @author
   @date   2011-5-18
   @note
*/
/*----------------------------------------------------------------------------*/
#ifndef _MUSIC_H_
#define _MUSIC_H_

#include "config.h"
#include "tff.h"
#include "iic.h"
#include "disp.h"
#include "key.h"

#ifdef __C51__

enum
{
    REPEAT_ALL = 0,
    REPEAT_FOLDER,
    REPEAT_ONE,
    REPEAT_RANDOM,
    REPEAT_BACK,
    
};


enum
{
    UNKNOW_FORMAT = 0,
    IS_WAV,
    IS_WMA,
    IS_MP3,
    NOT_SUPPORT,
};

enum 							//config command
{
    MAD_STOP = 0,				//播放结停止，解码模块已经被关闭
    MAD_PLAY,					//正在播放中
    MAD_PAUSE,					//播放暂停
    MAD_FAST_FORWARD,
    MAD_FAST_REVERASE,
    MAD_INIT,					//播放初始化
    MAD_FF,
    MAD_FR,
    MAD_STOP_WAIT,				//当前歌曲播放结束，但需要延时一段时间才能停止
    MAD_PLAY_END,				//当前歌曲播放结束或被提前结束，但还未停止解码模块
};

enum							//播放文件的方式定义
{
    PLAY_NEXT_FILE = 0,
    PLAY_AUTO_NEXT,
    PLAY_FIRST_FILE,  		    //从第一个文件播放
    PLAY_BREAK_POINT,           //从记忆文件和位置开始播放
    PLAY_LAST_FILE,				//从最后一个文件播放
    PLAY_PREV_FILE,
    PLAY_SEL_FILE,
};


typedef struct _ID3V2_PARSE
{
    u8 isv34;
    u8 unsync;
    u8 tunsync;
    u8 id3v2_version;
    u8 id2v3_flags;
    u8 taghdrlen;
    u32 id3v2_len;				// ID3 总长度, 但不包帧头和Footer preset
    u32 tlen;					// 当前ID3 frame长度，不包含帧头
} ID3V2_PARSE;

typedef struct _DECODER_MSG
{
    u16 (_code *read_file) (u8 _xdata *buffer, u16 len);
    u8 (_code *seek_file) (u8, u16, u16);
    u8 (_code *file_status) (void);
    u32 (_code *f_tell_fptr)(void);
    u32 (_code *f_tell_fsize)(void);
    void (_code *f_backup)(u8 file_index, FIL_BACKUP _xdata *buf);
    void (_code *f_restore)(u8 file_index, FIL_BACKUP _xdata *buf);
    u8 * eq_table;
    u8 _xdata *buffer;      //解码所使用的buffer
    u16  buffer_len;
    u8  format;             //音频格式：1，2，3：MP3， 8~15：WAV，16~23：WMA
    u32 id1;
    u16 total_time;         //歌曲总时间
    u16 play_time;          //当前播放时间，单位为秒
    u32 bit_rate;           //当前帧的编码率, MP3格式时，需乘2000的系数
    u16 sample_rate;        //当前帧的采样率
    u32 tag_len;
    u32 id2;
    u8  err;
    u8  err_counter;
}DECODER_MSG;

typedef struct _DISK_MUSIC_POINT
{
    u16     id0;		// 文件计数,搜索文件时,可以用它来计算总的文件数
    u32	    id1;			// 当前文件序号
    u32	    id2;			// 文件总数
} DISK_MUSIC_POINT;

DECODER_MSG _xdata * get_dec_msg_ptr(void);
u32 ff_id3v2_frame_len(const u8 _xdata *buf);
bool ff_id3v1_match(u8 _xdata *buf);
bool ff_id3v2_parse(u8 _xdata *buf, ID3V2_PARSE _xdata *id3);
void ff_id3v2_parse_header(u8 _xdata *buf, ID3V2_PARSE _xdata *id3);
bool ff_id3v2_check(u8 _xdata * buf, ID3V2_PARSE _xdata *id3);
void ff_cal_id3v2_tag_len(const u8 _xdata * buf);

///////
void music_decode(void);
void get_mp3_play_time(void);
void backup_music_point(void);
#endif

#define FR_LIMIT_SIZE    50L					//快退支持的最大文件大小,以M为单位
#define FF_FR_STEP			2					//快进快退的步长，每半秒内快进或快退的时间，以秒为单位



#endif