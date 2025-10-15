/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  main.c
* @brief:     Main program body
* @author:    AE Team
* @version:   V1.0.0/2023-10-23
*             1.Initial version
* @log:
*******************************************************************************/


/* Includes ------------------------------------------------------------------*/
#include "main.h"

/** @addtogroup HK32F103xxxxA_StdPeriph_Examples
  * @{
  */

/** @addtogroup GPIO_IOToggle
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
static void GPIO_Configuration(void);

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
    GPIO_Configuration();

    /* Infinite loop */
    while (1)
    {
        /* Set PE5 and PE6 */
        GPIOE->BSRR = 0x00000060;

        /* Reset PE5 and PE6 */
        GPIOE->BRR  = 0x00000060;

        /* Set PE5 and PE6 */
        GPIOE->BSRR = 0x00000060;

        /* Reset PE5 and PE6 */
        GPIOE->BRR  = 0x00000060;

        /* Set PE5 and PE6 */
        GPIOE->BSRR = 0x00000060;

        /* Reset PE5 and PE6 */
        GPIOE->BRR  = 0x00000060;

        /* Set PE5 and PE6 */
        GPIOE->BSRR = 0x00000060;

        /* Reset PE5 and PE6 */
        GPIOE->BRR  = 0x00000060;

        /* Set PE5 and PE6 */
        GPIOE->BSRR = 0x00000060;

        /* Reset PE5 and PE6 */
        GPIOE->BRR  = 0x00000060;
    }
}
/**
  * @brief  GPIO Initialization Function
  * @param  None
  * @retval None
  */
static void GPIO_Configuration(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    /* GPIOE clocks enable */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);

    /* Configure pull-push output IO PE.05 and PE.06*/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Schmit = GPIO_Schmit_Enable;
    GPIO_Init(GPIOE, &GPIO_InitStructure);
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
