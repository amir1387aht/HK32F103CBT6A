/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  hk32f103xxxxa_cache.h
* @brief:     This file contains all the functions prototypes for the CACHE
*             firmware library.
* @author:    AE Team
*******************************************************************************/


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HK32F103XXXXA_CACHE_H
#define __HK32F103XXXXA_CACHE_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "hk32f103xxxxa_conf.h"

/** @addtogroup CACHE
  * @{
  */

/** @defgroup  CACHE_Exported_Types CACHE Exported Types
  * @{
  */
/** @defgroup CACHE_CTL_SERVE CACHE CTL SERVE
  * @{
  */


#define CACHE_CTL_None              0
#define CACHE_CTL_IBUS              CACHE_CTL_ICACHE_EN
#define CACHE_CTL_FSMC              CACHE_CTL_FSMC_CACHE_EN

#define IS_CACHE_CTL(CACHE_CTL) (((CACHE_CTL) == CACHE_CTL_None) || \
                                                                ((CACHE_CTL) == CACHE_CTL_IBUS) || \
                                                                ((CACHE_CTL) == CACHE_CTL_FSMC))
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

/*------------ Functions used for all HK32F103xxxxA devices -----*/
void CACHE_ReadHITCNTRegister(uint32_t *HIT_CNT);
void CACHE_ReadMISSCNTRegister(uint32_t *MISS_CNT);
void CACHE_ServeCTL(uint32_t CacheServeCtrl);
void CACHE_IVTCacheConfig(FunctionalState NewState);
void CACHE_ProgFlushConfig(FunctionalState NewState);
void CACHE_ForceFlushConfig(FunctionalState NewState);
void CACHE_HitMissCounterConfig(FunctionalState NewState);
void CACHE_HitMissCounterClear(FunctionalState NewState);

#ifdef __cplusplus
}
#endif

#endif /*__HK32F103XXXXA_CACHE_H */

