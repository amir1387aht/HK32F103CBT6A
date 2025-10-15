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
#include "usb_lib.h"
#include "usb_istr.h"
#include "usb_desc.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
extern __IO uint8_t Receive_Buffer[REPORT_COUNT];
extern __IO uint8_t PrevXferComplete;
extern uint32_t Receive_length;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/**
  * @brief  EP1 OUT Callback Routine.
  * @retval None.
  */
void EP1_OUT_Callback(void)
{
    Receive_length = GetEPRxCount(ENDP1);
    PMAToUserBufferCopy((uint8_t*)Receive_Buffer, ENDP1_RXADDR, Receive_length);
    SetEPRxStatus(ENDP1, EP_RX_VALID);
    PrevXferComplete = 1;
}

/**
  * @brief  EP1 IN Callback Routine.
  * @retval None.
  */
void EP1_IN_Callback(void)
{
}
/************************ (C) COPYRIGHT HK Microelectronics *****END OF FILE****/


