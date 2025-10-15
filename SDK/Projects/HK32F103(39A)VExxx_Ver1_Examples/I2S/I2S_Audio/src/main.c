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

/** @addtogroup I2S_Audio
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
typedef enum {FAILED = 0, PASSED = !FAILED} TestStatus;

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void GPIO_Config(void);
static void I2S1_Init(void);
static void NVIC_Config(void);



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
    I2S1_Init();

    while (1)
    {

        
    }
}
/**
  * @brief  I2s initialization.
  * @param  None
  * @retval None
  */
void I2S1_Init(void)
{
    RCC_HCLKConfig(RCC_SYSCLK_Div1);
    I2S_InitTypeDef I2S_InitStructure;



    /* Enable the CODEC_I2S peripheral clock */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);

    /* CODEC_I2S peripheral configuration */
    SPI_I2SDeInit(SPI1);
    I2S_InitStructure.I2S_AudioFreq = I2S_AudioFreq_16k;
    I2S_InitStructure.I2S_Standard = I2S_Standard_Phillips;
    I2S_InitStructure.I2S_DataFormat = I2S_DataFormat_16b;
    I2S_InitStructure.I2S_CPOL = I2S_CPOL_Low;
    I2S_InitStructure.I2S_Mode = I2S_Mode_MasterTx;
    I2S_InitStructure.I2S_MCLKOutput = I2S_MCLKOutput_Disable;

    /* Initialize the I2S peripheral with the structure above */
    I2S_Init(SPI1, &I2S_InitStructure);  
    

    /* Enable the CODEC_I2S peripheral clock */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);

    /* CODEC_I2S peripheral configuration */
    SPI_I2SDeInit(SPI2);
    I2S_InitStructure.I2S_AudioFreq = I2S_AudioFreq_16k;
    I2S_InitStructure.I2S_Standard = I2S_Standard_Phillips;
    I2S_InitStructure.I2S_DataFormat = I2S_DataFormat_16b;
    I2S_InitStructure.I2S_CPOL = I2S_CPOL_Low;
    I2S_InitStructure.I2S_Mode = I2S_Mode_SlaveRx;
    I2S_InitStructure.I2S_MCLKOutput = I2S_MCLKOutput_Disable;

    /* Initialize the I2S peripheral with the structure above */
    I2S_Init(SPI2, &I2S_InitStructure);

    /* The I2S peripheral will be enabled only in the EVAL_AUDIO_Play() function
       or by user functions if DMA mode not enabled */

    /* Enable the I2S1 TxE interrupt */
    SPI_I2SITConfig(SPI1, SPI_I2S_IT_TXE, ENABLE);

    I2S_Cmd(SPI1, ENABLE);  


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






    /* Configure SPI1 pins: CK and SD ------------------------------------*/
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7| GPIO_Pin_5|GPIO_Pin_4;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;   
    GPIO_Init(GPIOA, &GPIO_InitStruct);  
        
 
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

  /* SPI1 IRQ Channel configuration */
  NVIC_InitStructure.NVIC_IRQChannel = SPI1_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);


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


