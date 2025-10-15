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
/** @addtogroup hk32f103xxxxa_StdPeriph_Examples
  * @{
  */

/** @addtogroup USART_HalfDuplex
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
typedef enum {FAILED = 0, PASSED = !FAILED} TestStatus;

/* Private define ------------------------------------------------------------*/
#define TxBufferSize1   (countof(TxBuffer1) - 1)
#define TxBufferSize2   (countof(TxBuffer2) - 1)

/* Private macro -------------------------------------------------------------*/
#define countof(a)   (sizeof(a) / sizeof(*(a)))

/* Private variables ---------------------------------------------------------*/
USART_InitTypeDef USART_InitStructure;
uint8_t TxBuffer1[] = "USART Half Duplex: USARTy -> USARTz using HalfDuplex mode";
uint8_t TxBuffer2[] = "USART Half Duplex: USARTz -> USARTy using HalfDuplex mode";
uint8_t RxBuffer1[TxBufferSize2];
uint8_t RxBuffer2[TxBufferSize1];
uint32_t NbrOfDataToRead1 = TxBufferSize2;
uint32_t NbrOfDataToRead2 = TxBufferSize1;
uint8_t TxCounter1 = 0, RxCounter1 = 0;
uint8_t TxCounter2 = 0, RxCounter2 = 0;
volatile TestStatus TransferStatus1 = FAILED, TransferStatus2 = FAILED;  

/* Private function prototypes -----------------------------------------------*/
static void UART_Config(void);
static void GPIO_Config(void);

void SendData(USART_TypeDef* USARTx,uint8_t data);
TestStatus Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint16_t BufferLength);
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
    USART_ReceiveData(USARTz);

    while(NbrOfDataToRead2--)
    {
        /* Wait until end of transmit */
        while(USART_GetFlagStatus(USARTy, USART_FLAG_TXE) == RESET)
        {
        }
 
        /* Write one byte in the USARTy Transmit Data Register */
        USART_SendData(USARTy, TxBuffer1[TxCounter1++]);

        
        /* Wait the byte is entirely received by USARTz */  
        while(USART_GetFlagStatus(USARTz, USART_FLAG_RXNE) == RESET)
        {
        }

        /* Store the received byte in the RxBuffer2 */
        RxBuffer2[RxCounter2++] = USART_ReceiveData(USARTz);
    }
    /* Clear the USARTy Data Register */
    USART_ReceiveData(USARTy);
    
    while(NbrOfDataToRead1--)
    { 
        /* Wait until end of transmit */
        while(USART_GetFlagStatus(USARTz, USART_FLAG_TXE)== RESET)
        {
        }

        /* Write one byte in the USARTz Transmit Data Register */
        USART_SendData(USARTz, TxBuffer2[TxCounter2++]);

        /* Wait the byte is entirely received by USARTy */
        while(USART_GetFlagStatus(USARTy,USART_FLAG_RXNE) == RESET)
        {
        }

        /* Store the received byte in the RxBuffer1 */
        RxBuffer1[RxCounter1++] = USART_ReceiveData(USARTy);
    }    
    
 



    TransferStatus1 = Buffercmp(TxBuffer1, RxBuffer2, TxBufferSize1);

    TransferStatus2 = Buffercmp(TxBuffer2, RxBuffer1, TxBufferSize2);

    while (1)
    {

        
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
	USART_ClockInitTypeDef UART_ClockInitStruct;
	
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
  
    /*Disable other function*/
    UART_ClockInitStruct.USART_Clock = USART_Clock_Disable;  
    USART_ClockInit(USART2,&UART_ClockInitStruct);
    USART_LINCmd(USART2,DISABLE);
    USART_SmartCardCmd(USART2,DISABLE);
    USART_IrDACmd(USART2,DISABLE);  
    
    USART_ClockInit(USART3,&UART_ClockInitStruct);
    USART_LINCmd(USART3,DISABLE);
    USART_SmartCardCmd(USART3,DISABLE);
    USART_IrDACmd(USART3,DISABLE);    


    /* Enable USARTy Half Duplex Mode*/
    USART_HalfDuplexCmd(USARTy, ENABLE);

    /* Enable USARTz Half Duplex Mode*/
    USART_HalfDuplexCmd(USARTz, ENABLE);   
    
    
    
    /* Enable the USARTy */
    USART_Cmd(USARTy, ENABLE);

    /* Enable the USARTz */
    USART_Cmd(USARTz, ENABLE);



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

 	/*USART3:PD5:TX*/
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
  * @brief  Compares two buffers.
  * @param  pBuffer1, pBuffer2: buffers to be compared.
  * @param  BufferLength: buffer's length
  * @retval PASSED: pBuffer1 identical to pBuffer2
  *         FAILED: pBuffer1 differs from pBuffer2
  */
TestStatus Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint16_t BufferLength)
{
  while(BufferLength--)
  {
    if(*pBuffer1 != *pBuffer2)
    {
      return FAILED;
    }
    
    pBuffer1++;
    pBuffer2++;
  }

  return PASSED;  
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


