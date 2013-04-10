/*--------------------------------------------------------------------------*/
/**@file     uart.c
   @brief    ´®¿Ú´òÓ¡Çý¶¯
   @details
   @author
   @date   2011-4-26
   @note
*/
/*----------------------------------------------------------------------------*/
#include "Custom_config.h"

#include "uart.h"
#include "resource.h"

#if defined(UART_ENABLE)

void uart_init(void)
{
    P0PU = 0;
    P0PD = 0;
    UTBAUD = (48000000/(8 * 115200)) - 1;	//25;//0x37;					/* 25: cpu 24M, 115200bps*/	/*77 for 384*/ /*0x137 for 9600*/
#if defined(USE_UART_P24_P25)
    P2DIR &= 0xef;							/* P24 for transmit */
    P2DIR |= 0x20;							/* P25 for receive */
    UTCON = 0x41;							/* enable uart */
#else
    UTCON = 0x01;							/* enable uart */
    P0DIR &= 0xBF;							/* P06 for transmit */
    P0DIR |= 0x80;							/* P07 for receive */
#endif	
}

#pragma disable
void putbyte(char c)
{
    
    while (!(UTSTA & 0x80))
    {
    }
    UTBUF = c;
}

char putchar (char c)
{
    if (c == '\n')
    {
        putbyte(0x0d);
        putbyte(0x0a);
    }
    else
    {
        putbyte(c);
    }

    return (c);
}

//void printf_buf(u8 _xdata *buf, u16 len)
//{
//    u16 i;
//
//    printf(":%04X", (u16)buf);
//    for (i = 0; i < len; i++)
//    {
//        if ((i % 16) == 0)
//            printf("\n");
//        printf("%02bX ", buf[i]);
//    }
//
//    printf("\n");
//}


void deg_str(u8 *p)
{
uart_init();
   while(*p)
   {
       putchar(*p);
       p++;
   }
}




void get_hex_data(u8 dat)
{
   u8 dat0;
   if(dat<0x0a)
   {
       dat0 = dat+'0';
   }
   else
   {
       dat0 = dat+'A'-10;
   }
   putchar(dat0);
}
void printf_u16(u16 dat,u8 c)
{
	uart_init();

    putchar(' ');
    get_hex_data(((u8 *)(&dat))[0] >> 4);
    get_hex_data(((u8 *)(&dat))[0] & 0xf);

    get_hex_data(((u8 *)(&dat))[1] >> 4);
    get_hex_data(((u8 *)(&dat))[1] & 0xf);
    putchar(' ');
	    putchar(c);

	putchar('\r');
	putchar('\n');
}

/*
void printf_u32(u32 dat)
{
    putchar(' ');
    get_hex_data(((u8 *)(&dat))[0] >> 4);
    get_hex_data(((u8 *)(&dat))[0] & 0xf);

    get_hex_data(((u8 *)(&dat))[1] >> 4);
    get_hex_data(((u8 *)(&dat))[1] & 0xf);

    get_hex_data(((u8 *)(&dat))[2] >> 4);
    get_hex_data(((u8 *)(&dat))[2] & 0xf);

    get_hex_data(((u8 *)(&dat))[3] >> 4);
    get_hex_data(((u8 *)(&dat))[3] & 0xf);
    putchar(' ');
}

void printf_u8(u8 dat)
{
    putchar(' ');
    get_hex_data(dat >> 4);
    get_hex_data(dat & 0xf);
    putchar(' ');
	//putchar('\n');
}
*/
#endif
