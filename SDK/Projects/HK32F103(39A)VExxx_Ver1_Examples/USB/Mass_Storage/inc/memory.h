/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  memory.h
* @brief:     Memory management layer.
* @author:    AE Team
*******************************************************************************/


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MEMORY_H
#define __MEMORY_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "hw_config.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
#define TXFR_IDLE     0
#define TXFR_ONGOING  1

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void Write_Memory (uint8_t lun, uint32_t Memory_Offset, uint32_t Transfer_Length);
void Read_Memory (uint8_t lun, uint32_t Memory_Offset, uint32_t Transfer_Length);

#ifdef __cplusplus
}
#endif

#endif /*__MEMORY_H */

/************************ (C) COPYRIGHT HK Microelectronics *****END OF FILE****/
