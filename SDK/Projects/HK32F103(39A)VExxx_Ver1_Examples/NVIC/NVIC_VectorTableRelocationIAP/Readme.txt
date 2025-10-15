/*
* @file name: Readme
* @author: AE Team
*/


V1.0.0/2023-10-31
1.首次发布

******************************例程详细描述*****************************
功能描述:
	本例程展示了如何使用NVIC_SetVectorTable函数设置中断向量表偏移地址。
  NVIC_VectorTableRelocationIAP程序while(1)中快速翻转LED2，然后跳转到地址(0x08003000+4)执行程序
	NVIC_VectorTableRelocation程序while(1)中慢速翻转LED2
	
时钟配置:
	本例程采用HSE+PLL72MHz作为系统时钟，用户如果需要更改系统时钟配置，请参考对应用户手册或者
	RCC库函数及RCC相关例程。

适用芯片:
	HK32F103xC,HK32F103xD,HK32F103xE,HK32F103xxxxA全系列

涉及外设:
	GPIO/NVIC/RCC
	
涉及管脚:	
	PB0 ---------> LED2

注意事项:
	1. 推荐使用MDK5.00及其以上版本编译本工程（MDK-ARM）
	          或者IAR8.22及其以上版本编译本工程(EWARM);
	2. 使用之前检测电源VCC、GND等是否正常。

如何使用:
	1. 下载NVIC_VectorTableRelocationIAP程序到评估板;
	2. 下载NVIC_VectorTableRelocation程序到评估版，重启评估版, LED2会先快闪，然后慢闪;
***********************************************************************