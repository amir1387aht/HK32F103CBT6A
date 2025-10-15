/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd 
* @filename:  usb_mem.h
* @brief:     Utility functions for memory transfers to/from PMA.
* @author:    AE Team 
*******************************************************************************/


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USB_MEM_H
#define __USB_MEM_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

/** @addtogroup usb_mem
  * @{
  */
  
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

/** @defgroup usb_mem_Exported_Functions usb_mem_Exported_Functions
  * @{
  */
  
void UserToPMABufferCopy(uint8_t *pbUsrBuf, uint16_t wPMABufAddr, uint16_t wNBytes);
void PMAToUserBufferCopy(uint8_t *pbUsrBuf, uint16_t wPMABufAddr, uint16_t wNBytes);
/* External variables --------------------------------------------------------*/

/**
  * @}
  */
  
/**
  * @}
  */  

#ifdef __cplusplus
}
#endif

#endif  /*__USB_MEM_H*/

/******************* (C) COPYRIGHT   HKMicroChip *****END OF FILE****/
