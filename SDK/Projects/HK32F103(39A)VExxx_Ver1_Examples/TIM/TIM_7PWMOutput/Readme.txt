/*
* @file name: Readme
* @author: AE Team
*/

V1.0.0/2023-10-26
1.首次发布

******************************例程详细描述*****************************
功能描述:
	本例程配置TIM1产生7路PWM输出信号，具有4个不同的占空比。
	1. 配置TIM1的PWM输出频率为17.57KHz；
                2. channel 1和channel 1N的占空比为50%，channel 2和channel 2N的占空比为37.5%，
	    channel 3和channel 3N的占空比为25%，channel 4的占空比为12.5%；
	
时钟配置:
	本例程采用HSE72MHz作为系统时钟，用户如果需要更改系统时钟配置, 请参考对应用户手册或者
	RCC库函数及RCC相关例程。

适用芯片:
	HK32F103xC,HK32F103xD,HK32F103xE,HK32F103xxxxA全系列

涉及外设:
	TIM,GPIO
	
涉及管脚:	
	TIM1_CH1(PA8),    TIM1_CH2(PA9),     TIM1_CH3(PA10)
	TIM1_CH1N(PB13),TIM1_CH2N(PB14),TIM1_CH3N(PB15)
	TIM1_CH4(PA11).

注意事项:
	1. 推荐使用MDK5.00及其以上版本编译本工程（MDK-ARM）
	          或者IAR8.22及其以上版本编译本工程(EWARM);
	2. 使用之前检测电源VCC、GND等是否正常。

如何使用:
	1. 直接编译程序下载到评估版，重启评估版;
	2. 用示波器查看TIM1的7个通道输出PWM,并查看它们的占空比。
	    channel 1和channel 1N的占空比为50%，channel 2和channel 2N的占空比为37.5%，
	    channel 3和channel 3N的占空比为25%，channel 4的占空比为12.5%；
***********************************************************************