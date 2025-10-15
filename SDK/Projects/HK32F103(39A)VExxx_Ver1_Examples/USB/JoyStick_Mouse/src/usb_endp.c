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
#include "hw_config.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
extern __IO uint8_t PrevXferComplete;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  EP1 OUT Callback Routine.
  * @retval None.
  */
void EP1_IN_Callback(void)
{
    /* Set the transfer complete token to inform upper layer that the current
    transfer has been complete */
    PrevXferComplete = 1;
}

/************************ (C) COPYRIGHT HK Microelectronics *****END OF FILE****/


