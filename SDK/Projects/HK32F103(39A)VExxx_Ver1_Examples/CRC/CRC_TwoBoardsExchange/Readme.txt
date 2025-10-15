/*
* @file name: Readme
* @author: AE Team
*/


V1.0.0/2023-10-31
1.首次发布

******************************例程详细描述*****************************
功能描述:
	本例程描述了如何在两个评估板A和B之间进行USART通信时验证CRC校验和。
	通过调用库函数CRC_DeInit()来完成对CRC的配置，在程序中使用USART1发送和接收数组TxBuffer中的数据，使能USART1中断，
	通过按下按键KEY3，则开始发送数组TxBuffer中的数据，具体两个评估板通信如下：
	1、在main.h中定义MODE_TRANSMITTER，则程序为USART发送程序，将程序下载到评估板A 。
	2、在main.h中打开定义MODE_RECEIVER，屏蔽MODE_TRANSMITTER，则程序为USART接收程序，将程序下载到评估板B 。
	3、将评估板A的USART1的TX与评估板B的USART1的RX连接，将评估板A的USART1的RX与评估板B的USART1的TX连接.
	4、按下评估板A的按键KEY3，观察评估板B的LED2和LED3亮灭，若：LED2亮，LED3灭，则计算的校验值和接收到的校验值一致；
	     LED2灭，LED3亮，则计算的校验值和接收到的校验值不一致
	 SysTick被配置为每10ms产生一次中断。SysTick ISR内部的专用计数器用于每隔100ms反转LED1，指示固件正在运行。    
	
时钟配置:
	本例程采用HSE+PLL72MHz作为系统时钟，用户如果需要更改系统时钟配置，请参考对应用户手册或者
	RCC库函数及RCC相关例程。

适用芯片:
	HK32F103xC,HK32F103xD,HK32F103xE,HK32F103xxxxA全系列

涉及外设:
	RCC/CRC/GPIO/USART1/SysTick 
	
涉及管脚:	
	PB1 ---------> LED1
	PB0 ---------> LED2
	PB5 ---------> LED3
	PC13 ---------> KEY3
	PA9 ---------> USART1 TX
	PA10 ---------> USART1 RX	

注意事项:
	1. 推荐使用MDK5.00及其以上版本编译本工程（MDK-ARM）
	          或者IAR8.22及其以上版本编译本工程(EWARM);
	2. 使用之前检测电源VCC、GND等是否正常。

如何使用:
	1. 在main.h中分别配置发送和接收，直接编译下载到评估版A和B，将A评估版的USART1的TX和RX分别和B评估版的USART1的RX、TX连接，重启评估版;
	2. 观察接收评估板B的LED亮灭状态，判断CRC计算和接收到的CRC结果是否一致。
***********************************************************************