/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  usb_istr.h
* @brief:     This file includes the peripherals header files in the user application.
* @author:    AE Team
*******************************************************************************/


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USB_ISTR_H
#define __USB_ISTR_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "usb_conf.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

void USB_Istr(void);

/* function prototypes Automatically built defining related macros */

void EP1_IN_Callback(void);
void EP2_IN_Callback(void);
void EP3_IN_Callback(void);
void EP4_IN_Callback(void);
void EP5_IN_Callback(void);
void EP6_IN_Callback(void);
void EP7_IN_Callback(void);

void EP1_OUT_Callback(void);
void EP2_OUT_Callback(void);
void EP3_OUT_Callback(void);
void EP4_OUT_Callback(void);
void EP5_OUT_Callback(void);
void EP6_OUT_Callback(void);
void EP7_OUT_Callback(void);

#ifdef CTR_CALLBACK
void CTR_Callback(void);
#endif

#ifdef DOVR_CALLBACK
void DOVR_Callback(void);
#endif

#ifdef ERR_CALLBACK
void ERR_Callback(void);
#endif

#ifdef WKUP_CALLBACK
void WKUP_Callback(void);
#endif

#ifdef SUSP_CALLBACK
void SUSP_Callback(void);
#endif

#ifdef RESET_CALLBACK
void RESET_Callback(void);
#endif

#ifdef SOF_CALLBACK
void SOF_Callback(void);
#endif

#ifdef ESOF_CALLBACK
void ESOF_Callback(void);
#endif

#ifdef __cplusplus
}
#endif

#endif /*__USB_ISTR_H */

/************************ (C) COPYRIGHT HK Microelectronics *****END OF FILE****/
