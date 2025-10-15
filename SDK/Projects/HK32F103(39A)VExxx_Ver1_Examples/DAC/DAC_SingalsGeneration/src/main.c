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

/** @addtogroup DAC_SignalsGeneration
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define DAC_DHR12R1_ADDRESS      0x40007408
#define DAC_DHR8R2_ADDRESS       0x4000741C
#define DAC_DHR8R1_ADDRESS       0x40007410

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
DAC_InitTypeDef            DAC_InitStructure;
DMA_InitTypeDef            DMA_InitStructure;
const uint16_t Sine12bit[32] =
{
    2047, 2447, 2831, 3185, 3498, 3750, 3939, 4056, 4095, 4056,
    3939, 3750, 3495, 3185, 2831, 2447, 2047, 1647, 1263, 909,
    599, 344, 155, 38, 0, 38, 155, 344, 599, 909, 1263, 1647
};
const uint8_t Escalator8bit[6] = {0x0, 0x33, 0x66, 0x99, 0xCC, 0xFF};
uint8_t Idx = 0;
__IO uint8_t  SelectedWavesForm = 1;
__IO uint8_t WaveChange = 1;

/* Private function prototypes -----------------------------------------------*/
static void DAC_Config(void);
static void TIM_Config(void);

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
         file (startup_kh32f39a.s) before to branch to application main.
         To reconfigure the default setting of SystemInit() function, refer to
         system_hk32f103xxxxa.c file
       */

    /* Preconfiguration before using DAC----------------------------------------*/
    DAC_Config();

    /* TIM2 configuration */
    TIM_Config();

    /* Configures Button GPIO and EXTI Line */
    HK_EVAL_PBInit(BUTTON_KEY1, BUTTON_MODE_EXTI);

    /* Infinite loop */
    while (1)
    {
        /* If the wave form is changed */
        if (WaveChange == 1)
        {
            /* Switch the selected waves forms according the Button status */
            if (SelectedWavesForm == 1)
            {
                /* The sine wave has been selected */

                /* Sine Wave generator ---------------------------------------------*/
                DAC_DeInit();

                /* DAC channels Configuration */
                DAC_StructInit(&DAC_InitStructure);
                DAC_InitStructure.DAC_Trigger = DAC_Trigger_T2_TRGO;

                /* DMA2 channel3 Configuration */
                DMA_DeInit(DMA2_Channel3);
                DMA_InitStructure.DMA_PeripheralBaseAddr = DAC_DHR12R1_ADDRESS;
                DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&Sine12bit;
                DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
                DMA_InitStructure.DMA_BufferSize = 32;
                DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
                DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
                DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
                DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
                DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
                DMA_InitStructure.DMA_Priority = DMA_Priority_High;
                DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
                DMA_Init(DMA2_Channel3, &DMA_InitStructure);

                /* Enable DMA2 Channel3 */
                DMA_Cmd(DMA2_Channel3, ENABLE);
                
                /* Escalator Wave generator -----------------------------------------*/

                /* DMA2 channel4 configuration */
                DMA_DeInit(DMA2_Channel4);
                DMA_InitStructure.DMA_PeripheralBaseAddr = DAC_DHR8R2_ADDRESS;
                DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&Escalator8bit;
                DMA_InitStructure.DMA_BufferSize = 6;
                DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
                DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
                DMA_Init(DMA2_Channel4, &DMA_InitStructure);

                /* Enable DMA2 Channel4 */
                DMA_Cmd(DMA2_Channel4, ENABLE);
                
                /* DAC Channel1 Init */
                DAC_Init(DAC_Channel_1, &DAC_InitStructure);

                /* Enable DAC Channel1: Once the DAC channel1 is enabled, PA.04 is
                   automatically connected to the DAC converter. */
                DAC_Cmd(DAC_Channel_1, ENABLE);

                /* Enable DMA for DAC Channel1 */
                DAC_DMACmd(DAC_Channel_1, ENABLE);
                
                /* DAC channel2 Configuration */
                DAC_Init(DAC_Channel_2, &DAC_InitStructure);

                /* Enable DAC Channel2: Once the DAC channel2 is enabled, PA.05 is
                   automatically connected to the DAC converter. */
                DAC_Cmd(DAC_Channel_2, ENABLE);

                /* Enable DMA for DAC Channel2 */
                DAC_DMACmd(DAC_Channel_2, ENABLE);

            }
            else
            {
                DAC_DeInit(); 

                /* DAC channels Configuration */
                DAC_StructInit(&DAC_InitStructure);
                DAC_InitStructure.DAC_Trigger = DAC_Trigger_T2_TRGO;
                DAC_InitStructure.DAC_WaveGeneration = DAC_WaveGeneration_Noise;
                DAC_InitStructure.DAC_LFSRUnmask_TriangleAmplitude = DAC_LFSRUnmask_Bits11_0;
                DAC_Init(DAC_Channel_1, &DAC_InitStructure);

                /* Enable DAC Channel1: Once the DAC channel1 is enabled, PA.04 is 
                automatically connected to the DAC converter. */
                DAC_Cmd(DAC_Channel_1, ENABLE);

                /* Set DAC Channel1 DHR12L register */
                DAC_SetChannel1Data(DAC_Align_12b_L, 0x7FF0);

                /* Enable DAC channel1 wave generator */
                DAC_WaveGenerationCmd(DAC_Channel_1, DAC_WaveGeneration_Noise , ENABLE);

                /* Triangle Wave generator -----------------------------------------*/

                /* DAC channel2 Configuration */
                DAC_InitStructure.DAC_WaveGeneration = DAC_WaveGeneration_Triangle;
                DAC_InitStructure.DAC_LFSRUnmask_TriangleAmplitude = DAC_TriangleAmplitude_1023;
                DAC_Init(DAC_Channel_2, &DAC_InitStructure);

                /* Enable DAC Channel2: Once the DAC channel2 is enabled, PA.05 is 
                automatically connected to the DAC converter. */
                DAC_Cmd(DAC_Channel_2, ENABLE);

                /* Set DAC channel2 DHR12RD register */
                DAC_SetChannel2Data(DAC_Align_12b_R, 0x100);
            }

            WaveChange = !WaveChange;
        }
    }
}

/**
  * @brief  PrecConfiguration: configure PA4/PA5 in analog,
  *         enable DAC clock, enable DMA1 clock
  * @param  None
  * @retval None
  */
static void DAC_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    /* DMA2 clock enable (to be used with DAC) */
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA2, ENABLE);

    /* DAC Periph clock enable */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);

    /* GPIOA clock enable */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    /* Configure PA.04 (DAC_OUT1) and PA.05 (DAC_OUT2)as analog */
    GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_4 | GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
}

/**
  * @brief  TIM2 Configuration
  * @param  None
  * @retval None
  */
static void TIM_Config(void)
{
    TIM_TimeBaseInitTypeDef    TIM_TimeBaseStructure;

    /* TIM2 Periph clock enable */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

    /* Time base configuration */
    TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
    TIM_TimeBaseStructure.TIM_Period = 0xFF;
    TIM_TimeBaseStructure.TIM_Prescaler = 0x0;
    TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

    /* TIM2 TRGO selection */
    TIM_SelectOutputTrigger(TIM2, TIM_TRGOSource_Update);

    /* TIM2 enable counter */
    TIM_Cmd(TIM2, ENABLE);
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

