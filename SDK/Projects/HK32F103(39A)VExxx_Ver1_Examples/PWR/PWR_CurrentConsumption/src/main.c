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
#include "hk32f103xxxxa_lp_modes.h"

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
__IO uint32_t uwCounter = 0;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/


/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
    /* Configure the system clock to HSI */
    RCC_SYSCLKConfig(RCC_SYSCLKSource_HSI);

    /* Turn off HSE */
    RCC_HSEConfig(RCC_HSE_OFF);

    /* Disable PLL */
    RCC_PLLCmd(DISABLE);

    /* Enable PWR APB1 Clock */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);

    /* Allow access to Backup */
    PWR_BackupAccessCmd(ENABLE);

    /* Reset RTC Domain */
    RCC_BackupResetCmd(ENABLE);
    RCC_BackupResetCmd(DISABLE);

    /* Check that the system was resumed from StandBy mode */
    if (PWR_GetFlagStatus(PWR_FLAG_SB) != RESET)
    {
        /* Clear SB Flag */
        PWR_ClearFlag(PWR_FLAG_SB);

        /* Initialize LED2 */
        HK_EVAL_LEDInit(LED2);

        /* Infinite loop */
        while (1)
        {
            /* Toggle The LED2 */
            HK_EVAL_LEDToggle(LED2);

            /* Inserted Delay */
            for (uwCounter = 0; uwCounter < 0x5FFFF; uwCounter++)
            {
            }
        }
    }

    /*  Configure Key Button */
    HK_EVAL_PBInit(BUTTON_KEY1, BUTTON_MODE_GPIO);

    /* Wait until Key button is pressed to enter the Low Power mode */
    while (HK_EVAL_PBGetState(BUTTON_KEY1) != RESET)
    {
    }

    /* Loop while Key button is maintained pressed */
    while (HK_EVAL_PBGetState(BUTTON_KEY1) == RESET)
    {
    }

#if defined (SLEEP_MODE)
    /* Sleep Mode Entry
        - System Running at PLL (72MHz)
        - Flash 2 wait state
        - Code running from Internal FLASH
        - All peripherals disabled.
        - Wakeup using EXTI Line (Key Button PA13)
     */
    SleepMode_Measure();
#elif defined (STOP_MODE)
    /* STOP Mode Entry
        - RTC Clocked by LSE/LSI
        - Regulator in LP mode
        - HSI, HSE OFF and LSI OFF if not used as RTC Clock source
        - No IWDG
        - FLASH in deep power down mode
        - Automatic Wakeup using RTC clocked by LSE/LSI (after ~20s)
     */
    StopMode_Measure();
#elif defined (STANDBY_MODE)
    /* STANDBY Mode Entry
        - RTC OFF
        - IWDG and LSI OFF
        - Wakeup using WakeUp Pin (PA0)
     */
    StandbyMode_Measure();
#elif defined (STANDBY_RTC_MODE)
    /* STANDBY Mode with RTC on LSE/LSI Entry
        - RTC Clocked by LSE or LSI
        - IWDG OFF and LSI OFF if not used as RTC Clock source
        - Backup SRAM OFF
        - Automatic Wakeup using RTC clocked by LSE/LSI (after ~20s)
     */
    StandbyRTCMode_Measure();
#else
    /* Initialize LED1 */
    HK_EVAL_LEDInit(LED2);

    /* Infinite loop */
    while (1)
    {
        /* Toggle The LED1 */
        HK_EVAL_LEDToggle(LED2);

        /* Inserted Delay */
        for (Counter = 0; Counter < 0x5FFFF; Counter++)
        {
        }
    }

#endif
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
