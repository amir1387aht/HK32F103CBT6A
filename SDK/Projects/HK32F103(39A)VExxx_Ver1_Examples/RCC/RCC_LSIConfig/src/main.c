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
void Delay(__IO uint32_t nCount);
/* Private functions ---------------------------------------------------------*/


/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    /* Initialize Leds mounted on EVAL*/
    HK_EVAL_LEDInit(LED2);

    /* Initialize User push-button, will be used to trigger an interrupt each time it's pressed.
    In the ISR the PLL source will be changed from different clocks */
    HK_EVAL_PBInit(BUTTON_KEY3, BUTTON_MODE_EXTI);

    /* Enable the GPIOA Clock */    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* Output LSI clock on MCO pin ---------------------------------------------*/
    RCC_MCOConfig(RCC_MCO_LSI, RCC_MCOPrescaler_1);

    while (1)
    {
        if ((RCC->CSR & RCC_CSR_LSION) !=  RCC_CSR_LSION)
        {
            /* if LSI is off, Toggle LED2 */

            /* Insert a delay */
            Delay(0x3FFFF);

            /* Toggle LED2 */
            HK_EVAL_LEDToggle(LED2);

            /* Insert a delay */
            Delay(0x4FFFF);
        }
        else
        {
            /* Insert a delay */
            Delay(0x3FFFF);

            /* turn on LED2 */
            HK_EVAL_LEDOn(LED2);

            /* Insert a delay */
            Delay(0x4FFFF);
        }
    }
}

/**
  * @brief  Inserts a delay time.
  * @param  nCount: specifies the delay time length.
  * @retval None
  */
void Delay(__IO uint32_t nCount)
{
    /* Decrement nCount value */
    while (nCount != 0)
    {
        nCount--;
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
