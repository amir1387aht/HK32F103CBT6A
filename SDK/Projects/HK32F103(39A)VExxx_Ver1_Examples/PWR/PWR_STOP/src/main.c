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
ErrorStatus HSEStartUpStatus;
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
extern uint8_t Counter;
/* Private function prototypes -----------------------------------------------*/
void Stop_Config(void);
void GPIO_Config(void);
void Systick_Config(void);
void SystemClock_Config(void);
/* Private functions ---------------------------------------------------------*/


/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
    /* Configures stop mode */
    Stop_Config();

    /* Configures systick */
    Systick_Config();

    /* Configures LEDs */
    HK_EVAL_LEDInit(LED1);

    /* Infinite loop */
    while (1)
    {
        /* wait 5 second */
        if (Counter == 50)
        {
            Counter = 0x00;

            /* Wkup push-button (lines 10 to 15) will be used to wakeup the system from STOP mode */
            HK_EVAL_PBInit(BUTTON_KEY3, BUTTON_MODE_EXTI);

            /* Enter Stop Mode */
            PWR_EnterSTOPMode(PWR_Regulator_LowPower, PWR_STOPEntry_WFI);

            /* Configures system clock after wake-up from STOP */
            SystemClock_Config();

            /* Toggles the LED1 */
            HK_EVAL_LEDToggle(LED1);
        } 
    }
}

/**
  * @brief  Configure GPIO to analog mode and turn off GPIO clock.
  * @param  None
  * @retval None
  */
void Stop_Config(void)
{
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

/**
  * @brief  Configures the Sysclock to HSE.
  * @param  None
  * @retval None
  */
void SystemClock_Config(void)
{
    /* SYSCLK, HCLK, PCLK2 and PCLK1 configuration -----------------------------*/

    /* RCC system reset(for debug purpose) */
    RCC_DeInit();

    /* Enable HSE */
    RCC_HSEConfig(RCC_HSE_ON);

    /* Wait till HSE is ready */
    HSEStartUpStatus = RCC_WaitForHSEStartUp();

    if (HSEStartUpStatus == SUCCESS)
    {
        /* Flash 2 wait state */
        FLASH->ACR &= (uint32_t)((uint32_t)~FLASH_ACR_LATENCY);
        FLASH->ACR |= (uint32_t)FLASH_Latency_2;

        /* HCLK = SYSCLK */
        RCC_HCLKConfig(RCC_SYSCLK_Div1);

        /* PCLK2 = HCLK */
        RCC_PCLK2Config(RCC_HCLK_Div1);

        /* PCLK1 = HCLK/2 */
        RCC_PCLK1Config(RCC_HCLK_Div2);

        /* PLLCLK = 8MHz * 9 = 72 MHz */
        RCC_PLLConfig(RCC_PLLSource_HSE, 9);

        /* Enable PLL */
        RCC_PLLCmd(ENABLE);

        /* Wait till PLL is ready */
        while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
        {
        }

        /* Select PLL as system clock source */
        RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

        /* Wait till PLL is used as system clock source */
        while (RCC_GetSYSCLKSource() != 0x02)
        {
        }
    }
    else
    {
        /* If HSE fails to start-up, the application will have wrong clock configuration.
           User can add here some code to deal with this error */

        /* Go to infinite loop */
        while (1)
        {
        }
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
       tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
}
#endif /* USE_FULL_ASSERT */

/**
  * @}
  */

/**
  * @}
  */
