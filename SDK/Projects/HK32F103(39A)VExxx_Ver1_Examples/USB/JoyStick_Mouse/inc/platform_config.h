/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  platform_config.h
* @brief:     Evaluation board specific configuration file.
* @author:    AE Team
*******************************************************************************/


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __PLATFORM_CONFIG_H
#define __PLATFORM_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "hk32f103xxxxa_conf.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/* Define if Low power mode is enabled; it allows entering the device into
   STOP mode following USB Suspend event, and wakes up after the USB wakeup
   event is received. */
//#define USB_LOW_PWR_MGMT_SUPPORT

/*Unique Devices IDs register set*/
#define         ID1          (0x1FFFF7E8)
#define         ID2          (0x1FFFF7EC)
#define         ID3          (0x1FFFF7F0)


#define USB_DISCONNECT                      GPIOD
#define USB_DISCONNECT_PIN                  GPIO_Pin_6
#define RCC_APB2Periph_GPIO_DISCONNECT      RCC_APB2Periph_GPIOD

#define RCC_APB2Periph_ALLGPIO              (RCC_APB2Periph_GPIOA | \
                                             RCC_APB2Periph_GPIOB | \
                                             RCC_APB2Periph_GPIOC | \
                                             RCC_APB2Periph_GPIOD | \
                                             RCC_APB2Periph_GPIOE )


/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

#ifdef __cplusplus
}
#endif

#endif /*__PLATFORM_CONFIG_H */

/************************ (C) COPYRIGHT HK Microchip *****END OF FILE****/

