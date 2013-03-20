/*! \page AUX AUX功能介绍
 *
 * \section aux0 USB 从机功能概述
 *
 * - 支持LINE IN检测和播放,
 *
 * - 支持AD频谱显示,
 *
 *
 * \section aux1 函数介绍
 *
 * - aux_fun.c （AUX模式函数）\n
 *	 本文件中的函数主要完成AUX模式的主循环，主循环会从消息池获取各种消息进而响应不同操作，
 *
 * \section aux2 文件组织方式介绍
 *
 * - AUX模式主要在aux_fun.c文件中完成，进入USB从机模式主循环后从消息池获取各种消息，然后作出不同的响应操作；
 *
 */