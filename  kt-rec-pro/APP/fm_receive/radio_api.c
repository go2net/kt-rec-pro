/*--------------------------------------------------------------------------*/
/**@file     fm_receive_api.c
   @brief    FM任务应用接口
   @details
   @author
   @date   2011-3-7
   @note
*/
/*----------------------------------------------------------------------------*/


#include "fm_api.h"
#include "radio_rev.h"
#if 0//(FM_MODULE == 1)

extern u16 frequency;

//u8 fm_addr;	///<在线的FM收量的地址指针

/*
void (_code * _code fm_init[])(void) = {init_rda5807,init_CL6017G};
bool (_code * _code fm_set_fre[])(u16) = {set_fre_rda5807,CL6017G_ValidStop};
void (_code * _code fm_power_off[])(void) = {rda5807_poweroff,CL6017G_PowerOff};
bool (_code * _code fm_read_id[])(void) = {rda5807_read_id,cl6017g_read_id};
void (_code * _code fm_mute[])(u8) = {rda5807_mute,cl6017g_mute};

void (_code * _code fm_init[])(void) 	  = {init_rda5807, 		init_CL6017G, 		Chip_wire2_Initialize, 	KT_FMWakeUp, 		init_QN8035};
bool (_code * _code fm_set_fre[])(u16)    = {set_fre_rda5807, 	CL6017G_ValidStop, 	BK1080_ValidStop,		KT0830EG_ValidStop, QND_RXValidCH};//QND_TuneToCH};set_fre_QN8035};//
void (_code * _code fm_power_off[])(void) = {rda5807_poweroff, 	CL6017G_PowerOff, 	BK1080_PowerDown, 		KT_FMStandby, 		QN8035_powerdown};
bool (_code * _code fm_read_id[])(void)   = {rda5807_read_id, 	cl6017g_read_id, 	BK1080_Read_ID, 		KT0830EG_ChipID, 	QN8035_Read_ID};
void (_code * _code fm_mute[])(u8)        = {rda5807_mute, 		cl6017g_mute, 		BK1080_MUTE, 			KT_FMMute, 			QN8035_MUTE};
void (_code * _code fm_setch[])(u8)	      = {rda5807_setch,     CL6017_setch,       BK1080_setch,           KT0830EG_setch,     QN8035_setch};
//void (_code * _code fm_set_vol[])(u8) = {0};
*/

/*----------------------------------------------------------------------------*/
/**@brief   FM模块初始化接口函数
   @param
   @return
   @note    void init_fm_rev(void)
*/
/*----------------------------------------------------------------------------*/
bool init_fm_rev(void)
{
#if 0
    for (fm_addr = 0; fm_addr < (sizeof(fm_read_id)/2); fm_addr++)
    {
        if ((*fm_read_id[fm_addr])())
        {
            (* fm_init[fm_addr])();

            return TRUE;
        }
    }

    fm_addr = 0xff;
    return FALSE;
#endif	
}

#if 0

/*----------------------------------------------------------------------------*/
/**@brief   关闭FM模块电源
   @param
   @return
   @note    void fm_rev_powerdown(void
*/
/*----------------------------------------------------------------------------*/
void fm_rev_powerdown(void)
{
    //(* fm_power_off[fm_addr])();
}
#endif

#if 0

/*----------------------------------------------------------------------------*/
/**@brief   设置一个FM频点的接口函数
   @param   mode = 0: 使用frequency中的值，= 1:频点加1， = 2:频点减1
   @return  1：有台；0：无台
   @note    bool set_fre(u16 fre, u8 mode)
*/
/*----------------------------------------------------------------------------*/
bool set_fre(u8 mode)
{
#if 0
    if (mode == FM_FRE_INC)
    {
        frequency++;
    }
    else if (mode == FM_FRE_DEC)
    {
        frequency--;
    }
    if (frequency > radio_freq_tab[cur_sw_fm_band].MAX_FREQ)
        frequency = radio_freq_tab[cur_sw_fm_band].MIN_FREQ;
    if (frequency < radio_freq_tab[cur_sw_fm_band].MIN_FREQ)
        frequency = radio_freq_tab[cur_sw_fm_band].MIN_FREQ;
   // return (* fm_set_fre[fm_addr])(frequency);
   #endif
}
#endif

/*----------------------------------------------------------------------------*/
/**@brief   FM模块Mute开关
   @param   flag：Mute使能位
   @return  无
   @note    void fm_module_mute(u8 flag)
*/
/*----------------------------------------------------------------------------*/
void fm_module_mute(u8 flag)
{
    //(* fm_mute[fm_addr])(flag);
}

/*----------------------------------------------------------------------------*/
/**@brief   设置一个FM频点的接口函数
   @param   mode = 0: 使用frequency中的值，= 1:频点加1， = 2:频点减1
   @return  1：有台；0：无台
   @note    bool set_fre(u16 fre, u8 mode)
*/
/*----------------------------------------------------------------------------*/
void fm_set_ch(u8 db)
{
    //(* fm_setch[fm_addr])(db);
}

#endif
