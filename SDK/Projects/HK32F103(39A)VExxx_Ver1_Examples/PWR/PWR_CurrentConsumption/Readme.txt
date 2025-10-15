/*
* @file name: Readme
* @author: AE Team
*/


V1.0.0/2023-10-31
1.首次发布

******************************例程详细描述*****************************
功能描述:
	本例程描述了如何配置不同的低功耗模式。
	通过调用库函数PWR_EnterSleepMode()、PWR_EnterSTOPMode()、PWR_EnterSTANDBYMode完成不同低功耗模式的配置，可以在hk32f103xxxxa_lp_modes.h中选择不同的低功耗模式，
	该例程可以配置以下低功耗模式：
	1）SLEEP mode，使用方式如下：
	-按下按键KEY1后进入SLEEP模式，同时将按键配置为EXTI模式
	-按下按键KEY3从SLEEP mode退出，LED2循环亮灭。
	2）STOP mode，使用方式如下：
	-按下按键KEY1后RTC和RTC自动唤醒定时器使能，同时进入STOP模式
	-等待RTC自动唤醒后，LED2循环亮灭
	3）STANDBY mode，使用方式如下：
	-按下按键后进入STANDBY模式
	-通过给wake up pin PA0一个下降沿唤醒，唤醒后LED2循环亮灭
	4）STANDBY mode with RTC，使用方式如下：
	-按下按键KEY1后RTC和RTC自动唤醒定时器使能，同时进入STANDBY模式
	-等待约10s后RTC自动唤醒后，LED2循环亮灭				
	
时钟配置:
	本例程采用HSE+PLL72MHz作为系统时钟，用户如果需要更改系统时钟配置，请参考对应用户手册或者
	RCC库函数及RCC相关例程。

适用芯片:
	HK32F103xC,HK32F103xD,HK32F103xE,HK32F103xxxxA全系列

涉及外设:
	RCC/PWR/RTC/BKP/GPIO
	
涉及管脚:	
	PB0 ---------> LED2
	PA0 ---------> KEY1
	PC13 ---------> KEY3

注意事项:
	1. 推荐使用MDK5.00及其以上版本编译本工程（MDK-ARM）
	          或者IAR8.22及其以上版本编译本工程(EWARM);
	2. 使用之前检测电源VCC、GND等是否正常。

如何使用:
	1. 直接编译程序下载到评估版，重启评估版;
	2. 配置不同的低功耗模式，按下按键后进入低功耗模式，观察LED2亮灭，判断是否唤醒。
***********************************************************************