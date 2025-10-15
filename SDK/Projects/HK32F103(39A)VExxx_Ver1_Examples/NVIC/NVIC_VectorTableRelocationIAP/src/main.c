/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  main.c
* @brief:     Main program body
* @author:    AE Team
* @version:   V1.0.0/2023-10-23
*                     1.Initial version
* @log:
*******************************************************************************/


/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private typedef -----------------------------------------------------------*/
typedef void (*pFunction)(void);

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
pFunction Jump_To_Application;
unsigned int   JumpAddress;

/* Private function prototypes -----------------------------------------------*/
static void Delay(__IO uint32_t nCount);

/* Private functions ---------------------------------------------------------*/
/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{
    HK_EVAL_LEDInit(LED2);
    HK_EVAL_LEDOn(LED2);
  
    for(uint16_t i = 0; i < 100; i++)
    {
        Delay(0xffff);
        Delay(0xffff);
        Delay(0xffff);
        HK_EVAL_LEDToggle(LED2);  
    }
  
    JumpAddress = *(volatile unsigned int*) (0x08003000+4);
		Jump_To_Application = (pFunction) JumpAddress;
		Jump_To_Application();	

    while (1)
    {
    }
}

/**
  * @brief  Inserts a delay time.
  * @param  nCount: specifies the delay time length.
  * @retval None
  */
static void Delay(__IO uint32_t nCount)
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


