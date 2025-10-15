/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  hk32f103xxxxa_eval_i2c_ee.h
* @brief:     This file contains all the functions prototypes for the hk32f103xxxxa_eval_i2c_ee
*             firmware driver.
* @author:    AE Team
*******************************************************************************/


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HK32F103xxxxA_EVAL_I2C_EE_H
#define __HK32F103xxxxA_EVAL_I2C_EE_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "hk32f103xxxxa_conf.h"
#include "hk32f103xxxxa_eval.h"

#define sEE_HW_ADDRESS                   0xA0   
#define I2C_SPEED                        300000
#define I2C_SLAVE_ADDRESS7               0xA8
#define sEE_PAGESIZE                     8

#define sEE_FLAG_TIMEOUT                ((uint32_t)0x1000)
#define sEE_LONG_TIMEOUT                ((uint32_t)(10 * sEE_FLAG_TIMEOUT))

/* Maximum number of trials for sEE_WaitEepromStandbyState() function */
#define sEE_MAX_TRIALS_NUMBER           150

/* Defintions for the state of the DMA transfer */
#define sEE_STATE_READY                 0
#define sEE_STATE_BUSY                  1
#define sEE_STATE_ERROR                 2
#define sEE_OK                          0
#define sEE_FAIL                        1


void     sEE_DeInit(void);
void     sEE_Init(void);
uint32_t sEE_ReadBuffer(uint8_t* pBuffer, uint16_t ReadAddr, uint16_t* NumByteToRead);
uint32_t sEE_WritePage(uint8_t* pBuffer, uint16_t WriteAddr, uint8_t* NumByteToWrite);
void     sEE_WriteBuffer(uint8_t* pBuffer, uint16_t WriteAddr, uint16_t NumByteToWrite);
uint32_t sEE_WaitEepromStandbyState(void);
uint32_t sEE_TIMEOUT_UserCallback(void);
void sEE_EnterCriticalSection_UserCallback(void);
void sEE_ExitCriticalSection_UserCallback(void);

#ifdef __cplusplus
}
#endif

#endif /*__HK32F103xxxxA_EVAL_I2C_EE_H */

