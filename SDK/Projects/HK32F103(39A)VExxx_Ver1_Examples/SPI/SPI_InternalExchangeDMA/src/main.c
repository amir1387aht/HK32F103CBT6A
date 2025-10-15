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

/** @addtogroup SPI_InternalExchangeDMA
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
typedef enum {FAILED = 0, PASSED = !FAILED} TestStatus;

/* Private define ------------------------------------------------------------*/
#define BufferSize 32


/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
SPI_InitTypeDef   SPI_InitStructure;
uint8_t SPIy_Buffer_Tx[BufferSize] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
                                      0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E,
                                      0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15,
                                      0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C,
                                      0x1D, 0x1E, 0x1F, 0x20};

uint8_t SPIy_Buffer_Rx[BufferSize], SPIz_Buffer_Rx[BufferSize];
__IO uint8_t TxIdx = 0, RxIdx = 0, k = 0;
volatile TestStatus TransferStatus = FAILED;


/* Private function prototypes -----------------------------------------------*/
static void GPIO_Config(uint16_t SPIy_Mode, uint16_t SPIz_Mode);
static void SPI_Config(void);                                     
uint8_t SPI_ReadWriteBit_8(uint8_t data);
uint8_t SPIy_ReadWriteBit_8(uint8_t data);
TestStatus Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint16_t BufferLength);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */  
int main(void)
{
    GPIO_Config(SPI_Mode_Master, SPI_Mode_Slave);
    SPI_Config();
    
    
    /* Transfer procedure */
    while (TxIdx < BufferSize)
    {

        SPIy_ReadWriteBit_8(SPIy_Buffer_Tx[TxIdx++]);

    }  

    /* Wait for DMA1 channel4 transfer complete */
    while (!DMA_GetFlagStatus(DMA1_FLAG_TC4))
    {
    }        
    /* Check the correctness of written dada */
    TransferStatus = Buffercmp(SPIz_Buffer_Rx, SPIy_Buffer_Tx, BufferSize);
    /* TransferStatus = PASSED, if the transmitted and received data
     are equal */
    /* TransferStatus = FAILED, if the transmitted and received data
     are different */ 
    while (1)
    {

        
    }
}



/**
  * @brief  Deinitializes the GPIO peripheral registers to their default reset values.
  * @param  None
  * @retval None
  */
void GPIO_Config(uint16_t SPIy_Mode, uint16_t SPIz_Mode)
{

    RCC_AHBPeriphClockCmd(SPIz_DMA_CLK, ENABLE);

 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(SPIz_GPIO_CLK,ENABLE);
	RCC_APB2PeriphClockCmd(SPIy_GPIO_CLK,ENABLE);    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStruct;
 
    if((SPIy_Mode == SPI_Mode_Master)&&(SPIz_Mode == SPI_Mode_Slave))
    {
        /*SPI2_SLAVER:P13:CK---P14:MISO---P15:MOSI*/
        GPIO_InitStruct.GPIO_Pin = SPIz_PIN_MISO;
        GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(SPIz_GPIO, &GPIO_InitStruct);	 
      
        GPIO_InitStruct.GPIO_Pin =SPIz_PIN_SCK|SPIz_PIN_MOSI;
        GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_Init(SPIz_GPIO, &GPIO_InitStruct);	 	

        /*SPI3_MASTER:MOSI:PA7---SPI_SCK:PA4*/ 
        GPIO_InitStruct.GPIO_Pin = SPIy_PIN_SCK|SPIy_PIN_MOSI;
        GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(SPIy_GPIO, &GPIO_InitStruct);	
        /*MISO:PA6*/    
        GPIO_InitStruct.GPIO_Pin = SPIy_PIN_MISO;
        GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_Init(SPIy_GPIO, &GPIO_InitStruct);	 
    
  

    }else{
        /*SPI2_MASTER:P13:CK---P14:MISO---P15:MOSI*/
        GPIO_InitStruct.GPIO_Pin = SPIz_PIN_SCK|SPIz_PIN_MOSI;
        GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(SPIz_GPIO, &GPIO_InitStruct);	 
        GPIO_InitStruct.GPIO_Pin =SPIz_PIN_MISO;
        GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_Init(SPIz_GPIO, &GPIO_InitStruct);	 	




        /*SPI3_MASTER:MOSI:PD4---SPI_SCK:PD6--*MISO:PD5*/    
        GPIO_InitStruct.GPIO_Pin = SPIy_PIN_MISO;
        GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(SPIy_GPIO, &GPIO_InitStruct);	
        GPIO_InitStruct.GPIO_Pin = SPIy_PIN_SCK|SPIy_PIN_MOSI;
        GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_Init(SPIy_GPIO, &GPIO_InitStruct);	        
  

      
    }



}
/**
  * @brief  Deinitializes the SPI peripheral registers to their default reset values.
  * @param  None
  * @retval None
  */
void SPI_Config(void)
{
    /* Enable SPIy Periph clock */
    RCC_APB2PeriphClockCmd(SPIy_CLK, ENABLE);
                           

    /* Enable SPIz Periph clock */
    RCC_APB1PeriphClockCmd(SPIz_CLK, ENABLE);      
    
    DMA_InitTypeDef  DMA_InitStructure;   
    
    
    /* SPI_SLAVE_Rx_DMA_Channel configuration ---------------------------------------------*/
    DMA_DeInit(SPIz_DMA_Channel);
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)0x4000380C;
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)SPIz_Buffer_Rx;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
    DMA_InitStructure.DMA_BufferSize = BufferSize;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
    DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
    DMA_Init(SPIz_DMA_Channel, &DMA_InitStructure);    
    
    
    
    
    
    
    
    
    /* SPIy Config -------------------------------------------------------------*/
    SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
    SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
    SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
    SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_LSB;
    SPI_InitStructure.SPI_CRCPolynomial = 7;
    SPI_Init(SPIy, &SPI_InitStructure);

    /* SPIz Config -------------------------------------------------------------*/
    SPI_InitStructure.SPI_Mode = SPI_Mode_Slave;
    SPI_Init(SPIz, &SPI_InitStructure);
    
    
    /* Enable SPI_SLAVE Rx request */
    SPI_I2SDMACmd(SPIz, SPI_I2S_DMAReq_Rx, ENABLE);

    /* Enable SPIy */
    SPI_Cmd(SPIy, ENABLE);

    /* Enable SPIz */
    SPI_Cmd(SPIz, ENABLE);

    /* Enable DMA1 Channel4 */
    DMA_Cmd(DMA1_Channel4, ENABLE);
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
  while (BufferLength--)
  {
    if (*pBuffer1 != *pBuffer2)
    {
      return FAILED;
    }

    pBuffer1++;
    pBuffer2++;
  }

  return PASSED;
}
/**
  * @brief  8 bit Read and write program for the SPI peripheral registers.
  * @param  data: Written data
  * @retval SPI_I2SReceiveData(SPIz): read data for the SPIz.
  */
uint8_t SPI_ReadWriteBit_8(uint8_t data)
{
	while(SPI_I2SGetFlagStatus(SPIz,SPI_I2S_FLAG_TXE) == RESET)
    {
    };
    
    SPI_I2SSendData(SPIz,data);
    
	while(SPI_I2SGetFlagStatus(SPIz,SPI_I2S_FLAG_RXNE) == RESET)
    {
    }
	return SPI_I2SReceiveData(SPIz);
}
/**
  * @brief  8 bit Read and write program for the SPI peripheral registers.
  * @param  data: Written data
  * @retval SPI_I2SReceiveData(SPIy): read data for the SPIy.
  */
uint8_t SPIy_ReadWriteBit_8(uint8_t data)
{
	while(SPI_I2SGetFlagStatus(SPIy,SPI_I2S_FLAG_TXE) == RESET)
    {
    };
    
    SPI_I2SSendData(SPIy,data);
    
	while(SPI_I2SGetFlagStatus(SPIy,SPI_I2S_FLAG_RXNE) == RESET)
    {
    }
	return SPI_I2SReceiveData(SPIy);
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


