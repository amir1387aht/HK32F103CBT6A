/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  hk32f103xxxxa_lp_modes.c
* @brief:     This file provides the low power function.
* @author:    AE Team
* @version:   V1.0.0/2023-10-18
*             1.Initial version
* @log:
*******************************************************************************/

#include "hk32f103xxxxa.h"
#include "hk32f103xxxxa_lp_modes.h"
#include "hk32f103xxxxa_eval.h"

//#define RTC_CLOCK_SOURCE_LSE   /* LSE used as RTC source clock */
#define RTC_CLOCK_SOURCE_LSI  /* LSI used as RTC source clock. The RTC Clock may varies due to LSI frequency dispersion. */

/**
  * @brief  This function configures the system to enter Sleep mode for
  *         current consumption measurement purpose.
  *         Sleep Mode
  *         ==========
  *            - System Running at PLL (72MHz)
  *            - Flash 2 wait state
  *            - Code running from Internal FLASH
  *            - All peripherals disabled.
  * @param  None
  * @retval None
  */
void SleepMode_Measure(void)
{
    __IO uint32_t index = 0;
    GPIO_InitTypeDef GPIO_InitStructure;
    /* Configure all GPIO as analog to reduce current consumption on non used IOs */
    /* Enable GPIOs clock */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC |
                           RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOE, ENABLE);
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    GPIO_Init(GPIOC, &GPIO_InitStructure);
    GPIO_Init(GPIOD, &GPIO_InitStructure);
    GPIO_Init(GPIOE, &GPIO_InitStructure);
    /* Disable GPIOs clock */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC |
                           RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOE, DISABLE);
    /* Configure Key Button */
    HK_EVAL_PBInit(BUTTON_KEY3, BUTTON_MODE_EXTI);
    /* Request to enter SLEEP mode */
    __WFI();
    /* Initialize LED2 on EVAL board */
    HK_EVAL_LEDInit(LED2);

    /* Infinite loop */
    while (1)
    {
        /* Toggle The LED2 */
        HK_EVAL_LEDToggle(LED2);

        /* Inserted Delay */
        for (index = 0; index < 0x5FFFF; index++)
        {
        }
    }
}

/**
  * @brief  This function configures the system to enter Stop mode with RTC
  *         clocked by LSE or LSI  for current consumption measurement purpose.
  *         STOP Mode with RTC clocked by LSE/LSI
  *         =====================================
  *           - RTC Clocked by LSE or LSI
  *           - Regulator in LP mode
  *           - HSI, HSE OFF and LSI OFF if not used as RTC Clock source
  *           - No IWDG
  *           - FLASH in deep power down mode
  *           - Automatic Wakeup using RTC clocked by LSE/LSI (~10s)
  * @param  None
  * @retval None
  */
void StopMode_Measure(void)
{
    __IO uint32_t index = 0;
    GPIO_InitTypeDef GPIO_InitStructure;
    NVIC_InitTypeDef  NVIC_InitStructure;
    EXTI_InitTypeDef  EXTI_InitStructure;
    /* Allow access to RTC */
    PWR_BackupAccessCmd(ENABLE);
#if defined (RTC_CLOCK_SOURCE_LSI)  /* LSI used as RTC source clock*/
    /* The RTC Clock may varies due to LSI frequency dispersion. */
    /* Enable the LSI OSC */
    RCC_LSICmd(ENABLE);

    /* Wait till LSI is ready */
    while (RCC_GetFlagStatus(RCC_FLAG_LSIRDY) == RESET)
    {
    }

    /* Select the RTC Clock Source */
    RCC_RTCCLKConfig(RCC_RTCCLKSource_LSI);
#elif defined (RTC_CLOCK_SOURCE_LSE) /* LSE used as RTC source clock */
    /* Enable the LSE OSC */
    RCC_LSEConfig(RCC_LSE_ON);

    /* Wait till LSE is ready */
    while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET)
    {
    }
    /* Select the RTC Clock Source */
    RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);
#else
#error Please select the RTC Clock source inside the main.c file
#endif /* RTC_CLOCK_SOURCE_LSI */
    /* Enable the RTC Clock */
    RCC_RTCCLKCmd(ENABLE);
    /* Wait for RTC APB registers synchronisation */
    RTC_WaitForSynchro();
    /* Wait until last write operation on RTC registers has finished */
    RTC_WaitForLastTask();
    /* Set RTC prescaler: set RTC period to 1sec */
    RTC_SetPrescaler(32767); /* RTC period = RTCCLK/RTC_PR = (32.768 KHz)/(32767+1) */
    /* Wait until last write operation on RTC registers has finished */
    RTC_WaitForLastTask();
    /* Configure all GPIO as analog to reduce current consumption on non used IOs */
    /* Enable GPIOs clock */
    /* Disable GPIOs clock */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC |
                           RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOE, ENABLE);
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    GPIO_Init(GPIOC, &GPIO_InitStructure);
    GPIO_Init(GPIOD, &GPIO_InitStructure);
    GPIO_Init(GPIOE, &GPIO_InitStructure);
    /* Disable GPIOs clock */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC |
                           RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOE, DISABLE);
    /* EXTI configuration *******************************************************/
    EXTI_ClearITPendingBit(EXTI_Line17);
    EXTI_InitStructure.EXTI_Line = EXTI_Line17;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);
    /* Enable the RTC Wakeup Interrupt */
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    NVIC_InitStructure.NVIC_IRQChannel = RTCAlarm_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    /* RTC Wakeup Interrupt Generation: Clock Source: RTCCLK_Div16, Wakeup Time Base: ~10s
       RTC Clock Source LSE 32.768KHz or LSI ~32KHz
       Wakeup Time Base = (16 / (LSE or LSI)) * WakeUpCounter
    */
    BKP_SetRTCWakeupTimerClock(BKP_WUCKSEL_DIV16);
    RTC_WaitForLastTask();
    RTC_SetWakeupTimer(0x61A8-1);
    RTC_WaitForLastTask();
    BKP_WakeupTimerOutSel(DISABLE, DISABLE, ENABLE, DISABLE);
    /* Enable the Wakeup Interrupt */
    RTC_ITConfig(RTC_IT_WUT, ENABLE);
    /* Enable Wakeup Counter */
    BKP_WakeupTimerConfig(ENABLE);
    /* Enter Stop Mode */
    PWR_ClearFlag(PWR_FLAG_WU);
    PWR_EnterSTOPMode(PWR_Regulator_LowPower, PWR_STOPEntry_WFI);
    /* Initialize LED2 on EVAL board */
    HK_EVAL_LEDInit(LED2);
    /* Infinite loop */
    while (1)
    {
        /* Toggle The LED2 */
        HK_EVAL_LEDToggle(LED2);
        /* Inserted Delay */
        for (index = 0; index < 0x5FFFF; index++)
        {
        }
    }
}

/**
  * @brief  This function configures the system to enter Standby mode for
  *         current consumption measurement purpose.
  *         STANDBY Mode
  *         ============
  *           - RTC OFF
  *           - IWDG and LSI OFF
  *           - Wakeup using WakeUp Pin (PA0)
  * @param  None
  * @retval None
  */
void StandbyMode_Measure(void)
{
    /* Enable WKUP pin 1 */
    PWR_WakeUpPinCmd(PWR_WakeUpPin_1, ENABLE);
    PWR_WakeupPinPolarityConfig(WAKE_UP_PIN1, FALLING_EDGE);
    /* Clear Power WakeUp (CWUF) pending flag */
    PWR_ClearFlag(PWR_FLAG_WU);
    /* Request to enter STANDBY mode (Wake Up flag is cleared in PWR_EnterSTANDBYMode function) */
    PWR_EnterSTANDBYMode(PWR_STANDBYEntry_WFI);

    /* Infinite loop */
    while (1)
    {
    }
}

/**
  * @brief  This function configures the system to enter Standby mode with RTC
  *         clocked by LSE or LSI for current consumption measurement purpose.
  *         STANDBY Mode with RTC clocked by LSE/LSI
  *         ========================================
  *           - RTC Clocked by LSE/LSI
  *           - IWDG OFF
  *           - Backup SRAM OFF
  *           - Automatic Wakeup using RTC clocked by LSE/LSI (after ~10s)
  * @param  None
  * @retval None
  */
void StandbyRTCMode_Measure(void)
{
    /* Allow access to RTC */
    PWR_BackupAccessCmd(ENABLE);
#if defined (RTC_CLOCK_SOURCE_LSI)  /* LSI used as RTC source clock*/
    /* The RTC Clock may varies due to LSI frequency dispersion. */
    /* Enable the LSI OSC */
    RCC_LSICmd(ENABLE);

    /* Wait till LSI is ready */
    while (RCC_GetFlagStatus(RCC_FLAG_LSIRDY) == RESET)
    {
    }

    /* Select the RTC Clock Source */
    RCC_RTCCLKConfig(RCC_RTCCLKSource_LSI);
#elif defined (RTC_CLOCK_SOURCE_LSE) /* LSE used as RTC source clock */
    /* Enable the LSE OSC */
    RCC_LSEConfig(RCC_LSE_ON);

    /* Wait till LSE is ready */
    while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET)
    {
    }

    /* Select the RTC Clock Source */
    RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);
#else
#error Please select the RTC Clock source inside the main.c file
#endif /* RTC_CLOCK_SOURCE_LSI */
    /* Enable the RTC Clock */
    RCC_RTCCLKCmd(ENABLE);
    /* Wait for RTC APB registers synchronisation */
    RTC_WaitForSynchro();
    /* Wait until last write operation on RTC registers has finished */
    RTC_WaitForLastTask();
    /* Set RTC prescaler: set RTC period to 1sec */
    RTC_SetPrescaler(32767); /* RTC period = RTCCLK/RTC_PR = (32.768 KHz)/(32767+1) */
    /* Wait until last write operation on RTC registers has finished */
    RTC_WaitForLastTask();
    /* RTC Wakeup Interrupt Generation: Clock Source: RTCCLK_Div16, Wakeup Time Base: ~10s
       RTC Clock Source LSE 32.768KHz or LSI ~40KHz

       Wakeup Time Base = (16 / (LSE or LSI)) * WakeUpCounter
    */
    BKP_SetRTCWakeupTimerClock(BKP_WUCKSEL_DIV16);
    RTC_WaitForLastTask();
    RTC_SetWakeupTimer(0x61A8-1);
    RTC_WaitForLastTask();
    BKP_WakeupTimerOutSel(DISABLE, ENABLE, DISABLE, DISABLE);
    /* Enable Wakeup Counter */
    BKP_WakeupTimerConfig(ENABLE);
    PWR_ClearFlag(PWR_FLAG_WU);
    /* Request to enter STANDBY mode (Wake Up flag is cleared in PWR_EnterSTANDBYMode function) */
    PWR_EnterSTANDBYMode(PWR_STANDBYEntry_WFI);

    /* Infinite loop */
    while (1)
    {
    }
}
