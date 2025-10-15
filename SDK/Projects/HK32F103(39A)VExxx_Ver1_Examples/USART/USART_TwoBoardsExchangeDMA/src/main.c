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

/** @addtogroup USART_TwoBoardsExchangeDMA
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
typedef enum {FAILED = 0, PASSED = !FAILED} TestStatus;
/* Private define ------------------------------------------------------------*/


#define TxBufferSize1   (countof(TxBuffer1)-1)
#define TxBufferSize2   (countof(TxBuffer2)-1)

/* Private macro -------------------------------------------------------------*/
#define countof(a)   (sizeof(a) / sizeof(*(a)))
/* Private variables ---------------------------------------------------------*/
uint8_t TxBuffer1[] = "USART DMA Interrupt: USARTy -> USARTz using DMA Tx and Rx Flag";
uint8_t TxBuffer2[] = "USART DMA Polling: USARTz -> USARTy using DMA";
uint8_t RxBuffer1[TxBufferSize2];
uint8_t RxBuffer2[TxBufferSize1];
#if (DEVICE == MASTER) 
uint8_t NbrOfDataToRead = TxBufferSize2;
#elif (DEVICE == SLAVE) 
uint8_t NbrOfDataToRead = TxBufferSize1;
#endif  
uint8_t RxCounter = 0;
volatile TestStatus TransferStatus1 = FAILED, TransferStatus2 = FAILED;
extern  uint16_t Delay_ms;
/* Private function prototypes -----------------------------------------------*/

static void USART_Config(void);
static void GPIO_Config(void);
static void NVIC_Config(void);
static void DMA_Config(void);
void SendData(uint8_t data);
uint8_t ReceiveData(void);
TestStatus Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint16_t BufferLength);
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
    HK_EVAL_PBInit(BUTTON_KEY1,BUTTON_MODE_GPIO);   
	NVIC_SetPriority(SysTick_IRQn, 0x0);    
    NVIC_Config(); 
    GPIO_Config();
    DMA_Config();
    USART_Config();

    
    USART_Cmd(USART2,ENABLE);   
    while (HK_EVAL_PBGetState(BUTTON_KEY1) != RESET)
    {
    }     
   


    /* Enable USARTy DMA TX Channel */
    DMA_Cmd(DMA1_Channel7, ENABLE);     



    /* Wait until USARTy TX DMA1 Channel  Transfer Complete */
    while(DMA_GetFlagStatus(DMA1_FLAG_TC7) == RESET)
    {
    }

    /* Infinite loop */
    while (1)
    {

        if(RxCounter == NbrOfDataToRead)
        {
            #if (DEVICE == MASTER) 
            
                /* Check the received data with the send ones */
                TransferStatus1 = Buffercmp(TxBuffer2, RxBuffer1, TxBufferSize2);        
            #elif (DEVICE == SLAVE) 
                TransferStatus2 = Buffercmp(TxBuffer1, RxBuffer2, TxBufferSize1);
            #endif  
        }   
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
    /*USART1_RCC: AHB2*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
    /*USART1_RCC: AHB1*/
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
    
    
    /* Enable USARTy DMA TX request */
    USART_DMACmd(USART2, USART_DMAReq_Tx, ENABLE);

    
    USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);   



    USART_Cmd(USART1,ENABLE);



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
  * @brief  Send one byte
  * @param  data: Sent data
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
  * @retval data: Received data
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

/**
  * @brief  Configures the DMA.
  * @param  None
  * @retval None
  */
void DMA_Config(void)
{
    /* DMA clock enable */
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
    DMA_InitTypeDef DMA_InitStructure;


    #if (DEVICE == MASTER) 
    
    /* USARTy_Tx_DMA_Channel (triggered by USARTy Tx event) Config */
    DMA_DeInit(DMA1_Channel7);
    DMA_InitStructure.DMA_PeripheralBaseAddr = 0x40004404;
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)TxBuffer1;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
    DMA_InitStructure.DMA_BufferSize = TxBufferSize1;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
    DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
    DMA_Init(DMA1_Channel7, &DMA_InitStructure);   

    #elif (DEVICE == SLAVE) 
    
    /* USARTy_Tx_DMA_Channel (triggered by USARTy Tx event) Config */
    DMA_DeInit(DMA1_Channel7);
    DMA_InitStructure.DMA_PeripheralBaseAddr = 0x40004404;
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)TxBuffer2;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
    DMA_InitStructure.DMA_BufferSize = TxBufferSize2;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
    DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
    DMA_Init(DMA1_Channel7, &DMA_InitStructure);   
    #endif  
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


