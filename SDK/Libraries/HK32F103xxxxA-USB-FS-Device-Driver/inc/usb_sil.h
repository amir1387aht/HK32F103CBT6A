/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd 
* @filename:  usb_sil.h
* @brief:     Simplified Interface Layer for Global Initialization and Endpoint
*             Read/Write operations.
* @author:    AE Team 
*******************************************************************************/


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USB_SIL_H
#define __USB_SIL_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

/** @addtogroup usb_sil
  * @{
  */
  
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

/** @defgroup usb_sil_Exported_Functions usb_sil_Exported_Functions
  * @{
  */

uint32_t USB_SIL_Init(void);
uint32_t USB_SIL_Write(uint8_t bEpAddr, uint8_t* pBufferPointer, uint32_t wBufferSize);
uint32_t USB_SIL_Read(uint8_t bEpAddr, uint8_t* pBufferPointer);

/**
  * @}
  */

/* External variables --------------------------------------------------------*/

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __USB_SIL_H */

/******************* (C) COPYRIGHT   HKMicroChip *****END OF FILE****/
