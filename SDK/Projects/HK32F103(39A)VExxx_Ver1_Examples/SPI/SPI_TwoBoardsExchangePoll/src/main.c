/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  main.c
* @brief:     SPI/SPI_TwoBoardsExchangePoll/main.c 
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

/** @addtogroup SPI_TwoBoardsExchangePoll
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
typedef enum {FAILED = 0, PASSED = !FAILED} TestStatus;

/* Private define ------------------------------------------------------------*/
#define BufferSize 5
#define MASTER 1 
#define SLAVER 0

#define SPI_CS_HIGH  		  GPIO_SetBits(GPIOA,GPIO_Pin_4);
#define SPI_CS_LOW 		      GPIO_ResetBits(GPIOA,GPIO_Pin_4);
#define ACK    1
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
SPI_InitTypeDef   SPI_InitStructure;

uint8_t SPIz_Buffer_Tx[BufferSize] = {0x51, 0x52, 0x53, 0x54, 0x55};
uint8_t SPIy_Buffer_Rx[BufferSize], SPIz_Buffer_Rx[BufferSize];
__IO uint8_t TxIdx = 0, RxIdx = 0, k = 0;
volatile TestStatus TransferStatus1 = FAILED, TransferStatus2 = FAILED;
uint8_t AckFlag = 0;

/* Private function prototypes -----------------------------------------------*/

static void GPIO_Config(void);
static void SPI_Config(void);                                     

TestStatus Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint16_t BufferLength);
uint8_t SPI1_ReadWriteBit_8(uint8_t data);
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
    
   
    #if (DEVICE == MASTER)
        HK_EVAL_PBInit(BUTTON_KEY1,BUTTON_MODE_GPIO);     
        while(HK_EVAL_PBGetState(BUTTON_KEY1) != RESET)
        {
        }
        while (TxIdx <= BufferSize)
        { 
            SPI_CS_LOW
            while (SPI_I2SGetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET)
            {
            }

            /* Send SPIy data */
            SPI_I2SSendData(SPI1, SPIz_Buffer_Tx[TxIdx++]);   
            if(TxIdx == BufferSize)
            {
                TxIdx++;
            }
            SPI_CS_HIGH 
        }

    #elif (DEVICE == SLAVER)

        while (RxIdx <= BufferSize)
        { 

            while (SPI_I2SGetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET)
            {
            }

            /* Read SPIy received data */
            SPIz_Buffer_Rx[RxIdx++] = SPI_I2SReceiveData(SPI1);
            if(RxIdx == BufferSize)
            {
                RxIdx++;
            } 
            
        }  

           
    #endif         

    #if (DEVICE == MASTER)

    #elif (DEVICE == SLAVER)

        /* Check the correctness of written dada */
        TransferStatus2 = Buffercmp(SPIz_Buffer_Rx, SPIz_Buffer_Tx, BufferSize); 
    #endif       
    

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


	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);	
	GPIO_InitTypeDef GPIO_InitStruct;
 

	
    #if (DEVICE == MASTER)
        /*MISO:PA6*/
        GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7|GPIO_Pin_5;
        GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOA, &GPIO_InitStruct);	
        /*MOSI:PA7---SPI_SCK:PA5*/    
        GPIO_InitStruct.GPIO_Pin =GPIO_Pin_6;
        GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_Init(GPIOA, &GPIO_InitStruct);	 

	
        GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4;
        GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;	       
        GPIO_Init(GPIOA, &GPIO_InitStruct);
    #elif (DEVICE == SLAVER)


        /*MISO:PA6*/
        GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6;
        GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOA, &GPIO_InitStruct);	
        /*MOSI:PA7---SPI_SCK:PA5*/    
        GPIO_InitStruct.GPIO_Pin =GPIO_Pin_7|GPIO_Pin_5|GPIO_Pin_4;
        GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_Init(GPIOA, &GPIO_InitStruct);	 
    #endif  


}
/**
  * @brief  Deinitializes the SPI peripheral registers to their default reset values.
  * @param  None
  * @retval None
  */
void SPI_Config(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1,ENABLE);    
    
    SPI_InitTypeDef SPI_InitStructure;

    SPI_StructInit(&SPI_InitStructure);

    SPI_I2SDeInit(SPI1);
    

    /* SPI1 Config */
    SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
    SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
    SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
    SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_LSB;
    SPI_InitStructure.SPI_CRCPolynomial = 7;

    #if (DEVICE == MASTER)
        SPI_InitStructure.SPI_Mode = SPI_Mode_Master;   

    #elif (DEVICE == SLAVER)
        SPI_InitStructure.SPI_Mode = SPI_Mode_Slave;
    #endif

    
 
    /* Configure SPI1 */
    SPI_Init(SPI1, &SPI_InitStructure);

    

    /* SPI1 enable */
    SPI_Cmd(SPI1, ENABLE);   
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


