/*
* @file name: Readme
* @author: AE Team
*/


V1.0.0/2023-11-07
1.首次发布

******************************例程详细描述*****************************
功能描述:
	本例程描述了使用SDIO接口对SD卡进行基本读写(不含文件系统)，本例程使用
	了Kingston 4GB的SD卡，主要涉及以下几点内容：
    1. 初始化SD卡，对SD卡进行擦除操作；
    2. SD卡单个块测试：对SD卡的第一个块进行数据写入0x320F，然后读取SD卡的
	   第一个块，对比读出数据和写入数据是否一致；
    3. SD卡多个块测试：对SD卡的前32个块进行数据写入0x0000，然后读取SD卡的
	   前32个块，对比读出数据和写入数据是否一致；
        
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
	2. 在串口助手上可打印擦除测试，单个块测试、多个块测试信息：
		SD Erase Done!
		SD Single Block Test OK!
		SD Muti Block Test OK!;
***********************************************************************