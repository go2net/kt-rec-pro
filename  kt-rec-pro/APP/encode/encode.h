#ifndef _ENCODE_H_
#define _ENCODE_H_

#include "config.h"



#ifdef __C51__


enum
{
    RECODE_STOP  = 0,    ///<未录音状态
    RECODE_PLAY,         ///<播放录音文件状态
    RECODE_INIT,         ///<录音初始化
    RECODE_WORKING,	     ///<正在录音
    RECODE_PAUSE,        ///<录音暂停
};

typedef struct _FSAPIMSGREC
{
	u16  firstfilenum ;      //录音目录下面文件开始序号；
	u16  fileTotalInDir ;     //录音目录下面文件数目；
}FSAPIMSGREC;

extern u8 _xdata encode_status;
extern u8 _xdata encode_channel;
extern u8 _xdata encode_vol;
extern u8 _xdata encode_device;
extern FSAPIMSGREC _pdata fs_msg_rec;

extern u16 _xdata encode_fristfile;
extern u16 _xdata encode_filenum;
extern u16 _xdata logic_fileTotal;

extern u8 encode_cnt;
extern u8 mem_addr;

extern u8 play_mode_rec;

#define TRACK_ALL    0 
#define TRACK_RIGHT  1 
#define TRACK_LEFT   2

#define REC_FM     		0x00 
#define REC_LINEIN 		0x01
#define REC_MIC			0x02 

#define ENABLE_REC_DATA 0x81
#define REC_NO_OPT      0x80

#define ENABLE_REC_BIT  BIT(7)
#define FRIST_ADC_PACKET  BIT(3)

extern void break_encode(void);
extern void rec_mic_fun(void);
extern void get_rec_mem_info(void);
extern  u16 filenum_phy_logic(u16 filenumber);
extern u16 filenum_logic_phy(u16 filenumber);
extern void init_rec_name(void);
extern void api_stop_encode(void);
#endif

#endif



