/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  usb_desc.h
* @brief:     Descriptor Header for Device Firmware Upgrade (DFU).
* @author:    AE Team
*******************************************************************************/


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USB_DESC_H
#define __USB_DESC_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "platform_config.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
#define DFU_SIZ_DEVICE_DESC            18
#define DFU_SIZ_CONFIG_DESC          45
#define DFU_SIZ_STRING_LANGID           4
#define DFU_SIZ_STRING_VENDOR           38
#define DFU_SIZ_STRING_PRODUCT          18
#define DFU_SIZ_STRING_SERIAL           26
#define DFU_SIZ_STRING_INTERFACE0       98    /* Flash Bank 0 */

#define DFU_SIZ_STRING_INTERFACE1       98     /* SPI Flash : M25P64*/
#define DFU_SIZ_STRING_INTERFACE2       106    /* NOR Flash : M26M128*/

extern  uint8_t DFU_DeviceDescriptor[DFU_SIZ_DEVICE_DESC];
extern  uint8_t DFU_ConfigDescriptor[DFU_SIZ_CONFIG_DESC];
extern  uint8_t DFU_StringLangId     [DFU_SIZ_STRING_LANGID];
extern  uint8_t DFU_StringVendor     [DFU_SIZ_STRING_VENDOR];
extern  uint8_t DFU_StringProduct    [DFU_SIZ_STRING_PRODUCT];
extern  uint8_t DFU_StringSerial     [DFU_SIZ_STRING_SERIAL];
extern  uint8_t DFU_StringInterface0 [DFU_SIZ_STRING_INTERFACE0];
extern  uint8_t DFU_StringInterface1 [DFU_SIZ_STRING_INTERFACE1];
extern  uint8_t DFU_StringInterface2_1 [DFU_SIZ_STRING_INTERFACE2];
extern  uint8_t DFU_StringInterface2_2 [DFU_SIZ_STRING_INTERFACE2];
extern  uint8_t DFU_StringInterface2_3 [DFU_SIZ_STRING_INTERFACE2];

#define bMaxPacketSize0             0x40     /* bMaxPacketSize0 = 64 bytes   */

#define wTransferSize               0x0800   /* wTransferSize   = 2048 bytes */
/* bMaxPacketSize0 <= wTransferSize <= 32kbytes */
#define wTransferSizeB0             0x00
#define wTransferSizeB1             0x08

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
/* External variables --------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /*__USB_DESC_H */

/************************ (C) COPYRIGHT HK Microelectronics *****END OF FILE****/

