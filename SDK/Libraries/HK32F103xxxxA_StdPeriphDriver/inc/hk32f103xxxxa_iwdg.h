/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd 
* @filename:  hk32f103xxxxa_iwdg.h
* @brief:     hk32f103xxxxa_iwdg configuration file.
*             The file is the unique include file that the application programmer
*             is using in the C source code.it is a patch file.
* @author:    AE Team 
*******************************************************************************/


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HK32F103XXXXA_IWDG_H
#define __HK32F103XXXXA_IWDG_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "hk32f103xxxxa_conf.h"
/** @addtogroup IWDG
  * @{
  */

/** @defgroup IWDG_KR IWDG_KR
  * @{
  */
#define IWDG_WriteAccess_Enable     ((uint16_t)0x5555)
#define IWDG_WriteAccess_Disable    ((uint16_t)0x0000)
#define IS_IWDG_WRITE_ACCESS(ACCESS) (((ACCESS) == IWDG_WriteAccess_Enable) || \
                                      ((ACCESS) == IWDG_WriteAccess_Disable))
/**
  * @}
  */

/** @defgroup IWDG_PR IWDG_PR
  * @{
  */
#define IWDG_Prescaler_4            ((uint8_t)0x00)
#define IWDG_Prescaler_8            ((uint8_t)0x01)
#define IWDG_Prescaler_16           ((uint8_t)0x02)
#define IWDG_Prescaler_32           ((uint8_t)0x03)
#define IWDG_Prescaler_64           ((uint8_t)0x04)
#define IWDG_Prescaler_128          ((uint8_t)0x05)
#define IWDG_Prescaler_256          ((uint8_t)0x06)
#define IS_IWDG_PRESCALER(PRESCALER) (((PRESCALER) == IWDG_Prescaler_4)  || \
                                      ((PRESCALER) == IWDG_Prescaler_8)  || \
                                      ((PRESCALER) == IWDG_Prescaler_16) || \
                                      ((PRESCALER) == IWDG_Prescaler_32) || \
                                      ((PRESCALER) == IWDG_Prescaler_64) || \
                                      ((PRESCALER) == IWDG_Prescaler_128)|| \
                                      ((PRESCALER) == IWDG_Prescaler_256))
/**
  * @}
  */

/** @defgroup IWDG_SR IWDG_SR
  * @{
  */
#define IWDG_FLAG_PVU               ((uint16_t)0x0001)
#define IWDG_FLAG_RVU               ((uint16_t)0x0002)
#define IWDG_FLAG_WVU               ((uint16_t)0x0004)
#define IS_IWDG_FLAG(FLAG) (((FLAG) == IWDG_FLAG_PVU) || ((FLAG) == IWDG_FLAG_RVU)  || \
                            ((FLAG) == IWDG_FLAG_WVU))
/**
  * @}
  */

/** @defgroup IWDG_RLR IWDG_RLR
 * @{
 */
#define IS_IWDG_RELOAD(RELOAD) ((RELOAD) <= 0xFFF)
/**
  * @}
  */

/** @defgroup IWDG_WINR IWDG_WINR
 * @{
 */
#define IS_IWDG_WINDOW_VALUE(VALUE) ((VALUE) <= 0xFFF)
/**
  * @}
  */

void IWDG_WriteAccessCmd(uint16_t IWDG_WriteAccess);
void IWDG_SetPrescaler(uint8_t IWDG_Prescaler);
void IWDG_SetReload(uint16_t Reload);
void IWDG_ReloadCounter(void);
void IWDG_SetWindowValue(uint16_t WindowValue);
void IWDG_Enable(void);
FlagStatus IWDG_GetFlagStatus(uint16_t IWDG_FLAG);

#ifdef __cplusplus
}
#endif

#endif /*__HK32F103XXXXA_IWDG_H */

/**
  * @}
  */
