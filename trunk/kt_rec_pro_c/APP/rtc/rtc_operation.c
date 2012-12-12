/*--------------------------------------------------------------------------*/
/**@file     rtc_operation.c
   @brief    RTC算法功能函数
   @details
   @author
   @date   2011-4-26
   @note
*/
/*----------------------------------------------------------------------------*/
#if 0
#include "rtc_operation.h"

/*******************************************************
				CONST
********************************************************/
//const u16 year_tab[]={365,366};
u8 _code month_tab1[] = {31,28,31,30,31,30,31,31,30,31,30,31};		   ///<非闰年每月的天数
u8 _code month_tab2[] = {31,29,31,30,31,30,31,31,30,31,30,31};		   ///<闰年每月的天数

//                         1  2  3  4   5   6   7   8   9   10  11  12
u16 _code smonth_tab1[]={0,31,59,90,120,151,181,212,243,273,304,334,365};	   ///<非闰年的当月累计天数
u16 _code smonth_tab2[]={0,31,60,91,121,152,182,213,244,274,305,335,366};	   ///<	闰年的当月累计天数

//char calendar[][10]={"Sunday","Monday","Tuesday","Wednesday","Thursday","Friday","Saturday"};


/*----------------------------------------------------------------------------*/
/**@brief	判断闰年
   @param 	year:年份
   @return  真假
   @note	bool leapyear(u16 year)
*/
/*----------------------------------------------------------------------------*/
#if 1
bool leapyear(u16 year)
{
    if ((year%4==0 && year%100!=0)||(year%400==0))
        return TRUE;
    else
        return FALSE;
}
#endif
/*----------------------------------------------------------------------------*/
/**@brief	总日数换算为星期的日数
   @param 	day：总日数
   @return  星期的日数
   @note	u8 day_to_weekday(u16 day)
*/
/*----------------------------------------------------------------------------*/
#if 1
u8 day_to_weekday(u16 day)
{
    u16 tmp;
    u8 weekday;

    tmp = day + DATE;
    weekday = tmp % 7;

    if (tmp < 7)
        return tmp;
    else if (weekday)
        return (tmp % 7);
    else
        return 7;
}
#endif
/*----------------------------------------------------------------------------*/
/**@brief	年份换算为天数
   @param 	day：总日数
   @return  星期的日数
   @note	u16 year_to_day(u16 year)
*/
/*----------------------------------------------------------------------------*/
#if 1
u16 year_to_day(u16 year)
{
    if (leapyear(year))
        return 366;
    else
        return 365;
}
#endif
/*----------------------------------------------------------------------------*/
/**@brief 当月的天数
   @param 	nmonth：当月月份；nyear：当年年份
   @return  当月天数
   @note u8 nowmonth(u8 nmonth,u16 nyear)
*/
/*----------------------------------------------------------------------------*/
#if 1
u8 nowmonth(u8 nmonth,u16 nyear)
{
    if (leapyear(nyear))
        return month_tab2[nmonth-1];
    else
        return month_tab1[nmonth-1];

}
#endif
/*----------------------------------------------------------------------------*/

/**@brief	月份换算为天数
   @param 	day：总日数
   @return  星期的日数
   @note	u8 month_to_day(u8 month)
*/
/*----------------------------------------------------------------------------*/
#if 1
u16 month_to_day(u16 year,u8 month)
{
    if (leapyear(year))
        return smonth_tab2[month];
    else
        return smonth_tab1[month];
}
#endif
/*----------------------------------------------------------------------------*/
/**@brief	总天数换算为年份/月份/日期
   @param 	day：总天数；time:当前日期
   @return  星期的天数
   @note	void day_to_ymd(u16 day,RTC_TIME *rtc_time)
*/
/*----------------------------------------------------------------------------*/
void day_to_ymd(u16 day,RTC_TIME *rtc_time)
{
    u8 tmp;

    rtc_time->weekday = day_to_weekday(day);

    tmp = 0;
    while (day >= year_to_day(YEAR+tmp))
    {
        day -= year_to_day(YEAR+tmp);
        tmp++;
    }
    rtc_time->year = YEAR+tmp;

    tmp = 0;
    while (day >= month_to_day(rtc_time->year,MONTH+tmp))
    {
        tmp++;
    }
    day -= month_to_day(rtc_time->year,MONTH+tmp-1);
    rtc_time->month = MONTH+tmp;

    rtc_time->day = DAY+day;
}

/*----------------------------------------------------------------------------*/
/**@brief	当前年份/月份/日期换算成总天数
   @param 	time:当前日期
   @return  星期的天数
   @note	u16 ymd_to_day(RTC_TIME *time,u16 day)
*/
/*----------------------------------------------------------------------------*/
u16 ymd_to_day(RTC_TIME *time)
{
    u16 _xdata tmp_year;
    u16 _xdata tmp_day = 0;

    for (tmp_year=YEAR;tmp_year<time->year;tmp_year++)			//年->日，当年不算在内，所以是<
    {
        tmp_day += year_to_day(tmp_year);
    }

    if (leapyear(time->year))						//月->日
        tmp_day += smonth_tab2[time->month-1];
    else
        tmp_day += smonth_tab1[time->month-1];

    tmp_day += (time->day-1);						//日->日,当日不算在内，所以日应该减1
    return tmp_day;
}
#endif