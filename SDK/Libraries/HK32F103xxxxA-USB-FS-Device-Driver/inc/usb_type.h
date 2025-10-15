/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd 
* @filename:  usb_type.h
* @brief:     Type definitions used by the USB Library.
* @author:    AE Team 
*******************************************************************************/


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USB_TYPE_H
#define __USB_TYPE_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "usb_conf.h"

/** @addtogroup USB
  * @brief  USB driver modules
  * @{
  */
  
/** @defgroup usb_type usb_type
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/** @defgroup usb_type_Exported_Constants usb_type_Exported_Constants
  * @{
  */
  
#ifndef NULL
#define NULL ((void *)0)
#endif

typedef enum
{
	FALSE = 0, TRUE  = !FALSE
}
bool;

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
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

#endif /* __USB_TYPE_H */

/******************* (C) COPYRIGHT   HKMicroChip *****END OF FILE****/
