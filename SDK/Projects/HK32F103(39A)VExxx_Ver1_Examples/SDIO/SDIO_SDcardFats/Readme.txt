/*
* @file name: Readme
* @author: AE Team
*/


V1.0.0/2023-11-07
1.�״η���

******************************������ϸ����*****************************
��������:
ʹ��
	������������ʹ���ļ�ϵͳ��SD�����ж�д(Fats�ļ�ϵͳ)��������ʹ����
	Kingston 4GB��SD������Ҫ�漰���¼������ݣ�
    1. ��Fats�ļ�ϵͳ���ص�SD����, �ڴ˹����л��ʼ��SD����
    2. ͨ���ļ�ϵͳ��SD��������Ϊtest.txt���ļ�������ļ���д��һ���ַ�����
    3. ͨ���ļ�ϵͳ��SD������Ϊtest.txt���ļ�����ȡ�ļ����ַ���
        
ʱ������:
    �����̲���HSE48MHz��Ϊϵͳʱ�ӣ��û������Ҫ����ϵͳʱ�����ã���ͨ��
	ɾ��SetSysClockTo48M_PLL()���������ϵͳʱ��48M�Ĺ̶����ã���ͨ��
	SYSCLK_SOURCE�궨����ѡ��ͬ��ʱ��Դ��

����оƬ:
	HK32F103xC,HK32F103xD,HK32F103xE,HK32F103xxxxAȫϵ��
	
�漰����:
	SDIO/RCC/GPIO/USART
	
�漰�ܽ�:
    SDIO����źţ�
	SDIO_CLK  --> PC12
	SDIO_CMD  --> PD2
	SDIO_DAT0 --> PC8
	SDIO_DAT1 --> PC9
	SDIO_DAT2 --> PC10
	SDIO_DAT3 --> PC11   
    USART����źţ�
	USART1_TX --> PA9
	USART1_RX --> PA10
ע������:
	1. �Ƽ�ʹ��MDK5.00�������ϰ汾���뱾���̣�MDK-ARM��
	          ����IAR8.22�������ϰ汾���뱾����(EWARM);
	2. ʹ��֮ǰ����ԴVCC��GND���Ƿ�������
	3. ʹ��SD��ʱ����ע��SD�����������ʱ��Ƶ�ʡ�

���ʹ��:
	1. ֱ�ӱ���������ص������棬����������;
	2. �ڴ��������Ͽɴ�ӡ�����ļ����ļ���С��������Ϣ��
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