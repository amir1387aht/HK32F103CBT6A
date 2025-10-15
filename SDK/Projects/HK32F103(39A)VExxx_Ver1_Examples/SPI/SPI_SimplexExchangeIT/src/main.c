/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  main.c
* @brief:     SPI/SPI_SimplexExchangeIT/main.c 
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

/** @addtogroup SPI_SimplexExchangeIT
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
typedef enum {FAILED = 0, PASSED = !FAILED} TestStatus;

/* Private define ------------------------------------------------------------*/
#define BufferSize 32

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
SPI_InitTypeDef SPI_InitStructure;
uint8_t SPI_MASTER_Buffer_Tx[BufferSize] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06,
                                            0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C,
                                            0x0D, 0x0E, 0x0F, 0x10, 0x11, 0x12,
                                            0x13, 0x14, 0x15, 0x16, 0x17, 0x18,
                                            0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E,
                                            0x1F, 0x20};
uint8_t SPI_SLAVE_Buffer_Rx[BufferSize];
__IO uint8_t TxIdx = 0, RxIdx = 0;
volatile TestStatus TransferStatus = FAILED;


/* Private function prototypes -----------------------------------------------*/

static void GPIO_Config(void);
static void SPI_Config(void);                                     
static void NVIC_Config(void);
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
    NVIC_Config(); 
    SPI_Config();
   
    
    /* Transfer procedure */
    while (RxIdx < BufferSize)
    {
    }

    /* Check the correctness of written dada */
    TransferStatus = Buffercmp(SPI_SLAVE_Buffer_Rx, SPI_MASTER_Buffer_Tx, BufferSize);
    /* TransferStatus = PASSED, if the transmitted and received data
     are equal */
    /* TransferStatus = FAILED, if the transmitted and received data
     are different */

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

	RCC_APB2PeriphClockCmd(SPIy_GPIO_CLK,ENABLE);
	RCC_APB2PeriphClockCmd(SPIz_GPIO_CLK,ENABLE);    
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

    /*SPI3_MASTER:MOSI:PA5---SPI_SCK:PA3*/ 
    GPIO_InitStruct.GPIO_Pin = SPIy_PIN_SCK|SPIy_PIN_MOSI;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(SPIy_GPIO, &GPIO_InitStruct);	
    /*MISO:PA4*/    
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
    RCC_APB2PeriphClockCmd(SPIy_CLK,ENABLE);  
    RCC_APB1PeriphClockCmd(SPIz_CLK,ENABLE);      
    
    SPI_InitTypeDef SPI_InitStructure;

    SPI_StructInit(&SPI_InitStructure);


    
    SPI_I2SDeInit(SPIz);
    SPI_I2SDeInit(SPIy);

    /* SPI1 Config */
    SPI_InitStructure.SPI_Direction = SPI_Direction_1Line_Tx;


    SPI_InitStructure.SPI_Mode = SPI_Mode_Master;   
    SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
    SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_LSB;

    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;

    /* Configure SPIy */
    SPI_Init(SPIy, &SPI_InitStructure);

    /* Configure SPIz*/ 
    SPI_InitStructure.SPI_Direction = SPI_Direction_1Line_Rx;
    SPI_InitStructure.SPI_Mode = SPI_Mode_Slave;
    SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_RxOnly;  

    /* Configure SPIz */
    SPI_Init(SPIz, &SPI_InitStructure);

    /* SPIy enable */
    SPI_Cmd(SPIy, ENABLE);    

    /* SPIz enable */
    SPI_Cmd(SPIz, ENABLE);  


    /* Enable SPI_SLAVE RXNE interrupt */
    SPI_I2SITConfig(SPIz, SPI_I2S_IT_RXNE, ENABLE);       

    /* Enable SPI_MASTER TXE interrupt */
    SPI_I2SITConfig(SPIy, SPI_I2S_IT_TXE, ENABLE);
    
    
}
/**
  * @brief  Deinitializes the NVIC peripheral registers to their default reset values.
  * @param  None
  * @retval None
  */
void NVIC_Config(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;

    /* 1 bit for pre-emption priority, 3 bits for subpriority */
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
  
    /* Configure and enable SPI_MASTER interrupt -------------------------------*/
    NVIC_InitStructure.NVIC_IRQChannel = SPI3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    /* Configure and enable SPI_SLAVE interrupt --------------------------------*/
    NVIC_InitStructure.NVIC_IRQChannel = SPI2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority =1;
    NVIC_Init(&NVIC_InitStructure);   
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


