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
uint8_t USB_Rx_Buffer[VIRTUAL_COM_PORT_DATA_SIZE];
extern uint8_t USART_Rx_Buffer[];
extern uint32_t USART_Rx_ptr_out;
extern uint32_t USART_Rx_length;
extern uint8_t  USB_Tx_State;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  EP1_IN_Callback
  * @retval None.
  */
void EP1_IN_Callback(void)
{
    VCP_Data_InISR();
}

/**
  * @brief  EP3_OUT_Callback
  * @retval None.
  */
void EP3_OUT_Callback(void)
{
    uint16_t USB_Rx_Cnt;

    /* Get the received data buffer and update the counter */
    USB_Rx_Cnt = USB_SIL_Read(EP3_OUT, USB_Rx_Buffer);

    /* USB data will be immediately processed, this allow next USB traffic being
    NAKed till the end of the USART Xfer */
    USB_To_USART_Send_Data(USB_Rx_Buffer, USB_Rx_Cnt);

    /* Enable the receive of data on EP3 */
    SetEPRxValid(ENDP3);
}


/**
  * @brief  sof callback
  * @retval None.
  */
void SOF_Callback(void)
{
    static uint32_t FrameCount = 0;

    if (bDeviceState == CONFIGURED)
    {
        if (FrameCount++ == VCOMPORT_IN_FRAME_INTERVAL)
        {
            /* Reset the frame counter */
            FrameCount = 0;

            /* Check the data to be sent through IN pipe */
            Handle_USBAsynchXfer();
        }
    }
}

/************************ (C) COPYRIGHT HK Microelectronics *****END OF FILE****/


