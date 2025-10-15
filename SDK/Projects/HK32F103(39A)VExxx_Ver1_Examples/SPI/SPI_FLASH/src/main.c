/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  main.c
* @brief:     Main program body
* @author:    AE Team
* @version:   V1.0.0/2023-10-23
* @log:
*******************************************************************************/


/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "hk32f103xxxxa_eval_spi_flash.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/
#define countof(a)   (sizeof(a) / sizeof(*(a)))
/* Private variables ---------------------------------------------------------*/
uint8_t readBuff[4096];
uint8_t writeBuff[4096] = {1,2,3,4,5};
/* Private function prototypes -----------------------------------------------*/
static void GPIO_Config(void);
static void SPI_Config(void);
static void UART_Config(void);
void delay(uint32_t i);
																					
void SPI_WaitForWriteEnd(void);
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */    
int main(void)
{
    uint32_t id = 0;
	uint16_t i = 0;
    GPIO_Config();
	UART_Config();
    SPI_Config();

    delay(72000); 	
	printf("\r\n This is a example for the SPI-FLASH test \r\n");     
    
   
    id = SPI_Read_ID();
	printf("\r\n id =0x%x \r\n",id);
	
	SPI_Erase_Sector(0);
 	for(i=0;i<25;i++)
	{
		writeBuff[i]=i+25;
	}
	
	SPI_Write_Data(0,writeBuff,25);
	
	SPI_Read_Data(0,readBuff,4096);
	
	for(i=0;i<4096;i++)
	{
		printf("0x%x ",readBuff[i]);
		if(i%10==0)
        {
			printf("\r\n");
        }
	}
	   

    /* Infinite loop */
    while (1)
    {

    }
}
/**
  * @brief  Deinitializes the USART1 peripheral registers to their default reset values.
  * @param  None
  * @retval None
  */
void UART_Config()
{
    RCC_HCLKConfig(RCC_SYSCLK_Div1);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	
	USART_InitTypeDef UART_InitStruct;

 	
	UART_InitStruct.USART_BaudRate = 115200;
	UART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	UART_InitStruct.USART_Mode = USART_Mode_Tx|USART_Mode_Rx;
	UART_InitStruct.USART_StopBits = USART_StopBits_1;
	UART_InitStruct.USART_WordLength = USART_WordLength_8b;
	UART_InitStruct.USART_Parity = USART_Parity_No;
	


	USART_Init(USART1,&UART_InitStruct);
  
	USART_Cmd(USART1,ENABLE);
    


}



/**
  * @brief  Deinitializes the GPIO peripheral registers to their default reset values.
  * @param  None
  * @retval None
  */
void GPIO_Config(void)
{

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    
	GPIO_InitTypeDef GPIO_InitStruct;
    /*USART1:PA9_TX---PA10_RX---MISO:PA6*/
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9|GPIO_Pin_8|GPIO_Pin_7|GPIO_Pin_5;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStruct);	
    /*MOSI:PA7---SPI_SCK:PA5*/    
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_6;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStruct);	 
    

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;	       
    GPIO_Init(GPIOA, &GPIO_InitStruct);    
    
    GPIO_SetBits(GPIOA,GPIO_Pin_4);
}
/**
  * @brief  Configures the SPI.
  * @param  None
  * @retval None
  */
void SPI_Config(void)
{
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1,ENABLE);  
    
    SPI_InitTypeDef SPI_InitStructure;

    SPI_StructInit(&SPI_InitStructure);

    SPI_I2SDeInit(SPI1);

    /* SPI1 Config */
    SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;

	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_64 ;
    SPI_InitStructure.SPI_Mode = SPI_Mode_Master;   
    SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
    SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;

    /* Configure SPI1 */
    SPI_Init(SPI1, &SPI_InitStructure);

    /* SPI1 enable */
    SPI_Cmd(SPI1, ENABLE);       
}


/**
  * @brief  Serial port redirection
  * @param  None
  * @retval None
  */
int fputc(int ch,FILE *f)
{

    USART_SendData(USART1, (uint8_t) ch);
    while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET)
    {
    }		
    return ch;
}
/**
  * @brief  Delay function
  * @param  i:delay count
  * @retval None
  */
void delay(uint32_t i )
{

    while(i--)
    {
    }

}


#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
}
#endif /* USE_FULL_ASSERT */


