/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  mass_mal.h
* @brief:     Header for mass_mal.c file.
* @author:    AE Team
*******************************************************************************/


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MASS_MAL_H
#define __MASS_MAL_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
#define MAL_OK   0
#define MAL_FAIL 1
#define MAX_LUN  1

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

uint16_t MAL_Init (uint8_t lun);
uint16_t MAL_GetStatus (uint8_t lun);
uint16_t MAL_Read(uint8_t lun, uint32_t Memory_Offset, uint32_t *Readbuff, uint16_t Transfer_Length);
uint16_t MAL_Write(uint8_t lun, uint32_t Memory_Offset, uint32_t *Writebuff, uint16_t Transfer_Length);

#ifdef __cplusplus
}
#endif

#endif /*__MASS_MAL_H */

/************************ (C) COPYRIGHT HK Microelectronics *****END OF FILE****/
