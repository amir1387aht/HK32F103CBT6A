/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  platform_config.h
* @brief:     This file contains all the functions prototypes for the AES firmware
*             library.
* @author:    AE Team
*******************************************************************************/


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __PLATFORM_CONFIG_H
#define __PLATFORM_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "hk32f103xxxxa_eval_sdio_sd.h"
#include "hk32f103xxxxa_conf.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/* Define if Low power mode is enabled; it allows entering the device into
   STOP mode following USB Suspend event, and wakes up after the USB wakeup
   event is received. */
//#define USB_LOW_PWR_MGMT_SUPPORT

/*Unique Devices IDs register set*/
#define         ID1          (0x1FFFF7E8)
#define         ID2          (0x1FFFF7EC)
#define         ID3          (0x1FFFF7F0)

#define RCC_AHBPeriph_ALLGPIO                 (RCC_AHBPeriph_GPIOA \
        | RCC_AHBPeriph_GPIOB \
        | RCC_AHBPeriph_GPIOC \
        | RCC_AHBPeriph_GPIOD \
        | RCC_AHBPeriph_GPIOE \
        | RCC_AHBPeriph_GPIOF )

#define USB_DISCONNECT                      GPIOB
#define USB_DISCONNECT_PIN                  GPIO_Pin_14
#define RCC_APB2Periph_GPIO_DISCONNECT      RCC_APB2Periph_GPIOB
#define ADC1_DR_Address                     ((uint32_t)0x4001244C)

#define RCC_APB2Periph_ALLGPIO              (RCC_APB2Periph_GPIOA \
        | RCC_APB2Periph_GPIOB \
        | RCC_APB2Periph_GPIOC \
        | RCC_APB2Periph_GPIOD \
        | RCC_APB2Periph_GPIOE )

#define RCC_APB2Periph_GPIO_IOAIN           RCC_APB2Periph_GPIOC
#define GPIO_IOAIN                          GPIOC
#define GPIO_IOAIN_PIN                      GPIO_Pin_4   /* PC.04 */
#define ADC_AIN_CHANNEL                     ADC_Channel_14


/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

#ifdef __cplusplus
}
#endif

#endif /*__PLATFORM_CONFIG_H */

/************************ (C) COPYRIGHT HK Microelectronics *****END OF FILE****/

