/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  main.c
* @brief:     Main program body
* @author:    AE Team
* @version:   V1.0.0/2023-10-31
*              1.Initial version
* @log:
*******************************************************************************/


/* Includes ------------------------------------------------------------------*/
#include "main.h"

/** @addtogroup HK32F103xxxxA_StdPeriph_Examples
  * @{
  */

/** @addtogroup _template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
GPIO_InitTypeDef GPIO_InitStructure;
RCC_ClocksTypeDef RCC_ClockFreq;
ErrorStatus HSEStartUpStatus;
/* Private define ------------------------------------------------------------*/
#ifdef SYSCLK_HSE
    void SetSysClockToHSE(void);
#elif defined SYSCLK_FREQ_24MHz
    void SetSysClockTo24(void);
#elif defined SYSCLK_FREQ_36MHz
    void SetSysClockTo36(void);
#elif defined SYSCLK_FREQ_48MHz
    void SetSysClockTo48(void);
#elif defined SYSCLK_FREQ_56MHz
    void SetSysClockTo56(void);
#elif defined SYSCLK_FREQ_72MHz
    void SetSysClockTo72(void);
#endif
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
void NVIC_Configuration(void);
void Delay(__IO uint32_t nCount);
void SetSysClock(void);
/* Private functions ---------------------------------------------------------*/



/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
    /* Configure the System clock frequency, HCLK, PCLK2 and PCLK1 prescalers */
    SetSysClock();

    /* This function fills the RCC_ClockFreq structure with the current
       frequencies of different on chip clocks (for debug purpose) */
    RCC_GetClocksFreq(&RCC_ClockFreq);

    /* Enable Clock Security System(CSS): this will generate an NMI exception
       when HSE clock fails */
    RCC_ClockSecuritySystemCmd(ENABLE);

    /* NVIC configuration ------------------------------------------------------*/
    NVIC_Configuration();

    /* Initialize Leds ---------------------------------------------------------*/
    HK_EVAL_LEDInit(LED2);

    /* Output system clock on MCO pin ---------------------------------------------*/
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    RCC_MCOConfig(RCC_MCO_SYSCLK, RCC_MCOPrescaler_1);

    while (1)
    {
        /* Toggle LED2 */
        HK_EVAL_LEDToggle(LED2);

        /* Insert delay */
        Delay(DELAY_COUNT);
    }
}

/**
  * @brief  Configures the System clock frequency, HCLK, PCLK2 and PCLK1
  *         prescalers.
  * @param  None
  * @retval None
  */
void SetSysClock(void)
{
#if defined SYSCLK_HSE
    SetSysClockToHSE();
#elif defined SYSCLK_FREQ_24MHz
    SetSysClockTo24();
#elif defined SYSCLK_FREQ_36MHz
    SetSysClockTo36();
#elif defined SYSCLK_FREQ_48MHz
    SetSysClockTo48();
#elif defined SYSCLK_FREQ_56MHz
    SetSysClockTo56();
#elif defined SYSCLK_FREQ_72MHz
    SetSysClockTo72();
#endif

    /* If none of the define above is enabled, the HSI is used as System clock
       source (default after reset) */
}

/**
  * @brief  Selects HSE as System clock source and configure HCLK, PCLK2
  *         and PCLK1 prescalers.
  * @param  None
  * @retval None
  */
void SetSysClockToHSE(void)
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
        /* Flash 0 wait state */
        FLASH->ACR &= (uint32_t)((uint32_t)~FLASH_ACR_LATENCY);

        if (HSE_VALUE <= 24000000)
        {
            FLASH->ACR |= (uint32_t)FLASH_Latency_0;
        }
        else if (HSE_VALUE <= 48000000)
        {
            FLASH->ACR |= (uint32_t)FLASH_Latency_1;
        }
        else
        {
            FLASH->ACR |= (uint32_t)FLASH_Latency_2;
        }

        /* HCLK = SYSCLK */
        RCC_HCLKConfig(RCC_SYSCLK_Div1);
        /* PCLK2 = HCLK */
        RCC_PCLK2Config(RCC_HCLK_Div1);
        /* PCLK1 = HCLK */
        RCC_PCLK1Config(RCC_HCLK_Div1);
                /* Select PLL as system clock source */
        RCC_SYSCLKConfig(RCC_SYSCLKSource_HSE);

        /* Wait till PLL is used as system clock source */
        while (RCC_GetSYSCLKSource() != 0x01)
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

/**
  * @brief  Sets System clock frequency to 24MHz and configure HCLK, PCLK2
  *         and PCLK1 prescalers.
  * @param  None
  * @retval None
  */
void SetSysClockTo24(void)
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
        /* Flash 0 wait state */
        FLASH->ACR &= (uint32_t)((uint32_t)~FLASH_ACR_LATENCY);
        FLASH->ACR |= (uint32_t)FLASH_Latency_0;

        /* HCLK = SYSCLK */
        RCC_HCLKConfig(RCC_SYSCLK_Div1);

        /* PCLK2 = HCLK */
        RCC_PCLK2Config(RCC_HCLK_Div1);

        /* PCLK1 = HCLK */
        RCC_PCLK1Config(RCC_HCLK_Div1);

        /* PLLCLK = 8MHz * 3 = 24 MHz */
        RCC_PLLConfig(RCC_PLLSource_HSE, 3);

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

/**
  * @brief  Sets System clock frequency to 36MHz and configure HCLK, PCLK2
  *         and PCLK1 prescalers.
  * @param  None
  * @retval None
  */
void SetSysClockTo36(void)
{
    /* SYSCLK, HCLK, PCLK2 and PCLK1 configuration -----------------------------*/

    /* RCC system reset(for debug purpose) */
    RCC_DeInit();

    /* Enable HSI */
    RCC_HSICmd(ENABLE);

    /* Enable HSE */
    RCC_HSEConfig(RCC_HSE_ON);

    /* Wait till HSE is ready */
    HSEStartUpStatus = RCC_WaitForHSEStartUp();

    if (HSEStartUpStatus == SUCCESS)
    {
        /* Flash 1 wait state */
        FLASH->ACR &= (uint32_t)((uint32_t)~FLASH_ACR_LATENCY);
        FLASH->ACR |= (uint32_t)FLASH_Latency_1;

        /* HCLK = SYSCLK */
        RCC_HCLKConfig(RCC_SYSCLK_Div1);

        /* PCLK2 = HCLK */
        RCC_PCLK2Config(RCC_HCLK_Div1);

        /* PCLK1 = HCLK */
        RCC_PCLK1Config(RCC_HCLK_Div1);

        /*  PLL configuration:  = (HSE / 2) * 9 = 36 MHz */
        RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_PLLSRC | RCC_CFGR_PLLXTPRE | RCC_CFGR_PLLMULL));
        RCC->CFGR |= (uint32_t)(RCC_CFGR_PLLSRC_HSE | RCC_CFGR_PLLXTPRE_HSE_Div2 | RCC_CFGR_PLLMULL9);

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

/**
  * @brief  Sets System clock frequency to 48MHz and configure HCLK, PCLK2
  *         and PCLK1 prescalers.
  * @param  None
  * @retval None
  */
void SetSysClockTo48(void)
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
        /* Flash 1 wait state */
        FLASH->ACR &= (uint32_t)((uint32_t)~FLASH_ACR_LATENCY);
        FLASH->ACR |= (uint32_t)FLASH_Latency_1;

        /* HCLK = SYSCLK */
        RCC_HCLKConfig(RCC_SYSCLK_Div1);

        /* PCLK2 = HCLK */
        RCC_PCLK2Config(RCC_HCLK_Div1);

        /* PCLK1 = HCLK/2 */
        RCC_PCLK1Config(RCC_HCLK_Div2);

        /* PLLCLK = 8MHz * 6 = 48 MHz */
        RCC_PLLConfig(RCC_PLLSource_HSE, 6);

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

/**
  * @brief  Sets System clock frequency to 56MHz and configure HCLK, PCLK2
  *         and PCLK1 prescalers.
  * @param  None
  * @retval None
  */
void SetSysClockTo56(void)
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

        /* PLLCLK = 8MHz * 7 = 56 MHz */
        RCC_PLLConfig(RCC_PLLSource_HSE, 7);

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

/**
  * @brief  Sets System clock frequency to 72MHz and configure HCLK, PCLK2
  *         and PCLK1 prescalers.
  * @param  None
  * @retval None
  */
void SetSysClockTo72(void)
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

/**
  * @brief  Configures the NVIC.
  * @param  None
  * @retval None
  */
void NVIC_Configuration(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;

    /* Enable and configure RCC global IRQ channel */
    NVIC_InitStructure.NVIC_IRQChannel = RCC_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

/**
  * @brief  Inserts a delay time.
  * @param  nCount: specifies the delay time length.
  * @retval None
  */
void Delay(__IO uint32_t nCount)
{
    for (; nCount != 0; nCount--)
    {
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
