/*--------------------------------------------------------------------------*/
/**@file     blue_tooth.c
   @brief    blue_tooth 任务模块
   @details
   @author
   @date   2011-3-7
   @note
*/
/*----------------------------------------------------------------------------*/
#include "Custom_config.h"


#ifdef USE_BLUE_TOOTH_FUNC			
#include "blue_tooth.h"
#include "disp.h"
#include "dac.h"

extern u8 main_menu, cur_menu, main_menu_conter;

#if defined(BLUE_TOOTH_UART_FUNC)
extern bool bt_frame_rev_finished;
xd_u8 rev_bluetooth_status=0;

extern void blue_tooth_uart_init();
extern void blue_tooth_uart_release();
extern void promt_bt_cmd(AT_PROMPT_CMD cmd);
extern u8 bluetooth_cmd_parse(void);
#endif

xd_u8 bt_play_status=BT_STA_STOP;

xd_u8 spark_timer=0;

#if 0
#define  MSG_BLUETOOTH_PP
#define  MSG_BLUETOOTH_STOP
#define  MSG_BLUETOOTH_NEXT
#define  MSG_BLUETOOTH_PREV
#define  MSG_BLUETOOTH_VOL_UP
#define  MSG_BLUETOOTH_VOL_DOWN
#define  MSG_BLUETOOTH_PAIR
#endif
/*----------------------------------------------------------------------------*/
/**@brief  AUX消息处理
   @param  无
   @return 无
   @note   void deal_aux( void )
*/
/*----------------------------------------------------------------------------*/
void Blue_tooth_hdlr( void )
{
    u8 key=0;
#if defined(BLUE_TOOTH_UART_FUNC)
    u8 cmd_key=0;
    u8 bt_vol_timer=3;

    blue_tooth_uart_init();

#if 0	
    delay_10ms(20);
	
    promt_bt_cmd(BT_VOL_M);

    while(bt_vol_timer>0){

		if(bt_frame_rev_finished){

			bt_frame_rev_finished=0;
			
			cmd_key = bluetooth_cmd_parse();
			if(cmd_key==BT_ACK){
				promt_bt_cmd(BT_VOL_M);
				bt_vol_timer--;
			}	  

		}

		delay_10ms(20);
		if(key++>250){
			bt_vol_timer=0;
			break;
		}
    }	
#endif

#endif

    dac_out_select(DAC_AMUX0,0);
    delay_10ms(20);	
    //Mute_Ext_PA(UNMUTE);

    while (1)
    {
        	dac_out_select(DAC_AMUX0,0);
		//suspend_sdmmc();

		key = get_msg();

#if defined(BLUE_TOOTH_UART_FUNC)

		if(bt_frame_rev_finished){

			bt_frame_rev_finished=0;
			cmd_key = bluetooth_cmd_parse();

			//printf("bluetooth_cmd_parse    cmd_key %x \r\n",(u16)cmd_key);
			
			if(cmd_key<BT_ACK){
				rev_bluetooth_status = cmd_key;
			}
			else if(cmd_key==BT_ACK){

#if 1
				if(bt_play_status==(BT_STA_PLAY|BT_STA_MASK)){
		  			 //Mute_Ext_PA(UNMUTE);
					bt_play_status=BT_STA_PLAY;
				}
#endif				
			}
			else if(cmd_key ==BT_DEV_ISSUE_PLAY){
					bt_play_status=BT_STA_PLAY;
		  			// Mute_Ext_PA(UNMUTE);
			}
		}
#endif		

	switch (key)
        {
        case MSG_CHANGE_WORK_MODE:
            return;        
        case MSG_BLUETOOTH_STOP:
		if((rev_bluetooth_status==BT_CONECTED_A2DP)||(rev_bluetooth_status==BT_CONECTED_AVRCP)){
			bt_play_status=BT_STA_STOP;
			//Mute_Ext_PA(MUTE);
			promt_bt_cmd(BT_STOP);			
		}
		break;
        case MSG_BLUETOOTH_PAIR:
		promt_bt_cmd(BT_DISPAIR);			
		break;
        case MSG_BLUETOOTH_PP:
			
		if((rev_bluetooth_status==BT_CONECTED_A2DP)||(rev_bluetooth_status==BT_CONECTED_AVRCP)){

#if 1			
			if(bt_play_status==BT_STA_PLAY){

				//Mute_Ext_PA(MUTE);
				bt_play_status=BT_STA_PAUSE;
			}
			else if(bt_play_status!=BT_STA_PLAY){
				bt_play_status=BT_STA_PLAY|BT_STA_MASK;
			}
#endif			
			promt_bt_cmd(BT_PLAY);		

		}
		break;
        case MSG_BLUETOOTH_NEXT:
		promt_bt_cmd(BT_NEXT);						
		break;	
        case MSG_BLUETOOTH_PREV:
		promt_bt_cmd(BT_PREV);									
		break;	
        case MSG_BLUETOOTH_VOL_UP:
		//promt_bt_cmd(BT_VOL_P);									
		break;	
        case MSG_BLUETOOTH_VOL_DOWN:
		//promt_bt_cmd(BT_VOL_M);									
		break;	
#if 0		
        case INFO_VOL_PLUS| KEY_SHORT_UP:
		promt_bt_cmd(BT_VOL_P);						
		break;	
        case INFO_VOL_MINUS| KEY_SHORT_UP:
		promt_bt_cmd(BT_VOL_M);									
		break;	
#endif		
        case MSG_200MS :
			
		spark_timer++;		
		if(rev_bluetooth_status==BT_POWER_ON){


			//Mute_Ext_PA(MUTE);

	              if(MENU_MAIN_VOL== cur_menu)break;

			if(spark_timer%4==0){
    				disp_port(MENU_BLUE_TOOTH_MAIN);			
			}
			else{
    				disp_port(MENU_NULL);			
			}
		}
		else if((rev_bluetooth_status==BT_DISCONECT)||(rev_bluetooth_status==BT_PAIR_MODE)||(rev_bluetooth_status==BT_PAIR_MODE)){

	              if(MENU_MAIN_VOL== cur_menu)break;
				  	
			if(spark_timer%2==0){
    				disp_port(MENU_BLUE_TOOTH_MAIN);			
			}
			else{
    				disp_port(MENU_NULL);			
			}
		}
		else if((rev_bluetooth_status==BT_CONECTED_A2DP)||(rev_bluetooth_status==BT_CONECTED_AVRCP)){

			spark_timer=0;
	              if(MENU_NULL == cur_menu){
    				disp_port(MENU_BLUE_TOOTH_MAIN);			
	              }
  			 //Mute_Ext_PA(UNMUTE);
		}	
		break;			
        case MSG_HALF_SECOND :

#if defined(USE_BAT_MANAGEMENT)
	     bmt_hdlr();
#endif

            set_brightness_fade_out();
#ifndef LCD_BACK_LIGHT_DUMMY
	     set_brightness_fade_out();
#endif
            if (main_menu_conter < (SUB_MENU_TIME - 3))
            {
                	main_menu_conter++;
            }
            else if (cur_menu != main_menu)
            {
    			disp_port(MENU_BLUE_TOOTH_MAIN);
	     }
            break;

        default :
            ap_handle_hotkey(key);
                break;
        }
    }
}

/*----------------------------------------------------------------------------*/
/**@brief  AUX功能入口
   @param  无
   @return 无
   @note   void aux_function(void)
*/
/*----------------------------------------------------------------------------*/
void Blue_tooth_main(void)
{

	bt_play_status=BT_STA_STOP;
       main_menu = MENU_BLUE_TOOTH_MAIN;

       //Mute_Ext_PA(MUTE);

	BT_PWR_GPIO_ON();
       SYSTEM_CLK_DIV4();
    	flush_low_msg();
    	disp_port(MENU_BLUE_TOOTH_MAIN);			
		
	delay_10ms(60);		
	set_max_vol(MAX_ANOLOG_VOL, MAX_DIGITAL_VOL);			//设置AUX模式的音量上限
    	Blue_tooth_hdlr();

#if defined(BLUE_TOOTH_UART_FUNC)
	blue_tooth_uart_release();
#endif

       //Mute_Ext_PA(MUTE);
		
	main_vol_set(0, CHANGE_VOL_NO_MEM);
	BT_PWR_GPIO_OFF();
	
}
#endif

