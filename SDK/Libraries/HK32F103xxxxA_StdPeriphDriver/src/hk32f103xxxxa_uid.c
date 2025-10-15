/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  hk32f103xxxxa_uid.c
* @brief:     This file provides firmware functions to manage the following 
*             functionalities of the DBGMCU peripheral:
*             get the revision identifier
*             get the device identifier
*             Configures the specified peripheral and low power mode behavior when the MCU under Debug mode.
*             TraceConfiguration 
* @author:    AE Team
* @version:   V1.0.0/2023-10-23
* @log:       V1.0.0/2023-10-18// Initial release
*******************************************************************************/


/* Includes ------------------------------------------------------------------*/
#include "hk32f103xxxxa_uid.h"


/** @addtogroup HK32F103xxxxA_StdPeriph_Driver
  * @{
  */
	
/** @defgroup UID UID
  * @{
  */

/**
  * @brief  Return the unique device identifier (UID based on 96 bits)
  * @param  UID: pointer to 3 words array.
  * @retval Device identifier
  */
void UID_GetUID(uint32_t *UID)
{
	UID[0] = (uint32_t)(READ_REG(*((uint32_t *)0x1FFFF7E8)));
	UID[1] = (uint32_t)(READ_REG(*((uint32_t *)(0x1FFFF7E8 + 4U))));
	UID[2] = (uint32_t)(READ_REG(*((uint32_t *)(0x1FFFF7E8 + 8U))));
}


/**
  * @}
  */
  
/**
  * @}
  */   
