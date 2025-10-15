/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  hw_config.h
* @brief:     Hardware Configuration & Setup.
* @author:    AE Team
*******************************************************************************/


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HW_CONFIG_H
#define __HW_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "platform_config.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Flash memory address from where user application will be loaded */
#define ApplicationAddress 0x08005000

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void Set_System(void);
void Set_USBClock(void);
void Enter_LowPowerMode(void);
void Leave_LowPowerMode(void);
void USB_Cable_Config (FunctionalState NewState);
void USB_Interrupts_Config(void);
void Reset_Device(void);
void SMI_FLASH_Init(void);
void SMI_FLASH_SectorErase(uint32_t Address);
void SMI_FLASH_WordWrite(uint32_t Address, uint32_t Data);
void SMI_FLASH_PageWrite(uint32_t Address, uint32_t* wBuffer);
void Get_SerialNum(void);
/* External variables --------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif  /*__HW_CONFIG_H */

/************************ (C) COPYRIGHT HK Microelectronics *****END OF FILE****/
