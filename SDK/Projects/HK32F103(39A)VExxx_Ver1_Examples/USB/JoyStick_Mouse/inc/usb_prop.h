/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  usb_prop.h
* @brief:     All processing related to Joystick Mouse demo.
* @author:    AE Team
*******************************************************************************/


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USB_PROP_H
#define __USB_PROP_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "usb_lib.h"
/* Exported types ------------------------------------------------------------*/
typedef enum _HID_REQUESTS
{
    GET_REPORT = 1,
    GET_IDLE,
    GET_PROTOCOL,

    SET_REPORT = 9,
    SET_IDLE,
    SET_PROTOCOL
} HID_REQUESTS;

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void Joystick_init(void);
void Joystick_Reset(void);
void Joystick_SetConfiguration(void);
void Joystick_SetDeviceAddress (void);
void Joystick_Status_In (void);
void Joystick_Status_Out (void);
RESULT Joystick_Data_Setup(uint8_t);
RESULT Joystick_NoData_Setup(uint8_t);
RESULT Joystick_Get_Interface_Setting(uint8_t Interface, uint8_t AlternateSetting);
uint8_t *Joystick_GetDeviceDescriptor(uint16_t );
uint8_t *Joystick_GetConfigDescriptor(uint16_t);
uint8_t *Joystick_GetStringDescriptor(uint16_t);
RESULT Joystick_SetProtocol(void);
uint8_t *Joystick_GetProtocolValue(uint16_t Length);
RESULT Joystick_SetProtocol(void);
uint8_t *Joystick_GetReportDescriptor(uint16_t Length);
uint8_t *Joystick_GetHIDDescriptor(uint16_t Length);

/* Exported define -----------------------------------------------------------*/
#define Joystick_GetConfiguration          NOP_Process
//#define Joystick_SetConfiguration          NOP_Process
#define Joystick_GetInterface              NOP_Process
#define Joystick_SetInterface              NOP_Process
#define Joystick_GetStatus                 NOP_Process
#define Joystick_ClearFeature              NOP_Process
#define Joystick_SetEndPointFeature        NOP_Process
#define Joystick_SetDeviceFeature          NOP_Process
//#define Joystick_SetDeviceAddress          NOP_Process

#define REPORT_DESCRIPTOR                  0x22

#ifdef __cplusplus
}
#endif

#endif /*__USB_PROP_H */

/************************ (C) COPYRIGHT HK Microchip *****END OF FILE****/
