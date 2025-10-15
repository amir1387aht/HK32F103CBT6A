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

/** @addtogroup GPIO_JTAGRemap
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
static void GPIO_Configuration(void);
static void Delay(__IO uint32_t nCount);


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
        /* Toggle JTMS/SWDAT pin */
        GPIO_WriteBit(GPIOA, GPIO_Pin_13, (BitAction)(1 - GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_13)));

        /* Insert delay */
        Delay(0x5FFFF);

        /* Toggle JTCK/SWCLK pin */
        GPIO_WriteBit(GPIOA, GPIO_Pin_14, (BitAction)(1 - GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_14)));

        /* Insert delay */
        Delay(0x5FFFF);

        /* Toggle JTDI pin */
        GPIO_WriteBit(GPIOA, GPIO_Pin_15, (BitAction)(1 - GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_15)));

        /* Insert delay */
        Delay(0x5FFFF);

        /* Toggle JTDO pin */
        GPIO_WriteBit(GPIOB, GPIO_Pin_3, (BitAction)(1 - GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_3)));

        /* Insert delay */
        Delay(0x5FFFF);

        /* Toggle JTRST pin */
        GPIO_WriteBit(GPIOB, GPIO_Pin_4, (BitAction)(1 - GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_4)));

        /* Insert delay */
        Delay(0x5FFFF);
    }
}
/**
  * @brief  GPIO Initialization Function
  * @param  None
  * @retval None
  */
static void GPIO_Configuration(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);
    GPIO_InitTypeDef GPIO_InitStructure;

    /* Disable the Serial Wire Jtag Debug Port SWJ-DP */
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);

    /* Configure PA.13 (JTMS/SWDAT), PA.14 (JTCK/SWCLK) and PA.15 (JTDI) as 
       output push-pull */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    /* Configure PB.03 (JTDO) and PB.04 (JTRST) as output push-pull */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
}

/**
  * @brief  Inserts a delay time.
  * @param  nCount: specifies the delay time length.
  * @retval None
  */
static void Delay(__IO uint32_t nCount)
{
    for(; nCount != 0; nCount--)
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

