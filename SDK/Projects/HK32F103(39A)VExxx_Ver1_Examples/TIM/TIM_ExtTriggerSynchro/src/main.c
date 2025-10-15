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
TIM_ICInitTypeDef  TIM_ICInitStructure;
TIM_OCInitTypeDef  TIM_OCInitStructure;

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

    /* Configure the GPIO ports */
    GPIO_Configuration();

    /* Timers synchronisation in cascade mode with an external trigger -----
      1/TIM1 is configured as Master Timer:
       - Toggle Mode is used
       - The TIM1 Enable event is used as Trigger Output

      2/TIM1 is configured as Slave Timer for an external Trigger connected
       to TIM1 TI2 pin (TIM1 CH2 configured as input pin):
       - The TIM1 TI2FP2 is used as Trigger Input
       - Rising edge is used to start and stop the TIM1: Gated Mode.

      3/TIM3 is slave for TIM1 and Master for TIM4,
       - Toggle Mode is used
       - The ITR1(TIM1) is used as input trigger
       - Gated mode is used, so start and stop of slave counter
         are controlled by the Master trigger output signal(TIM1 enable event).
       - The TIM3 enable event is used as Trigger Output.

      4/TIM4 is slave for TIM3,
       - Toggle Mode is used
       - The ITR2(TIM3) is used as input trigger
       - Gated mode is used, so start and stop of slave counter
         are controlled by the Master trigger output signal(TIM3 enable event).

      The starts and stops of the TIM1 counters are controlled by the
      external trigger.
      The TIM3 starts and stops are controlled by the TIM1, and the TIM4
      starts and stops are controlled by the TIM3.
    -------------------------------------------------------------------- */

    /* Time base configuration */
    TIM_TimeBaseStructure.TIM_Period = 73;
    TIM_TimeBaseStructure.TIM_Prescaler = 2;
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);
    TIM_TimeBaseStructure.TIM_Period = 73;
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
    TIM_TimeBaseStructure.TIM_Period = 73;
    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);

    /* Master Configuration in Toggle Mode */
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Toggle;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 64;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OC1Init(TIM1, &TIM_OCInitStructure);

    /* TIM1 Input Capture Configuration */
    TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;
    TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Falling;
    TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
    TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
    TIM_ICInitStructure.TIM_ICFilter = 0;
    TIM_ICInit(TIM1, &TIM_ICInitStructure);

    /* TIM1 Input trigger configuration: External Trigger connected to TI2 */
    TIM_SelectInputTrigger(TIM1, TIM_TS_TI2FP2);
    TIM_SelectSlaveMode(TIM1, TIM_SlaveMode_Gated);

    /* Select the Master Slave Mode */
    TIM_SelectMasterSlaveMode(TIM1, TIM_MasterSlaveMode_Enable);

    /* Master Mode selection: TIM1 */
    TIM_SelectOutputTrigger(TIM1, TIM_TRGOSource_Enable);

    /* Slaves Configuration: Toggle Mode */
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Toggle;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OC1Init(TIM3, &TIM_OCInitStructure);
    TIM_OC1Init(TIM4, &TIM_OCInitStructure);

    /* Slave Mode selection: TIM3 */
    TIM_SelectInputTrigger(TIM3, TIM_TS_ITR0);
    TIM_SelectSlaveMode(TIM3, TIM_SlaveMode_Gated);

    /* Select the Master Slave Mode */
    TIM_SelectMasterSlaveMode(TIM3, TIM_MasterSlaveMode_Enable);

    /* Master Mode selection: TIM3 */
    TIM_SelectOutputTrigger(TIM3, TIM_TRGOSource_Enable);

    /* Slave Mode selection: TIM4 */
    TIM_SelectInputTrigger(TIM4, TIM_TS_ITR2);
    TIM_SelectSlaveMode(TIM4, TIM_SlaveMode_Gated);

    /* TIM1 Main Output Enable */
    TIM_CtrlPWMOutputs(TIM1, ENABLE);

    /* TIM enable counter */
    TIM_Cmd(TIM1, ENABLE);
    TIM_Cmd(TIM3, ENABLE);
    TIM_Cmd(TIM4, ENABLE);

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
    /* TIM1, TIM3 and TIM4 clock enable */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3 |
                           RCC_APB1Periph_TIM4, ENABLE);

    /* TIM1, GPIOA, GPIOE, GPIOC and GPIOB clocks enable */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1 | RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB |
                           RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO, ENABLE);
}

/**
  * @brief  Configure the GPIO Pins.
  * @param  None
  * @retval None
  */
static void GPIO_Configuration(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    /* GPIOA Configuration: PA.08(TIM1 CH1) and PA.06(TIM3 CH1) as alternate function push-pull */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* GPIOB Configuration: PB.06(TIM4 CH1) as alternate function push-pull */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    /* GPIOA Configuration: PA.09(TIM1 CH2) */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
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
       tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
}
#endif /* USE_FULL_ASSERT */


