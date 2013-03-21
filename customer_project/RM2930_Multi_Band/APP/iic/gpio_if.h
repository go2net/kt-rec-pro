/*--------------------------------------------------------------------------*/
/**@file     gpio_if.h
   @brief    gpio if
   @details
   @author
   @date   2010-12-13
   @note
*/
/*----------------------------------------------------------------------------*/
#include "config.h"

#ifndef _GPIO_IF_H_
#define _GPIO_IF_H_

//#include "Custom_config.h"

#if defined(LED_GPIO_USE_P16)
#define led_gpio_init()			P1DIR &= ~(BIT(6));P1PU &= ~(BIT(6))
#define LED_GPIO_CTRL_OFF()		P16 = 0
#define LED_GPIO_CTRL_ON()		P16 = 1
#elif defined(LED_GPIO_USE_P01)
#define led_gpio_init()			P0DIR &= ~(BIT(1));P0PU &= ~(BIT(1));P0PD &= ~(BIT(1))
#define LED_GPIO_CTRL_OFF()		P01 = 0
#define LED_GPIO_CTRL_ON()		P01 = 1
#elif defined(LED_GPIO_USE_P25)
#define led_gpio_init()			P2DIR &= ~(BIT(5));P2PU &= ~(BIT(5));P2PD &= ~(BIT(5))
#define LED_GPIO_CTRL_OFF()		P25 = 0
#define LED_GPIO_CTRL_ON()		P25 = 1 
#elif defined(LED_GPIO_USE_P07)
#define led_gpio_init()			P0DIR &= ~(BIT(7));P0PU &= ~(BIT(7));P0PD &= ~(BIT(7))
#define LED_GPIO_CTRL_OFF()		P07 = 0
#define LED_GPIO_CTRL_ON()		P07 = 1 
#else
#define led_gpio_init()			 
#define LED_GPIO_CTRL_OFF()		 
#define LED_GPIO_CTRL_ON()		
#endif

// msgfor_hot.c
#ifdef MUTE_CTRL_LEVEL_NORMAL
#define MUTE_LEVEL		1
#define UNMUTE_LEVEL	0
#else
#define MUTE_LEVEL		0
#define UNMUTE_LEVEL	1
#endif



#if defined(MUTE_PORT_USE_DUMP)
#define SET_MUTE_PORT_DIR()		
#define SET_MUTE_PORT_PU() 			
#define MUTE_PORT_HIGH()			
#define MUTE_PORT_LOW()	
#elif defined( MUTE_PORT_USE_P01)
#define AMP_MUTE_PORT_INIT() 	 P0DIR &= ~(BIT(1));P0PU &= ~(BIT(1));P0PD &= ~(BIT(1))
#define AMP_MUTE_DISABLE() 	 	 P01 = UNMUTE_LEVEL
#define AMP_MUTE_ENABLE() 	 	 P01 = MUTE_LEVEL
#elif defined( MUTE_PORT_USE_P03)
#define AMP_MUTE_PORT_INIT() 	 P0DIR &= ~(BIT(3));P0PU &= ~(BIT(3));P0PD &= ~(BIT(3))
#define AMP_MUTE_DISABLE() 	 	 P03 = UNMUTE_LEVEL
#define AMP_MUTE_ENABLE() 	 	 P03 = MUTE_LEVEL
#elif defined(MUTE_PORT_USE_WKUP)
//dummy
#elif defined(MUTE_PORT_USE_P25)
#define AMP_MUTE_PORT_INIT() 	 P2DIR &= ~(BIT(5));P2PU &= ~(BIT(5));P2PD &= ~(BIT(5))
#define AMP_MUTE_DISABLE() 	 	 P25 = UNMUTE_LEVEL
#define AMP_MUTE_ENABLE() 	 	 P25 = MUTE_LEVEL
#else
#define AMP_MUTE_PORT_INIT() 	
#define AMP_MUTE_DISABLE() 	 	 
#define AMP_MUTE_ENABLE() 	 	 
#endif


#if 1
//4 ----- IIC ¡£H
#if defined(IIC_GPIO_USE_P00_P01)
#define iic_data_out()    	P0DIR &= ~(BIT(0));P0PU |= BIT(0) 	
#define iic_data_in()     	P0DIR |= (BIT(0));P0PU |= BIT(0)	
#define iic_data_r()      	P00
#define iic_data_h()      	P00 = 1
#define iic_data_l()      	P00 = 0

#define iic_clk_out()    	P0DIR &= ~(BIT(1));P0PU |= (BIT(1))
#define iic_clk_h()      	P01 = 1
#define iic_clk_l()      		P01 = 0
#elif defined(IIC_GPIO_USE_P00_P07)
#define iic_data_out()    	P0DIR &= ~(BIT(0));P0PU |= BIT(0) 	
#define iic_data_in()     	P0DIR |= (BIT(0));P0PU |= BIT(0)	
#define iic_data_r()      	P00
#define iic_data_h()      	P00 = 1
#define iic_data_l()      	P00 = 0

#define iic_clk_out()    	P0DIR &= ~(BIT(7));P0PU |= (BIT(7))
#define iic_clk_h()      	P07 = 1
#define iic_clk_l()      		P07= 0
#elif defined(IIC_GPIO_USE_P01_P00)
#define iic_data_out()    	P0DIR &= ~(BIT(1));P0PU |= BIT(1) 	
#define iic_data_in()     	P0DIR |= (BIT(1));P0PU |= BIT(1)	
#define iic_data_r()      	P01
#define iic_data_h()      	P01 = 1
#define iic_data_l()      	P01 = 0

#define iic_clk_out()    	P0DIR &= ~(BIT(0));P0PU |= (BIT(0))
#define iic_clk_h()      	P00 = 1
#define iic_clk_l()      		P00 = 0

#elif defined(IIC_GPIO_USE_P05_P17)
#define iic_data_out()    	P1DIR &= ~(BIT(7));P1PU |= (BIT(7))
#define iic_data_in()      	P1DIR |= (BIT(7));P1PU |= (BIT(7))
#define iic_data_r()       	P17
#define iic_data_h()      	P17 = 1
#define iic_data_l()        	P17 = 0

#define iic_clk_out()     	P0DIR &= ~(BIT(5));P0PU |= (BIT(5))
#define iic_clk_h()        	P05 = 1
#define iic_clk_l()         	P05 = 0
#elif defined(IIC_GPIO_USE_P02_P03)
#define iic_data_out()    	P0DIR &= ~(1<<2);P0PU |= (1<<2)
#define iic_data_in()     	P0DIR |= (1<<2);P0PU |= (1<<2)
#define iic_data_r()      	P02
#define iic_data_h()      	P02 = 1
#define iic_data_l()      	P02 = 0

#define iic_clk_out()    	P0DIR &= ~(1<<3);P0PU |= (1<<3)
#define iic_clk_h()      	P03 = 1
#define iic_clk_l()      		P03 = 0
#else
#define iic_data_out()   	P1DIR &= ~(1<<6);//P0PU |= (1<<2)
#define iic_data_in()    	P1DIR |= (1<<6);P1PU |= (1<<6)
#define iic_data_r()     	P16
#define iic_data_h()     	P16 = 1
#define iic_data_l()     	P16 = 0
	
#define iic_clk_out()    	P1DIR &= ~(1<<7);//P0PU |= (1<<3)
#define iic_clk_h()      	P17 = 1
#define iic_clk_l()      		P17 = 0
#endif
#endif



//4 ----- LCD ¡£H
#if 0
#define LCD_BL_INIT()	P1DIR &= ~(BIT(0));P1PU |=BIT(0); P1|=(BIT(0))
#define LCD_BL_GPIO_H()	P1|=(BIT(0))
#define LCD_BL_GPIO_L()	P1&=~(BIT(0))

#define LCDPORT_OUT()  LCD_DATA_OUT;LCD_CLK_OUT;LCD_A0_OUT;LCD_RES_OUT;LCD_CS_OUT;//P1DIR &= ~( BIT(7)|BIT(6) );P3DIR &= ~( BIT(0) | BIT(1) | BIT(2) ) 
#define LCDPORT_H()    P1 |= ( BIT(7)|BIT(6) );LCD_A0_H;  LCD_RES_H;	LCD_CS_H;

#define LCD_DATA_OUT P1DIR &= ~(BIT(7));P1PU |= BIT(7)//7 
#define	LCD_CLK_OUT	 P1DIR &= ~(BIT(6));P1PU |= BIT(6)//6

#define	LCD_A0_OUT	  P1DIR &= ~(BIT(3));P1PU |= BIT(3)
#define	LCD_A0_L	  P13 = 0      //P0 &= ~BIT(5)
#define	LCD_A0_H	  P13 = 1      //P0 |= BIT(5)

#define LCD_RES_OUT	  P1DIR &= ~(BIT(2));
#define LCD_RES_L	  P12 = 0      //P3 &= ~BIT(2)
#define LCD_RES_H	  P12 = 1      //P3 |= BIT(2)

#define LCD_CS_OUT	  P1DIR &= ~(BIT(1));P1PU |= BIT(1)
#define LCD_CS_L	  P11 = 0      //P0 &= ~BIT(4)
#define LCD_CS_H	  P11 = 1      //P0 |= BIT(4)


#define SPIDMAISRDIS()  IE1 &= ~(BIT(3))
#define SPIDMAISREN()	IP1 |= BIT(3), IE1 |= BIT(3)
#endif
//4 ----- KEY ¡£H

#define ADC_KEY_IO6    0xFE
#define ADC_KEY_IO7    0xFF
#define ADC_KEY_IO5    0xFD
#define ADC_KEY_IO4    0xFC
#define ADC_KEY_IO3    0xFB
#define ADC_KEY_IO2    0xFA
#define ADC_VDD_12     0xF8
#define ADC_LDOIN        0xF9
#define ADC_MAX_USED   (0x03+1)

#if defined(USE_LCD_DRV_HT1621)
#define  LCD_BACKLIGHT_INIT()	  P0DIR &=~(BIT(4));P0PU|= (BIT(4))
#define LCD_BACKLIGHT_ON()		P04 =0;
#define LCD_BACKLIGHT_OFF()		P04 =1;
#endif


#ifdef LCD_BACK_LIGHT_USE_P06
#define  LCD_BACKLIGHT_INIT()	  P0DIR &=~(BIT(6));P0PU|= (BIT(6))
#define LCD_BACKLIGHT_ON()		P06 =0
#define LCD_BACKLIGHT_OFF()		P06=1
#elif defined(LCD_BACK_LIGHT_USE_P03)
#define  LCD_BACKLIGHT_INIT()	  P0DIR &=~(BIT(3));P0PU|= (BIT(3))
#define LCD_BACKLIGHT_ON()		P03 =0
#define LCD_BACKLIGHT_OFF()		P03=1
#elif defined(LCD_BACK_LIGHT_USE_P05)
#define  LCD_BACKLIGHT_INIT()	  P0DIR &=~(BIT(5));P0PU|= (BIT(5))
#define LCD_BACKLIGHT_ON()		  P05 =0
#define LCD_BACKLIGHT_OFF()		  P05=1
#elif defined(LCD_BACK_LIGHT_DUMMY)
#define  LCD_BACKLIGHT_INIT()	  
#define LCD_BACKLIGHT_ON()		
#define LCD_BACKLIGHT_OFF()		
#else
#define  LCD_BACKLIGHT_INIT()	  P0DIR &=~(BIT(4));P0PU|= (BIT(4))
#define LCD_BACKLIGHT_ON()		P04 =0
#define LCD_BACKLIGHT_OFF()		P04 =1
#endif


#define PLAY_LED_GPIO_INIT()		P0DIR &= ~(BIT(4));P0PU |=BIT(4);
#define PLAY_LED_ON()				P04=1
#define PLAY_LED_OFF()				P04=0

//#define HDMI_SRC_GPIO_INIT()		P3DIR &= ~(BIT(4));P3PU |=BIT(4); 
//#define SRC_HDMI_1_EN()		P3|=(BIT(4))
//
//#define SRC_HDMI_2_EN()		P3&=~(BIT(4))

#define KT_RF_AP_POWER_INIT()			P0DIR &= ~(BIT(6));P0PU |=BIT(6);
#define KT_RF_AP_POWER_ON()			P06=1
#define KT_RF_AP_POWER_OFF()			P06=0

#define SYS_POWER_ON()			P0DIR &= ~(BIT(4));P0PU |=BIT(4);P04=1
#define SYS_POWER_OFF()			P0DIR &= ~(BIT(4));P0PU |=BIT(4);P04=0

#if defined(ADKEY_PORT_P06)
#define ADKEY_PORT		P06
#elif defined(ADKEY_PORT_P02)
#define ADKEY_PORT		P02
#else
#define ADKEY_PORT		P07
#endif

#endif
