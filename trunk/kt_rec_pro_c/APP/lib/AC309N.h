/*--------------------------------------------------------------------------*/
/**@file    AC309N.h
   @brief   AC309NÍ·ÎÄ¼þ
   @details
   @author
   @date   2011-3-7
   @note
*/
/*----------------------------------------------------------------------------*/

#ifndef _AC309N_
#define _AC309N_


sfr P0 = 0x80;
sfr SP = 0x81;
sfr DP0L = 0x82;
sfr DP0H = 0x83;
sfr CLKCON1 = 0x84;
sfr CLKGAT = 0x85;
sfr CLKCON0 = 0x86;
sfr PCON = 0x87;
sfr DPCON = 0x88;
sfr SPH = 0x89;
sfr DP1L = 0x8A;
sfr DP1H = 0x8B;
sfr BANKSEL = 0x8C;
sfr P4DIR = 0x8D;
sfr P4PU = 0x8E;
sfr P5PU = 0x8F;
sfr P1 = 0x90;
sfr SINT = 0x91;
sfr P0PD = 0x92;
sfr P1PD = 0x93;
sfr P2PD = 0x94;
sfr P3PD = 0x95;
sfr IRTCON = 0x96;
sfr IRTBUF = 0x97;
sfr P5 = 0x98;
sfr ADCDATL = 0x99;
sfr ADCDATH = 0x9A;
sfr PLLCON0 = 0x99;
sfr PLLCON1 = 0x9A;
sfr ADCCON = 0x9B;
sfr P4PD = 0x9C;
sfr IICCON = 0x9D;
sfr IICSTA = 0x9E;
sfr IICBUF = 0x9F;
sfr P2 = 0xA0;
sfr T0CON = 0xA1;
sfr IP0H = 0xA2;
sfr T0CNT = 0xA3;
sfr DACCON0 = 0xA4;
sfr T0PWM = 0xA5;
sfr T2PWML = 0xA6;
sfr T2PWMH = 0xA7;
sfr IE0 = 0xA8;
sfr IE1 = 0xA9;
sfr T2CNTL = 0xAA;
sfr T2CNTH = 0xAB;
sfr DACCON2 = 0xAC;
sfr T2CON = 0xAD;
sfr CKCPRDL = 0xAE;
sfr CKCPRDH = 0xAF;
sfr P3 = 0xB0;
sfr T1CON = 0xB1;
sfr IP1H = 0xB2;
sfr T1CNT = 0xB3;
sfr DACCON1 = 0xB4;
sfr T1PWM = 0xB5;
sfr T3PWML = 0xB6;
sfr T3PWMH = 0xB7;
sfr IP0 = 0xB8;
sfr IP1 = 0xB9;
sfr T3CNTL = 0xBA;
sfr T3CNTH = 0xBB;
sfr DACCON3 = 0xBC;
sfr T3CON = 0xBD;
sfr CKCBEN = 0xBE;
sfr CKCCON = 0xBF;
sfr ADSPPND = 0xC0;
sfr P5DIR = 0xC1;
sfr P0HD = 0xC2;
sfr P1HD = 0xC3;
sfr P2HD = 0xC4;
sfr P3HD = 0xC5;
sfr P4HD = 0xC6;
sfr P5HD = 0xC7;
sfr USBCON0 = 0xC8;
sfr PSW = 0xD0;
sfr SPICON = 0xD1;
sfr P5PD = 0xD2;
sfr SPIBUF = 0xD3;
sfr SPIDMACON = 0xD4;
sfr SPIDMACNT = 0xD5;
sfr SPIDMAADR = 0xD6;
sfr ACC = 0xE0;
sfr P0DIR = 0xE4;
sfr P1DIR = 0xE5;
sfr P2DIR = 0xE6;
sfr P3DIR = 0xE7;
sfr P4 = 0xE8;
sfr UTCON = 0xEA;
sfr UTSTA = 0xEB;
sfr UTBUF = 0xEC;
sfr IE2 = 0xED;
sfr B = 0xF0;
sfr EMICON = 0xF1;
sfr EMIBUF = 0xF2;
sfr CRCFIFO = 0xF3;
sfr P0PU = 0xF4;
sfr P1PU = 0xF5;
sfr P2PU = 0xF6;
sfr P3PU = 0xF7;


sfr CRCREGL = 0xFA;
sfr CRCREGH = 0xFB;

sfr USBCON2 = 0xE9;

//PSW
sbit CY    = 0xD7;
sbit AC    = 0xD6;
sbit F0    = 0xD5;
sbit RS1   = 0xD4;
sbit RS0   = 0xD3;
sbit OV    = 0xD2;
sbit P     = 0xD0;

/*port*/
sbit P00 = P0 ^ 0;
sbit P01 = P0 ^ 1;
sbit P02 = P0 ^ 2;
sbit P03 = P0 ^ 3;
sbit P04 = P0 ^ 4;
sbit P05 = P0 ^ 5;
sbit P06 = P0 ^ 6;
sbit P07 = P0 ^ 7;

sbit P10 = P1 ^ 0;
sbit P11 = P1 ^ 1;
sbit P12 = P1 ^ 2;
sbit P13 = P1 ^ 3;
sbit P14 = P1 ^ 4;
sbit P15 = P1 ^ 5;
sbit P16 = P1 ^ 6;
sbit P17 = P1 ^ 7;


sbit P20 = P2 ^ 0;
sbit P21 = P2 ^ 1;
sbit P22 = P2 ^ 2;
sbit P23 = P2 ^ 3;
sbit P24 = P2 ^ 4;
sbit P25 = P2 ^ 5;
sbit P26 = P2 ^ 6;
sbit P27 = P2 ^ 7;


sbit P30 = P3 ^ 0;
sbit P31 = P3 ^ 1;
sbit P32 = P3 ^ 2;
sbit P33 = P3 ^ 3;
sbit P34 = P3 ^ 4;
sbit P35 = P3 ^ 5;
sbit P36 = P3 ^ 6;
sbit P37 = P3 ^ 7;


sbit P40 = P4 ^ 0;
sbit P41 = P4 ^ 1;
sbit P42 = P4 ^ 2;
sbit P43 = P4 ^ 3;
sbit P44 = P4 ^ 4;
sbit P45 = P4 ^ 5;
sbit P46 = P4 ^ 6;
sbit P47 = P4 ^ 7;

///////////
sbit DPSEL = DPCON ^ 0;
sbit DSP_TOGGLE = DPCON ^3;




/*  IE   */
sbit ET0  = IE0 ^0;
sbit ET1  = IE0 ^1;
sbit ET2  = IE0 ^2;
sbit ET3  = IE0 ^3;
sbit ESPI = IE0 ^4;
sbit EIIC = IE0 ^5;
sbit ESFT = IE0 ^6;
sbit EA   = IE0 ^7;

/*  IP   */
sbit PT0  = IP0 ^0;
sbit PT1  = IP0 ^1;
sbit PT2  = IP0 ^2;
sbit PT3  = IP0 ^3;
sbit PSPI = IP0 ^4;
sbit PIIC = IP0 ^5;
sbit PSFT = IP0 ^6;
sbit PUART = IP0 ^7;

#define SPIBAUD (*(volatile unsigned char xdata *)(0xff00 + 0x03))
#define IRCON0 (*(volatile unsigned char xdata *)(0xff00 + 0x04))
#define IRCON1 (*(volatile unsigned char xdata *)(0xff00 + 0x05))

#define UTBAUD (*(volatile unsigned char xdata *)(0xff00 + 0x0c))
#define IICBAUD (*(volatile unsigned char xdata *)(0xff00 + 0x0d))

#ifdef __C51__
#define LVDCON (*(volatile unsigned char xdata *)(0xff00 + 0x0e))
#else
#define LVDCON (0xff00 + 0x0e)
#endif

#define P0IE (*(volatile unsigned char xdata *)(0xff00 + 0x10))
#define P1IE (*(volatile unsigned char xdata *)(0xff00 + 0x11))
#define P2IE (*(volatile unsigned char xdata *)(0xff00 + 0x12))
#define P3IE (*(volatile unsigned char xdata *)(0xff00 + 0x13))
#define P4IE (*(volatile unsigned char xdata *)(0xff00 + 0x14))
#define P5IE (*(volatile unsigned char xdata *)(0xff00 + 0x15))

#define T0PRD (*(volatile unsigned char xdata *)(0xff00 + 0x20))
#define T1PRD (*(volatile unsigned char xdata *)(0xff00 + 0x21))
#define T2PRD (*(volatile unsigned char xdata *)(0xff00 + 0x22))
#define T3PRD (*(volatile unsigned char xdata *)(0xff00 + 0x23))
#define T0SCA (*(volatile unsigned char xdata *)(0xff00 + 0x24))
#define T1SCA (*(volatile unsigned char xdata *)(0xff00 + 0x25))
#define T2SCA (*(volatile unsigned char xdata *)(0xff00 + 0x26))
#define T3SCA (*(volatile unsigned char xdata *)(0xff00 + 0x27))
#define PWM4CON (*(volatile unsigned char xdata *)(0xff00 + 0x2b))
#define WDTCON (*(volatile unsigned char xdata *)(0xff00 + 0x5a))

#ifdef __C51__
#define enable_interrupt()		EA = 1
#define disable_interrupt()     EA = 0
#endif
#endif
