/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  hk32f103xxxxa_dbgmcu.h
* @brief:     This file contains all the functions prototypes for the DBGMCU firmware 
*             library
* @author:    AE Team
*******************************************************************************/


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HK32F103XXXXA_DBGMCU_H
#define __HK32F103XXXXA_DBGMCU_H

#ifdef __cplusplus
extern "C" {	
#endif

/* Includes ------------------------------------------------------------------*/
#include "hk32f103xxxxa_conf.h"

/** @addtogroup DBGMCU
  * @{
  */

/** @defgroup DBGMCU_Exported_Types DBGMCU_Exported_Types
  * @{
  */

/**
  * @}
  */

/** @defgroup DBGMCU_Exported_Constants DBGMCU_Exported_Constants
  * @{
  */

#define DBGMCU_SLEEP                 ((uint32_t)0x00000001)
#define DBGMCU_STOP                  ((uint32_t)0x00000002)
#define DBGMCU_STANDBY               ((uint32_t)0x00000004)
#define DBGMCU_IWDG_STOP             ((uint32_t)0x00000100)
#define DBGMCU_WWDG_STOP             ((uint32_t)0x00000200)
#define DBGMCU_TIM1_STOP             ((uint32_t)0x00000400)
#define DBGMCU_TIM2_STOP             ((uint32_t)0x00000800)
#define DBGMCU_TIM3_STOP             ((uint32_t)0x00001000)
#define DBGMCU_TIM4_STOP             ((uint32_t)0x00002000)
#define DBGMCU_CAN1_STOP             ((uint32_t)0x00004000)
#define DBGMCU_I2C1_SMBUS_TIMEOUT    ((uint32_t)0x00008000)
#define DBGMCU_I2C2_SMBUS_TIMEOUT    ((uint32_t)0x00010000)
#define DBGMCU_TIM8_STOP             ((uint32_t)0x00020000)
#define DBGMCU_TIM5_STOP             ((uint32_t)0x00040000)
#define DBGMCU_TIM6_STOP             ((uint32_t)0x00080000)
#define DBGMCU_TIM7_STOP             ((uint32_t)0x00100000)



#define IS_DBGMCU_PERIPH(PERIPH) ((((PERIPH) & 0x800000F8) == 0x00) && ((PERIPH) != 0x00))


#define TRACE_MODE_0                 0
#define TRACE_MODE_1                 DBGMCU_CR_TRACE_MODE_0
#define TRACE_MODE_2               	 DBGMCU_CR_TRACE_MODE_1
#define TRACE_MODE_3	             (DBGMCU_CR_TRACE_MODE_0|DBGMCU_CR_TRACE_MODE_1)

#define IS_TRACE_MODE(TRACE_MODE) ((TRACE_MODE == DBGMCU_CR_TRACE_MODE_0) | (TRACE_MODE == DBGMCU_CR_TRACE_MODE_1)\
																	|(TRACE_MODE == (DBGMCU_CR_TRACE_MODE_0|DBGMCU_CR_TRACE_MODE_1)))

/**
  * @}
  */

/** @defgroup DBGMCU_Exported_Macros DBGMCU_Exported_Macros
  * @{
  */

/**
  * @}
  */

/** @defgroup DBGMCU_Exported_Functions DBGMCU_Exported_Functions
  * @{
  */

uint32_t DBGMCU_GetREVID(void);
uint32_t DBGMCU_GetDEVID(void);
void DBGMCU_Config(uint32_t DBGMCU_Periph, FunctionalState NewState);
void DBGMCU_TraceCmd(FunctionalState NewState);
void DBGMCU_TraceModeConfig(uint32_t Trace_Mode);

#ifdef __cplusplus
}
#endif 

#endif /*__HK32F103XXXXA_DBGMCU_H */
/**
  * @}
  */

/**
  * @}
  */


/******************* (C) COPYRIGHT   HKMicroChip *****END OF FILE****/
