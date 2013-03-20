/*! \page0  CPU 编程指南
*
* -APP memory
*   -# DATA  0x18 ~ 0x7F\n
*   -# IDATA 0x80 ~ 0xFF\n
*   -# XDATA 0x300 ~ 0x307F\n
堆栈   0x3600 ~ 0x36FF(256B)\n
文件系统缓存  0X700 ~ 0X8FF(512B)\n
音频解码缓存  0X2880 ~ 0X30FF(2048B)\n
*   -# PDATA 0x80 ~ 0xFF\n
*   -# CODE  0x3000 ~ 0x7FDF\n
*   -# CONST 0x3000 ~ 0x7FDF\n
*   -# DATA 0x0 ~ 0xFF
*   -# CODE 0x0 ~ 0x57FF for APP
*
* - interrupt
*   -# TIMER0         0
*   -# TIMER1         1
*   -# TIMER2         2
*   -# TIMER3         3
*   -# UART           7
*   -# PORT           8
*   -# SPI_EMI DMA    11
*   -# LVD_RTC_IIC    15

*
* - clock system
* - CLKCON0(reset:0x21)\n
* - CLKCON1(reset:0x01)\n
*
* - PCON(reset:0x00)\n
*   BIT0  :SLEEP，高有效\n
*   BIT1  :SYSD3SEL，解码时钟除2选择，高有效\n
*   BIT2  :MP3D2SEL，MP3时钟除2选择，高有效\n
*   BIT3  :OTPD2SEL，OTP时钟除2选择，高有效\n
*   BIT6  :IDLE，高有效，这个寄存器写1会使CPU时钟暂停，直到外设中断唤醒\n
*   BIT7  :HOLD，高有效，全部时钟暂停，高有效\n
（注：当SYSD2SEL写1时，MP3D2SEL和OTPD2SEL也会自动变为1，保证MP3和OTP时钟不会比SYS时钟快）\n
*/