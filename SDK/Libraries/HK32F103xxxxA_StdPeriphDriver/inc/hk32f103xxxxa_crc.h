/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  hk32f103xxxxa_crc.h
* @brief:     CRC initialization and configuration
* @author:    AE Team
*******************************************************************************/


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HK32F103XXXXA_CRC_H
#define __HK32F103XXXXA_CRC_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "hk32f103xxxxa_conf.h"

/** @addtogroup CRC
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/** @defgroup CRC_Exported_Functions CRC_Exported_Functions
  * @{
  */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
/** @defgroup CRC_Configuration_Functions CRC_Configuration_Functions
	* @{
  */
void CRC_DeInit(void);
void CRC_ResetDR(void);
/**
  * @}
  */ 

/** @defgroup CRC_Computation_Functions CRC_Computation_Functions
  * @{
  */
uint32_t CRC_CalcCRC(uint32_t CRC_Data);
uint32_t CRC_CalcBlockCRC(uint32_t pBuffer[], uint32_t BufferLength);
uint32_t CRC_GetCRC(void);
/**
  * @}
  */ 

/** @defgroup CRC_Independent_Register_Access_Functions CRC_Independent_Register_Access_Functions
  * @{
  */
void CRC_SetIDRegister(uint8_t CRC_IDValue);
uint8_t CRC_GetIDRegister(void);
/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /*__HK32F103XXXXA_CRC_H */

/**
  * @}
  */ 

/**
  * @}
  */ 




