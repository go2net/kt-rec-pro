/*! \mainpage AC309N 开发包编程指南
 *
 * \section intro_sec_main 总体介绍
 *
 * \version 0.01
 *
 * \date 2011-7-13
 *
 * \section sec_descriptor 主芯片介绍
 * - 8051兼容指令集
 * - 最大工作频率：48M
 * - 256 byte DRAM\n
 *   11K byte XRAM for APP\n
 *   19.5K byte OTP for APP
 * - 四级可嵌套中断优先级
 * - TIMER,UART,IIC,SPI,EMI,LVD,ADC(10bit),DAC(24bit)
 * - SDMMC 控制器
 * - USB OTG full speed 控制器
 * - aDSP模块用于音频处理\n
 *   支持MPEG1/MPEG2,(layer1,2,3)格式\n
 *   支持MP3 CBR/VBR/ABR,最大编码率448kbps\n
 *   支持MP3 ID3V2\n
 *   支持WAV ima/microsoft ADPCM格式\n
 *   支持WAV PCM格式\n
 *   支持WMA(V7/V8/V9)格式\n
 *   支持WMA,码率>=5 kbps\n
 *   支持MP3/WAV/WMA 采样率(K):8/11.025/12/16/22.05/24/32/44.1/48\n
 *   支持音效模式(EQ)\n
 *   支持快进快退
 * - 支持USB Speaker/ mass storage
 * - 支持片内RTC，独立供电，内置电源控制电路
 * \section sec_descriptr 开发包介绍
 * - link_hex目录
 *   -# 工具链目录
 * - APP目录划分
 *   -# lib: 项目库，主要包含解码控制接口\n
 *   -# aux_fun: AUX功能流程控制，消息处理\n
 *   -# display: 界面显示\n
 *   -# fm_receive: 调频收收音功能流程控制，消息处理\n
 *   -# iic: IIC记忆\n
 *   -# key: 按键、遥控\n
 *   -# main: 主任务框架\n
 *   -# msg: 热消息处理\n
 *   -# music: 解码流程控制，消息处理\n
 *   -# output: 编译生成文件目录\n
 *   -# rtc: RTC功能流程控制，消息处理\n
 *   -# usb_device:  USB从机功能控制，消息处理\

 */