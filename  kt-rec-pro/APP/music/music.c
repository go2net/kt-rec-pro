/*--------------------------------------------------------------------------*/
/**@file   music.h
   @brief  music头文件
   @details
   @author
   @date   2011-5-18
   @note
*/
/*----------------------------------------------------------------------------*/
#include "config.h"

#include "music.h"
#include "msgfor_hot.h"
#include "device.h"
#include "dsp.h"
#include "id3.h"
#include "eq.h"
#include "get_music_file.h"
#include "main.h"
#include "dac.h"
#include "rtc_api.h"

extern bool input_number_en;
extern u8  main_menu, cur_menu, main_menu_conter;
extern u16 input_number;
extern u8 device_active;

extern u8 work_mode;
extern u8 bright_counter;
extern bool vol_change_en;

#ifdef AUTO_PLAY_RADIO_REC_FILE
extern bool auto_play_radio_rec;
#endif

//extern bool key_voice_en;
//extern u8 _idata last_work_mode;
u8 play_mode;							 ///<循环模式
//u8 play_mode_rec;							 ///<循环模式
u8 given_device;						 ///<需要查找的设备
u16 given_file_number;					 ///<需要查找的文件号
u16 break_point_filenum;				 ///<断点信息对应的文件号
u8 play_status;							///<播放状态
u8 play_delay_time;

u8 eq_mode=0;				  ///<EQ模式
u8 music_type;			  ///<音乐文件的格式
u8 given_file_method;	  ///<获取文件的方式
//u8 _pdata music_spec[9] _at_ 0x02;	 ///<频谱BUFF

//u8 _xdata decode_buffer[1024*2] _at_ 0x2880;	 ///<解码BUFF
//u8 _xdata win_buffer[512] _at_ 0x700;			 ///<文件系统缓存BUFF

//u8 _xdata decode_buffer[0x2580] _at_ 0x700;      ///<解码BUFF

u8 _xdata decode_buffer[1024*2] _at_ 0x2880;	 ///<解码BUFF
u8 _xdata buff_for_usb[64] _at_ 0x6c0;
u8 _xdata encode_buffer[0x2580] _at_ 0x700;      ///<解码BUFF

u8 _xdata win_buffer[512] _at_ 0x4C0;            ///<文件系统缓存BUFF

FSAPIMSG _pdata fs_msg _at_ 0x40;				 ///<文件系统相关消息

FSAPIMSGREC _pdata fs_msg_rec _at_ 0x40 + sizeof(FSAPIMSG) ;
DECODER_MSG _xdata *dec_msg;					 ///<解码相关的消息
FIL xdata fat_ptr1;								 ///<文件在文件系统中的相关消息
bool find_break_point_file_flag;			///<是否找到可以断点续播的文件
#if 0
#if VIRTUAL_ENABLE
DISK_MUSIC_POINT _idata	disk_mus_point[4];	   ///<音乐文件断点记忆的变量
#else
DISK_MUSIC_POINT _idata	disk_mus_point[2];	   ///<音乐文件断点记忆的变量
#endif
#else
//xd_u16 sd_music_bp=0,usb_music_bp=0;
#endif
extern void rtc_disp_hdlr(void);
extern u8 ldoin_voltage(void);
extern u8 _xdata adc_vdd12;
extern u8 _xdata adc_vddio;

extern u16 _idata adkey_value1;
extern u16 _idata user_code;
//extern u8 _pdata music_spec[9];
extern u8 _bdata device_online;
extern xd_u8 disp_scenario,rtc_setting_flag;
extern bool rec_pley_bp_flag;
/** 存放ID3V2信息的结构体变量 */
ID3V2_PARSE _xdata s_id3v2; 
/*----------------------------------------------------------------------------*/
/**@brief  跳过ID3信息获取阶段
   @param  无
   @return  无
   @note  void skip_music_tag(void)
*/
/*----------------------------------------------------------------------------*/
void skip_music_tag(void)
{

    f_seek(SEEK_SET, dec_msg->tag_len, dec_msg->tag_len >> 16);
    my_memset((u8 _xdata *)&s_id3v2, 0, sizeof(ID3V2_PARSE));
    while (ff_id3v2_check(decode_buffer, &s_id3v2)) //检测获取ID3头的头信息
    {
        ff_cal_id3v2_tag_len(decode_buffer);
        while (ff_id3v2_parse(decode_buffer, &s_id3v2))
        {
            f_seek(SEEK_CUR, s_id3v2.tlen,(s_id3v2.tlen ) >> 16);
        }
    }
    fat_ptr1.flag = 0; 
}
/*----------------------------------------------------------------------------*/
/**@brief MUSIC解码初始化
   @param 无
   @return  无
   @note void decode_init(void)
*/
/*----------------------------------------------------------------------------*/
static void decode_init(void)
{
    file_io_init();
    dec_msg->buffer = decode_buffer;
    dec_msg->buffer_len = 2048;
}
/*----------------------------------------------------------------------------*/
/**@brief MUSIC模式信息初始化
   @param 无
   @return  无
   @note void music_info_init(void)
*/
/*----------------------------------------------------------------------------*/
static void music_info_init(void)
{
    device_active = NO_DEVICE;
    if (given_device == NO_DEVICE)
    {
        given_device = read_info(MEM_ACTIVE_DEV);
    }

    if ( (given_device & (~VIRTUAL_DEVICE)) == DEVICE_SDMMC0)
    {
        given_file_method = PLAY_BREAK_POINT;
    }
    else if ((given_device & (~VIRTUAL_DEVICE)) == DEVICE_UDISK)
    {
        given_file_method = PLAY_BREAK_POINT;
    }
    else
    {
    	//delay_10ms(20);
    	if((get_device_online_status()&0x02)>0){
	        given_device = DEVICE_UDISK;
    	}
	else{
	        given_device = DEVICE_SDMMC0;

	}
        given_file_method = PLAY_FIRST_FILE;
    }

    put_msg_lifo(MSG_MUSIC_SELECT_NEW_DEVICE);

}
#if 0//USE_RTC_RAM
/*----------------------------------------------------------------------------*/
/**@brief MUSIC断点信息写入rtcram中
   @param 无
   @return  无
   @note void backup_mp_by_rtcram(void)
*/
/*----------------------------------------------------------------------------*/
void backup_music_point_to_rtcram(void)
{
    u8 i;
#if VIRTUAL_ENABLE
    if((VIRTUAL_DEVICE) & device_active)
    {
        if (DEVICE_SDMMC0 == ((~VIRTUAL_DEVICE) & device_active))
        {
            for (i = 2;i<10;i++)
            {
                write_rtc_ram(MEM_SD_PLAYPOINT_ID0+i,((u8 *)(&(disk_mus_point[0].id0)))[i]);
            }
        }
        if (DEVICE_UDISK == ((~VIRTUAL_DEVICE) & device_active))
        {
            for (i = 2;i<10;i++)
            {
                write_rtc_ram(MEM_USB_PLAYPOINT_ID0+i,((u8 *)(&(disk_mus_point[1].id0)))[i]);
            }
        }
    }
    else 
#endif
    if (DEVICE_SDMMC0 == device_active)
    {
        for (i = 2;i<10;i++)
        {
            write_rtc_ram(MEM_SD_PLAYPOINT_ID0+i,((u8 *)(&(disk_mus_point[0].id0)))[i]);
        }
    }
    if (DEVICE_UDISK == device_active)
    {
        for (i = 2;i<10;i++)
        {
            write_rtc_ram(MEM_USB_PLAYPOINT_ID0+i,((u8 *)(&(disk_mus_point[1].id0)))[i]);
        }
    }


}
//#else
/*----------------------------------------------------------------------------*/
/**@brief MUSIC断点信息写入EEPR0M中
   @param 无
   @return  无
   @note void backup_mp_by_eeprom(void)
*/
/*----------------------------------------------------------------------------*/
void backup_music_point_to_eeprom(void)
{
    u8 cnt,i;
    get_rec_mem_info();
    eeprom_page_write_start();
    if ((device_active & (~VIRTUAL_DEVICE)) == DEVICE_SDMMC0)
    {
        cnt = 0 + encode_cnt;
        iic_sendbyte(MEM_SD_PLAYPOINT_ID1 + mem_addr);
    }
    else if ((device_active & (~VIRTUAL_DEVICE)) == DEVICE_UDISK)
    {
        cnt = 1 + encode_cnt;
        iic_sendbyte(MEM_USB_PLAYPOINT_ID1 + mem_addr);
    }
    for ( i = 0;i<8;i++)
    {
        iic_sendbyte(((u8 *)(&(disk_mus_point[cnt].id1)))[i]);
    }
    eeprom_page_write_stop();
}
#endif
/*----------------------------------------------------------------------------*/
/**@brief MUSIC断点信息写入EEPROM中
   @param 无
   @return  无
   @note void backup_music_point(void)
*/
/*----------------------------------------------------------------------------*/
#if (BREAK_POINT_PLAY_EN == 1)
void backup_music_point(void)
{

    u16 reg_id=0;
    if ((play_status != MAD_PLAY) && (play_status != MAD_PAUSE))				//当前没有处于播放或暂停状态,不保存断点
    {
        return;
    }

    if ((device_active & (~VIRTUAL_DEVICE))== DEVICE_SDMMC0)
    {
		reg_id =(u16)(dec_msg->id1);
		write_info(MEM_SD_PLAYPOINT_ID1, (u8)(reg_id&(0x00FF)));
		write_info(MEM_SD_PLAYPOINT_ID1+1, (u8)((reg_id>>8)&(0x00FF)));
		reg_id =(u16)(dec_msg->id1>>16);
		write_info(MEM_SD_PLAYPOINT_ID1+2, (u8)(reg_id&(0x00FF)));
		write_info(MEM_SD_PLAYPOINT_ID1+3, (u8)((reg_id>>8)&(0x00FF)));

		reg_id =(u16)(dec_msg->id2);
		write_info(MEM_SD_PLAYPOINT_ID2, (u8)(reg_id&(0x00FF)));
		write_info(MEM_SD_PLAYPOINT_ID2+1, (u8)((reg_id>>8)&(0x00FF)));
		reg_id =(u16)(dec_msg->id2>>16);
		write_info(MEM_SD_PLAYPOINT_ID2+2, (u8)(reg_id&(0x00FF)));
		write_info(MEM_SD_PLAYPOINT_ID2+3, (u8)((reg_id>>8)&(0x00FF)));
		
    }
    else if ((device_active  & (~VIRTUAL_DEVICE)) == DEVICE_UDISK)
    {
		reg_id =(u16)(dec_msg->id1);
		write_info(MEM_USB_PLAYPOINT_ID1, (u8)(reg_id&(0x00FF)));
		write_info(MEM_USB_PLAYPOINT_ID1+1, (u8)((reg_id>>8)&(0x00FF)));
		reg_id =(u16)(dec_msg->id1>>16);
		write_info(MEM_USB_PLAYPOINT_ID1+2, (u8)(reg_id&(0x00FF)));
		write_info(MEM_USB_PLAYPOINT_ID1+3, (u8)((reg_id>>8)&(0x00FF)));
    
		reg_id =(u16)(dec_msg->id2);
		write_info(MEM_USB_PLAYPOINT_ID2, (u8)(reg_id&(0x00FF)));
		write_info(MEM_USB_PLAYPOINT_ID2+1, (u8)((reg_id>>8)&(0x00FF)));
		reg_id =(u16)(dec_msg->id2>>16);
		write_info(MEM_USB_PLAYPOINT_ID2+2, (u8)(reg_id&(0x00FF)));
		write_info(MEM_USB_PLAYPOINT_ID2+3, (u8)((reg_id>>8)&(0x00FF)));
    }
}
#endif

/*----------------------------------------------------------------------------*/
/**@brief 保存MUSIC断点信息
   @param 无
   @return  无
   @note void save_music_point(void)
*/
/*----------------------------------------------------------------------------
void save_music_point(void)
{
    if ((play_status != MAD_PLAY) && (play_status != MAD_PAUSE))				//当前没有处于播放或暂停状态,不保存断点
    {
        return;
    }

}*/
/*----------------------------------------------------------------------------*/
/**@brief 加载MUSIC断点信息
   @param 无
   @return  0：不存在有效地断点；1：存在有效地断点
   @note static bool load_music_point(void)
*/
/*----------------------------------------------------------------------------*/
#if (BREAK_POINT_PLAY_EN == 1)
static bool load_music_point(void)
{
    //get_rec_mem_info();
	u16 reg_id=0;
    if ((device_active & (~VIRTUAL_DEVICE)) == DEVICE_SDMMC0)
    {
		reg_id = read_info(MEM_SD_PLAYPOINT_ID1+3);
		reg_id=reg_id<<8;
		reg_id |= read_info(MEM_SD_PLAYPOINT_ID1+2); 
	
		dec_msg->id1=reg_id;
		dec_msg->id1=(dec_msg->id1<<16);

		reg_id = read_info(MEM_SD_PLAYPOINT_ID1+1);
		reg_id=reg_id<<8;
		reg_id |= read_info(MEM_SD_PLAYPOINT_ID1+0); 
	
		dec_msg->id1|=reg_id;


	 if (!dec_msg->id1)
        {
            return 0;
        }
		reg_id = read_info(MEM_SD_PLAYPOINT_ID2+3);
		reg_id=reg_id<<8;
		reg_id |= read_info(MEM_SD_PLAYPOINT_ID2+2); 
	
		dec_msg->id2=reg_id;
		dec_msg->id2=(dec_msg->id2<<16);

		reg_id = read_info(MEM_SD_PLAYPOINT_ID2+1);
		reg_id=reg_id<<8;
		reg_id |= read_info(MEM_SD_PLAYPOINT_ID2+0); 
	
		dec_msg->id2|=reg_id;
        //dec_msg->id1 = disk_mus_point[0 + encode_cnt].id1;
        //dec_msg->id2 = disk_mus_point[0 + encode_cnt].id2;
    }
    else if ((device_active & (~VIRTUAL_DEVICE)) == DEVICE_UDISK)
    {

		reg_id = read_info(MEM_USB_PLAYPOINT_ID1+3);
		reg_id=reg_id<<8;
		reg_id |= read_info(MEM_USB_PLAYPOINT_ID1+2); 
	
		dec_msg->id1=reg_id;
		dec_msg->id1=(dec_msg->id1<<16);

		reg_id = read_info(MEM_USB_PLAYPOINT_ID1+1);
		reg_id=reg_id<<8;
		reg_id |= read_info(MEM_USB_PLAYPOINT_ID1+0); 
	
		dec_msg->id1|=reg_id;


		 if (!dec_msg->id1)
	        {
	            return 0;
	        }
		reg_id = read_info(MEM_USB_PLAYPOINT_ID2+3);
		reg_id=reg_id<<8;
		reg_id |= read_info(MEM_USB_PLAYPOINT_ID2+2); 
	
		dec_msg->id2=reg_id;
		dec_msg->id2=(dec_msg->id2<<16);

		reg_id = read_info(MEM_USB_PLAYPOINT_ID2+1);
		reg_id=reg_id<<8;
		reg_id |= read_info(MEM_USB_PLAYPOINT_ID2+0); 
	
		dec_msg->id2|=reg_id;    
        //if (!disk_mus_point[1 + encode_cnt].id1)
        //{
        //    return 0;
        //}
        //dec_msg->id1 = disk_mus_point[1 + encode_cnt].id1;
        //dec_msg->id2 = disk_mus_point[1 + encode_cnt].id2;
    }
    return 1;
}
#endif
/*----------------------------------------------------------------------------*/
/**@brief 从EEPROM中读出断点信息，并初始化解码变量
   @param 无
   @return  无
   @note void music_info_init(void)
*/
/*----------------------------------------------------------------------------*/
#if 0
void restore_music_point(void)
{
#if 1
{
        //((u8 *)sd_music_bp)[0] = read_info(MEM_SD_PLAYPOINT_ID0);
        //((u8 *)sd_music_bp)[1] = read_info(MEM_SD_PLAYPOINT_ID0+1);
        //((u8 *)usb_music_bp)[0] = read_info(MEM_USB_PLAYPOINT_ID0);
        //((u8 *)usb_music_bp)[1] = read_info(MEM_USB_PLAYPOINT_ID0+1);
#if 0//VIRTUAL_ENABLE
        ((u8 *)(&(disk_mus_point[2].id0)))[i] = read_info(MEM_REC_SD_PLAYPOINT_ID0+i);
        ((u8 *)(&(disk_mus_point[3].id0)))[i] = read_info(MEM_REC_USB_PLAYPOINT_ID0+i);
#endif
    }
#else
    u8 i;
    for (i = 0;i<10;i++)
    {
        ((u8 *)(&(disk_mus_point[0].id0)))[i] = read_info(MEM_SD_PLAYPOINT_ID0+i);
        ((u8 *)(&(disk_mus_point[1].id0)))[i] = read_info(MEM_USB_PLAYPOINT_ID0+i);
#if VIRTUAL_ENABLE
        ((u8 *)(&(disk_mus_point[2].id0)))[i] = read_info(MEM_REC_SD_PLAYPOINT_ID0+i);
        ((u8 *)(&(disk_mus_point[3].id0)))[i] = read_info(MEM_REC_USB_PLAYPOINT_ID0+i);
#endif
    }
#endif

}
#endif
/*----------------------------------------------------------------------------*/
/**@brief   停止解码
   @param   无
   @return  无
   @note   stop_decode
*/
/*----------------------------------------------------------------------------*/
void stop_decode(void)
{
    	//if(MAD_STOP == play_status)
    	//{
        	//return;
    	//}
    	play_status = MAD_STOP;						   
	if(MUSIC_MODE == work_mode)
	{
#if (1 == MUSIC_FADE_OUT_EN)
        	main_vol_set(0, CHANGE_VOL_NO_MEM | CHANGE_VOL_PEND);
#endif	
	}

    	mad_control(MAD_STOP, 0);
    	decode_init();									//解码初始化，会将解码的变量及状态清零
}


/*----------------------------------------------------------------------------*/
/**@brief  开始解码
   @param  无
   @return 无
   @note   start_decode
*/
/*----------------------------------------------------------------------------*/
static u8 start_decode(void)
{

    mad_control(MAD_STOP, 0);
    decode_init();									//解码初始化，会将解码的变量及状态清零
    music_type = music_format_check(decode_buffer);	//检查文件格式

    if (music_type == NOT_SUPPORT)					//不支持的格式
    {
        return 1;
    }
    else if (music_type == IS_MP3)					//MP3
    {
	 skip_music_tag();
        if (!get_mp3_total_time())
            return 1;
    }

        

    if (dec_msg->total_time == 0)					//总播放时间为0，则不进行播放，如果遇到因为添加了此判断而不能播放的文件，则可去掉此条件
    {
        return 1;
    }

    set_eq(eq_mode);

#if (BREAK_POINT_PLAY_EN == 1)
    if (find_break_point_file_flag) 								//取保存过的断点信息
    {
        find_break_point_file_flag = load_music_point();
    }
#endif
    dsp_set_dcc_flt(14);
    dsp_set_ch_mode(0);  
    dsp_set_rinv_mode(0);
    mad_control(MAD_INIT, 0);
    mad_control(MAD_PLAY, 0);
    play_status = MAD_PLAY;
	
#ifdef PLAY_STATUS_LED_FUNC
	set_play_status_led_spark(PLED_SPARK_NOR);
#endif	
    //flashled(2);
    //amp_mute(0);	
    return 0;
}
/*----------------------------------------------------------------------------*/
/**@brief  设备拔出时MUSIC任务的处理
   @param  无
   @return 无
   @note   void disk_remove_deal_for_music(void)
*/
/*----------------------------------------------------------------------------*/
void disk_remove_deal_for_music(void)
{
    if ( (device_check() == 0))//当前播放设备已经不在线,则自动选取下一个设备
    {
        given_device = DEVICE_AUTO_NEXT;
        given_file_method = PLAY_BREAK_POINT;

        put_msg_lifo(MSG_MUSIC_SELECT_NEW_DEVICE);

#if (BREAK_POINT_PLAY_EN == 1)
        if((play_status == MAD_PAUSE) || (play_status == MAD_PLAY) )
        	backup_music_point();								//记录断点信息
#endif        	
    }
}

/*----------------------------------------------------------------------------*/
/**@brief  MUSIC模式主循环
   @param  无
   @return 无
   @note   void music_play(void)
*/
/*----------------------------------------------------------------------------*/
void music_play(void)
{
    u8 key;
    u8 res;

    clear_all_event();

#ifdef AUTO_PLAY_RADIO_REC_FILE
	if(auto_play_radio_rec){
		
#ifdef REC_PLAY_KEY_BREAK_POINT
		rec_pley_bp_flag=0;
#endif		
		auto_play_radio_rec=0;
		put_msg_lifo(MSG_REC_PLAY);
	}
#endif
	
    while (1)
    {
#if (FF_FR_MUSIC == 0)
        if (play_status == MAD_PLAY)
        {
            dac_out_select(DAC_MUSIC, 0);
        }
#else
        if ((play_status == MAD_PLAY) || (play_status == MAD_FF) || (play_status == MAD_FR))
        {
            dac_out_select(DAC_MUSIC, 0);
        }
#endif
        //suspend_sdmmc();						//可减少SDMMC功耗，但会增加电源波动
        key = app_get_msg();


        switch (key)
        {
    
        case MSG_CHANGE_WORK_MODE:
	     rtc_setting_flag=0;
#if (BREAK_POINT_PLAY_EN == 1)	 
            backup_music_point();
#endif
            return;

        case MSG_MUSIC_NEW_DEVICE_IN:							//有新设备接入
#if (BREAK_POINT_PLAY_EN == 1)       
            backup_music_point();
#endif            
            put_msg_lifo(MSG_MUSIC_SELECT_NEW_DEVICE);
            break;

        case MSG_MUSIC_SELECT_NEW_FILE:

            if (device_check() == 0)                                //当前播放设备已经不在线,则自动选取下一个设备
            {
                given_device = DEVICE_AUTO_NEXT;
                put_msg_lifo(MSG_MUSIC_SELECT_NEW_DEVICE);
                break;
            }

            res = fs_get_filenum(play_mode, given_file_method);

            if (res == GET_DEVICE_END)								//下一曲到设备的结束，查找下一个设备的第一首
            {
                	given_file_method = PLAY_FIRST_FILE;
                	given_device = DEVICE_AUTO_NEXT;
                	put_msg_lifo(MSG_MUSIC_SELECT_NEW_DEVICE);
                	break;
            }
            else if (res == GET_DEVICE_HEAD)								//上一曲到设备的结束，查找下一个设备的最后一首
            {
                	given_file_method = PLAY_LAST_FILE;
                	given_device = DEVICE_AUTO_PREV;
                	put_msg_lifo(MSG_MUSIC_SELECT_NEW_DEVICE);
                	break;
            }
            put_msg_lifo(MSG_MUSIC_PLAY_NEW_FILE);
            break;

        case MSG_MUSIC_PLAY_NEW_FILE:									//按文件序号选择文件进行播放
            flush_all_msg();
            stop_decode();

            res = fs_getfile_bynumber(0, &fat_ptr1, given_file_number);

	    if(disp_scenario == DISP_NORMAL)
	            disp_port(MENU_FILENUM);   
		
            if (res == 0)
            {
//                if (given_file_method == PLAY_BREAK_POINT)
//                    res = start_decode();
//                else
                    res = start_decode();
            }

            if (res != 0)                                       //播放不成功
            {
                play_status = MAD_STOP_WAIT;
                play_delay_time = 0;
                if (given_file_method <= PLAY_BREAK_POINT) 		//重新找下一首
                {
                    given_file_method = PLAY_NEXT_FILE;
                    break;
                }
                else											//重新找上一首
                {
                    given_file_method = PLAY_PREV_FILE;
                    break;
                }
            }
            main_menu = MENU_MUSIC_MAIN;
            write_file_info(0xff);
            break;

        case MSG_DECODE_FILE_END:
            if ((dec_msg->play_time >= 5) || (play_status == MAD_FF) || (play_status == MAD_FR))     //当前歌曲的播放时间大于5S时，直接播放下一首
            {
                	given_file_method = PLAY_AUTO_NEXT;
                	put_msg_lifo(MSG_MUSIC_SELECT_NEW_FILE);
            }
            else													//当前歌曲播放时间小于5S，有可能是不坏歌曲，等待一段时间
            {
                	play_delay_time = 0;
                	given_file_method = PLAY_AUTO_NEXT;
                	play_status = MAD_STOP_WAIT;
            }
#ifdef REC_PLAY_KEY_BREAK_POINT
		rec_pley_bp_flag=0;
#endif		
            break;

        case MSG_MUSIC_PREV_FILE:												//选择上一个文件进行播放

	     if((disp_scenario == DISP_RTC_SCEN)&&(rtc_setting_flag!=0)){
			goto __HOT_MSG_HDLR;
			break;
	     }
		 
            given_file_method = PLAY_PREV_FILE;
            put_msg_lifo(MSG_MUSIC_SELECT_NEW_FILE);
            break;

        case MSG_MUSIC_NEXT_FILE:												//选择下一个文件进行播放

	     if((disp_scenario == DISP_RTC_SCEN)&&(rtc_setting_flag!=0)){
			goto __HOT_MSG_HDLR;
			break;
	     }		
            //delay_10ms(30);
            given_file_method = PLAY_NEXT_FILE;
            put_msg_lifo(MSG_MUSIC_SELECT_NEW_FILE);
            break;

        case MSG_MUSIC_PP:											//暂停和播放

            if (cur_menu == MENU_INPUT_NUMBER)			            //数字输入模式
            {
                put_msg_lifo(MSG_PICH_SONG);
                break;
            }

            if (play_status == MAD_PLAY)
            {
                main_menu = MENU_PAUSE;
                disp_port(MENU_PAUSE);
                mad_control(MAD_PAUSE, 0);
                play_status = MAD_PAUSE;
#ifdef PLAY_STATUS_LED_FUNC
		 set_play_status_led_spark(PLED_ON);
#endif	
				
            }
            else if (play_status == MAD_PAUSE)
            {
                main_menu = MENU_MUSIC_MAIN;
                disp_port(MENU_MUSIC_MAIN);
                mad_control(MAD_PLAY, 0);
                play_status = MAD_PLAY;		
#ifdef PLAY_STATUS_LED_FUNC
		 set_play_status_led_spark(PLED_SPARK_NOR);
#endif	
				
            }
            flush_all_msg();
            break;

        case MSG_MUSIC_NEXT_EQ:
            if (play_status == MAD_PAUSE)
                break;
            eq_mode++;
            if (eq_mode > CLASSIC)
            {
                eq_mode = NORMAL;
            }
            set_eq(eq_mode);
            disp_port(MENU_SET_EQ);
            break;

#ifdef PLAY_MODE_IN_USE
        case MSG_NEXT_PLAYMODE:
            if (play_status == MAD_PAUSE)
                break;
#if VIRTUAL_ENABLE							       //如果虚拟识别开了，录音文件夹和设备音乐文件的播放模式分开处理
            if(device_active & VIRTUAL_DEVICE)
            {
#ifdef REPEAT_MODE_USE_ONE_ALL
		  if(play_mode_rec == REPEAT_ALL){
		  	
                    play_mode_rec = REPEAT_ONE;
		  }
		  else {
                    play_mode_rec = REPEAT_ALL;

		  }
		  break;
#else            
                play_mode_rec++;
                if (play_mode_rec > REPEAT_BACK)
                {
                    play_mode_rec = REPEAT_ALL;
                }
#endif			
            }
            else
            {
#ifdef REPEAT_MODE_USE_ONE_ALL
		  if(play_mode == REPEAT_ALL){
		  	
                    play_mode = REPEAT_ONE;
		  }
		  else {
                    play_mode = REPEAT_ALL;

		  }
		  break;
#else
		  	
                play_mode++;
                if (play_mode > REPEAT_RANDOM)
                {
                    play_mode = REPEAT_ALL;
                }
#endif				
            }
#else

#ifdef REPEAT_MODE_USE_ONE_ALL
		  if(play_mode == REPEAT_ALL){
		  	
                    play_mode = REPEAT_ONE;
		  }
		  else {
                    play_mode = REPEAT_ALL;

		  }
#else
                play_mode++;
                if (play_mode > REPEAT_RANDOM)
                {
                    play_mode = REPEAT_ALL;
                }
#endif
#endif
            disp_port(MENU_SET_PLAY_MODE);
            break;
#endif

#if (FF_FR_EN == 1)
        case MSG_MUSIC_FR:											//启动快退

	     if((disp_scenario == DISP_RTC_SCEN)&&(rtc_setting_flag!=0)){
			goto __HOT_MSG_HDLR;
			break;
	     }
		 
            if (find_break_point_file_flag)							//如果是记忆播放的歌曲，不能快退
            {
                break;
            }
            if (play_status == MAD_PLAY)
            {
                play_status = MAD_FR;
            }

            break;

        case MSG_MUSIC_FF:											//启动快进

	     if((disp_scenario == DISP_RTC_SCEN)&&(rtc_setting_flag!=0)){
			goto __HOT_MSG_HDLR;
			break;
	     }
		 
            if (play_status == MAD_PLAY)
            {
                play_status = MAD_FF;
            }
            break;

 	 case MSG_KEY_CHANGE:
        case MSG_MUSIC_FFR_DONE:									//快进快退结束，恢复播放
            if (play_status == MAD_FR)
            {
                set_eq(eq_mode);
                flush_all_msg();
#if (FF_FR_MUSIC == 0)

                dac_mute_control(0);
#endif
                play_status = MAD_PLAY;
            }
            else if (play_status == MAD_FF)
            {
                set_eq(eq_mode);
                flush_all_msg();
#if (FF_FR_MUSIC == 0)

                dac_mute_control(0);
#endif
                play_status = MAD_PLAY;
            }

            break;
#endif
        case MSG_PICH_SONG:
            if (cur_menu == MENU_INPUT_NUMBER)			           //数字输入模式
            {
                if ((input_number <= logic_fileTotal) && (input_number != 0))			   //输入数字是否有效  fs_msg.fileTotal
                {
                    given_file_number = input_number;
                    given_file_method = PLAY_FIRST_FILE;
                    given_device = DEVICE_AUTO_NEXT;
                    put_msg_lifo(MSG_MUSIC_PLAY_NEW_FILE);
                }
                else
                    disp_port(MENU_REC_ERR);
            }
            break;

        case MSG_200MS:
////////////////////////////////////////////////////////////
//快进快退实际的操作在这里完成
#if (FF_FR_EN == 1)
            if (play_status == MAD_FF)
            {
#if (FF_FR_MUSIC == 0)							//如果需要在快进快退过程中听到声音，可以不加此行
                dac_mute_control(1);
#endif
                mad_control(MAD_FF, FF_FR_STEP);
                mad_control(MAD_FAST_FORWARD, 0);
#if (FF_FR_MUSIC == 1)

                dac_mute_control(0,1);
#endif
                mad_control(MAD_PLAY, 0);
            }
            else if (play_status == MAD_FR)
            {
#if (FF_FR_MUSIC == 0)
                dac_mute_control(1);							//如果需要在快进快退过程中听到声音，可以不加此行
#endif
                mad_control(MAD_FR, FF_FR_STEP);
                mad_control(MAD_FAST_REVERASE, 0);
#if (FF_FR_MUSIC == 1)
                dac_mute_control(0,1);
#endif
                mad_control(MAD_PLAY, 0);
            }
			
	     if((disp_scenario ==  DISP_NORMAL)&&(play_status == MAD_PLAY)){
		 	
			if(main_menu==cur_menu)
				disp_port(MENU_HALF_SEC_REFRESH);
	     }
#endif

            break;

        case MSG_HALF_SECOND:

#if defined(USE_BAT_MANAGEMENT)
		bmt_hdlr();
#endif
		set_brightness_fade_out();
		
/////////////////////////////////////////////////////////////
//短歌曲或损坏的歌曲在这里跳到下一首
		if (play_status == MAD_STOP_WAIT)				//等待一段时间再自动选择下一首
		{
			if (play_delay_time < 4)
				play_delay_time++;
			else
			{
				put_msg_lifo(MSG_MUSIC_SELECT_NEW_FILE);
			}
		}
		if(cur_menu == main_menu)
		{
			disp_port(main_menu);
		}
////////////////////////////////////////////////////////////
//显示界面的切换

		if(disp_scenario == DISP_RTC_SCEN){

			rtc_disp_hdlr();
			break;
		}	
		if (main_menu_conter < (SUB_MENU_TIME - 3))
		{
                	main_menu_conter++;
		}
            	else if (cur_menu != main_menu)
            	{
			if (cur_menu == MENU_INPUT_NUMBER)			//数字输入模式
			{
				put_msg_lifo(MSG_PICH_SONG);
                    		break;
                	}
                	else if(RECODE_WORKING == encode_status)
                	{
                    		cur_menu = MENU_RECWORKING;
                	}
                	else
                	{
                    		cur_menu = main_menu;
                	}

                	disp_port(cur_menu);
            }
/////////////////////////////////////////////////////////////
//调整显示亮度
/////////////////////////////////////////////////////////////
//更新实时界面
//            disp_port(MENU_HALF_SEC_REFRESH);
			 // disp_port(main_menu);
            break;

#if 0//RTC_ENABLE
        case MSG_ALM_ON:
            write_next_alm_sec();
            work_mode = RTC_MODE;
            put_msg_lifo(MSG_CHANGE_WORK_MODE);
            break;
#endif
        case MSG_DEL_CURR_FILE:			 //删除当前播放文件

	    if(play_status != MAD_PLAY)break;
			
            stop_decode();
            delete_current_file((device_active & (~VIRTUAL_DEVICE)), &fat_ptr1);
            given_device = device_active;
            given_file_method = PLAY_SEL_FILE;//PLAY_BREAK_POINT;
            given_file_number = fs_msg.fileNumber;
            if(given_file_number == logic_fileTotal)
            {
                given_file_number--;// = logic_fileTotal -1;
            }

            disp_port(MENU_DEL_FIL);
	     delay_10ms(200);

            put_msg_lifo(MSG_MUSIC_SELECT_NEW_DEVICE);

            break;
#if 0
        case MSG_DEVICE_MODE:		    //设备切换
            set_brightness_all_on();
            device_check();
    		backup_music_point();
            given_device = DEVICE_AUTO_NEXT; //0x81;//自动获取下一个设备。
            given_file_method = PLAY_BREAK_POINT;
            put_msg_lifo(MSG_MUSIC_SELECT_NEW_DEVICE);
            break;
#endif		
#if 0
		  case	MSG_DEL_ALL_FILE:
			if(0 == encode_filenum)
				break;
			disp_port(MENU_REC_DEL);		  
			stop_decode();
			device_active |=VIRTUAL_DEVICE;
			given_file_number =1;
			delay_10ms(20);
			{
				u16 i;
				 for(i=0;i<encode_filenum;i++)
				 {	 				 	
					fs_getfile_bynumber(0, &fat_ptr1, filenum_logic_phy(given_file_number));
		            delete_current_file((device_active & (~VIRTUAL_DEVICE)), &fat_ptr1);
		            given_file_number = filenum_phy_logic(fs_msg.fileNumber);
				 }	
			}
			given_file_method = PLAY_FIRST_FILE;
			given_device = device_active &(~VIRTUAL_DEVICE);
			put_msg_lifo(MSG_MUSIC_SELECT_NEW_DEVICE);
			break;
#endif			
        default :
__HOT_MSG_HDLR:        			
            ap_handle_hotkey(key);
            break;
        }
    }
}


/*----------------------------------------------------------------------------*/
/**@brief   播放解码模式入口
   @param   无
   @return  无
   @note    void music_decode(void)
*/
/*----------------------------------------------------------------------------*/
void music_decode(void)
{
#ifdef UART_ENABLE
	uart_init();
	deg_str("music_decode \n");
#endif

    input_number_en = 1;									//允许数字输入功能
    vol_change_en=1;
    //enable_key_tone_flag(1);
    //flashled(3);
     play_mode = REPEAT_ALL;
     disp_scenario = DISP_NORMAL;

    main_menu = MENU_MUSIC_MAIN;
    dec_msg = get_dec_msg_ptr();
    fat_ptr1.buf = win_buffer;
    SYSTEM_CLK_DIV1();

    //key_table_sel(0);
    flush_all_msg();
    music_info_init();
    set_max_vol(MAX_ANOLOG_VOL,MAX_DIGITAL_VOL);///设置最大音量
    encode_channel = REC_MIC;
    music_play();
    //delay_10ms(3);
    stop_decode();
    //key_voice_en=0;
    main_vol_set(0, CHANGE_VOL_NO_MEM);
    given_device = NO_DEVICE;
    break_encode();
#ifdef PLAY_STATUS_LED_FUNC
    set_play_status_led_spark(PLED_ON);
#endif	
	
}
