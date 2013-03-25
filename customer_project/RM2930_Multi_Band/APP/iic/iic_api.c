/*--------------------------------------------------------------------------*/
/**@file     iic_api.c
   @brief    IIC_API模块
   @details
   @author
   @date   2011-3-7
   @note
*/
/*----------------------------------------------------------------------------*/


#include "iic.h"

bool iic_busy = 0; ///<iic繁忙标记
#define EPPROM_PAGE2	0x02
/*----------------------------------------------------------------------------*/
/**@brief   IIC写函数
   @param   chip_id ：目标IC的ID号
   @param   iic_addr: 目标IC的目标寄存器的地址
   @param   *iic_dat: 写望目标IC的数据的指针
   @param   n:需要写的数据的数目
   @return  无
   @note    void  iic_write(u8 chip_id,u8 iic_addr,u8 *iic_dat,u8 n)
*/
/*----------------------------------------------------------------------------*/
void  iic_write(u8 chip_id,u8 iic_addr,u8 *iic_dat,u8 n)
{
    iic_busy  = 1;
    iic_start();                //I2C启动
    iic_sendbyte(chip_id);         //写命令
    if (0xff != iic_addr)
    {
        iic_sendbyte(iic_addr);   //写地址
    }
    for (;n>0;n--)
    {
        iic_sendbyte(*iic_dat++);      //写数据
    }
    iic_stop();                 //I2C停止时序
    iic_busy = 0;
}
#if(USE_RTC_RAM==0)

/*----------------------------------------------------------------------------*/
/**@brief   IIC总线向一个目标ID读取几个数据
   @param   address : 目标ID
   @param   *p     :  存档读取到的数据的buffer指针
   @param   number :  需要读取的数据的个数
   @return  无
   @note    void i2c_read_nbyte(u8 address,u8 *p,u8 number)
*/
/*----------------------------------------------------------------------------*/
void iic_readn(u8 chip_id,u8 iic_addr,u8 *iic_dat,u8 n)
{

    iic_busy = 1;
    iic_start();                //I2C启动
    iic_sendbyte(chip_id);         //写命令
    if (0xff != iic_addr)
    {
        iic_sendbyte(iic_addr);   //写地址
    }
    for (;n>1;n--)
    {
        *iic_dat++ = iic_revbyte(0);      //写数据
    }
    *iic_dat++ = iic_revbyte(1);
    iic_stop();                 //I2C停止时序
    iic_busy = 0;
}
/*----------------------------------------------------------------------------*/
/**@brief   EEROM读函数
   @param   addr ：要写的EEROM的地址
   @param   无
   @return  无
   @note    u8 iic_read(u8 iic_addr)
*/
/*----------------------------------------------------------------------------*/
u8 read_eerom(u16 iic_addr)
{
    u8  byte,addr=0;

    iic_busy = 1;
    iic_start();                    //I2C启动
    if(iic_addr >255){
	addr =(u8)(iic_addr-255);
    	iic_sendbyte((0xa0|EPPROM_PAGE2));             //写命令
    }
    else{
	addr =(u8)(iic_addr);
    	iic_sendbyte(0xa0);             //写命令
    }
    iic_sendbyte(addr);       //写地址
    iic_start();                    //写转为读命令，需要再次启动I2C
    if(iic_addr >255){
    	iic_sendbyte((0xa1|EPPROM_PAGE2));             //写命令
    }
    else{    
    	iic_sendbyte(0xa1);             //读命令
    }
    byte = iic_revbyte(1);
    iic_stop();                     //I2C停止
    iic_busy = 0;
    return  byte;

}


/*----------------------------------------------------------------------------*/
/**@brief   带有毫秒延时的EEROM写函数
   @param   addr ：要写的EEROM的地址
   @param   dat    ：需要写的数据
   @return  无
   @note    void write_info(u8 addr,u8 dat)
*/
/*----------------------------------------------------------------------------*/
void write_eerom(u16 addr,u8 dat)
{
     u8 u8_addr=0;
	 
    if(addr >255){
	u8_addr =(u8)(addr-255);
    	iic_write((0xa0|EPPROM_PAGE2),u8_addr,&dat,1);
    }
    else{
	u8_addr= (u8)addr;
    	iic_write(0xa0,u8_addr,&dat,1);
    }
    delay_10ms(2);
}
#endif
/*----------------------------------------------------------------------------*/
/**@brief   EEROM/RTC RAM读函数
   @param   addr ：要写的EEROM/RTC RAM的地址
   @return  读到的数据
   @note    u8 read_info(u8 addr)
*/
/*----------------------------------------------------------------------------*/
u8 read_info(u16 addr)
{
#if USE_RTC_RAM
    return read_rtc_ram(addr);
#else

    return read_eerom(addr);
#endif
}
/*----------------------------------------------------------------------------*/
/**@brief   EEROM/RTC RAM写函数
   @param   addr ：要读的EEROM/RTC RAM的地址
   @param   dat    ：需要读的数据
   @return  无
   @note    void write_info(u8 addr,u8 dat)
*/
/*----------------------------------------------------------------------------*/
void write_info(u16 addr,u8 dat)
{
#if USE_RTC_RAM
    //printf("write RAM addr:%u\n",(u16)addr);
    write_rtc_ram(addr,dat);
#else
    //printf("write EEPROM addr:%u\n",(u16)addr);
    write_eerom(addr,dat);
#endif
}

/*----------------------------------------------------------------------------*/
/**@brief   eeprom START
   @param   无
   @return  无
   @note    void  eeprom_page_write_start(void)
*/
/*----------------------------------------------------------------------------*/
void  eeprom_page_write_start(void)
{
    iic_busy  = 1;
    iic_start();                //I2C启动
    iic_sendbyte(0xa0);         //写命令
}
/*----------------------------------------------------------------------------*/
/**@brief   IIC STOP
   @param   无
   @return  无
   @note    void eeprom_page_write_stop(void)
*/
/*----------------------------------------------------------------------------*/
void eeprom_page_write_stop(void)
{
    iic_stop();                     //I2C停止
    iic_busy = 0;
}



