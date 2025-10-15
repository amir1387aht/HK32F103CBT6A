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
#include "usb_type.h"
#include "usb_lib.h"
#include "usb_desc.h"
#include "usb_pwr.h"
#include "usb_istr.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported define -----------------------------------------------------------*/
#define BULK_MAX_PACKET_SIZE  0x00000040

/* Exported functions ------------------------------------------------------- */
void Set_System(void);
void Set_USBClock(void);
void Enter_LowPowerMode(void);
void Leave_LowPowerMode(void);
void USB_Interrupts_Config(void);
void USB_Cable_Config (FunctionalState NewState);
void Get_SerialNum(void);
void MAL_Config(void);
/* External variables --------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif  /*__HW_CONFIG_H */

/************************ (C) COPYRIGHT HK Microelectronics *****END OF FILE****/
