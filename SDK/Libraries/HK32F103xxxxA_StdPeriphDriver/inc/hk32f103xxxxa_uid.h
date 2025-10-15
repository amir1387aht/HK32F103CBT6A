/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  hk32f103xxxxa_uid.h
* @brief:     Header file of uid module.
* @author:    AE Team
*******************************************************************************/


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HK32F103XXXXA_UID_H
#define __HK32F103XXXXA_UID_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "hk32f103xxxxa_conf.h"


/** @addtogroup UID
  * @{
  */
	
	
/* Exported types ------------------------------------------------------------*/
/** @defgroup UID_Exported_Types UID_Exported_Types
  * @{
  */

/**
  * @}
  */
	
	
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/** @defgroup UID_Exported_Macros UID_Exported_Macros
  * @{
  */


/**
  * @}
  */
  
  
   
  
/* Exported functions ------------------------------------------------------- */
/** @defgroup UID_Exported_Functions UID_Exported_Functions
  * @{
  */
	
void UID_GetUID(uint32_t *UID);

#endif /*__HK32F103XXXXA_UID_H */


/**
  * @}
  */ 
	
/**
  * @}
  */
	
/******************* (C) COPYRIGHT   HKMicroChip *****END OF FILE****/
