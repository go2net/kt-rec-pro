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
#include "uart.h"

bool iic_busy = 0; ///<iic繁忙标记

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
u8 EEPROM_Addr_Align(u16 addr)
{
	u8 r_addr=0;
	
	if(r_addr>0xFF){
		r_addr = (u8)(addr %0xFF);
	}
	else{
		r_addr =  (u8)addr;
	}
	
#ifdef UART_ENABLE
	//deg_str("ADDR_  \n");
	//printf_u16(r_addr, 'A');
#endif

	return r_addr;
}
u8 EEPROM_Addr_to_Page(u16 addr)
{	
	u8 page=0;
	page =(u8)((addr&0xFF00)>>7);
#ifdef UART_ENABLE
	//deg_str("PAGE  \n");
	//printf_u16(page, 'P');
#endif
	//page = (page<<1);
	return (page);
}
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
    u8  byte,addr=0,page=0;

    iic_busy = 1;
    addr=EEPROM_Addr_Align(iic_addr);
    page =EEPROM_Addr_to_Page(iic_addr);
	
    iic_start();                    //I2C启动
    iic_sendbyte(0xa0|page);             //写命令
    iic_sendbyte(addr);       		//写地址
    iic_start();                    			//写转为读命令，需要再次启动I2C
    iic_sendbyte(0xa1|page);             //读命令
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
     u8 iic_addr=0,page=0;
	 
    iic_addr=EEPROM_Addr_Align(addr);
    page =EEPROM_Addr_to_Page(addr);
	
    iic_write((0xa0|page),iic_addr,&dat,1);
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
u8 read_music_info(u16 addr)
{
#if (BREAK_POINT_PLAY_EN == 1)
    return read_rtc_ram(addr);
#else

    return read_eerom(addr);
#endif
}
void write_music_info(u16 addr,u8 dat)
{
#if (BREAK_POINT_PLAY_EN == 1)
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
#if 0
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
#endif
#if 0
void EPPROM_TEST(void)
{
	u16 addr=0,w_data=0,r_data=0;

	deg_str(" EPPROM_TEST START\n");
	
	deg_str(" EPPROM_WRITE START \n");
#if 1
	w_data = 0xA0;

	for(addr=0;addr<0x3FF;){
		
		write_eerom(addr,w_data);
		printf_u16(w_data, 'W');
		printf_u16(addr, 'A');
		addr++;		
		if((addr%0xFF)==0){
			w_data++;
			deg_str(" W --------------- W  \n");
		}
	}

	deg_str(" EPPROM_WRITE END \n");
#endif	
	deg_str(" EPPROM_READ ...   \n");

	for(addr=0;addr<0x3FF;){
		r_data = read_eerom(addr);
		delay_10ms(2);
#ifdef UART_ENABLE
		printf_u16(r_data, 'R');
		printf_u16(addr, 'A');
#endif
		if((addr%0xFF)==0){
			deg_str(" R --------------- R  \n");
		}		

		addr++;
	}	


	deg_str(" EPPROM_TEST END \n");
	
}

#endif


