/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  hk32f103xxxxa_flash.h
* @brief:     This file contains all the functions prototypes for the FLASH
*             firmware library.
* @author:    AE Team
*******************************************************************************/


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HK32F103XXXXA_FLASH_H
#define __HK32F103XXXXA_FLASH_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "hk32f103xxxxa_conf.h"

/** @addtogroup FLASH
  * @{
  */

/** @defgroup  group_h1 FLASH_Exported_Types
  * @{
  */

/**
  * @brief  FLASH Status
  */

typedef enum
{
    FLASH_BUSY = 1,
    FLASH_ERROR_PG,
    FLASH_ERROR_WRP,
    FLASH_COMPLETE,
    FLASH_TIMEOUT
} FLASH_Status;

/**
  * @brief Option Bytes Registers
  */

typedef struct
{
    __IO uint16_t RDP;
    __IO uint16_t USER;
    __IO uint16_t Data0;
    __IO uint16_t Data1;
    __IO uint16_t WRP0;
    __IO uint16_t WRP1;
    __IO uint16_t WRP2;
    __IO uint16_t WRP3;
    __IO uint32_t RESERVED0;
    __IO uint32_t RESERVED1;
    __IO uint32_t RESERVED2;
    __IO uint32_t RESERVED3;
    __IO uint32_t Encry_CFG;
    __IO uint32_t Decry_CFG;
    __IO uint32_t UKEYL;
    __IO uint32_t UKEYH;
    __IO uint16_t IWDG_RL_IV;
    __IO uint16_t RESERVED4;
    __IO uint32_t IWDG_INI_KEY;
    __IO uint32_t LSI_LP_CTL;
    __IO uint32_t DBG_CLK_CTL;
} OB_TypeDef;
/**
  * @}
  */


/** @defgroup group_h2 Flash_Address
  * @{
  */

#define FLASHInfo_Sys_AddrBase            ((uint32_t)0x1FFFF000)  /*!< FLASH information block system storage base address */
#define FLASHInfo_Opt_AddrBase            ((uint32_t)0x1FFFF800)  /*!< FLASH information block user OPT base address */
#define OB                  ((OB_TypeDef *) FLASHInfo_Opt_AddrBase)

#define IS_FLASH_ADDRESS(ADDRESS) (((ADDRESS) >= 0x08000000) && ((ADDRESS) < 0x0807FFFF))

#define IS_USER_OPT_ADDRESS(ADDRESS) (((ADDRESS) >= 0x1FFFF800) && ((ADDRESS) <= 0x1FFFF840))
/**
  * @}
  */



/** @defgroup group_h3 Flash_Latency
  * @{
  */

#define FLASH_Latency_0                ((uint32_t)0x00000000)  /*!< FLASH 0 Latency cycle */
#define FLASH_Latency_1                ((uint32_t)0x00000001)  /*!< FLASH 1 Latency cycle */
#define FLASH_Latency_2                ((uint32_t)0x00000002)  /*!< FLASH 2 Latency cycles */
#define FLASH_Latency_3                ((uint32_t)0x00000003)  /*!< FLASH 3 Latency cycles */
#define FLASH_Latency_4                ((uint32_t)0x00000004)  /*!< FLASH 4 Latency cycles */
#define FLASH_Latency_5                ((uint32_t)0x00000005)  /*!< FLASH 5 Latency cycles */
#define FLASH_Latency_6                ((uint32_t)0x00000006)  /*!< FLASH 6 Latency cycles */
#define FLASH_Latency_7                ((uint32_t)0x00000007)  /*!< FLASH 7 Latency cycles */
#define FLASH_Latency_8                ((uint32_t)0x00000008)  /*!< FLASH 8 Latency cycles */
#define FLASH_Latency_9                ((uint32_t)0x00000009)  /*!< FLASH 9 Latency cycles */
#define FLASH_Latency_10                ((uint32_t)0x0000000a)  /*!< FLASH 10 Latency cycles */
#define FLASH_Latency_11                ((uint32_t)0x0000000b)  /*!< FLASH 11 Latency cycles */
#define FLASH_Latency_12                ((uint32_t)0x0000000c)  /*!< FLASH 12 Latency cycles */
#define FLASH_Latency_13                ((uint32_t)0x0000000d)  /*!< FLASH 13 Latency cycles */
#define FLASH_Latency_14                ((uint32_t)0x0000000e)  /*!< FLASH 14 Latency cycles */
#define FLASH_Latency_15                ((uint32_t)0x0000000f)  /*!< FLASH 15 Latency cycles */
#define FLASH_Latency_16                ((uint32_t)0x00000010)  /*!< FLASH 16 Latency cycles */
#define FLASH_Latency_17                ((uint32_t)0x00000011)  /*!< FLASH 17 Latency cycles */
#define FLASH_Latency_18                ((uint32_t)0x00000012)  /*!< FLASH 18 Latency cycles */
#define FLASH_Latency_19                ((uint32_t)0x00000013)  /*!< FLASH 19 Latency cycles */
#define FLASH_Latency_20                ((uint32_t)0x00000014)  /*!< FLASH 20 Latency cycles */
#define FLASH_Latency_21                ((uint32_t)0x00000015)  /*!< FLASH 21 Latency cycles */
#define FLASH_Latency_22                ((uint32_t)0x00000016)  /*!< FLASH 22 Latency cycles */
#define FLASH_Latency_23                ((uint32_t)0x00000017)  /*!< FLASH 23 Latency cycles */
#define FLASH_Latency_24                ((uint32_t)0x00000018)  /*!< FLASH 24 Latency cycles */
#define FLASH_Latency_25                ((uint32_t)0x00000019)  /*!< FLASH 25 Latency cycles */
#define FLASH_Latency_26                ((uint32_t)0x0000001a)  /*!< FLASH 26 Latency cycles */
#define FLASH_Latency_27                ((uint32_t)0x0000001b)  /*!< FLASH 27 Latency cycles */
#define FLASH_Latency_28                ((uint32_t)0x0000001c)  /*!< FLASH 28 Latency cycles */
#define FLASH_Latency_29                ((uint32_t)0x0000001d)  /*!< FLASH 29 Latency cycles */
#define FLASH_Latency_30                ((uint32_t)0x0000001e)  /*!< FLASH 30 Latency cycles */
#define FLASH_Latency_31                ((uint32_t)0x0000001f)  /*!< FLASH 31 Latency cycles */

#define IS_FLASH_LATENCY(LATENCY) (((LATENCY) == FLASH_Latency_0) || \
                                   ((LATENCY) == FLASH_Latency_1) || \
                                   ((LATENCY) == FLASH_Latency_2) || \
                                   ((LATENCY) == FLASH_Latency_3) || \
                                   ((LATENCY) == FLASH_Latency_4) || \
                                   ((LATENCY) == FLASH_Latency_5) || \
                                   ((LATENCY) == FLASH_Latency_6) || \
                                   ((LATENCY) == FLASH_Latency_7) || \
                                   ((LATENCY) == FLASH_Latency_8) || \
                                   ((LATENCY) == FLASH_Latency_9) || \
                                   ((LATENCY) == FLASH_Latency_10) || \
                                   ((LATENCY) == FLASH_Latency_11) || \
                                   ((LATENCY) == FLASH_Latency_12) || \
                                   ((LATENCY) == FLASH_Latency_13) || \
                                   ((LATENCY) == FLASH_Latency_14) || \
                                   ((LATENCY) == FLASH_Latency_15) || \
                                   ((LATENCY) == FLASH_Latency_16) || \
                                   ((LATENCY) == FLASH_Latency_17) || \
                                   ((LATENCY) == FLASH_Latency_18) || \
                                   ((LATENCY) == FLASH_Latency_19) || \
                                   ((LATENCY) == FLASH_Latency_20) || \
                                   ((LATENCY) == FLASH_Latency_21) || \
                                   ((LATENCY) == FLASH_Latency_22) || \
                                   ((LATENCY) == FLASH_Latency_23) || \
                                   ((LATENCY) == FLASH_Latency_24) || \
                                   ((LATENCY) == FLASH_Latency_25) || \
                                   ((LATENCY) == FLASH_Latency_26) || \
                                   ((LATENCY) == FLASH_Latency_27) || \
                                   ((LATENCY) == FLASH_Latency_28) || \
                                   ((LATENCY) == FLASH_Latency_29) || \
                                   ((LATENCY) == FLASH_Latency_30) || \
                                   ((LATENCY) == FLASH_Latency_31) )
/**
  * @}
  */

/** @defgroup group_h4 Half_Cycle_Enable_Disable
  * @{
  */

#define FLASH_HalfCycleAccess_Enable   ((uint32_t)0x00000008)  /*!< FLASH Half Cycle Enable */
#define FLASH_HalfCycleAccess_Disable  ((uint32_t)0x00000000)  /*!< FLASH Half Cycle Disable */
#define IS_FLASH_HALFCYCLEACCESS_STATE(STATE) (((STATE) == FLASH_HalfCycleAccess_Enable) || \
                                               ((STATE) == FLASH_HalfCycleAccess_Disable))
/**
  * @}
  */

/** @defgroup group_h5 Prefetch_Buffer_Enable_Disable
  * @{
  */

#define FLASH_PrefetchBuffer_Enable    ((uint32_t)0x00000010)  /*!< FLASH Prefetch Buffer Enable */
#define FLASH_PrefetchBuffer_Disable   ((uint32_t)0x00000000)  /*!< FLASH Prefetch Buffer Disable */
#define IS_FLASH_PREFETCHBUFFER_STATE(STATE) (((STATE) == FLASH_PrefetchBuffer_Enable) || \
                                              ((STATE) == FLASH_PrefetchBuffer_Disable))
/**
  * @}
  */

/** @defgroup group_h6 Option_Bytes_Write_Protection
  * @{
  */
/* Values to be used with All HK32F103xxxxA Serial Device */
#define FLASH_WRProt_Pages0to1         ((uint32_t)0x00000001) /*!< All HK32F103xxxxA Serial devices:
                                                                   Write protection of page 0 to 1 */
#define FLASH_WRProt_Pages2to3         ((uint32_t)0x00000002) /*!< All HK32F103xxxxA Serial devices:
                                                                   Write protection of page 2 to 3 */
#define FLASH_WRProt_Pages4to5         ((uint32_t)0x00000004) /*!< All HK32F103xxxxA Serial devices:
                                                                   Write protection of page 4 to 5 */
#define FLASH_WRProt_Pages6to7         ((uint32_t)0x00000008) /*!< All HK32F103xxxxA Serial devices:
                                                                   Write protection of page 6 to 7 */
#define FLASH_WRProt_Pages8to9         ((uint32_t)0x00000010) /*!< All HK32F103xxxxA Serial devices:
                                                                   Write protection of page 8 to 9 */
#define FLASH_WRProt_Pages10to11       ((uint32_t)0x00000020) /*!< All HK32F103xxxxA Serial devices:
                                                                   Write protection of page 10 to 11 */
#define FLASH_WRProt_Pages12to13       ((uint32_t)0x00000040) /*!< All HK32F103xxxxA Serial devices:
                                                                   Write protection of page 12 to 13 */
#define FLASH_WRProt_Pages14to15       ((uint32_t)0x00000080) /*!< All HK32F103xxxxA Serial devices:
                                                                   Write protection of page 14 to 15 */
#define FLASH_WRProt_Pages16to17       ((uint32_t)0x00000100) /*!< All HK32F103xxxxA Serial devices:
                                                                   Write protection of page 16 to 17 */
#define FLASH_WRProt_Pages18to19       ((uint32_t)0x00000200) /*!< All HK32F103xxxxA Serial devices:
                                                                   Write protection of page 18 to 19 */
#define FLASH_WRProt_Pages20to21       ((uint32_t)0x00000400) /*!< All HK32F103xxxxA Serial devices:
                                                                   Write protection of page 20 to 21 */
#define FLASH_WRProt_Pages22to23       ((uint32_t)0x00000800) /*!< All HK32F103xxxxA Serial devices:
                                                                   Write protection of page 22 to 23 */
#define FLASH_WRProt_Pages24to25       ((uint32_t)0x00001000) /*!< All HK32F103xxxxA Serial devices:
                                                                   Write protection of page 24 to 25 */
#define FLASH_WRProt_Pages26to27       ((uint32_t)0x00002000) /*!< All HK32F103xxxxA Serial devices:
                                                                   Write protection of page 26 to 27 */
#define FLASH_WRProt_Pages28to29       ((uint32_t)0x00004000) /*!< All HK32F103xxxxA Serial devices:
                                                                   Write protection of page 28 to 29 */
#define FLASH_WRProt_Pages30to31       ((uint32_t)0x00008000) /*!< All HK32F103xxxxA Serial devices:
                                                                   Write protection of page 30 to 31 */
#define FLASH_WRProt_Pages32to33       ((uint32_t)0x00010000) /*!< All HK32F103xxxxA Serial devices:
                                                                   Write protection of page 32 to 33 */
#define FLASH_WRProt_Pages34to35       ((uint32_t)0x00020000) /*!< All HK32F103xxxxA Serial devices:
                                                                   Write protection of page 34 to 35 */
#define FLASH_WRProt_Pages36to37       ((uint32_t)0x00040000) /*!< All HK32F103xxxxA Serial devices:
                                                                   Write protection of page 36 to 37 */
#define FLASH_WRProt_Pages38to39       ((uint32_t)0x00080000) /*!< All HK32F103xxxxA Serial devices:
                                                                   Write protection of page 38 to 39 */
#define FLASH_WRProt_Pages40to41       ((uint32_t)0x00100000) /*!< All HK32F103xxxxA Serial devices:
                                                                   Write protection of page 40 to 41 */
#define FLASH_WRProt_Pages42to43       ((uint32_t)0x00200000) /*!< All HK32F103xxxxA Serial devices:
                                                                   Write protection of page 42 to 43 */
#define FLASH_WRProt_Pages44to45       ((uint32_t)0x00400000) /*!< All HK32F103xxxxA Serial devices:
                                                                   Write protection of page 44 to 45 */
#define FLASH_WRProt_Pages46to47       ((uint32_t)0x00800000) /*!< All HK32F103xxxxA Serial devices:
                                                                   Write protection of page 46 to 47 */
#define FLASH_WRProt_Pages48to49       ((uint32_t)0x01000000) /*!< All HK32F103xxxxA Serial devices:
                                                                   Write protection of page 48 to 49 */
#define FLASH_WRProt_Pages50to51       ((uint32_t)0x02000000) /*!< All HK32F103xxxxA Serial devices:
                                                                   Write protection of page 50 to 51 */
#define FLASH_WRProt_Pages52to53       ((uint32_t)0x04000000) /*!< All HK32F103xxxxA Serial devices:
                                                                   Write protection of page 52 to 53 */
#define FLASH_WRProt_Pages54to55       ((uint32_t)0x08000000) /*!< All HK32F103xxxxA Serial devices:
                                                                   Write protection of page 54 to 55 */
#define FLASH_WRProt_Pages56to57       ((uint32_t)0x10000000) /*!< All HK32F103xxxxA Serial devices:
                                                                   Write protection of page 56 to 57 */
#define FLASH_WRProt_Pages58to59       ((uint32_t)0x20000000) /*!< All HK32F103xxxxA Serial devices:
                                                                   Write protection of page 58 to 59 */
#define FLASH_WRProt_Pages60to61       ((uint32_t)0x40000000) /*!< All HK32F103xxxxA Serial devices:
                                                                   Write protection of page 60 to 61 */
#define FLASH_WRProt_Pages62to255      ((uint32_t)0x80000000) /*!< ALL HK32F103xxxxA Serial Flash size 512KB devices:
                                                                   Write protection of page 62 to 255 */
#define FLASH_WRProt_Pages62to191      ((uint32_t)0x80000000) /*!< ALL HK32F103xxxxA Serial Flash size 384KB devices::
                                                                   Write protection of page 62 to 191 */
#define FLASH_WRProt_Pages62to127      ((uint32_t)0x80000000) /*!< ALL HK32F103xxxxA Serial Flash size 256KB and 128KB devices:
                                                                   Write protection of page 62 to 127 */
#define FLASH_WRProt_Pages62to63       ((uint32_t)0x80000000) /*!< ALL HK32F103xxxxA Serial Flash size 64KB devices:
                                                                   Write protection of page 62 to 63 */

#define FLASH_WRProt_AllPages          ((uint32_t)0xFFFFFFFF) /*!< Write protection of all Pages */

#define IS_FLASH_WRPROT_PAGE(PAGE) (((PAGE) != 0x00000000))
/**
  * @}
  */


/** @defgroup group_h7 FLASH_OPT_RDP_KEY
  * @{
  */
#define FLASH_OPT_RDP0_KEY                 ((uint8_t)0xA5)  /*!< FLASH read protection level 0 */
#define FLASH_OPT_RDP1_KEY                 ((uint8_t)0x00)  /*!< FLASH read protection level 1 */
#define FLASH_OPT_RDP2_KEY                 ((uint8_t)0xCC)  /*!< FLASH read protection level 2 */

#define IS_FLASH_OPT_RDP_KEY(RDP_KEY)  (((RDP_KEY) == FLASH_OPT_RDP0_KEY) || \
                                                                                ((RDP_KEY) == FLASH_OPT_RDP1_KEY) || \
                                                                                ((RDP_KEY) == FLASH_OPT_RDP2_KEY))
/**
  * @}
  */

/** @defgroup group_h8 Option_Bytes_IWatchdog
  * @{
  */

#define OB_IWDG_SW                     ((uint16_t)0x0001)  /*!< Software IWDG selected */
#define OB_IWDG_HW                     ((uint16_t)0x0000)  /*!< Hardware IWDG selected */
#define IS_OB_IWDG_SOURCE(SOURCE) (((SOURCE) == OB_IWDG_SW) || ((SOURCE) == OB_IWDG_HW))

/**
  * @}
  */

/** @defgroup group_h9 Option_Bytes_nRST_STOP
  * @{
  */

#define OB_STOP_NoRST                  ((uint16_t)0x0002) /*!< No reset generated when entering in STOP */
#define OB_STOP_RST                    ((uint16_t)0x0000) /*!< Reset generated when entering in STOP */
#define IS_OB_STOP_SOURCE(SOURCE) (((SOURCE) == OB_STOP_NoRST) || ((SOURCE) == OB_STOP_RST))

/**
  * @}
  */

/** @defgroup group_h10 Option_Bytes_nRST_STDBY
  * @{
  */

#define OB_STDBY_NoRST                 ((uint16_t)0x0004) /*!< No reset generated when entering in STANDBY */
#define OB_STDBY_RST                   ((uint16_t)0x0000) /*!< Reset generated when entering in STANDBY */
#define IS_OB_STDBY_SOURCE(SOURCE) (((SOURCE) == OB_STDBY_NoRST) || ((SOURCE) == OB_STDBY_RST))

/**
  * @}
  */


/** @defgroup group_h11 Option_Bytes_BOR_Level
  * @{
  */
#define OB_BOR_ENABLE                                   ((uint16_t)0x0008) /*!< Brown out Reset Enable>*/
#define OB_BOR_LEVEL1                 ((uint16_t)0x0001) /*!< Brown out Reset Level(Detected/Released) 1.68V / 1.78V */
#define OB_BOR_LEVEL2                 ((uint16_t)0x0002) /*!< Brown out Reset Level(Detected/Released) 1.88V / 1.98V */
#define OB_BOR_LEVEL3                 ((uint16_t)0x0003) /*!< Brown out Reset Level(Detected/Released) 2.08V / 2.18V */
#define OB_BOR_LEVEL4                 ((uint16_t)0x0004) /*!< Brown out Reset Level(Detected/Released) 2.28V / 2.38V */
#define OB_BOR_LEVEL5                 ((uint16_t)0x0005) /*!< Brown out Reset Level(Detected/Released) 2.48V / 2.58V */
#define OB_BOR_LEVEL6                 ((uint16_t)0x0006) /*!< Brown out Reset Level(Detected/Released) 2.68V / 2.78V */
#define OB_BOR_LEVEL7                 ((uint16_t)0x0007) /*!< Brown out Reset Level(Detected/Released) 2.88V / 2.98V */

#define IS_OB_BOR_LEVEL(LEVEL)               (((LEVEL) == OB_BOR_LEVEL1) || \
                                                                                ((LEVEL) == OB_BOR_LEVEL2) || \
                                                                                ((LEVEL) == OB_BOR_LEVEL3) || \
                                                                                ((LEVEL) == OB_BOR_LEVEL4) || \
                                                                                ((LEVEL) == OB_BOR_LEVEL5) || \
                                                                                ((LEVEL) == OB_BOR_LEVEL6) || \
                                                                                ((LEVEL) == OB_BOR_LEVEL7))

/**
  * @}
  */

/** @defgroup group_h12 FLASH_Interrupts
  * @{
  */
#define FLASH_IT_ERROR                 ((uint32_t)0x00000400)  /*!< FPEC error interrupt source */
#define FLASH_IT_EOP                   ((uint32_t)0x00001000)  /*!< End of FLASH Operation Interrupt source */

#define IS_FLASH_IT(IT) ((((IT) & (uint32_t)0xFFFFEBFF) == 0x00000000) && (((IT) != 0x00000000)))

/**
  * @}
  */

/** @defgroup group_h13 FLASH_Flags
  * @{
  */
#define FLASH_FLAG_BSY                 ((uint32_t)0x00000001)  /*!< FLASH Busy flag */
#define FLASH_FLAG_EOP                 ((uint32_t)0x00000020)  /*!< FLASH End of Operation flag */
#define FLASH_FLAG_PGERR               ((uint32_t)0x00000004)  /*!< FLASH Program error flag */
#define FLASH_FLAG_WRPRTERR            ((uint32_t)0x00000010)  /*!< FLASH Write protected error flag */
#define FLASH_FLAG_OPTERR              ((uint32_t)0x00000001)  /*!< FLASH Option Byte error flag */

#define IS_FLASH_CLEAR_FLAG(FLAG) ((((FLAG) & (uint32_t)0xFFFFFFCA) == 0x00000000) && ((FLAG) != 0x00000000))
#define IS_FLASH_GET_FLAG(FLAG)  (((FLAG) == FLASH_FLAG_BSY) || ((FLAG) == FLASH_FLAG_EOP) || \
                                  ((FLAG) == FLASH_FLAG_PGERR) || ((FLAG) == FLASH_FLAG_WRPRTERR) || \
                                  ((FLAG) == FLASH_FLAG_OPTERR))

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
void FLASH_SetLatency(uint32_t FLASH_Latency);
void FLASH_HalfCycleAccessCmd(uint32_t FLASH_HalfCycleAccess);
void FLASH_PrefetchBufferCmd(uint32_t FLASH_PrefetchBuffer);
void FLASH_Unlock(void);
void FLASH_Lock(void);

FLASH_Status FLASH_ProgramHalfWord(uint32_t Address, uint16_t Data);

FLASH_Status FLASH_ErasePage(uint32_t Page_Address);
FLASH_Status FLASH_EraseAllPages(void);
FLASH_Status FLASH_EraseMicroPage(uint32_t Page_Address);
FLASH_Status FLASH_EraseInfo(uint32_t Halfpage_Address);
FLASH_Status FLASH_EraseOptionBytes(void);
FLASH_Status FLASH_Program4Words(uint32_t Address, uint32_t *Data);
FLASH_Status FLASH_Program2Words(uint32_t Address, uint32_t DataL, uint32_t DataH);
FLASH_Status FLASH_ProgramWord(uint32_t Address, uint32_t Data);
FLASH_Status FLASH_ProgramOptionByteData(uint32_t Address, uint16_t Data);
FLASH_Status FLASH_ProgramInfoHalfWordData(uint32_t Address, uint16_t Data);
FLASH_Status FLASH_ProgramInfoWordData(uint32_t Address, uint32_t Data);
FLASH_Status FLASH_EnableWriteProtection(uint32_t FLASH_Pages);
FLASH_Status FLASH_ReadOutProtection(FunctionalState NewState);
FLASH_Status FLASH_UserOptionByteConfig(uint16_t OB_IWDG, uint16_t OB_STOP, uint16_t OB_STDBY);
uint32_t FLASH_GetUserOptionByte(void);
uint32_t FLASH_GetWriteProtectionOptionByte(void);
FlagStatus FLASH_GetReadOutProtectionStatus(void);
FlagStatus FLASH_GetPrefetchBufferStatus(void);
FlagStatus FLASH_GetFlagStatus(uint32_t FLASH_FLAG);
void FLASH_ClearFlag(uint32_t FLASH_FLAG);
FLASH_Status FLASH_GetStatus(void);
FLASH_Status FLASH_WaitForLastOperation(uint32_t Timeout);
FLASH_Status FLASH_OptionIWDGRLIV(uint16_t OB_IWDGRLIV);
FLASH_Status FLASH_OptionIWDGRLIVCMD(FunctionalState NewState);
FLASH_Status FLASH_OptionLSICMD(FunctionalState NewState);
FLASH_Status FLASH_OptionDebugCMD(FunctionalState NewState);
void FLASH_ITConfig(uint32_t FLASH_IT, FunctionalState NewState);

#ifdef __cplusplus
}
#endif

#endif /*__HK32F103XXXXA_FLASH_H */

