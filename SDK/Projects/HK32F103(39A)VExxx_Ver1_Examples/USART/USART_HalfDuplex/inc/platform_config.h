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

#define USARTy                   USART2
#define USARTy_GPIO              GPIOD
#define USARTy_CLK               RCC_APB1Periph_USART2
#define USARTy_GPIO_CLK          RCC_APB2Periph_GPIOD
#define USARTy_TxPin             GPIO_Pin_5
#define USARTy_RxPin             GPIO_Pin_6  

#define USARTz                   USART3
#define USARTz_GPIO              GPIOC
#define USARTz_CLK               RCC_APB1Periph_USART3
#define USARTz_GPIO_CLK          RCC_APB2Periph_GPIOC
#define USARTz_TxPin             GPIO_Pin_10
#define USARTz_RxPin             GPIO_Pin_11 

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

#ifdef __cplusplus
}
#endif

#endif /*__PLATFORM_CONFIG_H */


