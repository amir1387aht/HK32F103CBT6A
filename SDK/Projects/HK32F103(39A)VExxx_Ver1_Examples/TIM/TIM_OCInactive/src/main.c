/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  main.c
* @brief:     Main program body
* @author:    AE Team
* @version:   V1.0.0/2023-10-26
*             1.Initial version
* @log:
*******************************************************************************/


/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
TIM_OCInitTypeDef  TIM_OCInitStructure;
uint16_t CCR1_Val = 1000;
uint16_t CCR2_Val = 500;
uint16_t CCR3_Val = 250;
uint16_t CCR4_Val = 125;
uint16_t PrescalerValue = 0;

/* Private function prototypes -----------------------------------------------*/
static void RCC_Configuration(void);
static void GPIO_Configuration(void);
static void NVIC_Configuration(void);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{
    /* System Clocks Configuration */
    RCC_Configuration();

    /* NVIC Configuration */
    NVIC_Configuration();

    /* GPIO Configuration */
    GPIO_Configuration();

    /* ---------------------------------------------------------------
      TIM2 Configuration:
      TIM2CLK = SystemCoreClock / 2,
      The objective is to get TIM2 counter clock at 1 KHz:
       - Prescaler = (TIM2CLK / TIM2 counter clock) - 1
      And generate 4 signals with 4 different delays:
      TIM2_CH1 delay = CCR1_Val/TIM2 counter clock = 1000 ms
      TIM2_CH2 delay = CCR2_Val/TIM2 counter clock = 500 ms
      TIM2_CH3 delay = CCR3_Val/TIM2 counter clock = 250 ms
      TIM2_CH4 delay = CCR4_Val/TIM2 counter clock = 125 ms
    --------------------------------------------------------------- */

    /* Compute the prescaler value */
    PrescalerValue = (uint16_t) (SystemCoreClock / 2000) - 1;

    /* Time base configuration */
    TIM_TimeBaseStructure.TIM_Period = 65535;
    TIM_TimeBaseStructure.TIM_Prescaler = PrescalerValue;
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

    /* Output Compare Active Mode configuration: Channel1 */
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Inactive;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = CCR1_Val;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OC1Init(TIM2, &TIM_OCInitStructure);
    TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Disable);

    /* Output Compare Active Mode configuration: Channel2 */
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = CCR2_Val;
    TIM_OC2Init(TIM2, &TIM_OCInitStructure);
    TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Disable);

    /* Output Compare Active Mode configuration: Channel3 */
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = CCR3_Val;
    TIM_OC3Init(TIM2, &TIM_OCInitStructure);
    TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Disable);

    /* Output Compare Active Mode configuration: Channel4 */
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = CCR4_Val;
    TIM_OC4Init(TIM2, &TIM_OCInitStructure);
    TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Disable);
    TIM_ARRPreloadConfig(TIM2, ENABLE);

    /* TIM IT enable */
    TIM_ITConfig(TIM2, TIM_IT_CC1 | TIM_IT_CC2 | TIM_IT_CC3 | TIM_IT_CC4, ENABLE);

    /* Set PC.06, PC.07, PC.08 and PC.09 pins */
    GPIO_SetBits(GPIOC, GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9);

    /* TIM2 enable counter */
    TIM_Cmd(TIM2, ENABLE);

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
    /* PCLK1 = HCLK/4 */
    RCC_PCLK1Config(RCC_HCLK_Div4);

    /* TIM2 clock enable */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

    /* GPIOC clock enable */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
}

/**
  * @brief  Configure the GPIOD Pins.
  * @param  None
  * @retval None
  */
static void GPIO_Configuration(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    /* GPIOC Configuration: Pin6, 7, 8 and 9 as output push-pull */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
}

/**
  * @brief  Configure the nested vectored interrupt controller.
  * @param  None
  * @retval None
  */
static void NVIC_Configuration(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;

    /* Enable the TIM2 Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
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


