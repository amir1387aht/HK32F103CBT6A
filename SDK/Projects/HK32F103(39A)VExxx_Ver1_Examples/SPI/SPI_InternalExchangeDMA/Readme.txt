/*
* @file name: Readme
* @author: AE Team
*/

V1.0.1/2023-03-25
1.变更点

V1.0.0/2023-03-03
1.首次发布

******************************例程详细描述*****************************
功能描述:
	1.本例程实现了DMA接收SPI数据
	2.SPI3作为主机查询发送
	3.SPI2作为从机DMA接收数据，接收成功后比较结果
	
时钟配置:
	本例程采用HSE8M_PPL72MHZ作为系统时钟，用户如果需要更改系统时钟配置，需要在
	Usart_Config函数之前完成，关于系统时钟如何配置，请参考对应用户手册或者
	RCC库函数及RCC相关例程。

适用芯片:
	HK32F103xC,HK32F103xD,HK32F103xE,HK32F103xxxxA全系列

涉及外设:
	SPI2
	SPI3
	GPIO
	DMA
	
涉及管脚:	
	SPI2_SCK-PB13
	SPI2_MIOS-PB14
	SPI2_MOSI-PB15
 	SPI3_SCK- PA5 
	SPI3_MISO - PA6
	SPI3_MOSI - PA7 

注意事项:
	1. 推荐使用MDK5.00及其以上版本编译本工程（MDK-ARM）
	          或者IAR8.22及其以上版本编译本工程(EWARM);
	2. 使用之前检测电源VCC、GND等是否正常。
	3. HK32F103xC,HK32F103xD,HK32F103xE,HK32F103xxxxA系列USART固定16倍过采样。

如何使用:
	1. 直接编译程序下载到评估版，重启评估版;
	2. TransferStatus为PASSED接收结果正确
***********************************************************************