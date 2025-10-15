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
#include "platform_config.h"
#include "hk32f103xxxxa_eval.h"
/** @addtogroup hk32f103xxxxa_StdPeriph_Examples
  * @{
  */

/** @addtogroup USART_MultiProcessor
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
    HK_EVAL_LEDInit(LED1);
    HK_EVAL_LEDInit(LED2);
    HK_EVAL_LEDInit(LED3);
    HK_EVAL_PBInit(BUTTON_KEY1, BUTTON_MODE_EXTI);          
    HK_EVAL_PBInit(BUTTON_KEY2, BUTTON_MODE_EXTI);  



    while (1)
    {

        /* Send one byte from USARTy to USARTz */
        USART_SendData(USARTy, 0x33);
    
        /* Wait while USART1 TXE = 0 */
        while(USART_GetFlagStatus(USARTz, USART_FLAG_TXE) == RESET)
        {
        }

        if(USART_GetFlagStatus(USARTz, USART_FLAG_RXNE) != RESET)
        {
            if(USART_ReceiveData(USARTz) == 0x33)
            {
                HK_EVAL_LEDToggle(LED1);
                delay(0x5FFFF);
                HK_EVAL_LEDToggle(LED2);
                delay(0x5FFFF);
                HK_EVAL_LEDToggle(LED3);
                delay(0x5FFFF);

            }
        }       
    }
}

/**
  * @brief  Deinitializes the USARTy and USARTz  peripheral registers to their default reset values.
  * @param  None
  * @retval None
  */
void UART_Config()
{
    RCC_HCLKConfig(RCC_SYSCLK_Div1);
 
    RCC_APB1PeriphClockCmd(USARTy_CLK, ENABLE); 
    RCC_APB1PeriphClockCmd(USARTz_CLK, ENABLE); 
	
	USART_InitTypeDef UART_InitStruct;

	
	UART_InitStruct.USART_BaudRate = 115200;
	UART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	UART_InitStruct.USART_Mode = USART_Mode_Tx|USART_Mode_Rx;
	UART_InitStruct.USART_StopBits = USART_StopBits_1;

	UART_InitStruct.USART_WordLength = USART_WordLength_8b;
	UART_InitStruct.USART_Parity = USART_Parity_No;
    
    /* Configure USARTy */
    USART_Init(USARTy, &UART_InitStruct);
    
    /* Configure USARTz */
    USART_Init(USARTz, &UART_InitStruct);
  
    /* Enable the USARTy */
    USART_Cmd(USARTy, ENABLE);
    
    /* Enable the USARTz */
    USART_Cmd(USARTz, ENABLE);

    /* Set the USARTy Address */
    USART_SetAddress(USARTy, 0x1);
    
    /* Set the USARTz Address */
    USART_SetAddress(USARTz, 0x2);

    /* Select the USARTz WakeUp Method */
    USART_WakeUpConfig(USARTz, USART_WakeUp_AddressMark);



}


/**
  * @brief  Deinitializes the GPIO peripheral registers to their default reset values.
  * @param  None
  * @retval None
  */
void GPIO_Config(void)
{

    /* Enable GPIO clock */
    RCC_APB2PeriphClockCmd(USARTy_GPIO_CLK | USARTz_GPIO_CLK | RCC_APB2Periph_AFIO, ENABLE);
    
	GPIO_InitTypeDef GPIO_InitStruct;
    
	/*USART2:PD5:TX*/
	GPIO_InitStruct.GPIO_Pin = USARTy_TxPin;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(USARTy_GPIO, &GPIO_InitStruct);	 

 	/*USART3:PC11:TX*/
	GPIO_InitStruct.GPIO_Pin = USARTz_TxPin;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(USARTz_GPIO, &GPIO_InitStruct);	 



    /* Enable the USART3 Pins Software Remapping */
    GPIO_PinRemapConfig(GPIO_PartialRemap_USART3, ENABLE);
  
    /* Enable the USART2 Pins Software Remapping */
    GPIO_PinRemapConfig(GPIO_Remap1_USART2, ENABLE);  
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


/**
  * @brief  Send one byte
  * @param  data: data of send
  * @retval None
  */
void SendData(USART_TypeDef* USARTx,uint8_t data)
{
	USART_SendData(USARTx,data);
	
	while(USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET)
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


