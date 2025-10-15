/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  hk32f103xxxxa_eval_fsmc_nand.h
* @brief:     hk32f103xxxxa_dma configuration file.
*             The file is the unique include file that the application programmer
*             is using in the C source code, it is a patch file.
* @author:    AE Team
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HK32AUTO39A3XEVAL_FSMC_NAND_H
#define __HK32AUTO39A3XEVAL_FSMC_NAND_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "hk32f103xxxxa.h"

/** @addtogroup Utilities
  * @{
  */

/** @addtogroup HK32_EVAL
  * @{
  */

/** @addtogroup HK32AUTO39A3XEVAL
  * @{
  */

/** @addtogroup HK32F103xxxxA_EVAL_FSMC_NAND
  * @{
  */

/** @defgroup HK32F103xxxxA_EVAL_FSMC_NAND_Exported_Types
  * @{
  */
typedef struct
{
    uint8_t Maker_ID;
    uint8_t Device_ID;
    uint8_t Third_ID;
    uint8_t Fourth_ID;
} NAND_IDTypeDef;

typedef struct
{
    uint16_t Zone;
    uint16_t Block;
    uint16_t Page;
} NAND_ADDRESS;
/**
  * @}
  */

/** @defgroup HK32F103xxxxA_EVAL_FSMC_NAND_Exported_Constants
  * @{
  */
/**
  * @brief  NAND Area definition  for HK32F103xxxxA-EVAL Board RevD
  */
#define CMD_AREA                   (uint32_t)(1<<16)  /* A16 = CLE  high */
#define ADDR_AREA                  (uint32_t)(1<<17)  /* A17 = ALE high */

#define DATA_AREA                  ((uint32_t)0x00000000)

/**
  * @brief  FSMC NAND memory command
  */
#define NAND_CMD_AREA_A            ((uint8_t)0x00)
#define NAND_CMD_AREA_B            ((uint8_t)0x01)
#define NAND_CMD_AREA_C            ((uint8_t)0x50)
#define NAND_CMD_AREA_TRUE1        ((uint8_t)0x30)

#define NAND_CMD_WRITE0            ((uint8_t)0x80)
#define NAND_CMD_WRITE_TRUE1       ((uint8_t)0x10)

#define NAND_CMD_ERASE0            ((uint8_t)0x60)
#define NAND_CMD_ERASE1            ((uint8_t)0xD0)

#define NAND_CMD_READID            ((uint8_t)0x90)
#define NAND_CMD_STATUS            ((uint8_t)0x70)
#define NAND_CMD_LOCK_STATUS       ((uint8_t)0x7A)
#define NAND_CMD_RESET             ((uint8_t)0xFF)

/**
  * @brief  NAND memory status
  */
#define NAND_VALID_ADDRESS         ((uint32_t)0x00000100)
#define NAND_INVALID_ADDRESS       ((uint32_t)0x00000200)
#define NAND_TIMEOUT_ERROR         ((uint32_t)0x00000400)
#define NAND_BUSY                  ((uint32_t)0x00000000)
#define NAND_ERROR                 ((uint32_t)0x00000001)
#define NAND_READY                 ((uint32_t)0x00000040)

/**
  * @brief  FSMC NAND memory parameters
  */
#define NAND_PAGE_SIZE             ((uint16_t)0x0800) /* 2048 bytes per page w/o Spare Area */
#define NAND_BLOCK_SIZE            ((uint16_t)0x0040) /* 64x64 bytes pages per block */
#define NAND_ZONE_SIZE             ((uint16_t)0x0400) /* 1024 Block per zone */
#define NAND_SPARE_AREA_SIZE       ((uint16_t)0x0040) /* last 64 bytes as spare area */
#define NAND_MAX_ZONE              ((uint16_t)0x0001) /* 1 zones of 1024 block */

/**
  * @brief  FSMC NAND memory address computation
  */
#define ADDR_1st_CYCLE(ADDR)       (uint8_t)((ADDR)& 0xFF)               /* 1st addressing cycle */
#define ADDR_2nd_CYCLE(ADDR)       (uint8_t)(((ADDR)& 0xFF00) >> 8)      /* 2nd addressing cycle */
#define ADDR_3rd_CYCLE(ADDR)       (uint8_t)(((ADDR)& 0xFF0000) >> 16)   /* 3rd addressing cycle */
#define ADDR_4th_CYCLE(ADDR)       (uint8_t)(((ADDR)& 0xFF000000) >> 24) /* 4th addressing cycle */
/**
  * @}
  */

/** @defgroup HK32F103xxxxA_EVAL_FSMC_NAND_Exported_Macros
  * @{
  */
#define NAND_USE_BANK2          2
#define NAND_USE_BANK3          3
#define NAND_USE_BANK_NUMBER    NAND_USE_BANK2  // Only set number: 2 or 3 (2=NAND_USE_BANK2 | 3=NAND_USE_BANK3)

#define NAND_USE_NWAIT_ENABLE   1
#define NAND_USE_INT2_ENABLE    0

#if (NAND_USE_BANK_NUMBER == NAND_USE_BANK2)
/*NCE2*/
#define      NAND_CS_CLK                RCC_APB2Periph_GPIOD
#define      NAND_CS_PORT               GPIOD
#define      NAND_CS_PIN                GPIO_Pin_7
#else
/*NCE3*/
#define      NAND_CS_CLK                RCC_APB2Periph_GPIOC
#define      NAND_CS_PORT               GPIOC
#define      NAND_CS_PIN                GPIO_Pin_12
#endif


//NWE
#define      NAND_WR_CLK                RCC_APB2Periph_GPIOD
#define      NAND_WR_PORT               GPIOD
#define      NAND_WR_PIN                GPIO_Pin_5

//NOE
#define      NAND_RD_CLK                RCC_APB2Periph_GPIOD
#define      NAND_RD_PORT               GPIOD
#define      NAND_RD_PIN                GPIO_Pin_4

//NWAIT
#define      NAND_NWAIT_CLK             RCC_APB2Periph_GPIOD
#define      NAND_NWAIT_PORT            GPIOD
#define      NAND_NWAIT_PIN             GPIO_Pin_6


//INT2
#define      NAND_INT2_CLK              RCC_APB2Periph_GPIOB
#define      NAND_INT2_PORT             GPIOB
#define      NAND_INT2_PIN              GPIO_Pin_10

//data
#define      NAND_D0_CLK                RCC_APB2Periph_GPIOD
#define      NAND_D0_PORT               GPIOD
#define      NAND_D0_PIN                GPIO_Pin_14

#define      NAND_D1_CLK                RCC_APB2Periph_GPIOD
#define      NAND_D1_PORT               GPIOD
#define      NAND_D1_PIN                GPIO_Pin_15

#define      NAND_D2_CLK                RCC_APB2Periph_GPIOD
#define      NAND_D2_PORT               GPIOD
#define      NAND_D2_PIN                GPIO_Pin_0

#define      NAND_D3_CLK                RCC_APB2Periph_GPIOD
#define      NAND_D3_PORT               GPIOD
#define      NAND_D3_PIN                GPIO_Pin_1

#define      NAND_D4_CLK                RCC_APB2Periph_GPIOE
#define      NAND_D4_PORT               GPIOE
#define      NAND_D4_PIN                GPIO_Pin_7

#define      NAND_D5_CLK                RCC_APB2Periph_GPIOE
#define      NAND_D5_PORT               GPIOE
#define      NAND_D5_PIN                GPIO_Pin_8

#define      NAND_D6_CLK                RCC_APB2Periph_GPIOE
#define      NAND_D6_PORT               GPIOE
#define      NAND_D6_PIN                GPIO_Pin_9

#define      NAND_D7_CLK                RCC_APB2Periph_GPIOE
#define      NAND_D7_PORT               GPIOE
#define      NAND_D7_PIN                GPIO_Pin_10

#define      NAND_A16_CLK               RCC_APB2Periph_GPIOD
#define      NAND_A16_PORT              GPIOD
#define      NAND_A16_PIN               GPIO_Pin_11

#define      NAND_A17_CLK               RCC_APB2Periph_GPIOD
#define      NAND_A17_PORT              GPIOD
#define      NAND_A17_PIN               GPIO_Pin_12
/**
  * @}
  */

/** @defgroup HK32F103xxxxA_EVAL_FSMC_NAND_Exported_Functions
  * @{
  */
void NAND_Init(void);
void NAND_ReadID(NAND_IDTypeDef* NAND_ID);
uint32_t NAND_WriteSmallPage(uint8_t *pBuffer, NAND_ADDRESS Address, uint32_t NumPageToWrite);
uint32_t NAND_ReadSmallPage (uint8_t *pBuffer, NAND_ADDRESS Address, uint32_t NumPageToRead);
uint32_t NAND_WriteSpareArea(uint8_t *pBuffer, NAND_ADDRESS Address, uint32_t NumSpareAreaTowrite);
uint32_t NAND_ReadSpareArea(uint8_t *pBuffer, NAND_ADDRESS Address, uint32_t NumSpareAreaToRead);
uint32_t NAND_EraseBlock(NAND_ADDRESS Address);
uint32_t NAND_Reset(void);
uint32_t NAND_GetStatus(void);
uint32_t NAND_ReadStatus(void);
uint32_t NAND_AddressIncrement(NAND_ADDRESS* Address);

#ifdef __cplusplus
}
#endif

#endif /* __HK32F103xxxxA_EVAL_FSMC_NAND_H */
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

