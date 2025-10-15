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
__IO uint32_t uwCounter = 0;
/* Private function prototypes -----------------------------------------------*/
void PVD_Config(void);
void GPIO_Config(void);
/* Private functions ---------------------------------------------------------*/


/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
    /* Initialize Leds mounted on HK32F103xxxxA app base board */
    HK_EVAL_LEDInit(LED1);
    HK_EVAL_LEDInit(LED2);
    GPIO_Config();

    /* Configure the PVD */
    PVD_Config();

    /* turn off led1 and led2 */
    HK_EVAL_LEDOff(LED1);
    HK_EVAL_LEDOff(LED2);

    /* Infinite loop */
    while (1)
    {
        /* Toggle LED2 */
        HK_EVAL_LEDToggle(LED2);

        /* Inserted Delay */
        for (uwCounter = 0; uwCounter < 0x5FFFF; uwCounter++)
        {
        }
    }
}

/**
  * @brief  Configures the PVD resources.
  * @param  None
  * @retval None
  */
void PVD_Config(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;
    EXTI_InitTypeDef EXTI_InitStructure;

    /* Enable PWR clock */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);

    /* Configure one bit for preemption priority */
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

    /* Enable the PVD Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = PVD_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    /* Configure EXTI Line16(PVD Output) to generate an interrupt on rising and
       falling edges */
    EXTI_ClearITPendingBit(EXTI_Line16);
    EXTI_InitStructure.EXTI_Line = EXTI_Line16;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);

    /* Configure the PVD Level to 3 (PVD detection level set to 2.5V, refer to the
        electrical characteristics of you device datasheet for more details) */
    PWR_PVDLevelConfig(PWR_PVDLevel_3, PVD_MODE_IT, PVD_RISING_FALLING);

    /* Enable the PVD Output */
    PWR_PVDCmd(ENABLE);
}

/**
  * @brief  Configures GPIO.
  * @param  None
  * @retval None
  */
void GPIO_Config(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;

    /* GPIOA clocks enable */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    /* Configure PA4 pin */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
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

/**
  * @}
  */

/**
  * @}
  */
