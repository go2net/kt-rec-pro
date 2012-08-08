/*! \page ITER interrupt使用说明
 *
 * \section intr0 AC309N interrupt概述
 *
 * - AC309N中断为4级优先级中断\n
 *	 IE0、IE1中断使能，reset:0x00;\n
 *	 IP0/IP0H、IP1/IP1H中断优先级设置,reset:0x00(eg:TIMER0中断号为0,那么IP0.0/IP0H.0为设置TMERR0中断优先级)\n
 *   第一优先级：IP0H.0 = 1；IP0.0 = 1；  (最高优先级)\n
 *   第二优先级：IP0H.0 = 1；IP0.0 = 0；  (高优先级)\n
 *   第三优先级：IP0H.0 = 0；IP0.0 = 1；  (低优先级)\n
 *   第四优先级：IP0H.0 = 0；IP0.0 = 0；  (最低优先级)\n
 * - 在SDK开发中，客户如果需要自己开辟新的中断，原则上使用第三级优先级中断。\n
 *
 * \section intr1 中断使用方法介绍
 *
 * - 在AC309N的SDK中中断入口全部放在了MASKROM中，在开发中式不能见到的\n
 * - 例如现在要开辟一个中断xxx,那么就有如下\n
 * - 第一步：interrupt_init(n,xxx_isr);n是该中断的中断号，xxx_isr是该中断的中断服务程序\n
 * - 第二步：xxx_init();初始化该中断\n
 * - 第三部：设置中断服务程序调用关系：\n
 *   鼠标右键点击keil的project窗口的app树打开target options\n
 *   在“Options for Target 'app'”窗口中选择'LX51 Misc'页面\n
 *   在'LX51 Misc'页面中点击'Edit...'按钮会出现app.lin文件在编辑窗口中\n
 *   找到在app.lin文件第5行中有overlay(* !(lcd_dma_isr,rtcisr,timer3isr))这样一句代码\n
 *   将要运行的中断服务程序添加进去overlay(* !(lcd_dma_isr,rtcisr,timer3isr，xxx_isr))，保存app.lin文件\n
 *   完成\n
 *
 *
 */