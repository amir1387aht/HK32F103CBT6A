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

/** @addtogroup SPI_FullDuplex_SoftNSS
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
uint8_t SPIz_Buffer_Tx[BufferSize] = {0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57,
                                      0x58, 0x59, 0x5A, 0x5B, 0x5C, 0x5D, 0x5E,
                                      0x5F, 0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 
                                      0x66, 0x67, 0x68, 0x69, 0x6A, 0x6B, 0x6C,
                                      0x6D, 0x6E, 0x6F, 0x70};
uint8_t SPIy_Buffer_Rx[BufferSize], SPIz_Buffer_Rx[BufferSize];
__IO uint8_t TxIdx = 0, RxIdx = 0, k = 0;
volatile TestStatus TransferStatus1 = FAILED, TransferStatus2 = FAILED;
volatile TestStatus TransferStatus3 = FAILED, TransferStatus4 = FAILED;
/* Private function prototypes -----------------------------------------------*/

static void GPIO_Config(uint16_t SPIy_Mode, uint16_t SPIz_Mode);
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
    GPIO_Config(SPI_Mode_Master, SPI_Mode_Slave);
    SPI_Config();
    
    
    /* Transfer procedure */
    while (TxIdx < BufferSize)
    {
        /* Wait for SPIy Tx buffer empty */
        while (SPI_I2SGetFlagStatus(SPIy, SPI_I2S_FLAG_TXE) == RESET)
        {
        }

        /* Send SPIz data */
        SPI_I2SSendData(SPIz, SPIz_Buffer_Tx[TxIdx]);

        /* Send SPIy data */
        SPI_I2SSendData(SPIy, SPIy_Buffer_Tx[TxIdx++]);

        /* Wait for SPIz data reception */
        while (SPI_I2SGetFlagStatus(SPIz, SPI_I2S_FLAG_RXNE) == RESET)
        {
        }

        /* Read SPIz received data */
        SPIz_Buffer_Rx[RxIdx] = SPI_I2SReceiveData(SPIz);

        /* Wait for SPIy data reception */
        while (SPI_I2SGetFlagStatus(SPIy, SPI_I2S_FLAG_RXNE) == RESET)
        {
        }

        /* Read SPIy received data */
        SPIy_Buffer_Rx[RxIdx++] = SPI_I2SReceiveData(SPIy);
    }   
    
    /* Check the correctness of written dada */
    TransferStatus1 = Buffercmp(SPIz_Buffer_Rx, SPIy_Buffer_Tx, BufferSize);
    TransferStatus2 = Buffercmp(SPIy_Buffer_Rx, SPIz_Buffer_Tx, BufferSize);  


    /* GPIO configuration ------------------------------------------------------*/
    GPIO_Config(SPI_Mode_Slave , SPI_Mode_Master); 
    /* SPIy Re-configuration ---------------------------------------------------*/
    SPI_InitStructure.SPI_Mode = SPI_Mode_Slave;
    SPI_Init(SPIy, &SPI_InitStructure);
    /* SPIz Re-configuration ---------------------------------------------------*/
    SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
    SPI_Init(SPIz, &SPI_InitStructure); 
    /* Reset TxIdx, RxIdx indexes and receive tables values */
    TxIdx = 0;
    RxIdx = 0;
    for (k = 0; k < BufferSize; k++)  
    {
        SPIz_Buffer_Rx[k] = 0;
    }
    for (k = 0; k < BufferSize; k++)
    {    
        SPIy_Buffer_Rx[k] = 0;
    }

    /* Transfer procedure */
    while (TxIdx < BufferSize)
    {
        /* Wait for SPIz Tx buffer empty */
        while (SPI_I2SGetFlagStatus(SPIz, SPI_I2S_FLAG_TXE) == RESET)
        {
        }

        /* Send SPIy data */
        SPI_I2SSendData(SPIy, SPIy_Buffer_Tx[TxIdx]);

        /* Send SPIz data */
        SPI_I2SSendData(SPIz, SPIz_Buffer_Tx[TxIdx++]);

        /* Wait for SPIy data reception */
        while (SPI_I2SGetFlagStatus(SPIy, SPI_I2S_FLAG_RXNE) == RESET)
        {
        }

        /* Read SPIy received data */
        SPIy_Buffer_Rx[RxIdx] = SPI_I2SReceiveData(SPIy);

        /* Wait for SPIz data reception */
        while (SPI_I2SGetFlagStatus(SPIz, SPI_I2S_FLAG_RXNE) == RESET)
        {
        }

        /* Read SPIz received data */
        SPIz_Buffer_Rx[RxIdx++] = SPI_I2SReceiveData(SPIz);
    }

        /* Check the correctness of written dada */
        TransferStatus3 = Buffercmp(SPIz_Buffer_Rx, SPIy_Buffer_Tx, BufferSize);
        TransferStatus4 = Buffercmp(SPIy_Buffer_Rx, SPIz_Buffer_Tx, BufferSize);    
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
void GPIO_Config(uint16_t SPIy_Mode, uint16_t SPIz_Mode)
{

 

 

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

        /*SPI3_MASTER:MOSI:PA7---SPI_SCK:PA5*/ 
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

    /* Enable SPIy */
    SPI_Cmd(SPIy, ENABLE);

    /* Enable SPIz */
    SPI_Cmd(SPIz, ENABLE);
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


