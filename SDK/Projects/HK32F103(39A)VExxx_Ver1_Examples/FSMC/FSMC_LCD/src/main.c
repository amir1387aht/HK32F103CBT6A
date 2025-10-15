/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  main.c
* @brief:     This file provides the FSMC_LCD example.
* @author:    AE Team
* @version:   V1.0.0/2023-10-18
*             1.Initial version
* @log:
*******************************************************************************/


/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "hk32f103xxxxa_eval_lcd.h"
#include "bsp_xpt2046_lcd.h"
#include "palette.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  main function.
  * @param  None
  * @retval None
  */
int main(void)
{
    /*LCD Initialization*/
    ILI9341_Init();
    /*Touch Initialization*/
    XPT2046_Init();
    Calibrate_or_Get_TouchParaWithFlash(3, 0);

    /* Mode 0,3,5, and 6 are suitable for displaying text from left to right
       Other other mode display text is not recommended    
	   Other modes display text with a mirror effect
       The 6-mode is the default display direction for most of the LCD routines */
    ILI9341_GramScan ( 3 );

    /* Draw the touch drawing board interface */
    Palette_Init(LCD_SCAN_MODE);

    while ( 1 )
    {
        /* Touch detection function, this function is called at least 10ms once*/
        XPT2046_TouchEvenHandler();
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


