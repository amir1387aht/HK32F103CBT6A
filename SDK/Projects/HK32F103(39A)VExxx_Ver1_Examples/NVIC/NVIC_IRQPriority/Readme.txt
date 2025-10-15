/*
* @file name: Readme
* @author: AE Team
*/


V1.0.0/2023-10-31
1.首次发布

******************************例程详细描述*****************************
功能描述:
	本例程演示了嵌套矢量中断控制器(NVIC)的使用。
		1. 配置EXTI0/EXTI1，在下降沿产生一个中断，并且使用SysTick中断。
			这些中断使用以下参数配置：
				- EXTI0:
				- PreemptionPriority = PreemptionPriorityValue
        				- SubPriority = 0
				- EXTI1:
				- PreemptionPriority = 0
        				- SubPriority = 0
				systick
`				- PreemptionPriority = !PreemptionPriorityValue
        				- SubPriority = 0    
		2. 开始时，PreemptionPriorityValue等于0，EXTI0比SysTick有更高的抢占优先级。
		3. 当EXTI1中断触发后，在中断函数中配置EXTI0和SysTick抢占优先级倒置，此时SysTick
		比EXTI0有更高的抢占优先级。此时如果EXTI0中断触发，在中断函数中SysTick ISR被执行
		后SysTick中断发生，打断当前EXTI0中断，并且PreemptionOccured 置一, LED1点亮。
	
时钟配置:
	本例程采用HSE+PLL72MHz作为系统时钟，用户如果需要更改系统时钟配置，请参考对应用户手册或者
	RCC库函数及RCC相关例程。

适用芯片:
	HK32F103xC,HK32F103xD,HK32F103xE,HK32F103xxxxA全系列

涉及外设:
	EXTI/GPIO/NVIC/RCC/USART
	
涉及管脚:	
	PA0 ---------> KEY1
	PA1 ---------> KEY2
	PB1 ---------> LED1
	PA9 ---------> USART_TX

注意事项:
	1. 推荐使用MDK5.00及其以上版本编译本工程（MDK-ARM）
	          或者IAR8.22及其以上版本编译本工程(EWARM);
	2. 使用之前检测电源VCC、GND等是否正常。

如何使用:
	1. 直接编译程序下载到评估版，重启评估版;
	2. 按下KEY2，再按下KEY1，观察EXTI0中断是否被SysTick中断打断（LED1亮）
***********************************************************************