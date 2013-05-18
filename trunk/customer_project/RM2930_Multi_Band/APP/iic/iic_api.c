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
#include "uart.h"

bool iic_busy = 0; ///<iic��æ���

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
    u8  byte,addr=0,page=0;

    iic_busy = 1;
    addr=EEPROM_Addr_Align(iic_addr);
    page =EEPROM_Addr_to_Page(iic_addr);
	
    iic_start();                    //I2C����
    iic_sendbyte(0xa0|page);             //д����
    iic_sendbyte(addr);       		//д��ַ
    iic_start();                    			//дתΪ�������Ҫ�ٴ�����I2C
    iic_sendbyte(0xa1|page);             //������
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
     u8 iic_addr=0,page=0;
	 
    iic_addr=EEPROM_Addr_Align(addr);
    page =EEPROM_Addr_to_Page(addr);
	
    iic_write((0xa0|page),iic_addr,&dat,1);
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
   @param   ��
   @return  ��
   @note    void  eeprom_page_write_start(void)
*/
/*----------------------------------------------------------------------------*/
#if 0
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


