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

/** @addtogroup I2S_TwoBoardsExchangeIT
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
typedef enum {FAILED = 0, PASSED = !FAILED} TestStatus;

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
I2S_InitTypeDef I2S_InitStructure;
const uint16_t I2S_Buffer_Tx[32] = { 0x0102, 0x0304, 0x0506, 0x0708, 0x090A, 0x0B0C,
                                     0x0D0E, 0x0F10, 0x1112, 0x1314, 0x1516, 0x1718,
                                     0x191A, 0x1B1C, 0x1D1E, 0x1F20, 0x2122, 0x2324,
                                     0x2526, 0x2728, 0x292A, 0x2B2C, 0x2D2E, 0x2F30,
                                     0x3132, 0x3334, 0x3536, 0x3738, 0x393A, 0x3B3C,
                                     0x3D3E, 0x3F40};

uint16_t I2S_Buffer_Rx[32];
__IO uint32_t TxIdx = 0, RxIdx = 0;
TestStatus TransferStatus = FAILED;
ErrorStatus HSEStartUpStatus;

/* Private function prototypes -----------------------------------------------*/
void RCC_Config(void);
void GPIO_Config(void);
void I2s_Init(void);
void NVIC_Config(void);
#if (DEVEICE == I2S_SLAVE_RECEIVER)
TestStatus Buffercmp(uint16_t* pBuffer1, uint16_t* pBuffer2, uint16_t BufferLength);
#endif

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{
    GPIO_Config();
    NVIC_Config();
    I2s_Init();

    HK_EVAL_PBInit(BUTTON_KEY1,BUTTON_MODE_GPIO);

    /* Initialize the LEDs */
    HK_EVAL_LEDInit(LED1);
    HK_EVAL_LEDInit(LED3);    
#if (DEVEICE == I2S_MASTER_TRANSMITTER)
    while (HK_EVAL_PBGetState(BUTTON_KEY1) != RESET)
    {
        
    }
    I2S_Cmd(SPI1, ENABLE);  
#elif (DEVEICE == I2S_SLAVE_RECEIVER)
    while (RxIdx < 32)
    {
        
    }
    /* Check if the data transmitted from Master Board and received by
    Slave Board are the same */
    TransferStatus = Buffercmp(I2S_Buffer_Rx, (uint16_t*)I2S_Buffer_Tx, 32);  
    TransferStatus = Buffercmp(I2S_Buffer_Rx, (uint16_t*)I2S_Buffer_Tx, 32);  
    if (TransferStatus == PASSED) /* successful transfer */ 
    {

        HK_EVAL_LEDOn(LED1);
        HK_EVAL_LEDOff(LED3);
    }
    else /* unsuccessful transfer */ 
    {

        HK_EVAL_LEDOn(LED3);
        HK_EVAL_LEDOff(LED1);
    }       
#endif    



    /* Infinite loop */
    while (1)
    {

        
    }
}
/**
  * @brief  Configures the different system clocks.
  * @param  None
  * @retval None
  */
void I2s_Init(void)
{
    RCC_HCLKConfig(RCC_SYSCLK_Div1);
    I2S_InitTypeDef I2S_InitStructure;



    /* I2S peripheral configuration */
    I2S_InitStructure.I2S_Standard = I2S_Standard_Phillips;
    I2S_InitStructure.I2S_DataFormat = I2S_DataFormat_16b;
    I2S_InitStructure.I2S_MCLKOutput = I2S_MCLKOutput_Disable;
    I2S_InitStructure.I2S_AudioFreq = I2S_AudioFreq_16k;
    I2S_InitStructure.I2S_CPOL = I2S_CPOL_Low;

#if (DEVEICE == I2S_MASTER_TRANSMITTER)

    /* Enable the CODEC_I2S peripheral clock */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);

    /* I2S Master Transmitter configuration */
    I2S_InitStructure.I2S_Mode = I2S_Mode_MasterTx;

    /* Enable the I2S2 TxNE interrupt */
    SPI_I2SITConfig(SPI1, SPI_I2S_IT_TXE, ENABLE);
    I2S_Init(SPI1, &I2S_InitStructure);
#elif (DEVEICE ==I2S_SLAVE_RECEIVER)

    /* Enable the CODEC_I2S peripheral clock */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);

    /* I2S Slave Receiver configuration */
    I2S_InitStructure.I2S_Mode = I2S_Mode_SlaveRx;

    /* Enable the I2S2 RxNE interrupt */
    SPI_I2SITConfig(SPI2, SPI_I2S_IT_RXNE, ENABLE);
    
    I2S_Init(SPI2, &I2S_InitStructure);
    I2S_Cmd(SPI2, ENABLE);  
#endif


}




/**
  * @brief  Deinitializes the GPIO peripheral registers to their default reset values.
  * @param  None
  * @retval None
  */
void GPIO_Config(void)
{

	
	GPIO_InitTypeDef GPIO_InitStruct;
    

#if (DEVEICE == I2S_MASTER_TRANSMITTER)
   	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE); 

    /* Configure SPI1 pins: CK and SD ------------------------------------*/
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7| GPIO_Pin_5|GPIO_Pin_4;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;   
    GPIO_Init(GPIOA, &GPIO_InitStruct);
#elif (DEVEICE ==I2S_SLAVE_RECEIVER)    
    
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12| GPIO_Pin_13 | GPIO_Pin_15;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;

    GPIO_Init(GPIOB, &GPIO_InitStruct);
#endif


  
        
 
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
  * @brief  Configure the nested vectored interrupt controller.
  * @param  None
  * @retval None
  */
void NVIC_Config(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;

  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
#if (DEVEICE == I2S_MASTER_TRANSMITTER)

  /* SPI1 IRQ Channel configuration */
  NVIC_InitStructure.NVIC_IRQChannel = SPI1_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
    
#elif (DEVEICE ==I2S_SLAVE_RECEIVER)    

   /* SPI2 IRQ channel configuration */
  NVIC_InitStructure.NVIC_IRQChannel = SPI2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);   
#endif
}
#if (DEVEICE == I2S_SLAVE_RECEIVER)
/**
  * @brief  Compares two buffers.
  * @param  pBuffer1, pBuffer2: buffers to be compared.
  * @param  BufferLength: buffer's length
  * @retval PASSED: pBuffer1 identical to pBuffer2
  *         FAILED: pBuffer1 differs from pBuffer2
  */
static TestStatus Buffercmp(uint16_t* pBuffer1, uint16_t* pBuffer2, uint16_t BufferLength)
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
#endif
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


