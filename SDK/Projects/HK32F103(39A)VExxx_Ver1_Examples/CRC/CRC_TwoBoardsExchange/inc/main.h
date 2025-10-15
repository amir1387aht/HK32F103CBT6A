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
/* Uncomment the line below if you will use the TRANSMITTER mode */
#define MODE_TRANSMITTER  
/* Uncomment the line below if you will use the RECIVER mode */
//#define MODE_RECEIVER

#define countof(a)                       (sizeof(a) / sizeof(*(a)))
#define TXBUFFERSIZE                     (countof(TxBuffer) - 1)
#define RXBUFFERSIZE                     TXBUFFERSIZE + 1
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */


#ifdef __cplusplus
}
#endif

#endif /*__MAIN_H */

