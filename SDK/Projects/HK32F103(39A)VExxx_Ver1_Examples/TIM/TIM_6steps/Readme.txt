/*
* @file name: Readme
* @author: AE Team
*/

V1.0.0/2023-10-26
1.首次发布

******************************例程详细描述*****************************
功能描述:
	本例程描述了通过TIM1产生6 steps的PWM输出。
	1. 配置TIM1的channel 1 2 3为PWM互补输出；
	2. 配置SysTick中断，中断事件为100ms，并在中断中使能TIM1的COM事件；
	3. TIM1配置为定时器模式，每次COM事件发生，都会提前设置新的TIM1配置；等下一次COM事件发生时，更新TIM1的配置；
	4. Break极性设置为高电平。
	
时钟配置:
	本例程采用HSE72MHz作为系统时钟，用户如果需要更改系统时钟配置, 请参考对应用户手册或者
	RCC库函数及RCC相关例程。

适用芯片:
	HK32F103xC,HK32F103xD,HK32F103xE,HK32F103xxxxA全系列

涉及外设:
	TIM,SYSTICK,GPIO
	
涉及管脚:	
	TIM1_CH1(PA8),    TIM1_CH2(PA9),     TIM1_CH3(PA10)
	TIM1_CH1N(PB13),TIM1_CH2N(PB14),TIM1_CH3N(PB15)
	TIM1_BKIN(PB12).

注意事项:
	1. 推荐使用MDK5.00及其以上版本编译本工程（MDK-ARM）
	          或者IAR8.22及其以上版本编译本工程(EWARM);
	2. 使用之前检测电源VCC、GND等是否正常。

如何使用:
	1. 直接编译程序下载到评估版，重启评估版;
	2. 将TIM1_BKIN(PB12)接GND，用示波器查看TIM1的6个通道输出6 steps的PWM；
	3. 将TIM1_BKIN(PB12)接VCC, 进行刹车。
***********************************************************************