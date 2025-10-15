/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  hk32f103xxxxa_cache.c
* @brief:     This file provides all the CACHE firmware functions.
* @author:    AE Team
* @version:   V1.0.0/2023-12-15
*             1.Initial version
* @log:
*******************************************************************************/


/* Includes ------------------------------------------------------------------*/
#include "hk32f103xxxxa_cache.h"
/** @addtogroup HK32F103xxxxA_StdPeriph_Driver
  * @{
  */

/** @defgroup CACHE CACHE
  * @brief CACHE driver modules
  * @{
    @verbatim
=====================================================================
                 ##### How to use this driver #####
=====================================================================
  [..] This driver provides functions to configure and program the CACHE
             of all hk32f103xxxxa Serial devices
      (#)   The control register can be configured to determine which of the
                below three instruction fetching operations to cache,and Only one
                type of access can be cached at a time.
                     (++) ICACHE.
                     (++) FSMC.
    (#) CACHE configuration functions.
                     (++) CACHE_IVTCacheConfig: Enables or disables the Interrrupt
                                vector table cache function.
                     (++) CACHE_ProgFlushConfig: Clear Cache content when Flash on
                                chip is programmed or erased.
                     (++) CACHE_ForceFlushConfig: Force to Clear Cache content immediately.
                     (++) CACHE_HitMissCounterConfig: Enable or Disable Cache hit/miss
                                counter to continue counting.
                     (++) CACHE_HitMissCounterClear: Clear Cache hit/miss counter.
    (#) CACHE HIT-counter/ MISS-Counter functions.
                     (++) CACHE_ReadHITCNTRegister: Reads data from HIT_CNT_H and
                                HIT_CNT_L Register.
                     (++) CACHE_ReadMISSCNTRegister: Reads data from MISS_CNT_H and
                                MISS_CNT_L Register..
    @endverbatim
  *
  ******************************************************************************
  */

/** @defgroup CACHE_Private_TypesDefinitions CACHE Private TypesDefinitions
  * @{
  */

/* ------------ Cache Control registers bit address in the alias region --------------- */
#define CACHE_OFFSET     (CACHE_BASE - PERIPH_BASE)

/* --- Cache CTL Register ---*/
#define CACHE_CTL_OFFSET            (CACHE_OFFSET)
#define IV_CACHE_EN_BitNumber       0x08
#define PE_FLUSH_EN_BitNumber       0x0A
#define FORCE_FLUSH_BitNumber       0x0B
#define PR_CNT_EN_BitNumber         0x0C
#define PR_CNT_CLR_BitNumber        0x0D
#define CACHECTL_IV_CACHE_EN_BB   (PERIPH_BB_BASE + (CACHE_CTL_OFFSET * 32) + (IV_CACHE_EN_BitNumber * 4))
#define CACHECTL_PE_FLUSH_EN_BB   (PERIPH_BB_BASE + (CACHE_CTL_OFFSET * 32) + (PE_FLUSH_EN_BitNumber * 4))
#define CACHECTL_FORCE_FLUSH_BB   (PERIPH_BB_BASE + (CACHE_CTL_OFFSET * 32) + (FORCE_FLUSH_BitNumber * 4))
#define CACHECTL_PR_CNT_EN_BB     (PERIPH_BB_BASE + (CACHE_CTL_OFFSET * 32) + (PR_CNT_EN_BitNumber * 4))
#define CACHECTL_PR_CNT_CLR_BB    (PERIPH_BB_BASE + (CACHE_CTL_OFFSET * 32) + (PR_CNT_CLR_BitNumber * 4))

#define CACHE_CTL_MSK       0x00000007

/**
  * @}
  */


/** @defgroup CACHE_Private_Functions CACHE Private Functions
  * @{
  */

/**
  * @brief  Enables or disables the Interrrupt vector table cache function.
  * @param  NewState: new state of the Interrrupt vector table.
  *         This parameter can be: ENABLE: IV-TABLE can cached by CAHCE
  *         DISABLE: IV-TABLE can not cached by CAHCE
  * @retval None
  */
void CACHE_IVTCacheConfig(FunctionalState NewState)
{
    *(__IO uint32_t *) CACHECTL_IV_CACHE_EN_BB = (uint32_t)NewState;
}

/**
  * @brief  Clear Cache content when Flash on chip is programmed or erased.
  * @param  NewState: new state of the Clear Cache content.
  *         This parameter can be:
  *         ENABLE: Clear CACHE when when Flash on chip is programmed or erased
  *         DISABLE: DO not Clear CACHE when when Flash on chip is programmed or erased
  * @retval None
  */
void CACHE_ProgFlushConfig(FunctionalState NewState)
{
    *(__IO uint32_t *) CACHECTL_PE_FLUSH_EN_BB = (uint32_t)NewState;
}

/**
  * @brief  Force to Clear Cache content immediately.
  * @param  NewState: This parameter can be: ENABLE or DISABLE
  *         This parameter can be: ENABLE: Force to Clear Cache content immediately.
  *         DISABLE: No action
  * @retval None
  */
void CACHE_ForceFlushConfig(FunctionalState NewState)
{
    *(__IO uint32_t *) CACHECTL_FORCE_FLUSH_BB = (uint32_t)NewState;
}

/**
  * @brief  Enable or Disable Cache hit/miss counter to continue counting.
  * @param  NewState: This parameter can be: ENABLE or DISABLE
  *         This parameter can be: ENABLE: Hit and miss counter start working;
  *         DISABLE: Hit and miss counter stop counting;
  * @retval None
  */
void CACHE_HitMissCounterConfig(FunctionalState NewState)
{
    *(__IO uint32_t *) CACHECTL_PR_CNT_EN_BB = (uint32_t)NewState;
}

/**
  * @brief  Clear Cache hit/miss counter.
  * @param  NewState: This parameter can be: ENABLE or DISABLE
  *         This parameter can be: ENABLE: Clear Hit and miss counter;
  *         DISABLE: No Action;
  * @retval None
  */
void CACHE_HitMissCounterClear(FunctionalState NewState)
{
    *(__IO uint32_t *) CACHECTL_PR_CNT_CLR_BB = (uint32_t)NewState;
}

/**
  * @brief  Reads data from HIT_CNT_H and HIT_CNT_L Register.
  * @param  HIT_CNT: specifies the Data pointer.
  *         HIT_CNT[0] is HIT_CNT_L, HIT_CNT[1] is HIT_CNT_H
  * @retval None
  */
void CACHE_ReadHITCNTRegister(uint32_t *HIT_CNT)
{
    HIT_CNT[0] = CACHE->HIT_CNT_L;
    HIT_CNT[1] = CACHE->HIT_CNT_H;
}

/**
  * @brief  Reads data from MISS_CNT_H and MISS_CNT_L Register.
  * @param  MISS_CNT: specifies the Data pointer.
  *         MISS_CNT[0] is MISS_CNT_L, MISS_CNT[1] is MISS_CNT_H
  * @retval None
  */
void CACHE_ReadMISSCNTRegister(uint32_t *MISS_CNT)
{
    MISS_CNT[0] = CACHE->MISS_CNT_L;
    MISS_CNT[1] = CACHE->MISS_CNT_H;
}

/**
  * @brief  Config Cache function to serve for I-Bus or FSMC.
  * @param  CacheServeCtrl: Config Cache function.
  *         This parameter can be any combination of the following values:
  *         CACHE_CTL_None: Disable Cache, don't serve for I-Bus or FSMC.
  *         CACHE_CTL_IBUS: Enable Cache and Serve for I-bus.
  *         CACHE_CTL_FSMC: Enable Cache and Serve for FSMC.
  * @retval None
  */
void CACHE_ServeCTL(uint32_t CacheServeCtrl)
{
    /* Check the parameters */
    assert_param(IS_CACHE_CTL(CacheServeCtrl));
    CACHE->CTL &= (~CACHE_CTL_MSK);
    CACHE->CTL |= CacheServeCtrl;
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

