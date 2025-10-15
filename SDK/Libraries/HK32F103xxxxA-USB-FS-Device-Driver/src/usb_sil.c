/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  usb_sil.c
* @brief:     Simplified Interface Layer for Global Initialization and Endpoint
*             Read/Write operations.
* @author:    AE Team
* @version:   V1.0.0/2023-10-16
*             1.Initial version
* @log:
*******************************************************************************/


/* Includes ------------------------------------------------------------------*/
#include "usb_lib.h"

/** @addtogroup USB
  * @brief  USB driver modules
  * @{
  */

/** @defgroup usb_sil usb_sil
  * @{
    @verbatim
 ===============================================================================
                        ##### usb_sil.c explain #####
 ===============================================================================
....[..]
   (#) The usb_sil module implements an additional abstraction layer for USB-FS_Device
       peripheral. It offers simple functions for accessing the Endpoints for Read and Write
       operations.
    @endverbatim
  *
  ******************************************************************************
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Extern variables ----------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup usb_sil_Private_Functions usb_sil_Private_Functions
  * @{
  */

/**
  * @brief  Initialize the USB Device IP and the Endpoint 0.
  * @retval Status.
  **/
uint32_t USB_SIL_Init(void)
{
    /* USB interrupts initialization */
    /* clear pending interrupts */
    _SetISTR(0);
    wInterrupt_Mask = IMR_MSK;
    /* set interrupts mask */
    _SetCNTR(wInterrupt_Mask);
    return 0;
}

/**
  * @brief  Write a buffer of data to a selected endpoint.
  * @param  bEpAddr: The address of the non control endpoint.
  * @param  pBufferPointer: The pointer to the buffer of data to be written
  *         to the endpoint.
  * @param  wBufferSize: Number of data to be written (in bytes).
  * @retval Status.
  **/
uint32_t USB_SIL_Write(uint8_t bEpAddr, uint8_t* pBufferPointer, uint32_t wBufferSize)
{
    /* Use the memory interface function to write to the selected endpoint */
    UserToPMABufferCopy(pBufferPointer, GetEPTxAddr(bEpAddr & 0x7F), wBufferSize);

    /* Update the data length in the control register */
    SetEPTxCount((bEpAddr & 0x7F), wBufferSize);

    return 0;
}

/**
  * @brief  Write a buffer of data to a selected endpoint.
  * @param  bEpAddr: The address of the non control endpoint.
  * @param  pBufferPointer: The pointer to which will be saved the
  *         received data buffer.
  * @retval Number of received data (in Bytes).
  **/
uint32_t USB_SIL_Read(uint8_t bEpAddr, uint8_t* pBufferPointer)
{
    uint32_t DataLength = 0;

    /* Get the number of received data on the selected Endpoint */
    DataLength = GetEPRxCount(bEpAddr & 0x7F);

    /* Use the memory interface function to write to the selected endpoint */
    PMAToUserBufferCopy(pBufferPointer, GetEPRxAddr(bEpAddr & 0x7F), DataLength);

    /* @retval the number of received data */
    return DataLength;
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/******************* (C) COPYRIGHT   HKMicroChip *****END OF FILE****/
