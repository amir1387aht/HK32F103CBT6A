/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  hk32f103xxxxa_eval_i2c_tsensor.h
* @brief:     This file contains all the functions prototypes for the hk32f103xxxxa_eval_i2c_tsensor
*             firmware driver.
* @author:    AE Team
*******************************************************************************/


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HK32F103xxxxA_EVAL_I2C_TSENSOR_H
#define __HK32F103xxxxA_EVAL_I2C_TSENSOR_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "hk32f103xxxxa_conf.h"
#include "hk32f103xxxxa_eval.h"

/**
 * @brief  IOE DMA Direction
 */
typedef enum
{
    LM75_DMA_TX = 0,
    LM75_DMA_RX = 1
} LM75_DMADirection_TypeDef;

/**
  * @brief  TSENSOR Status
  */
typedef enum
{
    LM75_OK = 0,
    LM75_FAIL
} LM75_Status_TypDef;


/* Maximum Timeout values for flags and events waiting loops. These timeouts are
   not based on accurate values, they just guarantee that the application will
   not remain stuck if the I2C communication is corrupted.
   You may modify these timeout values depending on CPU frequency and application
   conditions (interrupts routines ...). */
#define LM75_FLAG_TIMEOUT         ((uint32_t)0x1000)
#define LM75_LONG_TIMEOUT         ((uint32_t)(10 * LM75_FLAG_TIMEOUT))

/**
  * @brief  Block Size
  */
#define LM75_REG_TEMP       0x00  /*!< Temperature Register of LM75 */
#define LM75_REG_CONF       0x01  /*!< Configuration Register of LM75 */
#define LM75_REG_THYS       0x02  /*!< Temperature Register of LM75 */
#define LM75_REG_TOS        0x03  /*!< Over-temp Shutdown threshold Register of LM75 */
#define I2C_TIMEOUT         ((uint32_t)0x3FFFF) /*!< I2C Time out */
#define LM75_ADDR           0x90   /*!< LM75 address */
#define LM75_I2C_SPEED      100000 /*!< I2C Speed */


void LM75_DeInit(void);
void LM75_Init(void);
ErrorStatus LM75_GetStatus(void);
uint16_t LM75_ReadTemp(void);
uint8_t LM75_WriteReg(uint8_t RegName, uint16_t RegValue);
uint8_t LM75_WriteConfReg(uint8_t RegValue);

#define LM75_TIMEOUT_UserCallback()  LM75_FAIL

#ifdef __cplusplus
}
#endif

#endif /*__HK32F103xxxxA_EVAL_I2C_TSENSOR_H */

