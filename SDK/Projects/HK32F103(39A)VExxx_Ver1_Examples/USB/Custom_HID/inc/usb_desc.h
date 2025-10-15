/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  usb_desc.h
* @brief:     Descriptor Header for Custom HID Demo.
* @author:    AE Team
*******************************************************************************/


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USB_DESC_H
#define __USB_DESC_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported define -----------------------------------------------------------*/
#define USB_DEVICE_DESCRIPTOR_TYPE              0x01
#define USB_CONFIGURATION_DESCRIPTOR_TYPE       0x02
#define USB_STRING_DESCRIPTOR_TYPE              0x03
#define USB_INTERFACE_DESCRIPTOR_TYPE           0x04
#define USB_ENDPOINT_DESCRIPTOR_TYPE            0x05

#define HID_DESCRIPTOR_TYPE                     0x21
#define CUSTOMHID_SIZ_HID_DESC                  0x09
#define CUSTOMHID_OFF_HID_DESC                  0x12

#define CUSTOMHID_SIZ_DEVICE_DESC               18
#define CUSTOMHID_SIZ_CONFIG_DESC               41
#define CUSTOMHID_SIZ_REPORT_DESC               33
#define CUSTOMHID_SIZ_STRING_LANGID             4
#define CUSTOMHID_SIZ_STRING_VENDOR             38
#define CUSTOMHID_SIZ_STRING_PRODUCT            30
#define CUSTOMHID_SIZ_STRING_SERIAL             26

#define STANDARD_ENDPOINT_DESC_SIZE             0x09

#define REPORT_COUNT                                                        64

/* Exported functions ------------------------------------------------------- */
extern const uint8_t CustomHID_DeviceDescriptor[CUSTOMHID_SIZ_DEVICE_DESC];
extern const uint8_t CustomHID_ConfigDescriptor[CUSTOMHID_SIZ_CONFIG_DESC];
extern const uint8_t CustomHID_ReportDescriptor[CUSTOMHID_SIZ_REPORT_DESC];
extern const uint8_t CustomHID_StringLangID[CUSTOMHID_SIZ_STRING_LANGID];
extern const uint8_t CustomHID_StringVendor[CUSTOMHID_SIZ_STRING_VENDOR];
extern const uint8_t CustomHID_StringProduct[CUSTOMHID_SIZ_STRING_PRODUCT];
extern uint8_t CustomHID_StringSerial[CUSTOMHID_SIZ_STRING_SERIAL];

#ifdef __cplusplus
}
#endif

#endif /*__USB_DESC_H */

/************************ (C) COPYRIGHT HK Microelectronics *****END OF FILE****/
