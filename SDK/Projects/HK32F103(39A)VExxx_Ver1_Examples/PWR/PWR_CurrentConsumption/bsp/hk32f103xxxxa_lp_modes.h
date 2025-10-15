/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd 
* @filename:  hk32f103xxxxa_lp_modes.h
* @brief:     Header for hk32f103xxxxa_lp_modes.h file.                   
* @author:    AE Team   
*******************************************************************************/


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HK32AUTO39A3Xxx_LP_MODES_H
#define __HK32AUTO39A3Xxx_LP_MODES_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
#if !defined (SLEEP_MODE) && !defined (STOP_MODE) && !defined (STANDBY_MODE)\
 && !defined (STANDBY_RTC_MODE)
/* Uncomment the corresponding line to select the Low Power mode */
#define SLEEP_MODE
//#define STOP_MODE
//#define STANDBY_MODE
//#define STANDBY_RTC_MODE
#endif

#if !defined (SLEEP_MODE) && !defined (STOP_MODE) && !defined (STANDBY_MODE)\
 && !defined (STANDBY_RTC_MODE)
 #error "Please select first the target hk32f103xxxxa Low Power mode to be measured (in hk32f103xxxxa_lp_modes.h file)"
#endif

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void SleepMode_Measure(void);
void StopMode_Measure(void);
void StandbyMode_Measure(void);
void StandbyRTCMode_Measure(void);


#ifdef __cplusplus
}
#endif

#endif /* __HK32AUTO39A3Xxx_LP_MODES_H */
