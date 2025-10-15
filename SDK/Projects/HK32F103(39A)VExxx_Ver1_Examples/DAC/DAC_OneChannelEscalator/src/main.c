/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  main.c
* @brief:     Main program body
* @author:    AE Team
* @version:   V1.0.0/2023-11-09
*             1.Initial Version
* @log:
*******************************************************************************/


/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "hk32f103xxxxa_eval.h"

/** @addtogroup HK32F103xxxxA_StdPeriph_Examples
  * @{
  */

/** @addtogroup DAC_OneChannelEscalator
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define DAC_DHR8R1_Address      0x40007410
/* Init Structure definition */
DAC_InitTypeDef            DAC_InitStructure;
DMA_InitTypeDef            DMA_InitStructure;
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
const uint8_t Escalator8bit[6] = {0x0, 0x33, 0x66, 0x99, 0xCC, 0xFF};
/* Private function prototypes -----------------------------------------------*/
static void RCC_Configuration(void);
static void GPIO_Configuration(void);
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
    /*!< At this stage the microcontroller clock setting is already configured,
         this is done through SystemInit() function which is called from startup
         file (startup_hk32f103xxxxa.s) before to branch to application main.
         To reconfigure the default setting of SystemInit() function, refer to
         system_hk32f103xxxxa.c file
       */

    /* System Clocks Configuration */
    RCC_Configuration();

    /* Once the DAC channel is enabled, the corresponding GPIO pin is automatically
       connected to the DAC converter. In order to avoid parasitic consumption,
       the GPIO pin should be configured in analog */
    GPIO_Configuration();

    /* TIM6 Configuration */
    TIM_PrescalerConfig(TIM6, 0xF, TIM_PSCReloadMode_Update);
    TIM_SetAutoreload(TIM6, 0xFF);

    /* TIM6 TRGO selection */
    TIM_SelectOutputTrigger(TIM6, TIM_TRGOSource_Update);

    /* DAC channel1 Configuration */
    DAC_InitStructure.DAC_Trigger = DAC_Trigger_T6_TRGO;
    DAC_InitStructure.DAC_WaveGeneration = DAC_WaveGeneration_None;
    DAC_InitStructure.DAC_OutputBuffer = DAC_OutputBuffer_Enable;
    DAC_Init(DAC_Channel_1, &DAC_InitStructure);

    /* DMA2 channel3 configuration */
    DMA_DeInit(DMA2_Channel3);
    DMA_InitStructure.DMA_PeripheralBaseAddr = DAC_DHR8R1_Address;
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&Escalator8bit;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
    DMA_InitStructure.DMA_BufferSize = 6;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
    DMA_Init(DMA2_Channel3, &DMA_InitStructure);

    /* Enable DMA2 Channel3 */
    DMA_Cmd(DMA2_Channel3, ENABLE);

    /* Enable DAC Channel1: Once the DAC channel1 is enabled, PA.04 is
       automatically connected to the DAC converter. */
    DAC_Cmd(DAC_Channel_1, ENABLE);

    /* Enable DMA for DAC Channel1 */
    DAC_DMACmd(DAC_Channel_1, ENABLE);

    /* TIM6 enable counter */
    TIM_Cmd(TIM6, ENABLE);

    while (1)
    {
    }
}

/**
  * @brief  Configures the different system clocks.
  * @param  None
  * @retval None
  */
static void RCC_Configuration(void)
{
    /* Enable peripheral clocks ------------------------------------------------*/

    /* DMA2 clock enable */
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA2, ENABLE);

    /* GPIOA Periph clock enable */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    /* DAC Periph clock enable */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);

    /* TIM6 Periph clock enable */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);
}

/**
  * @brief  Configures the different GPIO ports.
  * @param  None
  * @retval None
  */
static void GPIO_Configuration(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    /* Once the DAC channel is enabled, the corresponding GPIO pin is automatically
       connected to the DAC converter. In order to avoid parasitic consumption,
       the GPIO pin should be configured in analog */
    GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_4;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
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
       ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

    /* Infinite loop */
    while (1)
    {
    }
}
#endif

/**
  * @}
  */

/**
  * @}
  */

