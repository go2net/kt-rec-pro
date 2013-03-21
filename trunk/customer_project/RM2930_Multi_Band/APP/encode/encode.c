#include "encode.h"
#include "aux_fun.h"
#include "dac.h"
#include "clock.h"
#include "rtc_api.h"

u8 _xdata encode_status;  		 ///<录音状态标志
u8 _xdata encode_channel;  		///<录音通道
u8 _xdata encode_vol;			///<录音音量
u8 _xdata encode_device;   		///<录音设备
u16 _xdata encode_fristfile;		///<录音文件夹第一个文件号
u16 _xdata encode_filenum;  		///<录音文件夹的总文件夹数
u8 encode_cnt;					///<播放记忆数组号偏移
u8 mem_addr;					///<断点记忆位置偏移
u16 _xdata logic_fileTotal;		///<逻辑文件总数


extern u8 work_mode;
extern bool input_number_en;
extern u8  main_menu, cur_menu, main_menu_conter ;
extern u16 input_number;
extern u8 work_mode;
extern u8 _idata last_work_mode;
extern u8 _xdata decode_buffer[];
extern u8 eq_mode;
//extern bool vol_change_en;
extern u8 device_active;
extern void lcd_clr_flash_icon();

#if defined(CUSTOM_DEFINED_FOLDER)
u8 _code rec_mic_dirfile[2][12] = 
{
    {"MIC_REC     "},
    {"MIC00000MP3"},
};
u8 _code rec_fm_dirfile[2][12] = 
{
    {"FM_REC     "},
    {"FMR00000MP3"},
};
u8 _code rec_aux_dirfile[2][12] = 
{
    {"AUX_REC     "},
    {"AUX00000MP3"},
};
#else
u8 _code rec_dirfile[2][12] = 
{
    {"JKT_REC     "},
    {"REC00000MP3"},
};
#endif
u8 _xdata rec_dirfilename[2][12];                   

/*----------------------------------------------------------------------------*/
/**@brief   录音文件夹和文件名称赋值
   @param   无
   @return  无
   @note    void init_rec_name(void)
*/
/*----------------------------------------------------------------------------*/
void init_rec_name(void)
{
    u8 i;
#if defined(CUSTOM_DEFINED_FOLDER)

    if(REC_FM== encode_channel){
		
	    for(i = 0;i < 12;i++)
	    {
	        rec_dirfilename[0][i] = rec_fm_dirfile[0][i];
	        rec_dirfilename[1][i] = rec_fm_dirfile[1][i];		
	    } 
    }
    else if(REC_LINEIN == encode_channel){
		
	    for(i = 0;i < 12;i++)
	    {
	        rec_dirfilename[0][i] = rec_aux_dirfile[0][i];
	        rec_dirfilename[1][i] = rec_aux_dirfile[1][i];		
	    } 
   }
   else if(REC_MIC == encode_channel){
   	
	    for(i = 0;i < 12;i++)
	    {
	        rec_dirfilename[0][i] = rec_mic_dirfile[0][i];
	        rec_dirfilename[1][i] = rec_mic_dirfile[1][i];		
	    } 
   }	
#else
    for(i = 0;i < 12;i++)
    {
        rec_dirfilename[0][i] = rec_dirfile[0][i];
        rec_dirfilename[1][i] = rec_dirfile[1][i];
    }
#endif	
    rec_dirfile_name(&rec_dirfilename[0]);
}

/*----------------------------------------------------------------------------*/
/**@brief   文件号从物理文件号转换为逻辑文件号
   @param   无
   @return  无
   @note    u16 filenum_phy_logic(u16 filenumber)
*/
/*----------------------------------------------------------------------------*/
#if 0
u16 filenum_phy_logic(u16 filenumber)
{
#if VIRTUAL_ENABLE
    if(device_active & VIRTUAL_DEVICE)		  //录音文件
    {
        if( (filenumber < encode_fristfile) || (filenumber > (encode_fristfile + encode_filenum - 1)) )
        {
            return 1;
        }
        return filenumber - encode_fristfile + 1;
    }
    else					  //音乐文件
    {
        if(filenumber > encode_fristfile)
        {
            if(filenumber < (encode_filenum + encode_fristfile))
            {
                return 1;
            }
            return filenumber - encode_filenum;
        }
        else
            return filenumber;
    }
#else
    return filenumber;
#endif
}
#endif
/*----------------------------------------------------------------------------*/
/**@brief   文件号从逻辑文件号转换为物理文件号
   @param   无
   @return  无
   @note    u16 filenum_logic_phy(u16 filenumber)
*/
/*----------------------------------------------------------------------------*/
#if 0
u16 filenum_logic_phy(u16 filenumber)
{

#if VIRTUAL_ENABLE
    if(device_active & VIRTUAL_DEVICE)   //录音文件
    {
        if(filenumber > encode_filenum) 
        {
            return encode_fristfile;
        }

        return filenumber + encode_fristfile - 1;
    }
    else    //音乐文件
    {
        if(filenumber >= encode_fristfile)
        {
            return filenumber + encode_filenum;
        }
        else
            return filenumber;
    }
#else
    return filenumber;
#endif
}
#endif
/*----------------------------------------------------------------------------*/
/**@brief   设备断点记忆的数据准备
   @param   无
   @return  无
   @note    void get_rec_mem_info(void)
*/
/*----------------------------------------------------------------------------*/
#if 0
void get_rec_mem_info(void)
{
#if VIRTUAL_ENABLE
    if(device_active & VIRTUAL_DEVICE)
    {
        encode_cnt = 2;
        mem_addr = MEM_REC_D_VALUE;
    }
    else
    {
        encode_cnt = 0;
        mem_addr = 0;
    }
#else

#endif

}
#endif
void api_stop_encode(void) 
{
    stop_encode();
    encode_status = RECODE_STOP;
    lcd_clr_flash_icon();		
}
/*----------------------------------------------------------------------------*/
/**@brief   录音状态统一清理函数
   @param   无
   @return  无
   @note    void break_encode(void)
*/
/*----------------------------------------------------------------------------*/
void break_encode(void)
{
    switch (encode_status)
    {
    case RECODE_PLAY:
        if(REC_MIC_MODE != work_mode)
        {
            break;
        }
        encode_status = RECODE_STOP;
        break;
    case RECODE_INIT:
        if(REC_MIC_MODE == work_mode)
        {
            break;
        }
        encode_status = RECODE_STOP;
        break;
    case RECODE_WORKING:
    case RECODE_PAUSE:
        api_stop_encode();
        break;
    //default :
    //    break;
    }
}

/*----------------------------------------------------------------------------*/
/**@brief   rec模式主循环
   @param   无
   @return  无
   @note    void rec_mic_main(void)
*/
/*----------------------------------------------------------------------------*/
void rec_mic_main(void)
{
    u8 key;

    dac_out_select(DAC_MUSIC, 0);

    while (1)
    {
        key = app_get_msg();

        switch (key)
        {
        case MSG_CHANGE_WORK_MODE:
            return;

        case MSG_MUSIC_NEW_DEVICE_IN:							//有新设备接入
            work_mode = MUSIC_MODE;
            return;

        case MSG_HALF_SECOND:
						
////////////////////////////////////////////////////////////
//显示界面的切换
#if  1
//            if(RECODE_WORKING == encode_status)
//            {
//                main_menu = MENU_RECWORKING;
//            }
//			else if(RECODE_PAUSE == encode_status)
//			{
//				 main_menu = MENU_REC_PAUSE;
//			}
//            else
//            {
//                main_menu = MENU_REC;
//            }

	if(cur_menu == main_menu)
	{
	   disp_port(main_menu);
	}

#ifndef LCD_BACK_LIGHT_DUMMY
            set_brightness_fade_out();
#endif 
#endif 
           if (main_menu_conter < SUB_MENU_TIME)
            {
                main_menu_conter++;
            }
            else if (cur_menu != main_menu)
            {
                cur_menu = main_menu;
                disp_port(cur_menu);
            }
//            if(MENU_RECWORKING == cur_menu)
//            {
//               // disp_rec_working(); 
//			    disp_port(MENU_RECWORKING);  
//            }
            break;
        default:
            ap_handle_hotkey(key);
            break;
        }
    }

}
/*----------------------------------------------------------------------------*/
/**@brief   MIC录音入口
   @param   无
   @return  无
   @note    void rec_mic_fun(void)
*/
/*----------------------------------------------------------------------------*/
void rec_mic_fun(void)
{
    dac_mute_control(1,1);
    input_number_en = 0;
    //vol_change_en=1;
    main_menu = MENU_RECWORKING;
    disp_port(MENU_REC);
    SYSTEM_CLK_DIV2();
    encode_channel = REC_MIC;
    encode_vol = 7;
    key_table_sel(0);
    flush_all_msg();
    if(RECODE_INIT == encode_status)
    {
        put_msg_lifo(MSG_REC_FIND);
        //put_msg_lifo(MSG_REC_START);
    }
    //put_msg_lifo(MSG_REC_START);
    set_max_vol(MAX_ANOLOG_VOL,MAX_DIGITAL_VOL);///设置最大音量
    rec_mic_main();
    dac_mute_control(0,0);
    break_encode();
    lcd_clr_flash_icon();	
}





