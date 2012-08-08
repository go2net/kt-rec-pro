/*--------------------------------------------------------------------------*/
/**@file    fm_receive.c
   @brief   FM接收任务模块
   @details
   @author
   @date   2011-3-7
   @note
*/
/*----------------------------------------------------------------------------*/
#if 0
#include "aux_fun.h"
#include "dac.h"
#include "clock.h"
#include "rtc_api.h"
#include "eq.h"

extern bool input_number_en;
extern u8  main_menu, cur_menu, main_menu_conter ;
extern u16 input_number;
extern u8 work_mode;
extern u8 _idata last_work_mode;
extern u8 _xdata decode_buffer[];
extern u8 eq_mode;
extern bool vol_change_en;



/*----------------------------------------------------------------------------*/
/**@brief   Line IN模式主循环
   @param   无
   @return  无
   @note    void aux_main(void)
*/
/*----------------------------------------------------------------------------*/
void aux_main(void)
{
    u8 key;

    while (1)
    {
#if defined(EXCHANGE_AUX_CHANNEL)
        dac_out_select(DAC_AMUX0, 0);
#else
        dac_out_select(DAC_AMUX1, 0);
#endif
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
//				main_menu = MENU_REC_PAUSE;
//			}
//            else
//            {
//                main_menu = MENU_AUX;
//            }
			if(cur_menu == main_menu)
			{
			   disp_port(main_menu);
			}

            set_brightness_fade_out();
#endif 
            
            set_brightness_fade_out();
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
//              // disp_rec_working();   
//			   disp_port(MENU_RECWORKING); 
//            }
            break;
#if 0//RTC_ENABLE
        case MSG_ALM_ON:
            write_next_alm_sec();
            work_mode = RTC_MODE;
            put_msg_lifo(MSG_CHANGE_WORK_MODE);
            break;
#endif
        default:
            ap_handle_hotkey(key);
            break;
        }
    }

}
/*----------------------------------------------------------------------------*/
/**@brief   Line IN模式入口
   @param   无
   @return  无
   @note    void aux_fun(void)
*/
/*----------------------------------------------------------------------------*/
void aux_fun(void)
{
    flashled(3);
//	amp_abd(1);
    //work_mode++;
    //return ;
    input_number_en = 0;
    vol_change_en=1;
    main_menu = MENU_AUX;
    disp_port(MENU_AUX);
    amux_dsp_eq();
    SYSTEM_CLK_DIV4();
    encode_channel = REC_LINEIN;
	encode_vol = 3;
    key_table_sel(0);
    flush_all_msg();
    set_max_vol(MAX_ANOLOG_VOL,MAX_DIGITAL_VOL);///设置最大音量
    aux_main();
    main_vol_set(0, CHANGE_VOL_NO_MEM);

    break_encode();
}
#endif
