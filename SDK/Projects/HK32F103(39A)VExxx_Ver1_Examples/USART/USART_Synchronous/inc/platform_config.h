/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  platform_config.h
* @brief:     Header for main.c file.
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
/* Exported macro ------------------------------------------------------------*/

#define USARTy                   USART1
#define USARTy_GPIO              GPIOA
#define USARTy_CLK               RCC_APB2Periph_USART1
#define USARTy_GPIO_CLK          RCC_APB2Periph_GPIOA

#define USARTy_RxPin             GPIO_Pin_10
#define USARTy_TxPin             GPIO_Pin_9
#define USARTy_ClkPin            GPIO_Pin_8
  
#define SPIy                     SPI1
#define SPIy_GPIO                GPIOA
#define SPIy_CLK                 RCC_APB2Periph_SPI1
#define SPIy_GPIO_CLK            RCC_APB2Periph_GPIOA

#define SPIy_SCKPin              GPIO_Pin_5
#define SPIy_MISOPin             GPIO_Pin_6
#define SPIy_MOSIPin             GPIO_Pin_7
/* Exported functions ------------------------------------------------------- */

#ifdef __cplusplus
}
#endif

#endif /*__PLATFORM_CONFIG_H */

