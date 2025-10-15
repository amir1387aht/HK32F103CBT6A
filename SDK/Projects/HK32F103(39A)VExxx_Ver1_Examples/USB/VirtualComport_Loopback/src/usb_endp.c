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
#include "usb_desc.h"
#include "usb_mem.h"
#include "hw_config.h"
#include "usb_istr.h"
#include "usb_pwr.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/* Interval between sending IN packets in frame number (1 frame = 1ms) */
#define VCOMPORT_IN_FRAME_INTERVAL             5
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
extern __IO uint32_t packet_sent;
extern __IO uint32_t packet_receive;
extern __IO uint8_t Receive_Buffer[64];
uint32_t Receive_length;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  EP1_IN_Callback
  * @retval None.
  */
void EP1_IN_Callback(void)
{
    packet_sent = 1;
}

/**
  * @brief  EP3_OUT_Callback
  * @retval None.
  */
void EP3_OUT_Callback(void)
{
    packet_receive = 1;
    Receive_length = GetEPRxCount(ENDP3);
    PMAToUserBufferCopy((unsigned char*)Receive_Buffer, ENDP3_RXADDR, Receive_length);
}

/************************ (C) COPYRIGHT HK Microelectronics *****END OF FILE****/

