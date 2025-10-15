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
/** @addtogroup hk32f103xxxxa_StdPeriph_Examples
  * @{
  */

/** @addtogroup USART_Printf
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

static void UART_Config(void);
static void GPIO_Config(void);
static void delay(uint32_t i);
/* Private functions ---------------------------------------------------------*/
/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */   
int main(void)
{
    GPIO_Config();
    UART_Config();
    delay(720000);
    
    /* Output a message on Hyperterminal using printf function */
    printf("\n\rUSART Printf Example: retarget the C library printf function to the USART\n\r");
    
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

    USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);

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
    
	/*USART1:PA9(TX)---PA10(RX)*/
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStruct);	 
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStruct);	 

}

/**
  * @brief  Retargets the C library printf function to the USART.
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
  * @brief  Delay time function
  * @param  i: count of dalay time
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

/**
  * @}
  */ 

/**
  * @}
  */ 


