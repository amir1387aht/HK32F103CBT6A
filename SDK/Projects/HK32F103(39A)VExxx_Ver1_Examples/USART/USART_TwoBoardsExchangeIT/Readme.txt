/*
* @file name: Readme
* @author: AE Team
*/


V1.0.0/2023-10-15
1.�״η���

******************************������ϸ����*****************************
��������:
	�����������������������жϵķ�ʽ�������ݡ�	
	ͨ�����ÿ⺯��HK32F103xC,HK32F103xD,HK32F103xE,HK32F103xxxxA_USART����ɶ�USART2��Interrupt���ã�BPSΪ115200
	����1�ϵ�����USART�����жϷ���0x01��ͨ��USART1��ӡMaster flag of send leisure interrupt set
	����2�����жϵȴ����ݣ����ճɹ���ͨ��USART1��ӡSlave receive interrupt complete��Master flag of send leisure interrupt set��
	�������1����0x01,����1���ճɹ����ӡMaster receive interrupt complete��Slave receive interrupt complete������2���յ�����	
	����Master receive interrupt complete��
	
	
ʱ������:
	�����̲���HSE8M_PPL72MHZ��Ϊϵͳʱ�ӣ��û������Ҫ����ϵͳʱ�����ã���Ҫ��
	Usart_Config����֮ǰ��ɣ�����ϵͳʱ��������ã���ο���Ӧ�û��ֲ����
	RCC�⺯����RCC������̡�

����оƬ:
	HK32F103xC,HK32F103xD,HK32F103xE,HK32F103xxxxAȫϵ��

�漰����:
	USART1
	USART2
	
�漰�ܽ�:	
	PA3---->PA3
	PA2--->PA2
ע������:
	1. �Ƽ�ʹ��MDK5.00�������ϰ汾���뱾���̣�MDK-ARM��
	          ����IAR8.22�������ϰ汾���뱾����(EWARM);
	2. ʹ��֮ǰ����ԴVCC��GND���Ƿ�������

���ʹ��:
	1. ֱ�ӱ���������ص������棬����������;
	2. ͨ���鿴��ӡ��Ϣ�Ƿ���ȷ;
***********************************************************************