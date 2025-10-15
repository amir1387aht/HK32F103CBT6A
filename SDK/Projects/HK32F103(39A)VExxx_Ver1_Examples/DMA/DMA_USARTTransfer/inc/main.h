/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  main.h
* @brief:     This file contains all the functions prototypes for the main.c file.
*             library.
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

/* Exported typedef ----------------------------------------------------------*/
#define countof(a)   (sizeof(a) / sizeof(*(a)))
typedef enum {FAILED = 0, PASSED = !FAILED} TestStatus;

/* Exported define -----------------------------------------------------------*/

/* Communication boards USART Interface */
#define USART1_DR_Address     0x40013804

#define USART2_DR_Address     0x40004404

#define TXBUFFERSIZE          (countof(TxBuffer1) - 1)
#define RXBUFFERSIZE          TXBUFFERSIZE

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

#ifdef __cplusplus
}
#endif

#endif /*__MAIN_H */

