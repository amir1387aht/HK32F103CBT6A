/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  usb_pwr.h
* @brief:     Connection/disconnection & power management header.
* @author:    AE Team
*******************************************************************************/


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USB_PWR_H
#define __USB_PWR_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
typedef enum _RESUME_STATE
{
    RESUME_EXTERNAL,
    RESUME_INTERNAL,
    RESUME_LATER,
    RESUME_WAIT,
    RESUME_START,
    RESUME_ON,
    RESUME_OFF,
    RESUME_ESOF
} RESUME_STATE;

typedef enum _DEVICE_STATE
{
    UNCONNECTED,
    ATTACHED,
    POWERED,
    SUSPENDED,
    ADDRESSED,
    CONFIGURED
} DEVICE_STATE;

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void Suspend(void);
void Resume_Init(void);
void Resume(RESUME_STATE eResumeSetVal);
RESULT PowerOn(void);
RESULT PowerOff(void);

/* External variables --------------------------------------------------------*/
extern  __IO uint32_t bDeviceState; /* USB device status */
extern __IO bool fSuspendEnabled;  /* true when suspend is possible */

#ifdef __cplusplus
}
#endif

#endif  /*__USB_PWR_H */

/************************ (C) COPYRIGHT HK Microelectronics *****END OF FILE****/
