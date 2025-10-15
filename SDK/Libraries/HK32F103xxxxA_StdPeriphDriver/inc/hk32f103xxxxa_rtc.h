/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  hk32f103xxxxa_rtc.h
* @brief:     This file contains all the functions prototypes for the 
*             RTC firmware library
* @author:    AE Team
*******************************************************************************/


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HK32F103XXXXA_RTC_H
#define __HK32F103XXXXA_RTC_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "hk32f103xxxxa_conf.h"

/** @addtogroup RTC
  * @{
  */

/** @defgroup RTC_Exported_Constants RTC_Exported_Constants
  * @{
  */
/* Exported constants --------------------------------------------------------*/

/** @defgroup RTC_Interrupts_Definition RTC_Interrupts_Definition
  * @{
  */
#define RTC_IT_WUT           ((uint16_t)0x0100)  /*!< Wakeup Timer interrupt */
#define RTC_IT_OW            ((uint16_t)0x0004)  /*!< Overflow interrupt */
#define RTC_IT_ALR           ((uint16_t)0x0002)  /*!< Alarm interrupt */
#define RTC_IT_SEC           ((uint16_t)0x0001)  /*!< Second interrupt */
#define IS_RTC_IT(IT) ((((IT) & (uint16_t)0xFEF8) == 0x00) && ((IT) != 0x00))  /*!< RSM_MD,WUTIE,OWIE,ALRIE,SECIE mask*/
#define IS_RTC_GET_IT(IT) (((IT) == RTC_IT_WUT) ||((IT) == RTC_IT_OW) || ((IT) == RTC_IT_ALR) || \
                           ((IT) == RTC_IT_SEC))
/**
  * @}
  */

/** @defgroup RTC_Flags_Definition RTC_Flags_Definition
  * @{
  */
#define RTC_FLAG_WUTF        ((uint16_t)0x0100)  /*!< RTC wakeup timer over-reload flag */
#define RTC_FLAG_RTOFF       ((uint16_t)0x0020)  /*!< RTC Operation OFF flag */
#define RTC_FLAG_RSF         ((uint16_t)0x0008)  /*!< Registers Synchronized flag */
#define RTC_FLAG_OW          ((uint16_t)0x0004)  /*!< Overflow flag */
#define RTC_FLAG_ALR         ((uint16_t)0x0002)  /*!< Alarm flag */
#define RTC_FLAG_SEC         ((uint16_t)0x0001)  /*!< Second flag */
#define IS_RTC_CLEAR_FLAG(FLAG) ((((FLAG) & (uint16_t)0xFEF0) == 0x00) && ((FLAG) != 0x00))
#define IS_RTC_GET_FLAG(FLAG) (((FLAG) == RTC_FLAG_WUTF) ||((FLAG) == RTC_FLAG_RTOFF) || ((FLAG) == RTC_FLAG_RSF) || \
                               ((FLAG) == RTC_FLAG_OW) || ((FLAG) == RTC_FLAG_ALR) || \
                               ((FLAG) == RTC_FLAG_SEC))
/**
  * @}
  */

/** @defgroup RTC_PRESCALER_RANGE RTC_PRESCALER_RANGE
  * @{
  */
#define IS_RTC_PRESCALER(PRESCALER) ((PRESCALER) <= 0xFFFFF)  /*!< range of prescaler value */
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

/* Initialization and Configuration functions *********************************/
void RTC_EnterConfigMode(void);
void RTC_ExitConfigMode(void);
void RTC_SetCounter(uint32_t CounterValue);
uint32_t RTC_GetCounter(void);
void RTC_SetPrescaler(uint32_t PrescalerValue);
uint32_t RTC_GetDivider(void);
void RTC_SetAlarm(uint32_t AlarmValue);
void RTC_SetWakeupTimer(uint16_t ReloadValue);
void RTC_WaitForLastTask(void);
void RTC_WaitForSynchro(void);
void RTC_RSMReloadStrategy(FunctionalState NewState);

/* Interrupts and flags management functions **********************************/
void RTC_ITConfig(uint16_t RTC_IT, FunctionalState NewState);
ITStatus RTC_GetITStatus(uint16_t RTC_IT);
void RTC_ClearITPendingBit(uint16_t RTC_IT);
FlagStatus RTC_GetFlagStatus(uint16_t RTC_FLAG);
void RTC_ClearFlag(uint16_t RTC_FLAG);

#ifdef __cplusplus
}
#endif

#endif /*__HK32F103XXXXA_RTC_H */


