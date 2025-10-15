/*
* @file name: Readme
* @author: AE Team
*/



V1.0.0/2023-10-15
1.首次发布

******************************例程详细描述*****************************
功能描述:
	本例程描述了SPI两板DMA通信配置使用。
	通过调用库函数HK32F103xC,HK32F103xD,HK32F103xE,HK32F103xxxxA_DMA来完成对SPI的DMA配置,主机
	顺序发送数据，从机DMA接收。从机上电运行后主机上电，再按下主机按键。
	
时钟配置:
	本例程采用HSE8M_PPL72MHZ作为系统时钟，用户如果需要更改系统时钟配置，需要在
	GPIO_Config函数之前完成，关于系统时钟如何配置，请参考对应用户手册或者
	RCC库函数及RCC相关例程。

适用芯片:
	HK32F103xC,HK32F103xD,HK32F103xE,HK32F103xxxxA全系列

涉及外设:
	SPI
	GPIO
	
涉及管脚:
	MASTER：
	SPI2_SCK - PA5  
	SPI2_MISO - PA6 
	SPI2_MOSI - PA7 
 	SLAVER:
	SPI2_SCK - PB13  
	SPI2_MISO - PB14 
	SPI2_MOSI - PB15 
 


注意事项:
	1. 推荐使用MDK5.00及其以上版本编译本工程（MDK-ARM）
	          或者IAR8.22及其以上版本编译本工程(EWARM);
	2. 使用之前检测电源VCC、GND等是否正常。
	3. HK32F103xC,HK32F103xD,HK32F103xE,HK32F103xxxxA系列USART固定16倍过采样。

如何使用:
	1. 直接编译程序下载到评估版，重启评估版;
***********************************************************************