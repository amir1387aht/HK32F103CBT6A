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
/* Private function prototypes -----------------------------------------------*/
void Sleep_Config(void);
void Delay(uint32_t ntime);
/* Private functions ---------------------------------------------------------*/


/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
    /* Configure the Sleep mode */
    Sleep_Config();
    HK_EVAL_LEDInit(LED1);

    /* Infinite loop */
    while (1)
    {
            Delay(1000);

            /* Wkup push-button (lines 10 to 15) will be used to wakeup the system from Sleep mode */
            HK_EVAL_PBInit(BUTTON_KEY3, BUTTON_MODE_EXTI);

            /* Enter Sleep Mode */
            PWR_EnterSleepMode(PWR_SLEEPEntry_WFI);

            /* Toggle LED1 */
            HK_EVAL_LEDToggle(LED1);
    }
}

/**
  * @brief  Configures the PVD resources.
  * @param  None
  * @retval None
  */
void Sleep_Config(void)
{
    __IO uint32_t index = 0;
    GPIO_InitTypeDef GPIO_InitStructure;

    /* Enable PWR APB1 Clock */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);

    /* Allow access to Backup */
    PWR_BackupAccessCmd(ENABLE);

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
  * @brief  Configures the delay time.
  * @param  ntime:delay times
  * @retval None
  */
void Delay(uint32_t ntime)
{
    for(uint32_t i=0;i<ntime;i++)
    {
        for(uint32_t j=0;j<0xFFFF;j++)
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
