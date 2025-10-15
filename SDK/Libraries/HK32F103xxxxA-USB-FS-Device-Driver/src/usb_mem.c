/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  usb_mem.c
* @brief:     Utility functions for memory transfers to/from PMA.
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

/** @defgroup usb_mem usb_mem
  * @{
    @verbatim
 ===============================================================================
                        ##### usb_mem.c explain #####
 ===============================================================================
....[..]
   (#) The usb_mem copies a buffer data from the user memory area to the packet memory area
       (PMA) and vice versa.
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

/** @defgroup usb_mem_Private_Functions usb_mem_Private_Functions
  * @{
  */

/**
  * @brief  Copy a buffer from user memory area to packet memory area (PMA)
  * @param  pbUsrBuf: pointer to user memory area.
  * @param  wPMABufAddr: address into PMA.
  * @param  wNBytes: Number of bytes to be copied.
  * @retval None.
  **/
void UserToPMABufferCopy(uint8_t *pbUsrBuf, uint16_t wPMABufAddr, uint16_t wNBytes)
{
    uint32_t n = (wNBytes + 1) >> 1;   /* n = (wNBytes + 1) / 2 */
    uint32_t i, temp1, temp2;
    uint16_t *pdwVal;
    pdwVal = (uint16_t *)(wPMABufAddr * 2 + PMAAddr);

    for (i = n; i != 0; i--)
    {
        temp1 = (uint16_t) * pbUsrBuf;
        pbUsrBuf++;
        temp2 = temp1 | (uint16_t) * pbUsrBuf << 8;
        *pdwVal++ = temp2;
        pdwVal++;
        pbUsrBuf++;
    }
}

/**
  * @brief  Copy a buffer from user memory area to packet memory area (PMA)
  * @param  pbUsrBuf: pointer to user memory area.
  * @param  wPMABufAddr: address into PMA.
  * @param  wNBytes: Number of bytes to be copied.
  * @retval None
  **/
void PMAToUserBufferCopy(uint8_t *pbUsrBuf, uint16_t wPMABufAddr, uint16_t wNBytes)
{
    uint32_t n = (wNBytes + 1) >> 1;/* /2*/
    uint32_t i;
    uint32_t *pdwVal;
    pdwVal = (uint32_t *)(wPMABufAddr * 2 + PMAAddr);

    for (i = n; i != 0; i--)
    {
        *(uint16_t*)pbUsrBuf++ = *pdwVal++;
        pbUsrBuf++;
    }
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
