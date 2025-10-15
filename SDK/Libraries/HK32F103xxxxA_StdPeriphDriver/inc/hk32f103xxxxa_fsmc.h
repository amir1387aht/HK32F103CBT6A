/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd 
* @filename:  hk32f103xxxxa_fsmc.h
* @brief:     hk32f103xxxxa_fsmc  configuration file.
*             The file is the unique include file that the application programmer
*             is using in the C source code, it is a patch file. 
* @author:    AE Team 
*******************************************************************************/


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HK32F103XXXXA_FSMC_H
#define __HK32F103XXXXA_FSMC_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "hk32f103xxxxa.h"


/** @addtogroup FSMC
  * @{
  */

/** @defgroup FSMC_Exported_Types FSMC_Exported_Types
  * @{
  */

/**
  * @brief  Timing parameters For NOR/SRAM Banks
  */

typedef struct
{
    uint32_t FSMC_AddressSetupTime;       /*!< Defines the number of HCLK cycles to configure
                                             the duration of the address setup time.
                                             This parameter can be a value between 0 and 0xF.
                                             @note: It is not used with synchronous NOR Flash memories. */

    uint32_t FSMC_AddressHoldTime;        /*!< Defines the number of HCLK cycles to configure
                                             the duration of the address hold time.
                                             This parameter can be a value between 0 and 0xF.
                                             @note: It is not used with synchronous NOR Flash memories.*/

    uint32_t FSMC_DataSetupTime;          /*!< Defines the number of HCLK cycles to configure
                                             the duration of the data setup time.
                                             This parameter can be a value between 0 and 0xFF.
                                             @note: It is used for SRAMs, ROMs and asynchronous multiplexed NOR Flash memories. */

    uint32_t FSMC_BusTurnAroundDuration;  /*!< Defines the number of HCLK cycles to configure
                                             the duration of the bus turnaround.
                                             This parameter can be a value between 0 and 0xF.
                                             @note: It is only used for multiplexed NOR Flash memories. */

    uint32_t FSMC_CLKDivision;            /*!< Defines the period of CLK clock output signal, expressed in number of HCLK cycles.
                                             This parameter can be a value between 1 and 0xF.
                                             @note: This parameter is not used for asynchronous NOR Flash, SRAM or ROM accesses. */

    uint32_t FSMC_DataLatency;            /*!< Defines the number of memory clock cycles to issue
                                             to the memory before getting the first data.
                                             The value of this parameter depends on the memory type as shown below:
                                              - It must be set to 0 in case of a CRAM
                                              - It is don't care in asynchronous NOR, SRAM or ROM accesses
                                              - It may assume a value between 0 and 0xF in NOR Flash memories
                                                with synchronous burst mode enable */

    uint32_t FSMC_AccessMode;             /*!< Specifies the asynchronous access mode.
                                             This parameter can be a value of @ref FSMC_Access_Mode */
} FSMC_NORSRAMTimingInitTypeDef;

/**
  * @brief  FSMC NOR/SRAM Init structure definition
  */

typedef struct
{
    uint32_t FSMC_Bank;                /*!< Specifies the NOR/SRAM memory bank that will be used.
                                          This parameter can be a value of @ref FSMC_NORSRAM_Bank */

    uint32_t FSMC_DataAddressMux;      /*!< Specifies whether the address and data values are
                                          multiplexed on the databus or not.
                                          This parameter can be a value of @ref FSMC_Data_Address_Bus_Multiplexing */

    uint32_t FSMC_MemoryType;          /*!< Specifies the type of external memory attached to
                                          the corresponding memory bank.
                                          This parameter can be a value of @ref FSMC_Memory_Type */

    uint32_t FSMC_MemoryDataWidth;     /*!< Specifies the external memory device width.
                                          This parameter can be a value of @ref FSMC_Data_Width */

    uint32_t FSMC_BurstAccessMode;     /*!< Enables or disables the burst access mode for Flash memory,
                                          valid only with synchronous burst Flash memories.
                                          This parameter can be a value of @ref FSMC_Burst_Access_Mode */

    uint32_t FSMC_AsynchronousWait;     /*!< Enables or disables wait signal during asynchronous transfers,
                                          valid only with asynchronous Flash memories.
                                          This parameter can be a value of @ref FSMC_AsynchronousWait */

    uint32_t FSMC_WaitSignalPolarity;  /*!< Specifies the wait signal polarity, valid only when accessing
                                          the Flash memory in burst mode.
                                          This parameter can be a value of @ref FSMC_Wait_Signal_Polarity */

    uint32_t FSMC_WrapMode;            /*!< Enables or disables the Wrapped burst access mode for Flash
                                          memory, valid only when accessing Flash memories in burst mode.
                                          This parameter can be a value of @ref FSMC_Wrap_Mode */

    uint32_t FSMC_WaitSignalActive;    /*!< Specifies if the wait signal is asserted by the memory one
                                          clock cycle before the wait state or during the wait state,
                                          valid only when accessing memories in burst mode.
                                          This parameter can be a value of @ref FSMC_Wait_Timing */

    uint32_t FSMC_WriteOperation;      /*!< Enables or disables the write operation in the selected bank by the FSMC.
                                          This parameter can be a value of @ref FSMC_Write_Operation */

    uint32_t FSMC_WaitSignal;          /*!< Enables or disables the wait-state insertion via wait
                                          signal, valid for Flash memory access in burst mode.
                                          This parameter can be a value of @ref FSMC_Wait_Signal */

    uint32_t FSMC_ExtendedMode;        /*!< Enables or disables the extended mode.
                                          This parameter can be a value of @ref FSMC_Extended_Mode */

    uint32_t FSMC_WriteBurst;          /*!< Enables or disables the write burst operation.
                                          This parameter can be a value of @ref FSMC_Write_Burst */

    FSMC_NORSRAMTimingInitTypeDef* FSMC_ReadWriteTimingStruct; /*!< Timing Parameters for write and read access if the  ExtendedMode is not used*/

    FSMC_NORSRAMTimingInitTypeDef* FSMC_WriteTimingStruct;     /*!< Timing Parameters for write access if the  ExtendedMode is used*/
	
	uint32_t NadvPol;                  /*!< NADV polarity config.
                                          This parameter can be a value of @ref FSMC_NADV_Pol */
} FSMC_NORSRAMInitTypeDef;

/**
  * @brief  Timing parameters For FSMC NAND and PCCARD Banks
  */

typedef struct
{
    uint32_t FSMC_SetupTime;      /*!< Defines the number of HCLK cycles to setup address before
                                     the command assertion for NAND-Flash read or write access
                                     to common/Attribute or I/O memory space (depending on
                                     the memory space timing to be configured).
                                     This parameter can be a value between 0 and 0xFF.*/

    uint32_t FSMC_WaitSetupTime;  /*!< Defines the minimum number of HCLK cycles to assert the
                                     command for NAND-Flash read or write access to
                                     common/Attribute or I/O memory space (depending on the
                                     memory space timing to be configured).
                                     This parameter can be a number between 0x00 and 0xFF */

    uint32_t FSMC_HoldSetupTime;  /*!< Defines the number of HCLK clock cycles to hold address
                                     (and data for write access) after the command deassertion
                                     for NAND-Flash read or write access to common/Attribute
                                     or I/O memory space (depending on the memory space timing
                                     to be configured).
                                     This parameter can be a number between 0x00 and 0xFF */

    uint32_t FSMC_HiZSetupTime;   /*!< Defines the number of HCLK clock cycles during which the
                                     databus is kept in HiZ after the start of a NAND-Flash
                                     write access to common/Attribute or I/O memory space (depending
                                     on the memory space timing to be configured).
                                     This parameter can be a number between 0x00 and 0xFF */
} FSMC_NAND_PCCARDTimingInitTypeDef;

/**
  * @brief  FSMC NAND Init structure definition
  */

typedef struct
{
    uint32_t FSMC_Bank;              /*!< Specifies the NAND memory bank that will be used.
                                      This parameter can be a value of @ref FSMC_NAND_Bank */

    uint32_t FSMC_Waitfeature;      /*!< Enables or disables the Wait feature for the NAND Memory Bank.
                                       This parameter can be any value of @ref FSMC_Wait_feature */

    uint32_t FSMC_MemoryDataWidth;  /*!< Specifies the external memory device width.
                                       This parameter can be any value of @ref FSMC_Data_Width */

    uint32_t FSMC_ECC;              /*!< Enables or disables the ECC computation.
                                       This parameter can be any value of @ref FSMC_ECC */

    uint32_t FSMC_ECCPageSize;      /*!< Defines the page size for the extended ECC.
                                       This parameter can be any value of @ref FSMC_ECC_Page_Size */

    uint32_t FSMC_TCLRSetupTime;    /*!< Defines the number of HCLK cycles to configure the
                                       delay between CLE low and RE low.
                                       This parameter can be a value between 0 and 0xFF. */

    uint32_t FSMC_TARSetupTime;     /*!< Defines the number of HCLK cycles to configure the
                                       delay between ALE low and RE low.
                                       This parameter can be a number between 0x0 and 0xFF */

    FSMC_NAND_PCCARDTimingInitTypeDef*  FSMC_CommonSpaceTimingStruct;   /*!< FSMC Common Space Timing */

    FSMC_NAND_PCCARDTimingInitTypeDef*  FSMC_AttributeSpaceTimingStruct; /*!< FSMC Attribute Space Timing */
} FSMC_NANDInitTypeDef;

/**
  * @brief  FSMC PCCARD Init structure definition
  */

typedef struct
{
    uint32_t FSMC_Waitfeature;    /*!< Enables or disables the Wait feature for the Memory Bank.
                                    This parameter can be any value of @ref FSMC_Wait_feature */

    uint32_t FSMC_TCLRSetupTime;  /*!< Defines the number of HCLK cycles to configure the
                                     delay between CLE low and RE low.
                                     This parameter can be a value between 0 and 0xFF. */

    uint32_t FSMC_TARSetupTime;   /*!< Defines the number of HCLK cycles to configure the
                                     delay between ALE low and RE low.
                                     This parameter can be a number between 0x0 and 0xFF */


    FSMC_NAND_PCCARDTimingInitTypeDef*  FSMC_CommonSpaceTimingStruct; /*!< FSMC Common Space Timing */

    FSMC_NAND_PCCARDTimingInitTypeDef*  FSMC_AttributeSpaceTimingStruct;  /*!< FSMC Attribute Space Timing */

    FSMC_NAND_PCCARDTimingInitTypeDef*  FSMC_IOSpaceTimingStruct; /*!< FSMC IO Space Timing */
} FSMC_PCCARDInitTypeDef;

/**
  * @brief Flexible Static Memory Controller LCD Init Type
  */
typedef struct
{
    uint32_t NSBank;            /*!< The FSMC LCD Bank select.
                                            This parameter can be any value of @ref FSMC_LCD_Bank_Sel */

    uint32_t HSPol;             /*!< The FSMC LCD horizontal polarity config.
                                            This parameter can be any value of @ref FSMC_LCD_Horizontal_Polarity. */

    uint32_t VSPol;             /*!< The FSMC LCD vertical polarity config.
                                            This parameter can be any value of @ref FSMC_LCD_Vertical_Polarity.   */

    uint32_t DEPol;             /*!< The FSMC LCD data enable polarity config.
                                            This parameter can be any value of @ref FSMC_LCD_Data_Enable_Polarity. */

    uint32_t DCLKPol;           /*!< The FSMC LCD dclk_active_negative config.
                                    This parameter can be any value of @ref FSMC_LCD_Dclk_Active_Negative. */

    uint32_t DLCK_setup_time;   /*!< The FSMC LCD DCLK pixel data setting time.
                                    This parameter can be a value between 0 and 0xFF. */

    uint32_t HSW;               /*!< The FSMC LCD horizontal synchronization width.
                                            This parameter can be a value between 0 and 0xFFF. */

    uint32_t VSH;               /*!< The FSMC LCD vertical synchronization width.
                                            This parameter can be a value between 0 and 0x7FF. */

    uint32_t AHBP;              /*!< The FSMC LCD accumulated horizonal back porch.
                                            This parameter can be a value between 0 and 0xFFF. */

    uint32_t AVBP;              /*!< The FSMC LCD accumulated vertical back porch.
                                            This parameter can be a value between 0 and 0x7FF. */

    uint32_t AAW;               /*!< The FSMC LCD accumulated active width.
                                            This parameter can be a value between 0 and 0xFFF. */

    uint32_t AAH;               /*!< The FSMC LCD accumulated active height.
                                            This parameter can be a value between 0 and 0xFFF. */

    uint32_t TOTALW;            /*!< The FSMC LCD total width.
                                            This parameter can be a value between 0 and 0x7FF. */

    uint32_t TOTALH;            /*!< The FSMC LCD total height.
                                            This parameter can be a value between 0 and 0x7FF. */

    uint32_t AUTOPOR;           /*!< The FSMC LCD auto writing into the porch enable.
                                            This parameter can be any value of @ref FSMC_LCD_Auto_Por. */

    uint32_t POR_data;          /*!< The FSMC LCD auto-writing data into the range of the porch .
                                            This parameter can be a value between 0 and 0xFFFF. */

    uint32_t LCDEN;             /*!< The FSMC LCD panel enable.
                                    This parameter can be any value of @ref FSMC_LCD_Panel */
} FSMC_LCD_InitTypeDef;


/**
  * @brief Flexible Static Memory Controller
  */

typedef struct
{
    __IO uint32_t BTCR[8];
} FSMC_Bank1_TypeDef;

/**
  * @brief Flexible Static Memory Controller Bank1E
  */

typedef struct
{
    __IO uint32_t BWTR[7];
} FSMC_Bank1E_TypeDef;

/**
  * @brief Flexible Static Memory Controller Bank2
  */

typedef struct
{
    __IO uint32_t PCR2;
    __IO uint32_t SR2;
    __IO uint32_t PMEM2;
    __IO uint32_t PATT2;
    uint32_t  RESERVED0;
    __IO uint32_t ECCR2;
} FSMC_Bank2_TypeDef;

/**
  * @brief Flexible Static Memory Controller Bank3
  */

typedef struct
{
    __IO uint32_t PCR3;
    __IO uint32_t SR3;
    __IO uint32_t PMEM3;
    __IO uint32_t PATT3;
    uint32_t  RESERVED0;
    __IO uint32_t ECCR3;
} FSMC_Bank3_TypeDef;

/**
  * @brief Flexible Static Memory Controller Bank4
  */

typedef struct
{
    __IO uint32_t PCR4;
    __IO uint32_t SR4;
    __IO uint32_t PMEM4;
    __IO uint32_t PATT4;
    __IO uint32_t PIO4;
} FSMC_Bank4_TypeDef;

/**
  * @brief Flexible Static Memory Controller LCD
  */
typedef struct
{
    __IO uint32_t LCD_CTRL[4];
    __IO uint32_t LCD_SSCR[4];
    __IO uint32_t LCD_BPCR[4];
    __IO uint32_t LCD_AWCR[4];
    __IO uint32_t LCD_TWCR[4];

    __IO uint32_t LCD_CPSR;
    __IO uint32_t LCD_CFG;
} FSMC_LCD_TypeDef;

/**
  * @}
  */

/** @defgroup FSMC_Exported_Constants FSMC_Exported_Constants
  * @{
  */

/** @defgroup FSMC_Base_Address_And_Type FSMC_Base_Address_And_Type
  * @{
  */
#define FSMC_Bank1_R_BASE     (FSMC_BASE + 0x0000)                          /*!< FSMC Bank1 registers base address */
#define FSMC_Bank1E_R_BASE    (FSMC_BASE + 0x0104)                          /*!< FSMC Bank1E registers base address */
#define FSMC_Bank2_R_BASE     (FSMC_BASE + 0x0060)                          /*!< FSMC Bank2 registers base address */
#define FSMC_Bank3_R_BASE     (FSMC_BASE + 0x0080)                          /*!< FSMC Bank3 registers base address */
#define FSMC_Bank4_R_BASE     (FSMC_BASE + 0x00A0)                          /*!< FSMC Bank4 registers base address */
#define FSMC_Bank1            ((FSMC_Bank1_TypeDef *) FSMC_Bank1_R_BASE)
#define FSMC_Bank1E           ((FSMC_Bank1E_TypeDef *) FSMC_Bank1E_R_BASE)
#define FSMC_Bank2            ((FSMC_Bank2_TypeDef *) FSMC_Bank2_R_BASE)
#define FSMC_Bank3            ((FSMC_Bank3_TypeDef *) FSMC_Bank3_R_BASE)
#define FSMC_Bank4            ((FSMC_Bank4_TypeDef *) FSMC_Bank4_R_BASE)
#define FSMC_LCD_R_BASE       (FSMC_BASE + 0x00000200U)                 /*!< FSMC Bank1(LCD) registers base address */
#define FSMC_LCD              ((FSMC_LCD_TypeDef *)FSMC_LCD_R_BASE)
/**
  * @}
  */



/** @defgroup FSMC_NORSRAM_Bank FSMC_NORSRAM_Bank
  * @{
  */
#define FSMC_Bank1_NORSRAM1                             ((uint32_t)0x00000000)
#define FSMC_Bank1_NORSRAM2                             ((uint32_t)0x00000002)
#define FSMC_Bank1_NORSRAM3                             ((uint32_t)0x00000004)
#define FSMC_Bank1_NORSRAM4                             ((uint32_t)0x00000006)
/**
  * @}
  */

/** @defgroup FSMC_NAND_Bank FSMC_NAND_Bank
  * @{
  */
#define FSMC_Bank2_NAND                                 ((uint32_t)0x00000010)
#define FSMC_Bank3_NAND                                 ((uint32_t)0x00000100)
/**
  * @}
  */

/** @defgroup FSMC_PCCARD_Bank FSMC_PCCARD_Bank
  * @{
  */
#define FSMC_Bank4_PCCARD                               ((uint32_t)0x00001000)
/**
  * @}
  */

#define IS_FSMC_NORSRAM_BANK(BANK) (((BANK) == FSMC_Bank1_NORSRAM1) || \
                                    ((BANK) == FSMC_Bank1_NORSRAM2) || \
                                    ((BANK) == FSMC_Bank1_NORSRAM3) || \
                                    ((BANK) == FSMC_Bank1_NORSRAM4))

#define IS_FSMC_NAND_BANK(BANK) (((BANK) == FSMC_Bank2_NAND) || \
                                 ((BANK) == FSMC_Bank3_NAND))

#define IS_FSMC_GETFLAG_BANK(BANK) (((BANK) == FSMC_Bank2_NAND) || \
                                    ((BANK) == FSMC_Bank3_NAND) || \
                                    ((BANK) == FSMC_Bank4_PCCARD))

#define IS_FSMC_IT_BANK(BANK) (((BANK) == FSMC_Bank2_NAND) || \
                               ((BANK) == FSMC_Bank3_NAND) || \
                               ((BANK) == FSMC_Bank4_PCCARD))

/** @defgroup NOR_SRAM_Controller NOR_SRAM_Controller
  * @{
  */

/** @defgroup FSMC_Data_Address_Bus_Multiplexing FSMC_Data_Address_Bus_Multiplexing
  * @{
  */

#define FSMC_DataAddressMux_Disable                       ((uint32_t)0x00000000)
#define FSMC_DataAddressMux_Enable                        ((uint32_t)0x00000002)
#define IS_FSMC_MUX(MUX) (((MUX) == FSMC_DataAddressMux_Disable) || \
                          ((MUX) == FSMC_DataAddressMux_Enable))

/**
  * @}
  */

/** @defgroup FSMC_Memory_Type FSMC_Memory_Type
  * @{
  */

#define FSMC_MemoryType_SRAM                            ((uint32_t)0x00000000)
#define FSMC_MemoryType_PSRAM                           ((uint32_t)0x00000004)
#define FSMC_MemoryType_NOR                             ((uint32_t)0x00000008)
#define IS_FSMC_MEMORY(MEMORY) (((MEMORY) == FSMC_MemoryType_SRAM) || \
                                ((MEMORY) == FSMC_MemoryType_PSRAM)|| \
                                ((MEMORY) == FSMC_MemoryType_NOR))

/**
  * @}
  */

/** @defgroup FSMC_Data_Width FSMC_Data_Width
  * @{
  */

#define FSMC_MemoryDataWidth_8b                         ((uint32_t)0x00000000)
#define FSMC_MemoryDataWidth_16b                        ((uint32_t)0x00000010)
#define IS_FSMC_MEMORY_WIDTH(WIDTH) (((WIDTH) == FSMC_MemoryDataWidth_8b) || \
                                     ((WIDTH) == FSMC_MemoryDataWidth_16b))

/**
  * @}
  */

/** @defgroup FSMC_Burst_Access_Mode FSMC_Burst_Access_Mode
  * @{
  */

#define FSMC_BurstAccessMode_Disable                    ((uint32_t)0x00000000)
#define FSMC_BurstAccessMode_Enable                     ((uint32_t)0x00000100)
#define IS_FSMC_BURSTMODE(STATE) (((STATE) == FSMC_BurstAccessMode_Disable) || \
                                  ((STATE) == FSMC_BurstAccessMode_Enable))
/**
  * @}
  */
 
/** @defgroup FSMC_AsynchronousWait FSMC_AsynchronousWait
  * @{
  */
#define FSMC_AsynchronousWait_Disable                   ((uint32_t)0x00000000)
#define FSMC_AsynchronousWait_Enable                    ((uint32_t)0x00008000)
#define IS_FSMC_ASYNWAIT(STATE) (((STATE) == FSMC_AsynchronousWait_Disable) || \
                                 ((STATE) == FSMC_AsynchronousWait_Enable))

/**
  * @}
  */

/** @defgroup FSMC_Wait_Signal_Polarity FSMC_Wait_Signal_Polarity
  * @{
  */

#define FSMC_WaitSignalPolarity_Low                     ((uint32_t)0x00000000)
#define FSMC_WaitSignalPolarity_High                    ((uint32_t)0x00000200)
#define IS_FSMC_WAIT_POLARITY(POLARITY) (((POLARITY) == FSMC_WaitSignalPolarity_Low) || \
                                         ((POLARITY) == FSMC_WaitSignalPolarity_High))

/**
  * @}
  */

/** @defgroup FSMC_Wrap_Mode FSMC_Wrap_Mode
  * @{
  */

#define FSMC_WrapMode_Disable                           ((uint32_t)0x00000000)
#define FSMC_WrapMode_Enable                            ((uint32_t)0x00000400)
#define IS_FSMC_WRAP_MODE(MODE) (((MODE) == FSMC_WrapMode_Disable) || \
                                 ((MODE) == FSMC_WrapMode_Enable))

/**
  * @}
  */

/** @defgroup FSMC_Wait_Timing FSMC_Wait_Timing
  * @{
  */

#define FSMC_WaitSignalActive_BeforeWaitState           ((uint32_t)0x00000000)
#define FSMC_WaitSignalActive_DuringWaitState           ((uint32_t)0x00000800)
#define IS_FSMC_WAIT_SIGNAL_ACTIVE(ACTIVE) (((ACTIVE) == FSMC_WaitSignalActive_BeforeWaitState) || \
                                            ((ACTIVE) == FSMC_WaitSignalActive_DuringWaitState))

/**
  * @}
  */

/** @defgroup FSMC_Write_Operation FSMC_Write_Operation
  * @{
  */

#define FSMC_WriteOperation_Disable                     ((uint32_t)0x00000000)
#define FSMC_WriteOperation_Enable                      ((uint32_t)0x00001000)
#define IS_FSMC_WRITE_OPERATION(OPERATION) (((OPERATION) == FSMC_WriteOperation_Disable) || \
                                            ((OPERATION) == FSMC_WriteOperation_Enable))

/**
  * @}
  */

/** @defgroup FSMC_Wait_Signal FSMC_Wait_Signal
  * @{
  */

#define FSMC_WaitSignal_Disable                         ((uint32_t)0x00000000)
#define FSMC_WaitSignal_Enable                          ((uint32_t)0x00002000)
#define IS_FSMC_WAITE_SIGNAL(SIGNAL) (((SIGNAL) == FSMC_WaitSignal_Disable) || \
                                      ((SIGNAL) == FSMC_WaitSignal_Enable))
/**
  * @}
  */

/** @defgroup FSMC_Extended_Mode FSMC_Extended_Mode
  * @{
  */

#define FSMC_ExtendedMode_Disable                       ((uint32_t)0x00000000)
#define FSMC_ExtendedMode_Enable                        ((uint32_t)0x00004000)

#define IS_FSMC_EXTENDED_MODE(MODE) (((MODE) == FSMC_ExtendedMode_Disable) || \
                                     ((MODE) == FSMC_ExtendedMode_Enable))

/**
  * @}
  */

/** @defgroup FSMC_Write_Burst FSMC_Write_Burst
  * @{
  */

#define FSMC_WriteBurst_Disable                         ((uint32_t)0x00000000)
#define FSMC_WriteBurst_Enable                          ((uint32_t)0x00080000)
#define IS_FSMC_WRITE_BURST(BURST) (((BURST) == FSMC_WriteBurst_Disable) || \
                                    ((BURST) == FSMC_WriteBurst_Enable))
/**
  * @}
  */

/** @defgroup FSMC_Address_Setup_Time FSMC_Address_Setup_Time
  * @{
  */

#define IS_FSMC_ADDRESS_SETUP_TIME(TIME) ((TIME) <= 0xF)

/**
  * @}
  */

/** @defgroup FSMC_Address_Hold_Time FSMC_Address_Hold_Time
  * @{
  */

#define IS_FSMC_ADDRESS_HOLD_TIME(TIME) ((TIME) <= 0xF)

/**
  * @}
  */

/** @defgroup FSMC_Data_Setup_Time FSMC_Data_Setup_Time
  * @{
  */

#define IS_FSMC_DATASETUP_TIME(TIME) (((TIME) > 0) && ((TIME) <= 0xFF))

/**
  * @}
  */

/** @defgroup FSMC_Bus_Turn_around_Duration FSMC_Bus_Turn_around_Duration
  * @{
  */

#define IS_FSMC_TURNAROUND_TIME(TIME) ((TIME) <= 0xF)

/**
  * @}
  */

/** @defgroup FSMC_CLK_Division FSMC_CLK_Division
  * @{
  */

#define IS_FSMC_CLK_DIV(DIV) ((DIV) <= 0xF)

/**
  * @}
  */

/** @defgroup FSMC_Data_Latency FSMC_Data_Latency
  * @{
  */

#define IS_FSMC_DATA_LATENCY(LATENCY) ((LATENCY) <= 0xF)

/**
  * @}
  */

/** @defgroup FSMC_Access_Mode FSMC_Access_Mode
  * @{
  */

#define FSMC_AccessMode_A                               ((uint32_t)0x00000000)
#define FSMC_AccessMode_B                               ((uint32_t)0x10000000)
#define FSMC_AccessMode_C                               ((uint32_t)0x20000000)
#define FSMC_AccessMode_D                               ((uint32_t)0x30000000)
#define IS_FSMC_ACCESS_MODE(MODE) (((MODE) == FSMC_AccessMode_A) || \
                                   ((MODE) == FSMC_AccessMode_B) || \
                                   ((MODE) == FSMC_AccessMode_C) || \
                                   ((MODE) == FSMC_AccessMode_D))

/**
  * @}
  */

/**
  * @}
  */

/** @defgroup NAND_PCCARD_Controller NAND_PCCARD_Controller
  * @{
  */

/** @defgroup FSMC_Wait_feature FSMC_Wait_feature
  * @{
  */

#define FSMC_Waitfeature_Disable                        ((uint32_t)0x00000000)
#define FSMC_Waitfeature_Enable                         ((uint32_t)0x00000002)
#define IS_FSMC_WAIT_FEATURE(FEATURE) (((FEATURE) == FSMC_Waitfeature_Disable) || \
                                       ((FEATURE) == FSMC_Waitfeature_Enable))

/**
  * @}
  */


/** @defgroup FSMC_ECC FSMC_ECC
  * @{
  */

#define FSMC_ECC_Disable                                ((uint32_t)0x00000000)
#define FSMC_ECC_Enable                                 ((uint32_t)0x00000040)
#define IS_FSMC_ECC_STATE(STATE) (((STATE) == FSMC_ECC_Disable) || \
                                  ((STATE) == FSMC_ECC_Enable))

/**
  * @}
  */

/** @defgroup FSMC_ECC_Page_Size FSMC_ECC_Page_Size
  * @{ 
  */

#define FSMC_ECCPageSize_256Bytes                       ((uint32_t)0x00000000)
#define FSMC_ECCPageSize_512Bytes                       ((uint32_t)0x00020000)
#define FSMC_ECCPageSize_1024Bytes                      ((uint32_t)0x00040000)
#define FSMC_ECCPageSize_2048Bytes                      ((uint32_t)0x00060000)
#define FSMC_ECCPageSize_4096Bytes                      ((uint32_t)0x00080000)
#define FSMC_ECCPageSize_8192Bytes                      ((uint32_t)0x000A0000)
#define IS_FSMC_ECCPAGE_SIZE(SIZE) (((SIZE) == FSMC_ECCPageSize_256Bytes) || \
                                    ((SIZE) == FSMC_ECCPageSize_512Bytes) || \
                                    ((SIZE) == FSMC_ECCPageSize_1024Bytes) || \
                                    ((SIZE) == FSMC_ECCPageSize_2048Bytes) || \
                                    ((SIZE) == FSMC_ECCPageSize_4096Bytes) || \
                                    ((SIZE) == FSMC_ECCPageSize_8192Bytes))

/**
  * @}
  */

/** @defgroup FSMC_TCLR_Setup_Time FSMC_TCLR_Setup_Time
  * @{
  */

#define IS_FSMC_TCLR_TIME(TIME) ((TIME) <= 0xFF)

/**
  * @}
  */

/** @defgroup FSMC_TAR_Setup_Time FSMC_TAR_Setup_Time
  * @{
  */

#define IS_FSMC_TAR_TIME(TIME) ((TIME) <= 0xFF)

/**
  * @}
  */

/** @defgroup FSMC_Setup_Time FSMC_Setup_Time
  * @{
  */

#define IS_FSMC_SETUP_TIME(TIME) ((TIME) <= 0xFF)

/**
  * @}
  */

/** @defgroup FSMC_Wait_Setup_Time FSMC_Wait_Setup_Time
  * @{
  */

#define IS_FSMC_WAIT_TIME(TIME) ((TIME) <= 0xFF)

/**
  * @}
  */

/** @defgroup FSMC_Hold_Setup_Time FSMC_Hold_Setup_Time
  * @{
  */

#define IS_FSMC_HOLD_TIME(TIME) ((TIME) <= 0xFF)

/**
  * @}
  */

/** @defgroup FSMC_HiZ_Setup_Time FSMC_HiZ_Setup_Time
  * @{
  */

#define IS_FSMC_HIZ_TIME(TIME) ((TIME) <= 0xFF)

/**
  * @}
  */

/** @defgroup FSMC_Interrupt_sources FSMC_Interrupt_sources
  * @{
  */

#define FSMC_IT_RisingEdge                              ((uint32_t)0x00000008)
#define FSMC_IT_Level                                   ((uint32_t)0x00000010)
#define FSMC_IT_FallingEdge                             ((uint32_t)0x00000020)
#define IS_FSMC_IT(IT) ((((IT) & (uint32_t)0xFFFFFFC7) == 0x00000000) && ((IT) != 0x00000000))
#define IS_FSMC_GET_IT(IT) (((IT) == FSMC_IT_RisingEdge) || \
                            ((IT) == FSMC_IT_Level) || \
                            ((IT) == FSMC_IT_FallingEdge))
/**
  * @}
  */

/** @defgroup FSMC_Flags FSMC_Flags
  * @{
  */

#define FSMC_FLAG_RisingEdge                            ((uint32_t)0x00000001)
#define FSMC_FLAG_Level                                 ((uint32_t)0x00000002)
#define FSMC_FLAG_FallingEdge                           ((uint32_t)0x00000004)
#define FSMC_FLAG_FEMPT                                 ((uint32_t)0x00000040)
#define IS_FSMC_GET_FLAG(FLAG) (((FLAG) == FSMC_FLAG_RisingEdge) || \
                                ((FLAG) == FSMC_FLAG_Level) || \
                                ((FLAG) == FSMC_FLAG_FallingEdge) || \
                                ((FLAG) == FSMC_FLAG_FEMPT))

#define IS_FSMC_CLEAR_FLAG(FLAG) ((((FLAG) & (uint32_t)0xFFFFFFF8) == 0x00000000) && ((FLAG) != 0x00000000))

/**
  * @}
  */

/** @defgroup FSMC_LCD_Bank_Sel  FSMC_LCD_Bank_Sel
  * @{
  */
#define FSMC_LCD_BANK1      0
#define FSMC_LCD_BANK2      1
#define FSMC_LCD_BANK3      2
#define FSMC_LCD_BANK4      3
#define IS_FSMC_LCD_BANK(BANK) ((BANK == FSMC_LCD_BANK1) || (BANK == FSMC_LCD_BANK2) || (BANK == FSMC_LCD_BANK3) || (BANK == FSMC_LCD_BANK4))
/**
  * @}
  */

/** @defgroup FSMC_LCD_Horizontal_Polarity  FSMC_LCD_Horizontal_Polarity
  * @{
  */
#define FSMC_LCD_HORIZONTAL_POLARITY_LOW           ((uint32_t)0x00000000U)
#define FSMC_LCD_HORIZONTAL_POLARITY_HIGH          ((uint32_t)0x80000000U)
#define IS_FSMC_LCD_HORIZONTAL_POLARITY(POLARITY)  ((POLARITY == FSMC_LCD_HORIZONTAL_POLARITY_LOW) || (POLARITY == FSMC_LCD_HORIZONTAL_POLARITY_HIGH))
/**
  * @}
  */

/** @defgroup FSMC_LCD_Vertical_Polarity  FSMC_LCD_Vertical_Polarity
  * @{
  */
#define FSMC_LCD_VERTICAL_POLARITY_LOW              ((uint32_t)0x00000000U)
#define FSMC_LCD_VERTICAL_POLARITY_HIGH             ((uint32_t)0x40000000U)
#define IS_FSMC_LCD_VERTICAL_POLARITY(POLARITY)     ((POLARITY == FSMC_LCD_VERTICAL_POLARITY_LOW) || (POLARITY == FSMC_LCD_VERTICAL_POLARITY_HIGH))
/**
  * @}
  */

/** @defgroup FSMC_LCD_Data_Enable_Polarity  FSMC_LCD_Data_Enable_Polarity
  * @{
  */
#define FSMC_LCD_DATA_ENABLE_POLARITY_LOW           ((uint32_t)0x00000000U)
#define FSMC_LCD_DATA_ENABLE_POLARITY_HIGH          ((uint32_t)0x20000000U)
#define IS_FSMC_LCD_DATA_ENABLE_POLARITY(POLARITY)  ((POLARITY == FSMC_LCD_DATA_ENABLE_POLARITY_LOW) || (POLARITY == FSMC_LCD_DATA_ENABLE_POLARITY_HIGH))
/**
  * @}
  */

/** @defgroup FSMC_LCD_Dclk_Active_Negative  FSMC_LCD_Dclk_Active_Negative
  * @{
  */
#define FSMC_LCD_DCLK_ACTIVE_NEGATIVE               ((uint32_t)0x00000000U)
#define FSMC_LCD_DCLK_ACTIVE_POSITIVE               ((uint32_t)0x10000000U)
#define IS_FSMC_LCD_DCLK_ACTIVE(POLARITY)           ((POLARITY == FSMC_LCD_DCLK_ACTIVE_NEGATIVE) || (POLARITY == FSMC_LCD_DCLK_ACTIVE_POSITIVE))
/**
  * @}
  */

/** @defgroup FSMC_LCD_DCLK_Setup_Time  FSMC_LCD_DCLK_Setup_Time
  * @{
  */
#define IS_FSMC_LCD_DCLK_Setup_Time(TIME) ((TIME) <= 0xFF)
/**
  * @}
  */

/** @defgroup FSMC_LCD_Horizontal_Synchronization_Width  FSMC_LCD_Horizontal_Synchronization_Width
  * @{
  */
#define IS_FSMC_LCD_HSW(WIDTH) ((WIDTH) <= 0xFFF)
/**
  * @}
  */

/** @defgroup FSMC_LCD_Vertical_Synchronization_Width  FSMC_LCD_Vertical_Synchronization_Width
  * @{
  */
#define IS_FSMC_LCD_VSH(WIDTH) ((WIDTH) <= 0x7FF)
/**
  * @}
  */

/** @defgroup FSMC_LCD_Accumulated_Horizonal_Backporch  FSMC_LCD_Accumulated_Horizonal_Backporch
  * @{
  */
#define IS_FSMC_LCD_AHBP(WIDTH) ((WIDTH) <= 0xFFF)
/**
  * @}
  */

/** @defgroup FSMC_LCD_Accumulated_Vertical_Backporch  FSMC_LCD_Accumulated_Vertical_Backporch
  * @{
  */
#define IS_FSMC_LCD_AVBP(WIDTH) ((WIDTH) <= 0x7FF)
/**
  * @}
  */

/** @defgroup FSMC_LCD_Accumulated_Active_Width  FSMC_LCD_Accumulated_Active_Width
  * @{
  */
#define IS_FSMC_LCD_AAW(WIDTH) ((WIDTH) <= 0xFFF)
/**
  * @}
  */

/** @defgroup FSMC_LCD_Accumulated_Active_Height  FSMC_LCD_Accumulated_Active_Height
  * @{
  */
#define IS_FSMC_LCD_AAH(WIDTH) ((WIDTH) <= 0x7FF)
/**
  * @}
  */

/** @defgroup FSMC_LCD_Total_Width  FSMC_LCD_Total_Width
  * @{
  */
#define IS_FSMC_LCD_TOTALW(WIDTH) ((WIDTH) <= 0xFFF)
/**
  * @}
  */

/** @defgroup FSMC_LCD_Total_Height  FSMC_LCD_Total_Height
  * @{
  */
#define IS_FSMC_LCD_TOTALH(WIDTH) ((WIDTH) <= 0x7FF)
/**
  * @}
  */

/** @defgroup FSMC_LCD_Auto_Por  FSMC_LCD_Auto_Por
  * @{
  */
#define FSMC_LCD_AUTO_POR_DISABLE                   ((uint32_t)0x00000000U)
#define FSMC_LCD_AUTO_POR_ENABLE                    ((uint32_t)0x80000000U)
#define IS_FSMC_LCD_AUTO_POR(STATE)                 ((STATE == FSMC_LCD_AUTO_POR_DISABLE) || (STATE == FSMC_LCD_AUTO_POR_ENABLE))
/**
  * @}
  */

/** @defgroup FSMC_LCD_Auto_Writing_Data   FSMC_LCD_Auto_Writing_Data
  * @{
  */
#define IS_FSMC_LCD_POR_DATA(WIDTH) ((WIDTH) <= 0xFFFF)
/**
  * @}
  */

/** @defgroup FSMC_LCD_Panel   FSMC_LCD_Panel
  * @{
  */
#define FSMC_LCD_DISABLE                            ((uint32_t)0x00000000U)
#define FSMC_LCD_ENABLE                             ((uint32_t)0x00000001U)
#define IS_FSMC_LCD_PANEL(STATE)                    ((STATE == FSMC_LCD_DISABLE) || (STATE == FSMC_LCD_ENABLE))
/**
  * @}
  */

/** @defgroup FSMC_NADV_Pol   FSMC_NADV_Pol
  * @{
  */
#define FSMC_NADV_POLARITY_LOW             0x00000000U
#define FSMC_NADV_POLARITY_HIGH            0x00000002U
/**
  * @}
  */
  
/**
  * @}
  */

/**
  * @}
  */

/** @defgroup FSMC_Exported_Macros FSMC_Exported_Macros
  * @{
  */

/**
  * @}
  */

/** @defgroup FSMC_Exported_Functions FSMC_Exported_Functions
  * @{
  */

void FSMC_NORSRAMDeInit(uint32_t FSMC_Bank);
void FSMC_NANDDeInit(uint32_t FSMC_Bank);
void FSMC_PCCARDDeInit(void);
void FSMC_NORSRAMInit(FSMC_NORSRAMInitTypeDef* FSMC_NORSRAMInitStruct);
void FSMC_NANDInit(FSMC_NANDInitTypeDef* FSMC_NANDInitStruct);
void FSMC_PCCARDInit(FSMC_PCCARDInitTypeDef* FSMC_PCCARDInitStruct);
void FSMC_NORSRAMStructInit(FSMC_NORSRAMInitTypeDef* FSMC_NORSRAMInitStruct);
void FSMC_NANDStructInit(FSMC_NANDInitTypeDef* FSMC_NANDInitStruct);
void FSMC_PCCARDStructInit(FSMC_PCCARDInitTypeDef* FSMC_PCCARDInitStruct);
void FSMC_NORSRAMCmd(uint32_t FSMC_Bank, FunctionalState NewState);
void FSMC_NANDCmd(uint32_t FSMC_Bank, FunctionalState NewState);
void FSMC_PCCARDCmd(FunctionalState NewState);
void FSMC_NANDECCCmd(uint32_t FSMC_Bank, FunctionalState NewState);
uint32_t FSMC_GetECC(uint32_t FSMC_Bank);
void FSMC_ITConfig(uint32_t FSMC_Bank, uint32_t FSMC_IT, FunctionalState NewState);
FlagStatus FSMC_GetFlagStatus(uint32_t FSMC_Bank, uint32_t FSMC_FLAG);
void FSMC_ClearFlag(uint32_t FSMC_Bank, uint32_t FSMC_FLAG);
ITStatus FSMC_GetITStatus(uint32_t FSMC_Bank, uint32_t FSMC_IT);
void FSMC_ClearITPendingBit(uint32_t FSMC_Bank, uint32_t FSMC_IT);

#ifdef __cplusplus
}
#endif

#endif /*__HK32F103XXXXA_FSMC_H */
/**
  * @}
  */

/**
  * @}
  */


