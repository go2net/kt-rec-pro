/*--------------------------------------------------------------------------*/
/**@file    msgfor_hot.c
   @brief   HOT ��Ϣ����ģ��
   @details
   @author
   @date   2011-3-7
   @note
*/
/*----------------------------------------------------------------------------*/

#include "msgfor_hot.h"
#include "disp.h"
#include "main.h"
#include "device.h"
#include "eq.h"
#include "dac.h"
#include "rtc_api.h"
#include "rtc_ui.h"

extern void disk_remove_deal_for_music(void);
extern void rtc_disp_hdlr(void);

extern u8 work_mode;
//extern u8 _idata last_work_mode;
extern bool input_number_en;
extern bool eq_change_en;
extern bool play_mode_change_en;

extern u8 given_device;
extern u16 given_file_number;
extern u8 given_file_method;
extern u8 eq_mode;
extern u8 play_mode;
extern u8  main_menu, cur_menu, main_menu_conter;
extern u8 device_active;
u16 input_number;	 ///<��������ֵ�ʵ��ֵ
bool vol_change_en;	 ///<�����޸�����λ
extern u8 device_online;
bool rec_device_out;

extern RTC_TIME _xdata curr_time;
extern xd_u8 rtc_coordinate;
bool sys_mute_flag=0;
bool sys_pwr_flag=0;

#ifdef REC_PLAY_KEY_BREAK_POINT
bool rec_pley_bp_flag=0;
xd_u16 last_play_index=0;
#endif


xd_u8 rtc_set_cnt=0;
xd_u8 disp_scenario=DISP_NORMAL;
xd_u8 rtc_setting_flag=0;
/*----------------------------------------------------------------------------*/
/**@brief   �������񶼻��õ�����Ϣ���д���ĺ���
   @param   key�� ��Ҫ�������Ϣ
   @return  0����Ҫ�л�����ģʽ;
   @note    unsigned char I2C_sendbyte(unsigned char I2Cdata)
*/
/*----------------------------------------------------------------------------*/
void ap_handle_hotkey(u8 key)
{
    u8 res;
    switch (key)
    {
    case MSG_POWER_DOWN:

		if(sys_pwr_flag==0){
			sys_pwr_flag =1;
			sys_mute_flag =1;
        		dac_mute_control(sys_mute_flag,1);					//��������ʱ���Զ�UNMUTE
			work_mode =  IDLE_MODE;		
	        	put_msg_lifo(MSG_CHANGE_WORK_MODE);
		}
		else{

			sys_mute_flag =0;
        		//dac_mute_control(sys_mute_flag,1);					//��������ʱ���Զ�UNMUTE
			sys_pwr_flag =0;
			//work_mode =  IDLE_MODE;
		}



		break;
		
    case MSG_MUTE_UNMUTE:

		sys_mute_flag=~sys_mute_flag;
		//dac_mute_toggle();		
        	dac_mute_control(sys_mute_flag,1);					//��������ʱ���Զ�UNMUTE

		break;		    
#if 1   
    case MSG_MUSIC_PREV_FILE:												//ѡ����һ���ļ����в���
    case MSG_MUSIC_FR:											//��������
	      	if ((disp_scenario == DISP_RTC_SCEN)&&(rtc_setting_flag!=0))
            	{
                	rtc_set_cnt=30;
                	curr_time_minus();
                	write_rtc(&curr_time);
                	//write_next_alm_sec();
                	disp_port(MENU_RTC);
            	}
    		break;
    case MSG_MUSIC_NEXT_FILE:												//ѡ����һ���ļ����в���
    case MSG_MUSIC_FF:											//��������

	      	if ((disp_scenario == DISP_RTC_SCEN)&&(rtc_setting_flag!=0))
            	{
                	rtc_set_cnt=30;
                	curr_time_plus();
                	write_rtc(&curr_time);
                	//write_next_alm_sec();
                	disp_port(MENU_RTC);
            	}
		break;
    case MSG_NEXT_WORKMODE:
		
		//set_brightness_all_on();
		if(work_mode==FM_RADIO_MODE)break;
		
		if(rtc_setting_flag!=0){

			rtc_coordinate++;
                	rtc_set_cnt=30;

			if(rtc_coordinate>4){
				rtc_coordinate = 3;
				rtc_setting_flag = 0x00;
			}
			break;
		}
		
		if(disp_scenario == DISP_NORMAL){

			    	input_number_en = 0;									//�����������빦��
				disp_scenario = DISP_RTC_SCEN;
				rtc_disp_hdlr();
		}
		else{

			if(device_online==0)break;
		    	input_number_en = 1;									//�����������빦��
			disp_scenario = DISP_NORMAL;
	              disp_port(MENU_MUSIC_MAIN);
		}
		break;    
		
    case MSG_TIME_SETTING:
	       //set_brightness_all_on();
		if(disp_scenario == DISP_RTC_SCEN){

	             	rtc_set_cnt=30;				
			rtc_setting_flag = 0x01;
			rtc_coordinate = 3;
		}
	break;
    case MSG_USB_DISK_OUT:
    case MSG_SDMMC_OUT:
        if((RECODE_WORKING == encode_status)||(RECODE_PAUSE == encode_status))
        {	
			rec_device_out = 1;
			api_stop_encode();
            if(work_mode == FM_RADIO_MODE){
			main_menu = MENU_FM_MAIN;//
			disp_port(MENU_FM_MAIN);
            		break;
	     }
        } 
		
        set_brightness_all_on();
        if((!device_check()) && (REC_MIC_MODE == work_mode))
        {
             put_msg_lifo(MSG_MUSIC_NEW_DEVICE_IN);
             break;   
        }

	    if(MUSIC_MODE != work_mode)
			break;
        //put_msg_lifo(MSG_DEVICE_REMOVED);
        disk_remove_deal_for_music();
        break;
#endif
#if USB_DEVICE_ENABLE
    case MSG_USB_PC_IN:
        break_encode();
        set_brightness_all_on();
        device_check();
        work_mode = USB_DEVICE_MODE;
        put_msg_lifo(MSG_CHANGE_WORK_MODE);
        break;

    case MSG_USB_PC_OUT:
        set_brightness_all_on();
        break;
#endif

    case MSG_SDMMC_IN :
        set_brightness_all_on();
	 device_check();
        if((RECODE_WORKING == encode_status)||(RECODE_PAUSE == encode_status))
        {	
            break;
        } 
        
        break_encode();

	disp_scenario = DISP_NORMAL;

#if USB_DEVICE_ENABLE
        if (work_mode == USB_DEVICE_MODE)
            break;
#endif

		given_device = read_info(MEM_ACTIVE_DEV);

		if(given_device == DEVICE_SDMMC0_REC)
			given_device = DEVICE_SDMMC0_REC;
		else
			given_device = DEVICE_SDMMC0;

        given_file_method = PLAY_BREAK_POINT;
        put_msg_lifo(MSG_MUSIC_NEW_DEVICE_IN);
        break;

    case MSG_USB_DISK_IN  :
        set_brightness_all_on();
		device_check();
        if((RECODE_WORKING == encode_status)||(RECODE_PAUSE == encode_status))
        {
            break;
        }
        break_encode();

	disp_scenario = DISP_NORMAL;
	   
		given_device = read_info(MEM_ACTIVE_DEV);

		if(given_device == DEVICE_UDISK_REC)
			given_device = DEVICE_UDISK_REC;
		else
	    	given_device = DEVICE_UDISK;

        given_file_method = PLAY_BREAK_POINT;      
        put_msg_lifo(MSG_MUSIC_NEW_DEVICE_IN);
        break;
		
#if 0
    case MSG_NEXT_WORKMODE:

#if 0//def K820_LHD_820_REC_V001
	    if(MUSIC_MODE != work_mode)
			break;
	 if(device_check()>0){
	 
	        given_device = DEVICE_AUTO_NEXT;
	        given_file_method = PLAY_BREAK_POINT;
	        put_msg_lifo(MSG_MUSIC_SELECT_NEW_DEVICE);
	        backup_music_point();
	 }
	 else{
    		//flashled(3);
              work_mode =IDLE_MODE;
        	put_msg_lifo(MSG_CHANGE_WORK_MODE);		
	 }
	break;

#endif

	break_encode();
        work_mode++;
        if (work_mode > MAX_WORK_MODE)
            work_mode = MUSIC_MODE;

        put_msg_lifo(MSG_CHANGE_WORK_MODE);
        break;
#endif		
#if 1
    case MSG_VOL_UP:
        if(vol_change_en==0)
            break;
        dac_mute_control(0,1);					//��������ʱ���Զ�UNMUTE
        main_vol_set(0, CHANGE_VOL_INC);
        //write_info(MEM_VOL, main_vol_set(0, CHANGE_VOL_INC));
        disp_port(MENU_MAIN_VOL);
        break;

    case MSG_VOL_DOWN:
        if(vol_change_en==0)
            break;
        dac_mute_control(0,1);					//��������ʱ���Զ�UNMUTE
        main_vol_set(0, CHANGE_VOL_DEC);
        //write_info(MEM_VOL, main_vol_set(0, CHANGE_VOL_DEC));
        disp_port(MENU_MAIN_VOL);
        break;
#endif
    case MSG_0:
    case MSG_1:
    case MSG_2:
    case MSG_3:
    case MSG_4:
    case MSG_5:
    case MSG_6:
    case MSG_7:
    case MSG_8:
    case MSG_9:
        if (!input_number_en)
            break;
		
	 if((input_number)>6553){
		input_number = 0x0000;			
	 }
        if (input_number > 9999)
            input_number = 0;

           input_number = input_number * 10 + key;
        disp_port(MENU_INPUT_NUMBER);
        break;
//2  REC FSM BEGIN
    case MSG_REC_KEY:	  //¼����ʼ�ͽ���

	  if(work_mode ==IDLE_MODE)
	  	break;
	  	
        if(RECODE_PLAY >= encode_status)
        {
            put_msg_lifo(MSG_REC_FIND);
        }
        else
        {
            put_msg_lifo(MSG_REC_STOP);
        }
        break;

	case MSG_MUSIC_PP:      //¼����ͣ�ͼ���¼��
	//case MSG_REC_PP:      //¼����ͣ�ͼ���¼��

        if(RECODE_WORKING == encode_status)
        {
            put_msg_lifo(MSG_REC_PAUSE);
        }
        else if(RECODE_PAUSE == encode_status)
        {

            put_msg_lifo(MSG_REC_CONTINUE);
        }
        break;

    case MSG_ENCODE_END:   //�豸дerr  �� �豸��
		if(rec_device_out)		//¼��ʱ��豸�γ�,���豸�γ����ﴦ���ڴ˲�������
		{
			rec_device_out =0;
			break;
		}

        api_stop_encode();		//ֹͣ¼��
		put_msg_lifo(MSG_REC_PLAY);
		break;

	 case MSG_ENCODE_FAT_FULL:  //���ļ�ʱ
		api_stop_encode();		//ֹͣ¼��
        if((!device_check())&& (REC_MIC_MODE == work_mode))
        {
             put_msg_lifo(MSG_MUSIC_NEW_DEVICE_IN);
             break;   
        }
       // break_encode();

        disp_port(main_menu);
        break;
////////////////¼���漰�ĸ���״̬
    case MSG_REC_FIND:
//        if(RECODE_PLAY >= encode_status)
//        {
//            break;
//        }
	if(get_device_online_status()==0){
		disp_port(MENU_NODEVICE);
		break;
	}	
        encode_status = RECODE_INIT;
        if(MUSIC_MODE == work_mode)
        {
            encode_device = device_active;	 //����¼���洢�豸
            work_mode = REC_MIC_MODE;
            put_msg_lifo(MSG_CHANGE_WORK_MODE);
            break;
        }
	 else if(REC_MIC_MODE == work_mode){
		given_device = encode_device;
	 }
	 else //if((MUSIC_MODE != work_mode))
        {
            if (given_device == NO_DEVICE)
            {
                given_device = read_info(MEM_ACTIVE_DEV);
            }
        }
       // if( ((given_device & (~VIRTUAL_DEVICE))  != DEVICE_SDMMC0) && ((given_device & (~VIRTUAL_DEVICE)) != DEVICE_UDISK))
        {
            //given_device = DEVICE_SDMMC0;
        }
        SYSTEM_CLK_DIV2();

        put_msg_lifo(MSG_MUSIC_SELECT_NEW_DEVICE);
        break;
    case MSG_REC_START:		//��ʼ¼��
		 rec_device_out = 0;
		 rec_sys_set(0);  //0:24M   1:48M
        init_rec_name();
        device_active |= VIRTUAL_DEVICE;
        encode_device = device_active;	 //����¼���洢�豸
        write_file_info(0);
        SYSTEM_CLK_DIV2();

        set_rec_channel(encode_channel); //����¼��ͨ��
        set_rec_vol(encode_vol);		 //����¼������
        if(REC_MIC == encode_channel)
        {
            set_rec_track(TRACK_LEFT);
        }
        else
        {
            set_rec_track(TRACK_ALL);
        }
        /**/
        
        CLKGAT |= MP3CLK;// | SPIURCLK;
        CLKCON0 |= DACCLK;
        if(DEVICE_SDMMC0 == (device_active & (~VIRTUAL_DEVICE)))
        {
            CLKGAT |= USBCLK;
        }
        else if(DEVICE_UDISK == (device_active & (~VIRTUAL_DEVICE)))
        {
            CLKGAT |= SDCLK;
        }

        if(1 != start_encode(IS_MP3))			 //��ʼ¼��
		{
			put_msg_lifo(MSG_ENCODE_FAT_FULL);
			break;
		}
        /*
        if(REC_MIC_MODE == work_mode)
        {
    		while(!((cmd_ctl_rec(REC_NO_OPT,0)) &  FRIST_ADC_PACKET)) //������ǰ�Ĵ���
    		{
    
    		}
            delay_10ms(50);//�������������
        }
		cmd_ctl_rec(ENABLE_REC_DATA,ENABLE_REC_BIT);
        */
        encode_status = RECODE_WORKING;
#if FM_MODULE 
	//	if(FM_RADIO_MODE != work_mode)
#endif
		{
		 	main_menu = MENU_RECWORKING;//
		}
		disp_port(main_menu);
        break;
    case MSG_REC_STOP:      //ֹͣ¼��
        api_stop_encode();		//ֹͣ¼��
        if(work_mode==REC_MIC_MODE){
	 	put_msg_lifo(MSG_REC_PLAY);
        }
#ifdef REC_PLAY_KEY_BREAK_POINT
	rec_pley_bp_flag=0;
#endif		
        break;
    case MSG_REC_PAUSE:     //��ͣ¼��
		encode_status = RECODE_PAUSE;
	
#if FM_MODULE 
		if(FM_RADIO_MODE == work_mode)
			disp_port(MENU_FM_MAIN);
		else
#endif
		{
			//main_menu = MENU_REC_PAUSE;	
		  	disp_port(MENU_RECWORKING);
		}
		 		
        pause_encode();
        break;
    case MSG_REC_CONTINUE:  //��ͣ¼��֮�����¼��
		encode_status = RECODE_WORKING;
	
#if FM_MODULE 
		if(FM_RADIO_MODE == work_mode)
			disp_port(MENU_FM_MAIN);
		else
#endif
		{
		 	main_menu = MENU_RECWORKING;//
		    disp_port(MENU_RECWORKING);
		}
			
        continue_encode();
        break;
    case MSG_REC_PLAY:     //��������¼���ļ�

	  if(work_mode ==IDLE_MODE)
	  	break;

#ifdef REC_PLAY_KEY_BREAK_POINT
	rec_pley_bp_flag=~rec_pley_bp_flag;
	if(rec_pley_bp_flag){
		last_play_index =  given_file_number;
	}
	else{
		given_file_number=last_play_index;
              put_msg_lifo(MSG_MUSIC_PLAY_NEW_FILE);
		break;
	}
#endif
	  
        encode_status = RECODE_PLAY;
        given_device = encode_device & (~VIRTUAL_DEVICE);

        if( (given_device != DEVICE_SDMMC0) && (given_device != DEVICE_UDISK))
        {
            given_device = DEVICE_SDMMC0;
        }
        given_device |= VIRTUAL_DEVICE;
        if((MUSIC_MODE != work_mode))
        {
            put_msg_lifo(MSG_MUSIC_NEW_DEVICE_IN);
        }
        else
        {
            put_msg_lifo(MSG_MUSIC_SELECT_NEW_DEVICE);
        }
        break;

    case MSG_MUSIC_SELECT_NEW_DEVICE:					        //����ѡ���豸

        res = find_device(given_device);

        if ((res == DEV_INIT_ERR) ||
                (res == NO_DEFINE_DEV))                    //ָ�����豸�����ߣ����ʼ��ʧ��
        {
		
            given_device = DEVICE_AUTO_NEXT;			   //�Զ�ѡ����һ���豸
            put_msg_lifo(MSG_MUSIC_SELECT_NEW_DEVICE);
            break;
        }
        else if ((res == NO_EFFECTIVE_DEV) ||
                 (res == NO_DEV_ONLINE))                    //�޿ɲ��ŵ��豸
        {		
            if(RECODE_STOP != encode_status)
            {
                	encode_status = RECODE_STOP;
			if(REC_MIC_MODE == work_mode)
			{
				put_msg_lifo(MSG_NEXT_WORKMODE);
			}
            }
            else
            {	
                //put_msg_lifo(MSG_NEXT_WORKMODE);
                	if(disp_scenario == DISP_NORMAL){
				
				disp_scenario = DISP_RTC_SCEN;
				rtc_disp_hdlr();
			}
            }
            break;
        }
        else
        {		
            if(RECODE_PLAY < encode_status)
            {
                put_msg_lifo(MSG_REC_START);
            }
            else
            {
                if(RECODE_PLAY == encode_status)  //4ȥ����¼�õ��ļ�
                {
                    encode_status = RECODE_STOP;
#if VIRTUAL_ENABLE
#if 1//defined(K820_LHD_820_REC_V001)
                    given_file_number = logic_fileTotal;
#else
			given_file_number = encode_filenum;
#endif
#else
                    given_file_number = logic_fileTotal;
                    //given_file_number = encode_filenum + encode_fristfile -1; 
#endif
                    put_msg_lifo(MSG_MUSIC_PLAY_NEW_FILE);
                }
                else
                {
                    put_msg_lifo(MSG_MUSIC_SELECT_NEW_FILE);		//�ҵ������豸
                }
            }
        }
        break;
//2  REC FSM END



    }
}
