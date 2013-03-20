/*! \page USB_DEV USB从机功能介绍
 *
 * \section usb_device0 USB 从机功能概述
 *
 * - 支持USB Mass Storage,
 *
 * - 支持USB Speaker,
 *
 * - 支持USB HID,
 *
 * \section usb_device1 函数介绍
 *
 * - msgfor_usb.c （USB从机模式函数）\n
 *	 本文件中的函数主要完成USB从机模式的主循环，主循环会从消息池获取各种消息进而响应不同操作，
 *
 * \section usb_device2 文件组织方式介绍
 *
 * - USB从机模式主要在msgfor_usb.c文件中完成，进入USB从机模式主循环后从消息池获取各种消息，然后作出不同的响应操作；
 *
 */