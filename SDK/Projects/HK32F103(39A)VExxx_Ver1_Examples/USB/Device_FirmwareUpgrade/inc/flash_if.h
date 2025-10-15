/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  flash_if.h
* @brief:     Header for flash_if.c file.
* @author:    AE Team
*******************************************************************************/


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FLASH_IF_H
#define __FLASH_IF_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "platform_config.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

uint16_t FLASH_If_Init(void);
uint16_t FLASH_If_Erase (uint32_t SectorAddress);
uint16_t FLASH_If_Write(uint32_t SectorAddress, uint32_t DataLength);
uint8_t *FLASH_If_Read (uint32_t SectorAddress, uint32_t DataLength);

#ifdef __cplusplus
}
#endif

#endif /*__FLASH_IF_H */

/************************ (C) COPYRIGHT HK Microelectronics *****END OF FILE****/
