/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  hk32f103xxxxa_pwr.h
* @brief:     PWR initialization and configuration
* @author:    AE Team
*******************************************************************************/


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HK32F103XXXXA_PWR_H
#define __HK32F103XXXXA_PWR_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "hk32f103xxxxa_conf.h"

#define IS_WAKEUPPIN_STATE(STATE) (((STATE) == FALLING_EDGE) || ((STATE) == RISING_EDGE))
#define IS_WAKEUP_PIN(PIN) (((PIN) == 2) || ((PIN) == 1) || ((PIN) == 0))

/** @defgroup PWR PWR
  * @brief PWR driver modules
  * @{
  */



/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/

/** @defgroup PWR_Exported_Constants PWR_Exported_Constants
  * @{
  */

/** @defgroup PWR_PVD_detection_level  PWR_PVD_detection_level
  * @{
  */ 

#define  PWR_PVDLevel_0                     ((uint16_t)0x0000)     /*!< PVD level 0 */
#define  PWR_PVDLevel_1                     ((uint16_t)0x0001)     /*!< PVD level 1 */
#define  PWR_PVDLevel_2                     ((uint16_t)0x0002)     /*!< PVD level 2 */
#define  PWR_PVDLevel_3                     ((uint16_t)0x0003)     /*!< PVD level 3 */
#define  PWR_PVDLevel_4                     ((uint16_t)0x0004)     /*!< PVD level 4 */
#define  PWR_PVDLevel_5                     ((uint16_t)0x0005)     /*!< PVD level 5 */
#define  PWR_PVDLevel_6                     ((uint16_t)0x0006)     /*!< PVD level 6 */
#define  PWR_PVDLevel_7                     ((uint16_t)0x0007)     /*!< PVD level 7 */

#define IS_PWR_PVD_LEVEL(LEVEL) (((LEVEL) == PWR_PVDLevel_0) || ((LEVEL) == PWR_PVDLevel_1)|| \
                                 ((LEVEL) == PWR_PVDLevel_2) || ((LEVEL) == PWR_PVDLevel_3)|| \
                                 ((LEVEL) == PWR_PVDLevel_4) || ((LEVEL) == PWR_PVDLevel_5)|| \
                                 ((LEVEL) == PWR_PVDLevel_6) || ((LEVEL) == PWR_PVDLevel_7))


#define PVD_MODE_IT               ((uint32_t)0x00010000U)
#define PVD_MODE_EVT              ((uint32_t)0x00020000U)

#define PVD_RISING_EDGE           ((uint32_t)0x00000001U)
#define PVD_FALLING_EDGE          ((uint32_t)0x00000002U)
#define PVD_RISING_FALLING        ((uint32_t)0x00000003U)
/**
  * @}
  */

/** @defgroup PWR_WakeUp_Pins PWR_WakeUp_Pins
  * @{
  */
#define PWR_WakeUpPin_1                 PWR_CSR_EWUP1
#define PWR_WakeUpPin_2                 PWR_CSR_EWUP2
#define PWR_WakeUpPin_3                 PWR_CSR_EWUP3
#define IS_PWR_WAKEUP_PIN(PIN) (((PIN) == PWR_WakeUpPin_1) || ((PIN) == PWR_WakeUpPin_2) || ((PIN) == PWR_WakeUpPin_3))

/**
  * @}
  */

 
/** @defgroup PWR_Regulator_state_is_Sleep_STOP_mode PWR_Regulator_state_is_Sleep_STOP_mode
  * @{
  */
#define PWR_Regulator_ON                0
#define PWR_Regulator_LowPower          ((uint32_t)0x00000001)
#define IS_PWR_REGULATOR(REGULATOR) (((REGULATOR) == PWR_Regulator_ON) || \
                                     ((REGULATOR) == PWR_Regulator_LowPower))

/**
  * @}
  */

/** @defgroup PWR_SLEEP_mode_entry PWR_SLEEP_mode_entry
  * @{
  */
#define PWR_SLEEPEntry_WFI              ((uint8_t)0x01)
#define PWR_SLEEPEntry_WFE              ((uint8_t)0x02)
#define IS_PWR_SLEEP_ENTRY(ENTRY) (((ENTRY) == PWR_SLEEPEntry_WFI) || ((ENTRY) == PWR_SLEEPEntry_WFE))

/**
  * @}
  */



/** @defgroup PWR_STOP_mode_entry PWR_STOP_mode_entry
  * @{
  */
#define PWR_STOPEntry_WFI               ((uint8_t)0x01)
#define PWR_STOPEntry_WFE               ((uint8_t)0x02)
#define PWR_STOPEntry_SLEEPONEXIT       ((uint8_t)0x03)
#define IS_PWR_STOP_ENTRY(ENTRY) (((ENTRY) == PWR_STOPEntry_WFI) || ((ENTRY) == PWR_STOPEntry_WFE) ||\
                                  ((ENTRY) == PWR_STOPEntry_SLEEPONEXIT))
/**
  * @}
  */	
	
/** @defgroup PWR_STANDBY_mode_entry PWR_STANDBY_mode_entry
  * @{
  */
#define PWR_STANDBYEntry_WFI               ((uint8_t)0x01)
#define PWR_STANDBYEntry_WFE               ((uint8_t)0x02)
#define PWR_STANDBYEntry_SLEEPONEXIT       ((uint8_t)0x03)
#define IS_PWR_STANDBY_ENTRY(ENTRY) (((ENTRY) == PWR_STANDBYEntry_WFI) || ((ENTRY) == PWR_STANDBYEntry_WFE) ||\
                                  ((ENTRY) == PWR_STANDBYEntry_SLEEPONEXIT))



/**
  * @}
  */

/** @defgroup PWR_Flag PWR_Flag
  * @{
  */

#define PWR_FLAG_WU                     PWR_CSR_WUF
#define PWR_FLAG_SB                     PWR_CSR_SBF
#define PWR_FLAG_PVDO                   PWR_CSR_PVDO
#define PWR_FLAG_LDORDY                 PWR_CSR_LDORDY
#define PWR_FLAG_EWUP1                  PWR_CSR_EWUP1
#define PWR_FLAG_EWUP2                  PWR_CSR_EWUP2
#define PWR_FLAG_EWUP3                  PWR_CSR_EWUP3 

#define IS_PWR_GET_FLAG(FLAG) (((FLAG) == PWR_FLAG_WU) || ((FLAG) == PWR_FLAG_SB) || \
                               ((FLAG) == PWR_FLAG_PVDO) || ((FLAG) == PWR_CSR_LDORDY) || \
                               ((FLAG) == PWR_CSR_EWUP1) || ((FLAG) == PWR_CSR_EWUP2) || \
								((FLAG) == PWR_CSR_EWUP3)) 

#define IS_PWR_CLEAR_FLAG(FLAG) (((FLAG) == PWR_FLAG_WU) || ((FLAG) == PWR_FLAG_SB))

/**
  * @}
  */	 	
  
  /** @defgroup PWR_SHUT_GET_FLAG PWR_SHUT_GET_FLAG
  * @{
  */
#define PWR_SHUT_FLAG_SHUTF                 PWR_CSR2_SHUTF
#define PWR_SHUT_FLAG_SWUF                  PWR_CSR2_SWUF 
#define IS_PWR_GET_SHUT_FLAG(FLAG) (((FLAG) == PWR_SHUT_FLAG_SHUTF) || ((FLAG) == PWR_SHUT_FLAG_SWUF))
 /**
  * @}
  */
  
/** @defgroup PWR_SHUT_CLEAR_FLAG PWR_SHUT_CLEAR_FLAG
  * @{
  */
#define PWR_SHUT_FLAG_CSHUTF                 PWR_CSR2_CSHUTF
#define PWR_SHUT_FLAG_CSWUF                  PWR_CSR2_CSWUF 
#define IS_PWR_CLEAR_SHUT_FLAG(FLAG) (((FLAG) == PWR_SHUT_FLAG_SHUTF) || ((FLAG) == PWR_SHUT_FLAG_SWUF))
/**
  * @}
  */



typedef enum {RISING_EDGE = 0, FALLING_EDGE = 1} WakeupPinPolarity;

typedef enum {WAKE_UP_PIN1 = 0, WAKE_UP_PIN2 = 1, WAKE_UP_PIN3 = 2} WakeupPinSel;

/**
  * @}
  */

/**
  * @}
  */


/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

/* Function used to set the PWR configuration to the default reset state ******/
void PWR_DeInit(void);

/* Backup Domain Access function **********************************************/
void PWR_BackupAccessCmd(FunctionalState NewState);

/* PVD configuration functions ************************************************/
void PWR_PVDLevelConfig(uint32_t PWR_PVDLevel, uint32_t PWR_PVDMode, uint32_t PWR_PVDEdge);
void PWR_PVDCmd(FunctionalState NewState);

/* WakeUp pins configuration functions ****************************************/
void PWR_WakeUpPinCmd(uint32_t PWR_WakeUpPin, FunctionalState NewState);

/* Low Power modes configuration functions ************************************/
void PWR_EnterSleepMode(uint8_t PWR_SLEEPEntry);
void PWR_EnterSTOPMode(uint32_t PWR_Regulator, uint8_t PWR_STOPEntry);
void PWR_EnterSTANDBYMode(uint8_t PWR_STANDBYEntry);

/* Flags management functions *************************************************/
FlagStatus PWR_GetFlagStatus(uint32_t PWR_FLAG);
 
void PWR_ClearFlag(uint32_t PWR_FLAG);
void PWR_WakeupPinPolarityConfig(uint32_t WakeUpPin, uint32_t Edge);

#ifdef __cplusplus
}
#endif

#endif /*__HK32F103XXXXA_PWR_H */



