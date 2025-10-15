/*
* @file name: Readme
* @author: AE Team
*/


V1.0.0/2023-10-31
1.�״η���

******************************������ϸ����*****************************
��������:
	��������ʾ��Ƕ��ʸ���жϿ�����(NVIC)��ʹ�á�
		1. ����EXTI0/EXTI1�����½��ز���һ���жϣ�����ʹ��SysTick�жϡ�
			��Щ�ж�ʹ�����²������ã�
				- EXTI0:
				- PreemptionPriority = PreemptionPriorityValue
        				- SubPriority = 0
				- EXTI1:
				- PreemptionPriority = 0
        				- SubPriority = 0
				systick
`				- PreemptionPriority = !PreemptionPriorityValue
        				- SubPriority = 0    
		2. ��ʼʱ��PreemptionPriorityValue����0��EXTI0��SysTick�и��ߵ���ռ���ȼ���
		3. ��EXTI1�жϴ��������жϺ���������EXTI0��SysTick��ռ���ȼ����ã���ʱSysTick
		��EXTI0�и��ߵ���ռ���ȼ�����ʱ���EXTI0�жϴ��������жϺ�����SysTick ISR��ִ��
		��SysTick�жϷ�������ϵ�ǰEXTI0�жϣ�����PreemptionOccured ��һ, LED1������
	
ʱ������:
	�����̲���HSE+PLL72MHz��Ϊϵͳʱ�ӣ��û������Ҫ����ϵͳʱ�����ã���ο���Ӧ�û��ֲ����
	RCC�⺯����RCC������̡�

����оƬ:
	HK32F103xC,HK32F103xD,HK32F103xE,HK32F103xxxxAȫϵ��

�漰����:
	EXTI/GPIO/NVIC/RCC/USART
	
�漰�ܽ�:	
	PA0 ---------> KEY1
	PA1 ---------> KEY2
	PB1 ---------> LED1
	PA9 ---------> USART_TX

ע������:
	1. �Ƽ�ʹ��MDK5.00�������ϰ汾���뱾���̣�MDK-ARM��
	          ����IAR8.22�������ϰ汾���뱾����(EWARM);
	2. ʹ��֮ǰ����ԴVCC��GND���Ƿ�������

���ʹ��:
	1. ֱ�ӱ���������ص������棬����������;
	2. ����KEY2���ٰ���KEY1���۲�EXTI0�ж��Ƿ�SysTick�жϴ�ϣ�LED1����
***********************************************************************