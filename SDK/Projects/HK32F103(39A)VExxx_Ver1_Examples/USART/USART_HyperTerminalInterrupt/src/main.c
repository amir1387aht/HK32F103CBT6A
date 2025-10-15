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

/** @addtogroup USART_HyperTerminalInterrupt
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define USARTx_IRQn   USART1_IRQn
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void UART_Config(void);
static void NVIC_Config(void);
/* Private functions ---------------------------------------------------------*/
/**
  * @brief  Main program
  * @param  None
  * @retval None
  */   
int main(void)
{

    NVIC_Config();
    UART_Config();

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
	RCC_APB2PeriphClockCmd(EVAL_COM1_CLK,ENABLE);
	
	
	USART_InitTypeDef UART_InitStruct;
	
	UART_InitStruct.USART_BaudRate = 115200;
	UART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	UART_InitStruct.USART_Mode = USART_Mode_Tx|USART_Mode_Rx;
	UART_InitStruct.USART_StopBits = USART_StopBits_1;
	UART_InitStruct.USART_WordLength = USART_WordLength_8b;
	UART_InitStruct.USART_Parity = USART_Parity_No;
    
    
    HK_EVAL_COMInit(COM1, &UART_InitStruct);
	USART_Init(EVAL_COM1,&UART_InitStruct);

    /* Enable the EVAL_COM1 Transmit interrupt: this interrupt is generated when the 
        EVAL_COM1 transmit data register is empty */  
    USART_ITConfig(EVAL_COM1, USART_IT_TXE, ENABLE);

    /* Enable the EVAL_COM1 Receive interrupt: this interrupt is generated when the 
        EVAL_COM1 receive data register is not empty */
    USART_ITConfig(EVAL_COM1, USART_IT_RXNE, ENABLE);

	USART_Cmd(EVAL_COM1,ENABLE);
    
}

/**
  * @brief  Configures the nested vectored interrupt controller.
  * @param  None
  * @retval None
  */
void NVIC_Config(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;

  /* Enable the USARTx Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = USARTx_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
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


