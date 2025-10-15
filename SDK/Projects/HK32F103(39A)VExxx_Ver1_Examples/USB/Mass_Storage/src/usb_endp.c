/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  usb_endp.c
* @brief:     Endpoint routines.
* @author:    AE Team
* @version:   V1.0.0/2023-10-23
*             1.Initial version
* @log:
*******************************************************************************/


/* Includes ------------------------------------------------------------------*/
#include "usb_lib.h"
#include "usb_bot.h"
#include "usb_istr.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  EP1 IN Callback Routine
  * @retval None.
  */
void EP1_IN_Callback(void)
{
    Mass_Storage_In();
}

/**
  * @brief  EP2 OUT Callback Routine.
  * @retval None.
  */
void EP2_OUT_Callback(void)
{
    Mass_Storage_Out();
}

/************************ (C) COPYRIGHT HK Microelectronics *****END OF FILE****/


