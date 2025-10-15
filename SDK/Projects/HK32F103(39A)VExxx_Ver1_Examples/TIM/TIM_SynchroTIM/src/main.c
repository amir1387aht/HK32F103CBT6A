/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  main.c
* @brief:     Main program body
* @author:    AE Team
* @version:   V1.0.0/2023-11-06
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
TIM_BDTRInitTypeDef TIM_BDTRInitStructure;

/* Private function prototypes -----------------------------------------------*/
static void RCC_Configuration(void);
static void GPIO_Configuration(void);

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

    /* GPIO Configuration */
    GPIO_Configuration();

    /* TIM1 and Timers(TIM3 and TIM4) synchronisation in parallel mode
       1/TIM1 is configured as Master Timer:
       - PWM Mode is used
       - The TIM1 Update event is used as Trigger Output

       2/TIM3 and TIM4 are slaves for TIM1,
       - PWM Mode is used
       - The ITR0(TIM1) is used as input trigger for both slaves
       - Gated mode is used, so starts and stops of slaves counters
         are controlled by the Master trigger output signal(update event).

      The Master Timer TIM1 is running at:
      TIM1 frequency = TIM1 counter clock / (TIM1_Period + 1) = 281.250 KHz
      and the duty cycle is equal to: TIM1_CCR1/(TIM1_ARR + 1) = 50%

      The TIM3 is running at:
      (TIM1 frequency)/ ((TIM3 period +1)* (Repetition_Counter+1)) = 18.750 KHz and
      a duty cycle equal to TIM3_CCR1/(TIM3_ARR + 1) = 33.3%

      The TIM4 is running at:
      (TIM1 frequency)/ ((TIM4 period +1)* (Repetition_Counter+1)) = 28.125 KHz and
      a duty cycle equal to TIM4_CCR1/(TIM4_ARR + 1) = 50%

    --------------------------------------------------------------------------- */

    /* TIM3 Peripheral Configuration ----------------------------------------*/

    /* TIM3 Slave Configuration: PWM1 Mode */
    TIM_TimeBaseStructure.TIM_Period = 2;
    TIM_TimeBaseStructure.TIM_Prescaler = 0;
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 1;
    TIM_OC1Init(TIM3, &TIM_OCInitStructure);

    /* Slave Mode selection: TIM3 */
    TIM_SelectSlaveMode(TIM3, TIM_SlaveMode_Gated);
    TIM_SelectInputTrigger(TIM3, TIM_TS_ITR0);

    /* TIM4 Peripheral Configuration ----------------------------------------*/

    /* TIM4 Slave Configuration: PWM1 Mode */
    TIM_TimeBaseStructure.TIM_Period = 1;
    TIM_TimeBaseStructure.TIM_Prescaler = 0;
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 1;
    TIM_OC1Init(TIM4, &TIM_OCInitStructure);

    /* Slave Mode selection: TIM4 */
    TIM_SelectSlaveMode(TIM4, TIM_SlaveMode_Gated);
    TIM_SelectInputTrigger(TIM4, TIM_TS_ITR0);

    /* TIM1 Peripheral Configuration ----------------------------------------*/

    /* Time Base configuration */
    TIM_TimeBaseStructure.TIM_Prescaler = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseStructure.TIM_Period = 255;
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 4;
    TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);

    /* Channel 1 Configuration in PWM mode */
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 127;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
    TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_Low;
    TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
    TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;
    TIM_OC1Init(TIM1, &TIM_OCInitStructure);

    /* Automatic Output enable, Break, dead time and lock configuration*/
    TIM_BDTRInitStructure.TIM_OSSRState = TIM_OSSRState_Enable;
    TIM_BDTRInitStructure.TIM_OSSIState = TIM_OSSIState_Enable;
    TIM_BDTRInitStructure.TIM_LOCKLevel = TIM_LOCKLevel_1;
    TIM_BDTRInitStructure.TIM_DeadTime = 5;
    TIM_BDTRInitStructure.TIM_Break = TIM_Break_Disable;
    TIM_BDTRInitStructure.TIM_BreakPolarity = TIM_BreakPolarity_High;
    TIM_BDTRInitStructure.TIM_AutomaticOutput = TIM_AutomaticOutput_Disable;
    TIM_BDTRConfig(TIM1, &TIM_BDTRInitStructure);

    /* Master Mode selection */
    TIM_SelectOutputTrigger(TIM1, TIM_TRGOSource_Update);

    /* Select the Master Slave Mode */
    TIM_SelectMasterSlaveMode(TIM1, TIM_MasterSlaveMode_Enable);

    /* TIM1 counter enable */
    TIM_Cmd(TIM1, ENABLE);

    /* TIM enable counter */
    TIM_Cmd(TIM3, ENABLE);
    TIM_Cmd(TIM4, ENABLE);

    /* Main Output Enable */
    TIM_CtrlPWMOutputs(TIM1, ENABLE);

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
    /* TIM1, GPIOA and GPIOB clock enable */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1 | RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOE |
                           RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);

    /* TIM3 and TIM4 clock enable */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3 | RCC_APB1Periph_TIM4, ENABLE);
}

/**
  * @brief  Configures TIM1, TIM3 and TIM4 Pins.
  * @param  None
  * @retval None
  */
static void GPIO_Configuration(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    /* GPIOA Configuration: TIM1 Channel1 and TIM3 Channel1 as alternate function push-pull */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_8;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* GPIOB Configuration: TIM4 Channel1 as alternate function push-pull */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
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


