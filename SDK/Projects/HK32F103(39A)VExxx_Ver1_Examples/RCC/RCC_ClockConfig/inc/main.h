/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  main.h
* @brief:     Header for main.c file.
* @author:    AE Team
*******************************************************************************/


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/
#include "hk32f103xxxxa_conf.h"
#include "hk32f103xxxxa_eval.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
#define SYSCLK_HSE
//#define SYSCLK_FREQ_24MHz
//#define SYSCLK_FREQ_36MHz
//#define SYSCLK_FREQ_48MHz
//#define SYSCLK_FREQ_56MHz
//#define SYSCLK_FREQ_72MHz

#define DELAY_COUNT                        0x3FFFF
#define RCC_CFGR_PLLSRC_HSE                ((uint32_t)0x00010000) 
#define RCC_CFGR_PLLXTPRE_HSE_Div2         ((uint32_t)0x00020000) 
#define RCC_CFGR_PLLMULL9                  ((uint32_t)0x001C0000)
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */


#ifdef __cplusplus
}
#endif

#endif /*__MAIN_H */

