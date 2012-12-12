/*--------------------------------------------------------------------------*/
/**@file    rtc_ui.c
   @brief   RTC用户界面操作
   @details
   @author
   @date   2011-7-5
   @note
*/
/*----------------------------------------------------------------------------*/
#include "rtc_ui.h"

#if RTC_ENABLE
extern RTC_TIME _xdata curr_time;
//extern ALM_TIME _xdata alarm;

//extern u8 _xdata rtc_mode_setting;
extern u8 _xdata rtc_coordinate;
//extern u8 _xdata alm_coordinate;
#if 0
u8 _code rtc_coordinate_tab[][3] =		///<RTC设置界面坐标表,起始X坐标，起始Y坐标，坐标宽度
{
    {RTC_YEAR_COORDINATE,0,32},	///<year coordinate
    {RTC_MONTH_COORDINATE,0,16},	///<month coordinate
    {RTC_DAY_COORDINATE,0,16},	///<day coordinate
    {RTC_HOUR_COORDINATE,2,16},	///<hour coordinate
    {RTC_MIN_COORDINATE,2,16},	///<minutes coordinate
    {RTC_SEC_COORDINATE,2,16},	///<second coordinate
};

u8 _code alm_coordinate_tab[][3] =		///<ALARM设置界面坐标表，起始X坐标，起始Y坐标，坐标宽度
{
    {ALM_SW_COORDINATE,0,24},	 ///<switch coordinate
    {ALM_HOUR_COORDINATE,2,16},	 ///<hour coordinate
    {ALM_MIN_COORDINATE,2,16},	 ///<minutes coordinate
};
#endif


/*----------------------------------------------------------------------------*/
/**@brief 当前日期的加操作
   @param 	void
   @return  void
   @note  void curr_time_plus()
*/
/*----------------------------------------------------------------------------*/
void curr_time_plus(void)
{
#if 0
    if (rtc_coordinate==0)
    {
        curr_time.year+=1;
        if (curr_time.year>2178)	curr_time.year=2000;
    }
    if (rtc_coordinate==1)
    {
        curr_time.month+=1;
        if (curr_time.month>12)		curr_time.month=1;
    }
    if (rtc_coordinate==2)
    {
        curr_time.day+=1;
        if (curr_time.day>nowmonth(curr_time.month,curr_time.year))	curr_time.day=1;
    }
#endif
    if (rtc_coordinate==3)
    {
        curr_time.hour+=1;
        if (curr_time.hour>23)		curr_time.hour=0;
    }
    if (rtc_coordinate==4)
    {
        curr_time.min+=1;
        if (curr_time.min>59)		curr_time.min=0;
    }
    //if (rtc_coordinate==5)
    {
     //   curr_time.sec+=1;
    //    if (curr_time.sec>59)		curr_time.sec=0;
    }

}
/*----------------------------------------------------------------------------*/
/**@brief 当前日期的减操作
   @param 	void
   @return  void
   @note   void curr_time_minus()
*/
/*----------------------------------------------------------------------------*/
void curr_time_minus(void)
{
#if 0
    if (rtc_coordinate == 0)
    {
        curr_time.year -= 1;
        if (curr_time.year < 2000)	curr_time.year = 2178;
    }
    if (rtc_coordinate == 1)
    {
        curr_time.month -= 1;
        if (curr_time.month < 1)	curr_time.month = 12;
    }
    if (rtc_coordinate == 2)
    {
        curr_time.day -= 1;
        if (curr_time.day < 1)	curr_time.day = nowmonth(curr_time.month,curr_time.year);
    }

#endif
    if (rtc_coordinate == 3)
    {
        if (curr_time.hour < 1)	curr_time.hour = 24;
        curr_time.hour -= 1;
    }
    if (rtc_coordinate == 4)
    {
        if (curr_time.min < 1)	curr_time.min = 60;
        curr_time.min -= 1;
    }
    //if (rtc_coordinate == 5)
    {
        //if (curr_time.sec < 1)	curr_time.sec = 60;
        //curr_time.sec -= 1;
    }
}
#if 0
/*----------------------------------------------------------------------------*/
/**@brief 闹钟的加操作
   @param 	num:闹钟序号
   @return  void
   @note   void alm_time_plus(void)
*/
/*----------------------------------------------------------------------------*/
void alm_time_plus(void)
{
    if (alm_coordinate == 0)
    {
        alarm.sw = !alarm.sw;
    }
    if (alm_coordinate == 1)
    {
        alarm.hour += 1;
        if (alarm.hour>23)	alarm.hour = 0;
    }
    if (alm_coordinate == 2)
    {
        alarm.min += 1;
        if (alarm.min > 59)	alarm.min = 0;
    }
}
/*----------------------------------------------------------------------------*/
/**@brief 闹钟的减操作
   @param 	num:闹钟序号
   @return  void
   @note void alm_time_minus(void)
*/
/*----------------------------------------------------------------------------*/
void alm_time_minus(void)
{
    if (alm_coordinate == 0)
    {
        alarm.sw = !alarm.sw;
    }
    if (alm_coordinate == 1)
    {
        if (alarm.hour < 1)	alarm.hour = 24;
        alarm.hour -= 1;
    }
    if (alm_coordinate == 2)
    {
        if (alarm.min < 1)	alarm.min = 60;
        alarm.min -= 1;
    }
}
#endif

#endif