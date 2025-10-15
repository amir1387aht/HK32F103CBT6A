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

/** @addtogroup USART_Synchronous
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
typedef enum {FAILED = 0, PASSED = !FAILED} TestStatus;

/* Private define ------------------------------------------------------------*/
#define TxBufferSize1   (countof(TxBuffer1) - 1)
#define TxBufferSize2   (countof(TxBuffer2) - 1)
#define DYMMY_BYTE      0x00

/* Private macro -------------------------------------------------------------*/
#define countof(a)   (sizeof(a) / sizeof(*(a)))

/* Private variables ---------------------------------------------------------*/
USART_InitTypeDef USART_InitStructure;
USART_ClockInitTypeDef USART_ClockInitStructure; 

uint8_t TxBuffer1[] = "USART Synchronous Example: USARTy -> SPIy using TXE and RXNE Flags";
uint8_t TxBuffer2[] = "USART Synchronous Example: SPIy -> USARTy using TXE and RXNE Flags";
uint8_t RxBuffer1[TxBufferSize2];
uint8_t RxBuffer2[TxBufferSize1];
__IO uint8_t NbrOfDataToRead1 = TxBufferSize2;
__IO uint8_t NbrOfDataToRead2 = TxBufferSize1;
__IO uint8_t TxCounter1 = 0, RxCounter1 = 0;
__IO uint8_t TxCounter2 = 0, RxCounter2 = 0;
volatile TestStatus TransferStatus1 = FAILED, TransferStatus2 = FAILED; 

/* Private function prototypes -----------------------------------------------*/

static void UART_Config(void);
static void GPIO_Config(void);
static void SPI_Config(void);

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

    SPI_Config();

    while(NbrOfDataToRead2--)
    {
        /* Write one byte in the USARTy Transmit Data Register */
        USART_SendData(USARTy, TxBuffer1[TxCounter1++]);
        
        /* Wait until end of transmit */
        while(USART_GetFlagStatus(USARTy, USART_FLAG_TC) == RESET)
        {
        }
        
        /* Wait the byte is entirely received by SPIy */  
        while(SPI_I2SGetFlagStatus(SPIy, SPI_I2S_FLAG_RXNE) == RESET)
        {
        }

        /* Store the received byte in the RxBuffer2 */
        RxBuffer2[RxCounter2++] = SPI_I2SReceiveData(SPIy);
    }

    /* Clear the USARTy Data Register */
    USART_ReceiveData(USARTy);

    while(NbrOfDataToRead1--)
    {
        /* Wait until end of transmit */
        while(SPI_I2SGetFlagStatus(SPIy, SPI_I2S_FLAG_TXE)== RESET)
        {
        }

        /* Write one byte in the SPIy Transmit Data Register */
        SPI_I2SSendData(SPIy, TxBuffer2[TxCounter2++]);

        /* Send a Dummy byte to generate clock to slave */ 
        USART_SendData(USARTy, DYMMY_BYTE);
        
        /* Wait until end of transmit */
        while(USART_GetFlagStatus(USARTy, USART_FLAG_TC) == RESET)
        {
        }

        /* Wait the byte is entirely received by USARTy */
        while(USART_GetFlagStatus(USARTy, USART_FLAG_RXNE) == RESET)
        {
        }

        /* Store the received byte in the RxBuffer1 */
        RxBuffer1[RxCounter1++] = USART_ReceiveData(USARTy);
  }
  
  /* Check the received data with the send ones */
  TransferStatus1 = Buffercmp(TxBuffer1, RxBuffer2, TxBufferSize1);

  /* TransferStatus = PASSED, if the data transmitted from USARTy and  
     received by SPIy are the same */

  /* TransferStatus = FAILED, if the data transmitted from USARTy and 
     received by SPIy are different */
  TransferStatus2 = Buffercmp(TxBuffer2, RxBuffer1, TxBufferSize2);

  /* TransferStatus = PASSED, if the data transmitted from SPIy and  
     received by USARTy are the same */

  /* TransferStatus = FAILED, if the data transmitted from SPIy and 
     received by USARTy are different */

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
 
    RCC_APB2PeriphClockCmd(USARTy_CLK, ENABLE); 

	
	USART_InitTypeDef USART_InitStructure;

    USART_ClockInitTypeDef USART_ClockInitStructure;
	
    USART_ClockInitStructure.USART_Clock = USART_Clock_Enable;
    USART_ClockInitStructure.USART_CPOL = USART_CPOL_High;
    USART_ClockInitStructure.USART_CPHA = USART_CPHA_2Edge;
    USART_ClockInitStructure.USART_LastBit = USART_LastBit_Enable;
    USART_ClockInit(USARTy, &USART_ClockInitStructure);

    USART_InitStructure.USART_BaudRate = 115200;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No ;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(USARTy, &USART_InitStructure);
  
    /* Configure the USARTy */
    USART_Init(USARTy, &USART_InitStructure);

    /* Enable the USARTy */
    USART_Cmd(USARTy, ENABLE);

    RCC_HCLKConfig(RCC_SYSCLK_Div1);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);


 	


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
	GPIO_InitStruct.GPIO_Pin = USARTy_TxPin|USARTy_ClkPin|SPIy_MISOPin;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStruct);	
    /*MOSI:PA7---SPI_SCK:PA5*/    
    GPIO_InitStruct.GPIO_Pin = USARTy_RxPin|SPIy_MOSIPin|SPIy_SCKPin;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStruct);	

    /*USART1:PA9_TX---PA10_RX---MISO:PA6*/
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9|GPIO_Pin_8|GPIO_Pin_6;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStruct);	
    /*MOSI:PA7---SPI_SCK:PA5*/    
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_7|GPIO_Pin_5;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStruct);	     
}

/**
  * @brief  Configures the SPI.
  * @param  None
  * @retval None
  */
void SPI_Config(void)
{
    RCC_APB2PeriphClockCmd(SPIy_CLK,ENABLE);    
    SPI_InitTypeDef SPI_InitStructure;

    SPI_StructInit(&SPI_InitStructure);

    SPI_I2SDeInit(SPIy);

    /* SPIy Config */
    SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
    SPI_InitStructure.SPI_Mode = SPI_Mode_Slave;
    SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
    SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_LSB;
  
    /* Configure SPIy */
    SPI_Init(SPIy, &SPI_InitStructure);

    /* SPIy enable */
    SPI_Cmd(SPIy, ENABLE);
   
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


