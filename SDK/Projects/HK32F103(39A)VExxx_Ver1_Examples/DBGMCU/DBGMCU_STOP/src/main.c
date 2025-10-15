/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  main.c
* @brief:     USART/Printf/main.c 
* @author:    AE Team
* @version:   V1.0.0/2023-10-23
* @log:
*******************************************************************************/


/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "hk32f103xxxxa_eval.h"
/** @addtogroup hk32f103xxxxa_StdPeriph_Examples
  * @{
  */

/** @addtogroup DBGMCU_STOP
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint32_t TickCnt = 0;
/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/
/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
    /* Setup SysTick Timer for 10 msec interrupts  */
	if (SysTick_Config((SystemCoreClock) / 1000))
	{ 
		/* Capture error */ 
		while (1)
        {
        }
	}

	NVIC_SetPriority(SysTick_IRQn, 0x0);
    HK_EVAL_PBInit(BUTTON_KEY1,BUTTON_MODE_EXTI);
    HK_EVAL_LEDInit(LED1);
    HK_EVAL_LEDInit(LED2);

    /*DISABLE debugging in stop mode*/
    DBGMCU_Config(DBGMCU_STOP, DISABLE);
    /*Enable debugging in stop mode*/
    DBGMCU_Config(DBGMCU_STOP, ENABLE);
    /*Enter stop mode*/
    PWR_EnterSTOPMode(PWR_Regulator_LowPower, PWR_SLEEPEntry_WFI);
    /* Infinite loop */
    while (1)
    {
        if(TickCnt == 20)
        {
          HK_EVAL_LEDToggle(LED1);
        }
        
    }
}

/**
  * @brief  This function performs several random numbers generation.
  * @note   Generated random numbers are stored in global variable array, so that
  *         generated values could be observed by user by watching variable content
  *         in specific debugger window
  * @param  None
  * @retval None
  */

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


