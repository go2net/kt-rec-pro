/*--------------------------------------------------------------------------*/
/**@file     iic_api.c
   @brief    IIC_APIģ��
   @details
   @author
   @date   2011-3-7
   @note
*/
/*----------------------------------------------------------------------------*/


#include "iic.h"

bool iic_busy = 0; ///<iic��æ���
#define EPPROM_PAGE2	0x02
/*----------------------------------------------------------------------------*/
/**@brief   IICд����
   @param   chip_id ��Ŀ��IC��ID��
   @param   iic_addr: Ŀ��IC��Ŀ��Ĵ����ĵ�ַ
   @param   *iic_dat: д��Ŀ��IC�����ݵ�ָ��
   @param   n:��Ҫд�����ݵ���Ŀ
   @return  ��
   @note    void  iic_write(u8 chip_id,u8 iic_addr,u8 *iic_dat,u8 n)
*/
/*----------------------------------------------------------------------------*/
void  iic_write(u8 chip_id,u8 iic_addr,u8 *iic_dat,u8 n)
{
    iic_busy  = 1;
    iic_start();                //I2C����
    iic_sendbyte(chip_id);         //д����
    if (0xff != iic_addr)
    {
        iic_sendbyte(iic_addr);   //д��ַ
    }
    for (;n>0;n--)
    {
        iic_sendbyte(*iic_dat++);      //д����
    }
    iic_stop();                 //I2Cֹͣʱ��
    iic_busy = 0;
}
#if(USE_RTC_RAM==0)

/*----------------------------------------------------------------------------*/
/**@brief   IIC������һ��Ŀ��ID��ȡ��������
   @param   address : Ŀ��ID
   @param   *p     :  �浵��ȡ�������ݵ�bufferָ��
   @param   number :  ��Ҫ��ȡ�����ݵĸ���
   @return  ��
   @note    void i2c_read_nbyte(u8 address,u8 *p,u8 number)
*/
/*----------------------------------------------------------------------------*/
void iic_readn(u8 chip_id,u8 iic_addr,u8 *iic_dat,u8 n)
{

    iic_busy = 1;
    iic_start();                //I2C����
    iic_sendbyte(chip_id);         //д����
    if (0xff != iic_addr)
    {
        iic_sendbyte(iic_addr);   //д��ַ
    }
    for (;n>1;n--)
    {
        *iic_dat++ = iic_revbyte(0);      //д����
    }
    *iic_dat++ = iic_revbyte(1);
    iic_stop();                 //I2Cֹͣʱ��
    iic_busy = 0;
}
/*----------------------------------------------------------------------------*/
/**@brief   EEROM������
   @param   addr ��Ҫд��EEROM�ĵ�ַ
   @param   ��
   @return  ��
   @note    u8 iic_read(u8 iic_addr)
*/
/*----------------------------------------------------------------------------*/
u8 read_eerom(u16 iic_addr)
{
    u8  byte,addr=0;

    iic_busy = 1;
    iic_start();                    //I2C����
    if(iic_addr >255){
	addr =(u8)(iic_addr-255);
    	iic_sendbyte((0xa0|EPPROM_PAGE2));             //д����
    }
    else{
	addr =(u8)(iic_addr);
    	iic_sendbyte(0xa0);             //д����
    }
    iic_sendbyte(addr);       //д��ַ
    iic_start();                    //дתΪ�������Ҫ�ٴ�����I2C
    if(iic_addr >255){
    	iic_sendbyte((0xa1|EPPROM_PAGE2));             //д����
    }
    else{    
    	iic_sendbyte(0xa1);             //������
    }
    byte = iic_revbyte(1);
    iic_stop();                     //I2Cֹͣ
    iic_busy = 0;
    return  byte;

}


/*----------------------------------------------------------------------------*/
/**@brief   ���к�����ʱ��EEROMд����
   @param   addr ��Ҫд��EEROM�ĵ�ַ
   @param   dat    ����Ҫд������
   @return  ��
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
/**@brief   EEROM/RTC RAM������
   @param   addr ��Ҫд��EEROM/RTC RAM�ĵ�ַ
   @return  ����������
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
/**@brief   EEROM/RTC RAMд����
   @param   addr ��Ҫ����EEROM/RTC RAM�ĵ�ַ
   @param   dat    ����Ҫ��������
   @return  ��
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
   @param   ��
   @return  ��
   @note    void  eeprom_page_write_start(void)
*/
/*----------------------------------------------------------------------------*/
void  eeprom_page_write_start(void)
{
    iic_busy  = 1;
    iic_start();                //I2C����
    iic_sendbyte(0xa0);         //д����
}
/*----------------------------------------------------------------------------*/
/**@brief   IIC STOP
   @param   ��
   @return  ��
   @note    void eeprom_page_write_stop(void)
*/
/*----------------------------------------------------------------------------*/
void eeprom_page_write_stop(void)
{
    iic_stop();                     //I2Cֹͣ
    iic_busy = 0;
}



