/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd 
* @filename:  usb_int.h
* @brief:     Endpoint CTR (Low and High) interrupt's service routines.
* @author:    AE Team 
*******************************************************************************/


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USB_INT_H
#define __USB_INT_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

/** @addtogroup usb_int
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

/** @defgroup usb_int_External_Variables usb_int_External_Variables
  * @{
  */
  
void CTR_LP(void);
void CTR_HP(void);

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

#endif /* __USB_INT_H */

/******************* (C) COPYRIGHT   HKMicroChip *****END OF FILE****/
