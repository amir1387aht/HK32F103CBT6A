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
#include "hk32f103xxxxa_eval.h"
/** @addtogroup hk32f103xxxxa_StdPeriph_Examples
  * @{
  */

/** @addtogroup USART_TwoBoardsExchangeIT
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

static void USART_Config(void);
static void GPIO_Config(void);
static void NVIC_Config(void);
void SendData(uint8_t data);
uint8_t ReceiveData(void);
/* Private functions ---------------------------------------------------------*/
/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */   
int main(void)
{
	if (SysTick_Config((SystemCoreClock) / 1000))
	{ 
		/* Capture error */ 
		while (1)
        {
            
        }
        
	}    

	NVIC_SetPriority(SysTick_IRQn, 0x0);    
    NVIC_Config(); 
    GPIO_Config();
    USART_Config();

    /* Infinite loop */
    while (1)
    {
        
    }
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
    
    /*USART:PA:TX---PA10:RX;USART2:PA:TX---PA3:RX*/
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9|GPIO_Pin_2;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStruct);	 
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_3;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStruct);	 


}
/**
  * @brief  Deinitializes the USART1 peripheral registers to their default reset values.
  * @param  None
  * @retval None
  */
void USART_Config()
{
    RCC_HCLKConfig(RCC_SYSCLK_Div1);
 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
    
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);	
	
	USART_InitTypeDef UART_InitStruct;
	
	UART_InitStruct.USART_BaudRate = 115200;
	UART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	UART_InitStruct.USART_Mode = USART_Mode_Tx|USART_Mode_Rx;
	UART_InitStruct.USART_StopBits = USART_StopBits_1;
	UART_InitStruct.USART_WordLength = USART_WordLength_8b;
	UART_InitStruct.USART_Parity = USART_Parity_No;
    
	USART_Init(USART1,&UART_InitStruct); 
	USART_Init(USART2,&UART_InitStruct);
    #if (DEVICE == MASTER) 
    

        /* Enable USART2  TX interrupt */
        USART_ITConfig(USART2,USART_IT_TXE,ENABLE);
        
        /* Enable USART2  RX interrupt */ 
        USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);  
    #elif (DEVICE == SLAVE) 
 
        /* Enable USART2  RX interrupt */
        USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);  
    #endif


	USART_Cmd(USART1,ENABLE);
    USART_Cmd(USART2,ENABLE);

    
}

/**
  * @brief  Configures the nested vectored interrupt controller.
  * @param  None
  * @retval None
  */
void NVIC_Config(void)
{
	NVIC_InitTypeDef nvic_struct;
  
	nvic_struct.NVIC_IRQChannel = USART2_IRQn;
	nvic_struct.NVIC_IRQChannelSubPriority = 0;
	nvic_struct.NVIC_IRQChannelCmd = ENABLE;	
	NVIC_Init(&nvic_struct);   
}
/**
  * @brief  Send one byte data.
  * @param  data: data of send
  * @retval None
  */
void SendData(uint8_t data)
{
	USART_SendData(USART2,data);
	
	while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET)
    {
    }
}

/**
  * @brief  Receive one byte
  * @param  None
  * @retval data: data of receive
  */
uint8_t ReceiveData()
{
    uint8_t data=0;
    while(USART_GetFlagStatus(USART2,USART_FLAG_RXNE) == RESET)
    {
    }
    data=USART_ReceiveData(USART2);
    return data;
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

/**
  * @}
  */ 

/**
  * @}
  */ 


