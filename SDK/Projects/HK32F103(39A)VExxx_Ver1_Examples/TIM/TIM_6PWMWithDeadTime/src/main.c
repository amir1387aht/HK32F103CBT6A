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
TIM_BDTRInitTypeDef TIM_BDTRInitStructure;
uint16_t TimerPeriod = 0;
uint16_t Channel1Pulse = 0, Channel2Pulse = 0, Channel3Pulse = 0;

/* Private function prototypes -----------------------------------------------*/
static void RCC_Configuration(void);
static void GPIO_Configuration(void);
static void TIM1_Config(void);
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
    TIM1_Config();

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
    /* TIM1, GPIOA, GPIOB, GPIOE and AFIO clocks enable */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1 | RCC_APB2Periph_GPIOA |
                           RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);
}

/**
  * @brief  Configure the TIM1 Pins.
  * @param  None
  * @retval None
  */
static void GPIO_Configuration(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    /* GPIOA Configuration: Channel 1, 2 and 3 as alternate function push-pull */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* GPIOB Configuration: Channel 1N, 2N and 3N as alternate function push-pull */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    /* GPIOB Configuration: BKIN pin */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
}

/**
  * @brief  Configure the TIM1.
  * @param  None
  * @retval None
  */
static void TIM1_Config(void)
{
    /* -----------------------------------------------------------------------
    TIM1 Configuration to:

    1/ Generate 3 complementary PWM signals with 3 different duty cycles:
      TIM1CLK is fixed to SystemCoreClock, the TIM1 Prescaler is equal to 0 so the
      TIM1 counter clock used is SystemCoreClock.

      The objective is to generate PWM signal at 17.57 KHz:
      - TIM1_Period = (SystemCoreClock / 17570) - 1

      The Three Duty cycles are computed as the following description:

      The channel 1 duty cycle is set to 50% so channel 1N is set to 50%.
      The channel 2 duty cycle is set to 25% so channel 2N is set to 75%.
      The channel 3 duty cycle is set to 12.5% so channel 3N is set to 87.5%.
      The Timer pulse is calculated as follows:
        - ChannelxPulse = DutyCycle * (TIM1_Period - 1) / 100

    2/ Insert a dead time equal to 11/SystemCoreClock s
    3/ Configure the break feature, active at High level, and using the automatic
       output enable feature
    4/ Use the Locking parameters level1.
    ----------------------------------------------------------------------- */

    /* Compute the value to be set in ARR register to generate signal frequency at 17.57 Khz */
    TimerPeriod = (SystemCoreClock / 17570) - 1;

    /* Compute CCR1 value to generate a duty cycle at 50% for channel 1 */
    Channel1Pulse = (uint16_t) (((uint32_t) 5 * (TimerPeriod - 1)) / 10);

    /* Compute CCR2 value to generate a duty cycle at 25%  for channel 2 */
    Channel2Pulse = (uint16_t) (((uint32_t) 25 * (TimerPeriod - 1)) / 100);

    /* Compute CCR3 value to generate a duty cycle at 12.5%  for channel 3 */
    Channel3Pulse = (uint16_t) (((uint32_t) 125 * (TimerPeriod - 1)) / 1000);

    /* Time Base configuration */
    TIM_TimeBaseStructure.TIM_Prescaler = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseStructure.TIM_Period = TimerPeriod;
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);

    /* Channel 1, 2 and 3 Configuration in PWM mode */
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
    TIM_OCInitStructure.TIM_Pulse = Channel1Pulse;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
    TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_Low;
    TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
    TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Set;
    TIM_OC1Init(TIM1, &TIM_OCInitStructure);
    TIM_OCInitStructure.TIM_Pulse = Channel2Pulse;
    TIM_OC2Init(TIM1, &TIM_OCInitStructure);
    TIM_OCInitStructure.TIM_Pulse = Channel3Pulse;
    TIM_OC3Init(TIM1, &TIM_OCInitStructure);

    /* Automatic Output enable, Break, dead time and lock configuration*/
    TIM_BDTRInitStructure.TIM_OSSRState = TIM_OSSRState_Enable;
    TIM_BDTRInitStructure.TIM_OSSIState = TIM_OSSIState_Enable;
    TIM_BDTRInitStructure.TIM_LOCKLevel = TIM_LOCKLevel_1;
    /*dead time equal to 11/TIMClock */
    TIM_BDTRInitStructure.TIM_DeadTime = 11;
    TIM_BDTRInitStructure.TIM_Break = TIM_Break_Enable;
    TIM_BDTRInitStructure.TIM_BreakPolarity = TIM_BreakPolarity_High;
    TIM_BDTRInitStructure.TIM_AutomaticOutput = TIM_AutomaticOutput_Enable;
    TIM_BDTRConfig(TIM1, &TIM_BDTRInitStructure);

    /* TIM1 counter enable */
    TIM_Cmd(TIM1, ENABLE);

    /* Main Output Enable */
    TIM_CtrlPWMOutputs(TIM1, ENABLE);
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


