
#include "config.h"
#include "lcd_ht1621_drv.h"

#if defined(USE_LCD_DRV_HT1621)
//GPIO DEF
xd_u8 Ht1621_buf[MAX_SEG_NUM];


#define LCD_spi_gpio_Init()	P3DIR &=~(( BIT(3))|( BIT(1))|( BIT(2)));P3PU |=(( BIT(3))|( BIT(1))|( BIT(2)))

#define LCD_SPI_CS_HIGH()		P33 =1;
#define LCD_SPI_CS_LOW()		P33 =0;
#define LCD_SPI_CLK_HIGH()		P31 =1;
#define LCD_SPI_CLK_LOW()		P31 =0;
#define LCD_SPI_DATA_HIGH()	P32 =1;
#define LCD_SPI_DATA_LOW()		P32 =0;


void Ht1621_Delay(u16 t)
{ 
    while(--t);  
}
void Ht1621_Wr_Data(u8 W_Data, u8 Num) 
{ 
    u8 i; 
    
    for (i = 0; i < Num; i++) 
    {   
        LCD_SPI_CLK_LOW();
	 _nop_();_nop_();
        //Ht1621_Delay(HT1621_BIT_DELAY);
        if(W_Data & 0x80){
            LCD_SPI_DATA_HIGH();
        }
        else{
            LCD_SPI_DATA_LOW();                              
        }
	 _nop_();_nop_();		
        //Ht1621_Delay(HT1621_BIT_DELAY);
        LCD_SPI_CLK_HIGH();
	 _nop_();_nop_();		
        //Ht1621_Delay(HT1621_BIT_DELAY);
        W_Data <<= 1;  
    } 
} 
void Ht1621_Wr_Cmd(u8 Cmd) 
{ 
    LCD_SPI_CS_LOW();
    Ht1621_Delay(HT1621_BIT_DELAY);
    Ht1621_Wr_Data(0x80, 4);               //写入命令标志100 
    Ht1621_Wr_Data(Cmd, 8);                //写入命令数据 
    LCD_SPI_CS_HIGH();
    Ht1621_Delay(HT1621_BIT_DELAY); 
} 
void Ht1621WrAllData(u8 Addr, u8 *buf_p, u8 Num) 
{ 
    u8 i; 
   //EA =0;
    LCD_SPI_CS_LOW();
    Ht1621_Wr_Data(0xa0, 3);           //写入数据标志101 
    Ht1621_Wr_Data(Addr << 2, 6);      //写入地址数据 
    for (i = 0; i < Num; i++) 
    { 
        Ht1621_Wr_Data(*buf_p, 8);         // 写入数据 
        buf_p++; 
    } 
    LCD_SPI_CS_HIGH(); 
    //EA =1;
}

void lcd_ht1621_init(void)
{
    LCD_spi_gpio_Init();
	
    Ht1621_Delay(HT1621_INI_DELAY);      //延时使LCD工作电压稳定 
    Ht1621_Wr_Cmd(HT1621_BIAS); 
    Ht1621_Wr_Cmd(HT1621_RC256);                 //使用内部振荡器 
    Ht1621_Wr_Cmd(HT1621_SYSDIS); 
    Ht1621_Wr_Cmd(HT1621_WDTDIS); 
    Ht1621_Wr_Cmd(HT1621_SYSEN); 
    Ht1621_Wr_Cmd(HT1621_LCDON); 
   //Ht1621_Wr_Cmd(HT1621_LCDOFF); 
    UpdateLcd_HT1621_Buf();
}
extern void updatae_lcd_buf();
void UpdateLcd_HT1621_Buf(void)
{
	LCD_spi_gpio_Init();
    	Lcd_check_buf();
    	Ht1621WrAllData(0x00, Ht1621_buf, MAX_SEG_NUM);
    	//printf("HUpdateLcd_HT_1621_Bufr ...........  \r\n");	
} 
#endif
