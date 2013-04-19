/*--------------------------------------------------------------------------*/
/**@file     rtc_api.c
   @brief    RTC接口函数
   @details
   @author
   @date   2011-4-27
   @note
*/
/*----------------------------------------------------------------------------*/
#include "uart.h"
#include "msgfor_usb.h"
#include "dac.h"
#include "eq.h"
#if RTC_ENABLE

#include "rtc_api.h"

RTC_TIME _xdata curr_time;
//ALM_TIME _xdata alarm;
//u8 _xdata alm_cnt;

extern u8 work_mode;
//extern u8 _idata last_work_mode;
extern bool input_number_en;
extern bool eq_change_en;
//extern bool key_voice_en;
extern bool play_mode_change_en;

extern u8 given_device;
extern u16 given_file_number;
extern u8 given_file_method;
extern u8 eq_mode;
extern u8 play_mode;
extern u8  main_menu, cur_menu, main_menu_conter;
//extern bool alm_on_flag;
//extern void write_next_alm_sec(void);

/*----------------------------------------------------------------------------*/
/**@brief 写IRTC
   @param 	cmd：写指令 w_time:写入日期
   @return  void
   @note  void write_irtc(u8 cmd,RTC_TIME *w_time)
*/
/*----------------------------------------------------------------------------*/
void write_irtc(u8 cmd,RTC_TIME *w_time)
{
    u8 _xdata buf;
    //u16 _xdata w_day;
    IRTC_CSEN;
    irtc_sr_byte(cmd);
#if 0
    w_day = ymd_to_day(w_time);
    buf = ((u8 *)(&w_day))[0];
    irtc_sr_byte(buf);
    buf = ((u8 *)(&w_day))[1];
    irtc_sr_byte(buf);
#else
    irtc_sr_byte(0);
    irtc_sr_byte(0);
#endif
    buf = w_time->hour;
    irtc_sr_byte(buf);

    buf = w_time->min;
    irtc_sr_byte(buf);

    buf = w_time->sec;
    irtc_sr_byte(buf);

    IRTC_CSDIS;
}
/*----------------------------------------------------------------------------*/
/**@brief 读IRTC
   @param 	cmd：读指令 r_time：读出的日期
   @return  void
   @note  void read_irtc(u8 cmd,RTC_TIME *r_time)
*/
/*----------------------------------------------------------------------------*/
void read_irtc(u8 cmd,RTC_TIME *r_time)
{
    u16 r_day;

    IRTC_CSEN;
    irtc_sr_byte(cmd);

    ((u8 *)(&r_day))[0] = irtc_sr_byte(0x0);
    ((u8 *)(&r_day))[1] = irtc_sr_byte(0x0);

   // day_to_ymd(r_day,r_time);
    r_time->hour = irtc_sr_byte(0x0);
    r_time->min = irtc_sr_byte(0x0);
    r_time->sec = irtc_sr_byte(0x0);


    IRTC_CSDIS;
}
/*----------------------------------------------------------------------------*/
/**@brief 写RTC
   @param 	void
   @return  void
   @note  void write_rtc(RTC_TIME *curr_time)
*/
/*----------------------------------------------------------------------------*/
void write_rtc(RTC_TIME *curr_time)
{
    write_irtc(WRITE_RTC_SEC,curr_time);
}
/*----------------------------------------------------------------------------*/
/**@brief 读RTC
   @param 	void
   @return  void
   @note  void read_rtc(RTC_TIME *curr_time)
*/
/*----------------------------------------------------------------------------*/
void read_rtc(RTC_TIME *curr_time)
{
    read_irtc(READ_RTC_SEC,curr_time);
}
/*----------------------------------------------------------------------------*/
/**@brief 写ALM
   @param 	void
   @return  void
   @note  void write_alm(RTC_TIME *w_alm)
*/
/*----------------------------------------------------------------------------*/
//void write_alm(RTC_TIME *curr_time_alm)
//{
   // write_irtc(WRITE_RTC_ALM,curr_time_alm);
//}
/*----------------------------------------------------------------------------*/
/**@brief 掉电后RTC RAM清空
   @param 	void
   @return  void
   @note  void reset_rtc_ram(void)
*/
/*----------------------------------------------------------------------------*/
void reset_rtc_ram(void)
{
    u8 i;
    for (i = 0; i < 64; i++)
    {
        write_rtc_ram(i, 0);
    }
}
/*----------------------------------------------------------------------------*/
/**@brief 读ALM
   @param 	void
   @return  void
   @note  void read_alm(RTC_TIME *r_alm)
*/
/*----------------------------------------------------------------------------*/
//void read_alm(RTC_TIME *curr_time_alm)
//{
    //read_irtc(READ_RTC_ALM,curr_time_alm);
//}
/*----------------------------------------------------------------------------*/
/**@brief	开关ALM
   @param 	flag；1：打开闹钟；0：关闭闹钟
   @return  void
   @note  void alm_sw(u8 flag)
*/
/*----------------------------------------------------------------------------*/
#if 0
void alm_sw(u8 flag)
{
    u8 rtc_reg;
    rtc_reg = read_rtc_reg();
    if (flag)
    {
        write_rtc_reg(rtc_reg|BIT(2));
    }
    else
    {
        write_rtc_reg(rtc_reg&~BIT(2));
    }
}
/*----------------------------------------------------------------------------*/
/**@brief 检测ALM
   @param 	void
   @return  void
   @note  void alm_check(void)
*/
/*----------------------------------------------------------------------------*/
void alm_check(void)
{
    if (IRTCON & BIT(7))
    {
        //printf("RTC CON:%u\n",(u16)read_rtc_reg());
        alm_cnt = 1;
        put_msg_lifo(MSG_ALM_ON);
    }
}
#endif
/*----------------------------------------------------------------------------*/
/**@brief 设置RTC Power On
   @param 	sw 电源开关
   @return  void
   @note  void set_rtc_power(u8 sw)
*/
/*----------------------------------------------------------------------------*/
//void set_rtc_power(u8 sw)
//{
#if 0
    u8 rtc_reg;
    rtc_reg = read_rtc_reg();
    if (sw)
    {
        write_rtc_reg(rtc_reg|BIT(3));
    }
    else
    {
        write_rtc_reg(rtc_reg&~BIT(3));
    }
	#endif
//}

/*----------------------------------------------------------------------------*/
/**@brief 设置下一个闹钟，并写入IRTC
   @param 	void
   @return  void
   @note  void set_next_alm_sec(void)
*/
/*----------------------------------------------------------------------------*/
#if 0
void write_next_alm_sec(void)
{
    u8 i;
    RTC_TIME alm_sec;

    if (alarm.sw)
    {
        read_rtc(&curr_time);
        for (i = 0;i < sizeof(RTC_TIME);i++)
        {
            ((u8 *)(&alm_sec))[i] = ((u8 *)(&curr_time))[i];
        }
        alm_sec.sec = 0;

        alm_sec.hour = alarm.hour;
        alm_sec.min = alarm.min;
        if ((alarm.hour < curr_time.hour)||((alarm.hour == curr_time.hour)&&(alarm.min <= curr_time.min)))
            alm_sec.day += 1;
        //Attention！当闹钟没有有效闹钟日期时会写入错误闹钟时间
        write_alm(&alm_sec);
//		read_alm(&alm_sec);
//		printf("Next alarm:%u/%u/%u %u:%u\n",alm_sec.year,(u16)alm_sec.month,(u16)alm_sec.day,(u16)alm_sec.hour,(u16)alm_sec.min);
    }
}
#endif
/*----------------------------------------------------------------------------*/
/**@brief 当前时间复位，2000/1/1 0:0:0
   @param 	void
   @return  void
   @note  void rtc_reset(void)
*/
/*----------------------------------------------------------------------------*/
void rtc_reset(void)
{
    curr_time.year	= 2012;
    curr_time.month = 1;
    curr_time.day = 1;
    curr_time.hour = 0;
    curr_time.min = 0;
    curr_time.sec = 0;

    write_rtc(&curr_time);
    //write_next_alm_sec();
}
/*----------------------------------------------------------------------------*/
/**@brief 日期超限校验
   @param 	void
   @return  void
   @note void chk_date_err(void)
*/
/*----------------------------------------------------------------------------*/
void chk_date_err(void)
{
    if (curr_time.year>2178)
    {
        rtc_reset();
    }
}
/*----------------------------------------------------------------------------*/
/**@brief 保存各个闹钟信息到存储器（EEPROM/RAM）
   @param 	void
   @return  void
   @note  void save_alarm_info(void)
*/
/*----------------------------------------------------------------------------*/
#if 0
void save_alarm_info(void)
{
    write_info(MEM_ALARM_0_HOUR , alarm.hour);
    write_info(MEM_ALARM_0_MIN , alarm.min);

    alm_sw(alarm.sw);//alm_sw(all_alm_sw);
}
/*----------------------------------------------------------------------------*/
/**@brief 读取各个闹钟信息到存储器（EEPROM/RAM）
   @param 	void
   @return  void
   @note  void load_alarm_info(void)
*/
/*----------------------------------------------------------------------------*/
void load_alarm_info(void)
{
    alarm.hour = read_info(MEM_ALARM_0_HOUR );
    if (alarm.hour>23)
    {
        alarm.hour = 12;
    }
    alarm.min = read_info(MEM_ALARM_0_MIN );
    if (alarm.min>59)
    {
        alarm.min = 0;
    }
}

/*----------------------------------------------------------------------------*/
/**@brief 关闭闹钟
   @param 	void
   @return  void
   @note  void close_alarm(void)
*/
/*----------------------------------------------------------------------------*/
void close_alarm(void)
{
    alm_cnt = 0;
    alm_on_flag = 0;
    //set_eq(0);
    key_voice_en = 0;
    //disp_port(main_menu);
}
/*----------------------------------------------------------------------------*/
/**@brief 闹钟响闹
   @param 	void
   @return  闹钟30秒后结束标志位
   @note  bool alarm_on(void)
*/
/*----------------------------------------------------------------------------*/
bool alarm_on(void)
{
    if (alm_cnt >= 60)
    {
        return 0;
    }
    else if (alm_cnt)
    {
        alm_cnt++;
        alarm_tone();
        disp_port(MENU_ALM_UP);
        return 1;
    }
    return 0;
}

/*----------------------------------------------------------------------------*/
/**@brief 闹钟响闹模式循环
   @param 	void
   @return  void
   @note  void alarm_on_mode(void)
*/
/*----------------------------------------------------------------------------*/
void alarm_on_mode(void)
{
    //write_next_alm_sec();
    key_voice_en = 0;

    main_vol_set(0, SET_USE_CURRENT_VOL | CHANGE_VOL_NO_PEND);
}
/*----------------------------------------------------------------------------*/
/**@brief 闹钟响闹时的消息过滤
   @param 	key：系统消息
   @return  转换后闹钟响应的消息
   @note  u8 alm_msg_convert(u8 key)
*/
/*----------------------------------------------------------------------------*/
u8 alm_msg_convert(u8 key)
{
    switch (key)
    {
    case MSG_HALF_SECOND:
        if (alarm_on())
        {
            break;
        }
    case MSG_MUSIC_PP:
        work_mode = last_work_mode;
        put_msg_lifo(MSG_CHANGE_WORK_MODE);
        close_alarm();
        break;


    case MSG_USB_PC_IN:
    case MSG_AUX_IN :
    case MSG_SDMMC_IN :
    case MSG_USB_DISK_IN  :
        close_alarm();
        return key;

    default:
        return NO_MSG;
    }
    return NO_MSG;
}
#endif
/*----------------------------------------------------------------------------*/
/**@brief RTC初始化
   @param 	void
   @return  void
   @note  void rtc_init(void)
*/
/*----------------------------------------------------------------------------*/
void rtc_init(void)
{
    u8 rtc_reg;
    //u8 alm_wkup = 0;


    //alarm.sw = 0;

    rtc_reg = read_rtc_reg();
    if (rtc_reg & BIT(7))					//检测是否掉电
    {
        rtc_reg &= ~(BIT(7)); 				//清零PDFLAG
        rtc_reset();
#if 1//USE_RTC_RAM
        reset_rtc_ram();
#endif
    }
#if 0	
    else
    {
        if (rtc_reg & BIT(2))
        {
            //alarm.sw	= 1;
        }
        if (IRTCON & BIT(7))
        {
            //alm_wkup = 1;
            //alm_cnt = 1;
            //last_work_mode = RTC_MODE;
        }
    }
#endif
    //load_alarm_info();
    ///alm_sw(alarm.sw);		//alm_sw(all_alm_sw);				 //闹钟开关
    read_rtc(&curr_time);
    chk_date_err();
    //write_next_alm_sec();
    write_rtc_reg(rtc_reg);

}
#endif
