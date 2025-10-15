/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  main.c
* @brief:     Main program body
* @author:    AE Team
* @version:   V1.0.0/2023-10-31
*                     1.Initial version
* @log:
*******************************************************************************/


/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "hk32f103xxxxa_eval.h"

/** @addtogroup HK32F103xxxxA_StdPeriph_Examples
  * @{
  */

/** @addtogroup _template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
extern uint8_t Counter;
/* Private function prototypes -----------------------------------------------*/
void Systick_Config(void);
void Standby_Config(void);
/* Private functions ---------------------------------------------------------*/


/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
    /* Enable PWR APB1 Clock */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);

    /* Configures LEDs */
    HK_EVAL_LEDInit(LED1);

    /* Check that the system was resumed from StandBy mode */
    if (PWR_GetFlagStatus(PWR_FLAG_SB) != RESET)
    {
        /* Clear SB Flag */
        PWR_ClearFlag(PWR_FLAG_SB);

        /* turn on LED1 */
        HK_EVAL_LEDOn(LED1);
    }

    /* Configures systick */
    Systick_Config();

    /* delay 5s*/
    while (Counter != 50)
    {
    }
    SysTick->CTRL = ~SysTick_CTRL_ENABLE_Msk;

    /* Clear Power WakeUp (CWUF) pending flag */
    PWR_ClearFlag(PWR_FLAG_WU);

    /* standby configures */
    Standby_Config();

    /* Request to enter STANDBY mode (Wake Up flag is cleared in PWR_EnterSTANDBYMode function) */
    PWR_EnterSTANDBYMode(PWR_STANDBYEntry_WFI);

    /* Infinite loop */
    while (1)
    {
    }
}

/**
  * @brief  Configures RTC and BKP
  * @param  None
  * @retval None
  */
void Standby_Config(void)
{
        /* Enable BKP APB1 Clock */
    RCC_APB1PeriphClockCmd( RCC_APB1Periph_BKP, ENABLE);

    /* Allow access to RTC */
    PWR_BackupAccessCmd(ENABLE);

    /* The RTC Clock may varies due to LSI frequency dispersion. */

    /* Enable the LSI OSC */
    RCC_LSICmd(ENABLE);

    /* Wait till LSI is ready */
    while (RCC_GetFlagStatus(RCC_FLAG_LSIRDY) == RESET)
    {
    }

    /* Select the RTC Clock Source */
    RCC_RTCCLKConfig(RCC_RTCCLKSource_LSI);

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
    RTC_SetWakeupTimer(0x61A8 - 1);
    RTC_WaitForLastTask();
    BKP_WakeupTimerOutSel(DISABLE, ENABLE, DISABLE, DISABLE);

    /* Enable Wakeup Counter */
    BKP_WakeupTimerConfig(ENABLE);
}

/**
  * @brief  Configures the SysTick to generate an interrupt each 100 ms.
  * @param  None
  * @retval None
  */
void Systick_Config(void)
{
    /* Setup SysTick Timer for 100ms interrupts  */
    if (SysTick_Config(SystemCoreClock / 10))
    {
        /* Capture error */
        while (1)
        {
        }
    }

    /* Configure the SysTick handler priority */
    NVIC_SetPriority(SysTick_IRQn, 0x0);
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
