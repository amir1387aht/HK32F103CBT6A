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

/** @addtogroup SPI_CRC
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
typedef enum {FAILED = 0, PASSED = !FAILED} TestStatus;

/* Private define ------------------------------------------------------------*/
#define BufferSize 32


/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
SPI_InitTypeDef   SPI_InitStructure;
uint16_t SPI1_Buffer_Tx[BufferSize] = {0x0102, 0x0304, 0x0506, 0x0708, 0x090A, 0x0B0C,
                                  0x0D0E, 0x0F10, 0x1112, 0x1314, 0x1516, 0x1718,
                                  0x191A, 0x1B1C, 0x1D1E, 0x1F20, 0x2122, 0x2324,
                                  0x2526, 0x2728, 0x292A, 0x2B2C, 0x2D2E, 0x2F30,
                                  0x3132, 0x3334, 0x3536, 0x3738, 0x393A, 0x3B3C,
                                  0x3D3E, 0x3F40};
uint16_t SPI2_Buffer_Tx[BufferSize] = {0x5152, 0x5354, 0x5556, 0x5758, 0x595A, 0x5B5C,
                                  0x5D5E, 0x5F60, 0x6162, 0x6364, 0x6566, 0x6768,
                                  0x696A, 0x6B6C, 0x6D6E, 0x6F70, 0x7172, 0x7374,
                                  0x7576, 0x7778, 0x797A, 0x7B7C, 0x7D7E, 0x7F80,
                                  0x8182, 0x8384, 0x8586, 0x8788, 0x898A, 0x8B8C,
                                  0x8D8E, 0x8F90};
uint16_t SPIy_Buffer_Rx[BufferSize], SPIz_Buffer_Rx[BufferSize];
__IO uint8_t TxIdx = 0, RxIdx = 0, k = 0;
__IO uint16_t CRC1Value = 0, CRC2Value = 0;                                  
volatile TestStatus TransferStatus1 = FAILED, TransferStatus2 = FAILED;
/* Private function prototypes -----------------------------------------------*/
static void GPIO_Config(void);
static void SPI_Config(void);                                     

TestStatus Buffercmp(uint16_t* pBuffer1, uint16_t* pBuffer2, uint16_t BufferLength);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */    
int main(void)
{
    GPIO_Config();
    SPI_Config();
    
    
    /* Transfer procedure */
    while (TxIdx < BufferSize )
    {
        /* Wait for SPIy Tx buffer empty */
        while (SPI_I2SGetFlagStatus(SPIy, SPI_I2S_FLAG_TXE) == RESET)
        {
        }

        /* Send SPIz data */
        SPI_I2SSendData(SPIz, SPI1_Buffer_Tx[TxIdx]);

        /* Send SPIy data */
        SPI_I2SSendData(SPIy, SPI2_Buffer_Tx[TxIdx++]);

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
    

    /* Wait for SPIy Tx buffer empty */
    while (SPI_I2SGetFlagStatus(SPIy, SPI_I2S_FLAG_TXE) == RESET)
    {
    }
    /* Wait for SPIz Tx buffer empty */
    while (SPI_I2SGetFlagStatus(SPIz, SPI_I2S_FLAG_TXE) == RESET)
    {
    }

    /* Send last SPIx_Buffer_Tx data */
    SPI_I2SSendData(SPIz, SPI1_Buffer_Tx[TxIdx]);
    
    /* Enable SPI2 CRC transmission */
    SPI_TransmitCRC(SPIz);
    
    /* Send last SPIy_Buffer_Tx data */
    SPI_I2SSendData(SPIy, SPI2_Buffer_Tx[TxIdx]);
    
    /* Enable SPIy CRC transmission */
    SPI_TransmitCRC(SPIy);

    /* Wait for SPIy last data reception */
    while(SPI_I2SGetFlagStatus(SPIy, SPI_I2S_FLAG_RXNE) == RESET)
    {
    }
    /* Read SPIy last received data */
    SPIy_Buffer_Rx[RxIdx++] = SPI_I2SReceiveData(SPIy);

    /* Wait for SPIz last data reception */
    while (SPI_I2SGetFlagStatus(SPIz, SPI_I2S_FLAG_RXNE) == RESET)
    {
    }
    /* Read SPIz last received data */
    SPIz_Buffer_Rx[RxIdx] = SPI_I2SReceiveData(SPIz);

    /* Wait for SPIy data reception: CRC transmitted by SPIz */
    while (SPI_I2SGetFlagStatus(SPIy, SPI_I2S_FLAG_RXNE) == RESET)
    {
    }
    /* Wait for SPIz data reception: CRC transmitted by SPIy */
    while (SPI_I2SGetFlagStatus(SPIz, SPI_I2S_FLAG_RXNE) == RESET)
    {
    }

    /* Check the received data with the send ones */
    TransferStatus1 = Buffercmp(SPIy_Buffer_Rx, SPI1_Buffer_Tx, BufferSize);
    TransferStatus2 = Buffercmp(SPIz_Buffer_Rx, SPI2_Buffer_Tx, BufferSize);


    /* Test on the SPIy CRC Error flag */
    if ((SPI_I2SGetFlagStatus(SPIy, SPI_FLAG_CRCERR)) == SET)
    {
        TransferStatus2 = FAILED;
    }

    /* Test on the SPIz CRC Error flag */
    if ((SPI_I2SGetFlagStatus(SPIz, SPI_FLAG_CRCERR)) == SET)
    {
        TransferStatus1 = FAILED;
    }

    /* Read SPIy received CRC value */
    CRC1Value = SPI_I2SReceiveData(SPIy);
    
    /* Read SPIz received CRC value */
    CRC2Value = SPI_I2SReceiveData(SPIz);
    
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

	RCC_APB2PeriphClockCmd(SPIz_GPIO_CLK,ENABLE);
	RCC_APB2PeriphClockCmd(SPIy_GPIO_CLK,ENABLE);    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStruct;
 

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
    SPI_InitStructure.SPI_DataSize = SPI_DataSize_16b;
    SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_LSB;
    SPI_InitStructure.SPI_CRCPolynomial = 7;
    SPI_Init(SPIy, &SPI_InitStructure);

    
    /* Enable SPIy CRC calculation */
    SPI_CalculateCRC(SPIy, ENABLE);

    /* Enable SPIz CRC calculation */
    SPI_CalculateCRC(SPIz, ENABLE);    

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
TestStatus Buffercmp(uint16_t* pBuffer1, uint16_t* pBuffer2, uint16_t BufferLength)
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


