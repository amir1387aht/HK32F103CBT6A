/*
* @file name: Readme
* @author: AE Team
*/


V1.0.0/2023-11-07
1.首次发布

******************************例程详细描述*****************************
功能描述:
使用
	本例程描述了使用文件系统对SD卡进行读写(Fats文件系统)，本例程使用了
	Kingston 4GB的SD卡，主要涉及以下几点内容：
    1. 将Fats文件系统挂载到SD卡上, 在此过程中会初始化SD卡；
    2. 通过文件系统对SD卡创建名为test.txt的文件，向此文件内写入一个字符串；
    3. 通过文件系统打开SD卡中名为test.txt的文件，读取文件内字符串
        
时钟配置:
    本例程采用HSE48MHz作为系统时钟，用户如果需要更改系统时钟配置，需通过
	删除SetSysClockTo48M_PLL()函数来解除系统时钟48M的固定配置，再通过
	SYSCLK_SOURCE宏定义来选择不同的时钟源。

适用芯片:
	HK32F103xC,HK32F103xD,HK32F103xE,HK32F103xxxxA全系列
	
涉及外设:
	SDIO/RCC/GPIO/USART
	
涉及管脚:
    SDIO相关信号：
	SDIO_CLK  --> PC12
	SDIO_CMD  --> PD2
	SDIO_DAT0 --> PC8
	SDIO_DAT1 --> PC9
	SDIO_DAT2 --> PC10
	SDIO_DAT3 --> PC11   
    USART相关信号：
	USART1_TX --> PA9
	USART1_RX --> PA10
注意事项:
	1. 推荐使用MDK5.00及其以上版本编译本工程（MDK-ARM）
	          或者IAR8.22及其以上版本编译本工程(EWARM);
	2. 使用之前检测电源VCC、GND等是否正常。
	3. 使用SD卡时，请注意SD卡工作的最大时钟频率。

如何使用:
	1. 直接编译程序下载到评估版，重启评估版;
	2. 在串口助手上可打印创建文件，文件大小和内容消息：
	   "Fats Write Test"
	   "Open And Write Data"
	   "Data Num:61"
	   "Data:"
	   "Hello Friend! Welcome to use HK32F103xC,HK32F103xD,HK32F103xE,HK32F103xxxxA EVAL Board V1.00!"
	   ""
	   "Fats Read Test"
	   "Open And Read Data"
	   "Read Num:61"
	   "Read Data:"
	   "Hello Friend! Welcome to use HK32F103xC,HK32F103xD,HK32F103xE,HK32F103xxxxA EVAL Board V1.00!"

***********************************************************************