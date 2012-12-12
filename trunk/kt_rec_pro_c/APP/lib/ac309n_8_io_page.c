/*! \page PORT PORT指南
 *
 * \section intro_sec_port PORT 总体介绍
 *
 * - AC309N 有P0、P1、P2、P3
 *
 * \subsection  PORT 寄存器-介绍
 * - Port寄存器Reset值：\n
 *   P0DIR 0b1111 1111 (R/W)\n
 *   P1DIR 0b1111 1111 (R/W)\n
 *   P2DIR 0b1111 1111 (R/W)\n
 *   P3DIR 0b1111 1111 (R/W)\n
 *   P0 0b0000 0000 (R/W)\n
 *   P1 0b0000 0000 (R/W)\n
 *   P2 0b0000 0000 (R/W)\n
 *   P3 0b0000 0000 (R/W)\n
 *   P0PU 0b0000 0011 (R/W)\n
 *   P1PU 0b0000 0000 (R/W)\n
 *   P2PU 0b0000 0000 (R/W)\n
 *   P3PU 0b0000 0000 (R/W)\n
 *   P0PD 0b1100 0000 (R/W)\n
 *   P1PD 0b0000 0000 (R/W)\n
 *   P2PD 0b0000 0000 (R/W)\n
 *   P3PD 0b0000 0000 (R/W)\n
 *   P0IE 0b1111 1111 (write only)\n
 *   P1IE 0b1111 1111 (write only)\n
 *   P2IE 0b1111 1111 (write only)\n
 *   P3IE 0b1111 1111 (write only)\n
 *   P0HD 0b0000 0000 (R/W)\n
 *   P1HD 0b0000 0000 (R/W)\n
 *   P2HD 0b0000 0000 (R/W)\n
 *   P3HD 0b0010 0000 (R/W)\n
 * - Port口输入、输出寄存器：P0、P1、P2、P3\n
 *   Reset值为0
 *
 * - Port口方向寄存器：P0DIR、P1DIR、P2DIR、P3DIR\n
 *   1：输入；0：输出；
 *
 * - Port口上拉控制寄存器：P0PU、P1PU、P2PU、P3PU\n
 *   高有效；
 *
 * - Port口下拉控制寄存器：P0PD、P1PD、P2PD、P3PD\n
 *   高有效\n
 *
 * - Port口数字模拟选择寄存器：P0IE、P1IE、P2IE、P3IE\n
 *   1：数字功能；0：模拟功能\n
 *
 * - Port口高驱动控制寄存器：P3HD\n
 *   高有效，Reset值为0， 0对应8mA输出，1对应24mA输出。\n
 *
 * - 当方向寄存器为0，相应的IO为输出（输出打开），输出的值为输出寄存器被写入的值。这时如果读Port口，只能读到输出寄存器的值。
 *
 * - 当方向寄存器为1，相应的IO不输出，这时该IO口是否作为输入，由输入允许寄存器控制，当输入允许寄存器为1，则该IO输入允许，读Port口可读到相应管脚的值。否则，读Port口只能读到0。
 *
 * - 上拉控制寄存器为0时，或方向寄存器为0时，上拉禁止。否则相应IO会有10K上拉。
 *
 * - P36和P37实际上就是USBDP和USBDM。\n
 *
 * \subsection port1 VPP介绍
 *
 * - P5PU BIT7控制VPP下拉 高有效，下拉电阻500欧姆；reset值：0\n
 * - P5PU BIT6控制VPP上拉 高有效，上拉电阻10K欧姆；reset值：0\n
 * - P5HD BIT7能读取VPP状态
 * \subsection port2 PORT WakeUp介绍
 * - 支持WakeUp的脚共有以下四条：P02、P05、P07、P23，这四条pin对WakeUp电路来说分别为WakeUp Pin0~3
 * - P5:\n
 *   P5的高4位为WKUPEN（高有效），分别控制四条pin是否能产生唤醒（或中断）。\n
 *   Reset值为0
 * - P5DIR:\n
 * - P5DIR的高4位为WKUPEDG，分别选择四条pin唤醒的边沿，0为上升沿，1为下降沿    \n
 *   Reset值为0
 * - P5PD\n
 *   P5PD的高4位为四条Pin的Pending信号，0为没有Pending，1为有Pending。\n
 *   Pending可以被CPU写0或1\n
 *   Reset值为X，使用前需初始化\n
 * - 以上的寄存器都是可读可写
 * - 当芯片处于正常工作状态，有效边沿出现，则芯片会产生中断（中断允许要打开，否则只会有Pending，而没有中断），Port中断的中断向量为8。
 * - 当芯片处于Stop Clock时，有效边沿出现，则芯片会被唤醒，若stop clock前中断允许是打开的，则被唤醒的CPU会马上进入中断，否则会执行stop clock后一条指令。
 * - 当芯片处于Sleep时，有效边沿出现，则芯片会被Reset。芯片重新起来后可以读PD（power down）寄存器，PD寄存器为1，说明是Sleep后唤醒。
 *
 * \subsection port3 GPIO分布介绍
 *   \image html port0.bmp
 * \subsection port4 P36、P37不适用于下图
 *   \image html port1.bmp

 */





