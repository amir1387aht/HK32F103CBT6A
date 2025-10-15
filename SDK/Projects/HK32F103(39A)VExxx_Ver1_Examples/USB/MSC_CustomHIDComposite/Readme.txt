/*
* @file name: Readme
* @author: AE Team
*/

V1.0.0/2023-10-23
1. 首次发布

******************************例程详细描述*****************************
功能描述:
	1. 本例程提供了基于HK32芯片的USB全速设备说明;
	2. 本例程描述了USB-FS设备与PC主机通过bulk传输通讯;
	3. 本例程支持BOT(bulk only transfer)协议，并且使用SCSI(small computer system interface)指令;
	4. 本例程描述了USB设备被枚举为USB-FS大容量设备，它使用USB-FS设备的Mass Storage驱动程序.
	  
时钟配置:
	1. 本例程采用PLL 72MHz作为系统时钟，用户如果需要更改系统时钟配置，
	    需要配置修改SYSCLK_SOURCE宏定义的。
	2. 关于系统时钟如何配置，请参考对应用户手册或者RCC库函数及RCC相关例程。

适用芯片:
	HK32F103xC,HK32F103xD,HK32F103xE,HK32F103xxxxA全系列

涉及外设:
	USB
	SDIO
	
涉及管脚:	
	USBDP - PA11
	USBDM - PA12
	SDIO_CMD - PD2
	SDIO_CLK - PC12
	SDIO_D0 - PC8
	SDIO_D1 - PC9
	SDIO_D2 - PC10
	SDIO_D3 - PC11

注意事项:
	1. 推荐使用MDK5.00及其以上版本编译本工程（MDK-ARM）
	    或者IAR8.22及其以上版本编译本工程(EWARM);
	2. 使用之前检测电源VCC、GND等是否正常。

如何使用:
	1. 直接编译程序下载到评估版，重启评估版;

***********************************************************************