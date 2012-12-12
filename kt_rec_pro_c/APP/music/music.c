/*--------------------------------------------------------------------------*/
/**@file   music.h
   @brief  musicͷ�ļ�
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
u8 play_mode;							 ///<ѭ��ģʽ
//u8 play_mode_rec;							 ///<ѭ��ģʽ
u8 given_device;						 ///<��Ҫ���ҵ��豸
u16 given_file_number;					 ///<��Ҫ���ҵ��ļ���
u16 break_point_filenum;				 ///<�ϵ���Ϣ��Ӧ���ļ���
u8 play_status;							///<����״̬
u8 play_delay_time;

u8 eq_mode=0;				  ///<EQģʽ
u8 music_type;			  ///<�����ļ��ĸ�ʽ
u8 given_file_method;	  ///<��ȡ�ļ��ķ�ʽ
//u8 _pdata music_spec[9] _at_ 0x02;	 ///<Ƶ��BUFF

//u8 _xdata decode_buffer[1024*2] _at_ 0x2880;	 ///<����BUFF
//u8 _xdata win_buffer[512] _at_ 0x700;			 ///<�ļ�ϵͳ����BUFF

//u8 _xdata decode_buffer[0x2580] _at_ 0x700;      ///<����BUFF

u8 _xdata decode_buffer[1024*2] _at_ 0x2880;	 ///<����BUFF
u8 _xdata buff_for_usb[64] _at_ 0x6c0;
u8 _xdata encode_buffer[0x2580] _at_ 0x700;      ///<����BUFF

u8 _xdata win_buffer[512] _at_ 0x4C0;            ///<�ļ�ϵͳ����BUFF

FSAPIMSG _pdata fs_msg _at_ 0x40;				 ///<�ļ�ϵͳ�����Ϣ

FSAPIMSGREC _pdata fs_msg_rec _at_ 0x40 + sizeof(FSAPIMSG) ;
DECODER_MSG _xdata *dec_msg;					 ///<������ص���Ϣ
FIL xdata fat_ptr1;								 ///<�ļ����ļ�ϵͳ�е������Ϣ
bool find_break_point_file_flag;			///<�Ƿ��ҵ����Զϵ��������ļ�
#if 0
#if VIRTUAL_ENABLE
DISK_MUSIC_POINT _idata	disk_mus_point[4];	   ///<�����ļ��ϵ����ı���
#else
DISK_MUSIC_POINT _idata	disk_mus_point[2];	   ///<�����ļ��ϵ����ı���
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
/** ���ID3V2��Ϣ�Ľṹ����� */
ID3V2_PARSE _xdata s_id3v2; 
/*----------------------------------------------------------------------------*/
/**@brief  ����ID3��Ϣ��ȡ�׶�
   @param  ��
   @return  ��
   @note  void skip_music_tag(void)
*/
/*----------------------------------------------------------------------------*/
void skip_music_tag(void)
{

    f_seek(SEEK_SET, dec_msg->tag_len, dec_msg->tag_len >> 16);
    my_memset((u8 _xdata *)&s_id3v2, 0, sizeof(ID3V2_PARSE));
    while (ff_id3v2_check(decode_buffer, &s_id3v2)) //����ȡID3ͷ��ͷ��Ϣ
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
/**@brief MUSIC�����ʼ��
   @param ��
   @return  ��
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
/**@brief MUSICģʽ��Ϣ��ʼ��
   @param ��
   @return  ��
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
/**@brief MUSIC�ϵ���Ϣд��rtcram��
   @param ��
   @return  ��
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
/**@brief MUSIC�ϵ���Ϣд��EEPR0M��
   @param ��
   @return  ��
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
/**@brief MUSIC�ϵ���Ϣд��EEPROM��
   @param ��
   @return  ��
   @note void backup_music_point(void)
*/
/*----------------------------------------------------------------------------*/
#if (BREAK_POINT_PLAY_EN == 1)
void backup_music_point(void)
{

    u16 reg_id=0;
    if ((play_status != MAD_PLAY) && (play_status != MAD_PAUSE))				//��ǰû�д��ڲ��Ż���ͣ״̬,������ϵ�
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
/**@brief ����MUSIC�ϵ���Ϣ
   @param ��
   @return  ��
   @note void save_music_point(void)
*/
/*----------------------------------------------------------------------------
void save_music_point(void)
{
    if ((play_status != MAD_PLAY) && (play_status != MAD_PAUSE))				//��ǰû�д��ڲ��Ż���ͣ״̬,������ϵ�
    {
        return;
    }

}*/
/*----------------------------------------------------------------------------*/
/**@brief ����MUSIC�ϵ���Ϣ
   @param ��
   @return  0����������Ч�ضϵ㣻1��������Ч�ضϵ�
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
/**@brief ��EEPROM�ж����ϵ���Ϣ������ʼ���������
   @param ��
   @return  ��
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
/**@brief   ֹͣ����
   @param   ��
   @return  ��
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
    	decode_init();									//�����ʼ�����Ὣ����ı�����״̬����
}


/*----------------------------------------------------------------------------*/
/**@brief  ��ʼ����
   @param  ��
   @return ��
   @note   start_decode
*/
/*----------------------------------------------------------------------------*/
static u8 start_decode(void)
{

    mad_control(MAD_STOP, 0);
    decode_init();									//�����ʼ�����Ὣ����ı�����״̬����
    music_type = music_format_check(decode_buffer);	//����ļ���ʽ

    if (music_type == NOT_SUPPORT)					//��֧�ֵĸ�ʽ
    {
        return 1;
    }
    else if (music_type == IS_MP3)					//MP3
    {
	 skip_music_tag();
        if (!get_mp3_total_time())
            return 1;
    }

        

    if (dec_msg->total_time == 0)					//�ܲ���ʱ��Ϊ0���򲻽��в��ţ����������Ϊ����˴��ж϶����ܲ��ŵ��ļ������ȥ��������
    {
        return 1;
    }

    set_eq(eq_mode);

#if (BREAK_POINT_PLAY_EN == 1)
    if (find_break_point_file_flag) 								//ȡ������Ķϵ���Ϣ
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
/**@brief  �豸�γ�ʱMUSIC����Ĵ���
   @param  ��
   @return ��
   @note   void disk_remove_deal_for_music(void)
*/
/*----------------------------------------------------------------------------*/
void disk_remove_deal_for_music(void)
{
    if ( (device_check() == 0))//��ǰ�����豸�Ѿ�������,���Զ�ѡȡ��һ���豸
    {
        given_device = DEVICE_AUTO_NEXT;
        given_file_method = PLAY_BREAK_POINT;

        put_msg_lifo(MSG_MUSIC_SELECT_NEW_DEVICE);

#if (BREAK_POINT_PLAY_EN == 1)
        if((play_status == MAD_PAUSE) || (play_status == MAD_PLAY) )
        	backup_music_point();								//��¼�ϵ���Ϣ
#endif        	
    }
}

/*----------------------------------------------------------------------------*/
/**@brief  MUSICģʽ��ѭ��
   @param  ��
   @return ��
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
        //suspend_sdmmc();						//�ɼ���SDMMC���ģ��������ӵ�Դ����
        key = app_get_msg();


        switch (key)
        {
    
        case MSG_CHANGE_WORK_MODE:
	     rtc_setting_flag=0;
#if (BREAK_POINT_PLAY_EN == 1)	 
            backup_music_point();
#endif
            return;

        case MSG_MUSIC_NEW_DEVICE_IN:							//�����豸����
#if (BREAK_POINT_PLAY_EN == 1)       
            backup_music_point();
#endif            
            put_msg_lifo(MSG_MUSIC_SELECT_NEW_DEVICE);
            break;

        case MSG_MUSIC_SELECT_NEW_FILE:

            if (device_check() == 0)                                //��ǰ�����豸�Ѿ�������,���Զ�ѡȡ��һ���豸
            {
                given_device = DEVICE_AUTO_NEXT;
                put_msg_lifo(MSG_MUSIC_SELECT_NEW_DEVICE);
                break;
            }

            res = fs_get_filenum(play_mode, given_file_method);

            if (res == GET_DEVICE_END)								//��һ�����豸�Ľ�����������һ���豸�ĵ�һ��
            {
                	given_file_method = PLAY_FIRST_FILE;
                	given_device = DEVICE_AUTO_NEXT;
                	put_msg_lifo(MSG_MUSIC_SELECT_NEW_DEVICE);
                	break;
            }
            else if (res == GET_DEVICE_HEAD)								//��һ�����豸�Ľ�����������һ���豸�����һ��
            {
                	given_file_method = PLAY_LAST_FILE;
                	given_device = DEVICE_AUTO_PREV;
                	put_msg_lifo(MSG_MUSIC_SELECT_NEW_DEVICE);
                	break;
            }
            put_msg_lifo(MSG_MUSIC_PLAY_NEW_FILE);
            break;

        case MSG_MUSIC_PLAY_NEW_FILE:									//���ļ����ѡ���ļ����в���
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

            if (res != 0)                                       //���Ų��ɹ�
            {
                play_status = MAD_STOP_WAIT;
                play_delay_time = 0;
                if (given_file_method <= PLAY_BREAK_POINT) 		//��������һ��
                {
                    given_file_method = PLAY_NEXT_FILE;
                    break;
                }
                else											//��������һ��
                {
                    given_file_method = PLAY_PREV_FILE;
                    break;
                }
            }
            main_menu = MENU_MUSIC_MAIN;
            write_file_info(0xff);
            break;

        case MSG_DECODE_FILE_END:
            if ((dec_msg->play_time >= 5) || (play_status == MAD_FF) || (play_status == MAD_FR))     //��ǰ�����Ĳ���ʱ�����5Sʱ��ֱ�Ӳ�����һ��
            {
                	given_file_method = PLAY_AUTO_NEXT;
                	put_msg_lifo(MSG_MUSIC_SELECT_NEW_FILE);
            }
            else													//��ǰ��������ʱ��С��5S���п����ǲ����������ȴ�һ��ʱ��
            {
                	play_delay_time = 0;
                	given_file_method = PLAY_AUTO_NEXT;
                	play_status = MAD_STOP_WAIT;
            }
#ifdef REC_PLAY_KEY_BREAK_POINT
		rec_pley_bp_flag=0;
#endif		
            break;

        case MSG_MUSIC_PREV_FILE:												//ѡ����һ���ļ����в���

	     if((disp_scenario == DISP_RTC_SCEN)&&(rtc_setting_flag!=0)){
			goto __HOT_MSG_HDLR;
			break;
	     }
		 
            given_file_method = PLAY_PREV_FILE;
            put_msg_lifo(MSG_MUSIC_SELECT_NEW_FILE);
            break;

        case MSG_MUSIC_NEXT_FILE:												//ѡ����һ���ļ����в���

	     if((disp_scenario == DISP_RTC_SCEN)&&(rtc_setting_flag!=0)){
			goto __HOT_MSG_HDLR;
			break;
	     }		
            //delay_10ms(30);
            given_file_method = PLAY_NEXT_FILE;
            put_msg_lifo(MSG_MUSIC_SELECT_NEW_FILE);
            break;

        case MSG_MUSIC_PP:											//��ͣ�Ͳ���

            if (cur_menu == MENU_INPUT_NUMBER)			            //��������ģʽ
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
#if VIRTUAL_ENABLE							       //�������ʶ���ˣ�¼���ļ��к��豸�����ļ��Ĳ���ģʽ�ֿ�����
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
        case MSG_MUSIC_FR:											//��������

	     if((disp_scenario == DISP_RTC_SCEN)&&(rtc_setting_flag!=0)){
			goto __HOT_MSG_HDLR;
			break;
	     }
		 
            if (find_break_point_file_flag)							//����Ǽ��䲥�ŵĸ��������ܿ���
            {
                break;
            }
            if (play_status == MAD_PLAY)
            {
                play_status = MAD_FR;
            }

            break;

        case MSG_MUSIC_FF:											//�������

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
        case MSG_MUSIC_FFR_DONE:									//������˽������ָ�����
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
            if (cur_menu == MENU_INPUT_NUMBER)			           //��������ģʽ
            {
                if ((input_number <= logic_fileTotal) && (input_number != 0))			   //���������Ƿ���Ч  fs_msg.fileTotal
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
//�������ʵ�ʵĲ������������
#if (FF_FR_EN == 1)
            if (play_status == MAD_FF)
            {
#if (FF_FR_MUSIC == 0)							//�����Ҫ�ڿ�����˹������������������Բ��Ӵ���
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
                dac_mute_control(1);							//�����Ҫ�ڿ�����˹������������������Բ��Ӵ���
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
//�̸������𻵵ĸ���������������һ��
		if (play_status == MAD_STOP_WAIT)				//�ȴ�һ��ʱ�����Զ�ѡ����һ��
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
//��ʾ������л�

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
			if (cur_menu == MENU_INPUT_NUMBER)			//��������ģʽ
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
//������ʾ����
/////////////////////////////////////////////////////////////
//����ʵʱ����
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
        case MSG_DEL_CURR_FILE:			 //ɾ����ǰ�����ļ�

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
        case MSG_DEVICE_MODE:		    //�豸�л�
            set_brightness_all_on();
            device_check();
    		backup_music_point();
            given_device = DEVICE_AUTO_NEXT; //0x81;//�Զ���ȡ��һ���豸��
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
/**@brief   ���Ž���ģʽ���
   @param   ��
   @return  ��
   @note    void music_decode(void)
*/
/*----------------------------------------------------------------------------*/
void music_decode(void)
{
#ifdef UART_ENABLE
	uart_init();
	deg_str("music_decode \n");
#endif

    input_number_en = 1;									//�����������빦��
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
    set_max_vol(MAX_ANOLOG_VOL,MAX_DIGITAL_VOL);///�����������
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
