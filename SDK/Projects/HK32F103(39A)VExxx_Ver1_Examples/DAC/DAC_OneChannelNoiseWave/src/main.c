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

/** @addtogroup DAC_OneChannelNoiseWave
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Init Structure definition */
DAC_InitTypeDef            DAC_InitStructure;
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
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

    /* DAC channel1 Configuration */
    DAC_InitStructure.DAC_Trigger = DAC_Trigger_Software;
    DAC_InitStructure.DAC_WaveGeneration = DAC_WaveGeneration_Noise;
    DAC_InitStructure.DAC_LFSRUnmask_TriangleAmplitude = DAC_LFSRUnmask_Bits8_0;
    DAC_InitStructure.DAC_OutputBuffer = DAC_OutputBuffer_Enable;
    DAC_Init(DAC_Channel_1, &DAC_InitStructure);

    /* Enable DAC Channel1: Once the DAC channel1 is enabled, PA.04 is
       automatically connected to the DAC converter. */
    DAC_Cmd(DAC_Channel_1, ENABLE);

    /* Set DAC Channel1 DHR12L register */
    DAC_SetChannel1Data(DAC_Align_12b_L, 0x7FF0);

    while (1)
    {
        /* Start DAC Channel1 conversion by software */
        DAC_SoftwareTriggerCmd(DAC_Channel_1, ENABLE);
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

    /* GPIOA Periph clock enable */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    /* DAC Periph clock enable */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);
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

