/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  main.c
* @brief:     Main program body
* @author:    AE Team
* @version:   V1.0.0/2023-11-12
*                     1.Initial version
* @log:
*******************************************************************************/


/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "hk32f103xxxxa_eval.h"

/** @addtogroup HK32F103xxxxA_StdPeriph_Examples
  * @{
  */

/** @addtogroup Cortex_SysTick
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static __IO uint32_t TimingDelay;

/* Private function prototypes -----------------------------------------------*/
void Delay(__IO uint32_t nTime);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
    /* Initialize Leds mounted on HK32F103(39A)VExxx_Ver_1 board */
    HK_EVAL_LEDInit(LED1);
    HK_EVAL_LEDInit(LED2);

    //  /* Turn on LED1 LED2 */
    HK_EVAL_LEDOn(LED1);
    HK_EVAL_LEDOn(LED2);    

    /* Setup SysTick Timer for 1 msec interrupts.
       ------------------------------------------
      1. The SysTick_Config() function is a CMSIS function which configure:
         - The SysTick Reload register with value passed as function parameter.
         - Configure the SysTick IRQ priority to the lowest value (0x0F).
         - Reset the SysTick Counter register.
         - Configure the SysTick Counter clock source to be Core Clock Source (HCLK).
         - Enable the SysTick Interrupt.
         - Start the SysTick Counter.

      2. You can change the SysTick Clock source to be HCLK_Div8 by calling the
         SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8) just after the
         SysTick_Config() function call. The SysTick_CLKSourceConfig() is defined
         inside the misc.c file.

      3. You can change the SysTick IRQ priority by calling the
         NVIC_SetPriority(SysTick_IRQn,...) just after the SysTick_Config() function
         call. The NVIC_SetPriority() is defined inside the core_cm3.h file.

      4. To adjust the SysTick time base, use the following formula:
           Reload Value = SysTick Counter Clock (Hz) x  Desired Time base (s)
         - Reload Value is the parameter to be passed for SysTick_Config() function
         - Reload Value should not exceed 0xFFFFFF
     */
    if (SysTick_Config(SystemCoreClock / 1000))
    {
        /* Capture error */
        while (1)
        {
        }
    }

    while (1)
    {
        /* Toggle LED2 */
        HK_EVAL_LEDToggle(LED2);

        /* Insert 500 ms delay */
        Delay(500);

        /* Toggle LED1 */
        HK_EVAL_LEDToggle(LED1);

        /* Insert 1000 ms delay */
        Delay(1000);
    }
}


/**
  * @brief  Inserts a delay time.
  * @param  nTime: specifies the delay time length, in milliseconds.
  * @retval None
  */
void Delay(__IO uint32_t nTime)
{
    TimingDelay = nTime;

    while (TimingDelay != 0)
    {
    }
}

/**
  * @brief  Decrements the TimingDelay variable.
  * @param  None
  * @retval None
  */
void TimingDelay_Decrement(void)
{
    if (TimingDelay != 0x00)
    {
        TimingDelay--;
    }
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

