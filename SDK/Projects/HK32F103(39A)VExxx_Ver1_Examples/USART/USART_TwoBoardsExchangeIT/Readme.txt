/*
* @file name: Readme
* @author: AE Team
*/


V1.0.0/2023-10-15
1.首次发布

******************************例程详细描述*****************************
功能描述:
	本例程描述了两个板子用中断的方式传输数据。	
	通过调用库函数HK32F103xC,HK32F103xD,HK32F103xE,HK32F103xxxxA_USART来完成对USART2的Interrupt配置，BPS为115200
	板子1上电后进入USART接收中断发送0x01并通过USART1打印Master flag of send leisure interrupt set
	板子2接收中断等待数据，接收成功后通过USART1打印Slave receive interrupt complete和Master flag of send leisure interrupt set，
	并向板子1发送0x01,板子1接收成功后打印Master receive interrupt complete和Slave receive interrupt complete。板子2接收到数据	
	发送Master receive interrupt complete。
	
	
时钟配置:
	本例程采用HSE8M_PPL72MHZ作为系统时钟，用户如果需要更改系统时钟配置，需要在
	Usart_Config函数之前完成，关于系统时钟如何配置，请参考对应用户手册或者
	RCC库函数及RCC相关例程。

适用芯片:
	HK32F103xC,HK32F103xD,HK32F103xE,HK32F103xxxxA全系列

涉及外设:
	USART1
	USART2
	
涉及管脚:	
	PA3---->PA3
	PA2--->PA2
注意事项:
	1. 推荐使用MDK5.00及其以上版本编译本工程（MDK-ARM）
	          或者IAR8.22及其以上版本编译本工程(EWARM);
	2. 使用之前检测电源VCC、GND等是否正常。

如何使用:
	1. 直接编译程序下载到评估版，重启评估版;
	2. 通过查看打印信息是否正确;
***********************************************************************