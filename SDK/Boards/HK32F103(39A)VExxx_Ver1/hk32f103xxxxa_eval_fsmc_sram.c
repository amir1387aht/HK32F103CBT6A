/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  hk32f103xxxxa_eval_fsmc_sram.c
* @brief:     This file provides a set of functions needed to drive the
*             EM681FV16BU-55LF SRAM memory mounted on HK32F103xxxxA-EVAL board.
* @author:    AE Team
* @version:   V1.0.0/2023-11-14
*             1.Initial version
* @log:
*******************************************************************************/ 

/* Includes ------------------------------------------------------------------*/
#include "hk32f103xxxxa_eval_fsmc_sram.h"

/** @addtogroup Utilities
  * @{
  */

/** @addtogroup HK32_EVAL
  * @{
  */

/** @addtogroup HK32F103xxxxA_EVAL
  * @{
  */

/** @addtogroup HK32F103xxxxA_EVAL_FSMC_SRAM
  * @brief      This file provides a set of functions needed to drive the
  *             IS61WV51216BLL SRAM memory mounted on HK32F103xxxxA-EVAL board.
  * @{
  */

/** @defgroup HK32F103xxxxA_EVAL_FSMC_SRAM_Private_Types
  * @{
  */
/**
  * @}
  */


/** @defgroup HK32F103xxxxA_EVAL_FSMC_SRAM_Private_Defines
  * @{
  */
/**
  * @brief  FSMC Bank 1 NOR/SRAM3
  */
#define Bank1_SRAM3_ADDR    ((uint32_t)0x68000000)
/**
  * @}
  */


/** @defgroup HK32F103xxxxA_EVAL_FSMC_SRAM_Private_Macros
  * @{
  */
/**
  * @}
  */


/** @defgroup HK32F103xxxxA_EVAL_FSMC_SRAM_Private_Variables
  * @{
  */
/**
  * @}
  */


/** @defgroup HK32F103xxxxA_EVAL_FSMC_SRAM_Private_Function_Prototypes
  * @{
  */
/**
  * @}
  */


/** @defgroup HK32F103xxxxA_EVAL_FSMC_SRAM_Private_Functions
  * @{
  */

/**
  * @brief  Configures the FSMC and GPIOs to interface with the SRAM memory.
  *         This function must be called before any write/read operation
  *         on the SRAM.
  * @param  None
  * @retval None
  */
void SRAM_Init(void)
{
    FSMC_NORSRAMInitTypeDef  FSMC_NORSRAMInitStructure;
    FSMC_NORSRAMTimingInitTypeDef  p;
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    SET_BIT(AFIO->MAPR2, AFIO_MAPR2_FSMC_100PIN_REMAP);
    /* 使能FSMC对应相应管脚时钟*/
    RCC_APB2PeriphClockCmd (SRAM_CS_CLK | SRAM_WR_CLK | SRAM_RD_CLK | SRAM_NBL0_CLK | SRAM_NBL1_CLK |
                            SRAM_D0_CLK | SRAM_D1_CLK |  SRAM_D2_CLK |
                            SRAM_D3_CLK | SRAM_D4_CLK | SRAM_D5_CLK |
                            SRAM_D6_CLK | SRAM_D7_CLK | SRAM_D8_CLK |
                            SRAM_D9_CLK | SRAM_D10_CLK | SRAM_D11_CLK |
                            SRAM_D12_CLK | SRAM_D13_CLK | SRAM_D14_CLK | SRAM_D15_CLK |
                            SRAM_A0_CLK | SRAM_A1_CLK | SRAM_A2_CLK | SRAM_A3_CLK |
                            SRAM_A4_CLK | SRAM_A5_CLK | SRAM_A6_CLK | SRAM_A7_CLK |
                            SRAM_A8_CLK | SRAM_A9_CLK | SRAM_A10_CLK | SRAM_A11_CLK |
                            SRAM_A12_CLK | SRAM_A13_CLK | SRAM_A14_CLK | SRAM_A15_CLK |
                            SRAM_A16_CLK | SRAM_A17_CLK | SRAM_A18_CLK | SRAM_A19_CLK, ENABLE );
    /* 配置FSMC相对应的数据线,FSMC-D0~D15 */
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Pin = SRAM_D0_PIN;
    GPIO_Init ( SRAM_D0_PORT, & GPIO_InitStructure );
    GPIO_InitStructure.GPIO_Pin = SRAM_D1_PIN;
    GPIO_Init ( SRAM_D1_PORT, & GPIO_InitStructure );
    GPIO_InitStructure.GPIO_Pin = SRAM_D2_PIN;
    GPIO_Init ( SRAM_D2_PORT, & GPIO_InitStructure );
    GPIO_InitStructure.GPIO_Pin = SRAM_D3_PIN;
    GPIO_Init ( SRAM_D3_PORT, & GPIO_InitStructure );
    GPIO_InitStructure.GPIO_Pin = SRAM_D4_PIN;
    GPIO_Init ( SRAM_D4_PORT, & GPIO_InitStructure );
    GPIO_InitStructure.GPIO_Pin = SRAM_D5_PIN;
    GPIO_Init ( SRAM_D5_PORT, & GPIO_InitStructure );
    GPIO_InitStructure.GPIO_Pin = SRAM_D6_PIN;
    GPIO_Init ( SRAM_D6_PORT, & GPIO_InitStructure );
    GPIO_InitStructure.GPIO_Pin = SRAM_D7_PIN;
    GPIO_Init ( SRAM_D7_PORT, & GPIO_InitStructure );
    GPIO_InitStructure.GPIO_Pin = SRAM_D8_PIN;
    GPIO_Init ( SRAM_D8_PORT, & GPIO_InitStructure );
    GPIO_InitStructure.GPIO_Pin = SRAM_D9_PIN;
    GPIO_Init ( SRAM_D9_PORT, & GPIO_InitStructure );
    GPIO_InitStructure.GPIO_Pin = SRAM_D10_PIN;
    GPIO_Init ( SRAM_D10_PORT, & GPIO_InitStructure );
    GPIO_InitStructure.GPIO_Pin = SRAM_D11_PIN;
    GPIO_Init ( SRAM_D11_PORT, & GPIO_InitStructure );
    GPIO_InitStructure.GPIO_Pin = SRAM_D12_PIN;
    GPIO_Init ( SRAM_D12_PORT, & GPIO_InitStructure );
    GPIO_InitStructure.GPIO_Pin = SRAM_D13_PIN;
    GPIO_Init ( SRAM_D13_PORT, & GPIO_InitStructure );
    GPIO_InitStructure.GPIO_Pin = SRAM_D14_PIN;
    GPIO_Init ( SRAM_D14_PORT, & GPIO_InitStructure );
    GPIO_InitStructure.GPIO_Pin = SRAM_D15_PIN;
    GPIO_Init ( SRAM_D15_PORT, & GPIO_InitStructure );
    /* A0~A19 */
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Pin = SRAM_A0_PIN;
    GPIO_Init ( SRAM_A0_PORT, & GPIO_InitStructure );
    GPIO_InitStructure.GPIO_Pin = SRAM_A1_PIN;
    GPIO_Init ( SRAM_A1_PORT, & GPIO_InitStructure );
    GPIO_InitStructure.GPIO_Pin = SRAM_A2_PIN;
    GPIO_Init ( SRAM_A2_PORT, & GPIO_InitStructure );
    GPIO_InitStructure.GPIO_Pin = SRAM_A3_PIN;
    GPIO_Init ( SRAM_A3_PORT, & GPIO_InitStructure );
    GPIO_InitStructure.GPIO_Pin = SRAM_A4_PIN;
    GPIO_Init ( SRAM_A4_PORT, & GPIO_InitStructure );
    GPIO_InitStructure.GPIO_Pin = SRAM_A5_PIN;
    GPIO_Init ( SRAM_A5_PORT, & GPIO_InitStructure );
    GPIO_InitStructure.GPIO_Pin = SRAM_A6_PIN;
    GPIO_Init ( SRAM_A6_PORT, & GPIO_InitStructure );
    GPIO_InitStructure.GPIO_Pin = SRAM_A7_PIN;
    GPIO_Init ( SRAM_A7_PORT, & GPIO_InitStructure );
    GPIO_InitStructure.GPIO_Pin = SRAM_A8_PIN;
    GPIO_Init ( SRAM_A8_PORT, & GPIO_InitStructure );
    GPIO_InitStructure.GPIO_Pin = SRAM_A9_PIN;
    GPIO_Init ( SRAM_A9_PORT, & GPIO_InitStructure );
    GPIO_InitStructure.GPIO_Pin = SRAM_A10_PIN;
    GPIO_Init ( SRAM_A10_PORT, & GPIO_InitStructure );
    GPIO_InitStructure.GPIO_Pin = SRAM_A11_PIN;
    GPIO_Init ( SRAM_A11_PORT, & GPIO_InitStructure );
    GPIO_InitStructure.GPIO_Pin = SRAM_A12_PIN;
    GPIO_Init ( SRAM_A12_PORT, & GPIO_InitStructure );
    GPIO_InitStructure.GPIO_Pin = SRAM_A13_PIN;
    GPIO_Init ( SRAM_A13_PORT, & GPIO_InitStructure );
    GPIO_InitStructure.GPIO_Pin = SRAM_A14_PIN;
    GPIO_Init ( SRAM_A14_PORT, & GPIO_InitStructure );
    GPIO_InitStructure.GPIO_Pin = SRAM_A15_PIN;
    GPIO_Init ( SRAM_A15_PORT, & GPIO_InitStructure );
    GPIO_InitStructure.GPIO_Pin = SRAM_A16_PIN;
    GPIO_Init ( SRAM_A16_PORT, & GPIO_InitStructure );
    GPIO_InitStructure.GPIO_Pin = SRAM_A17_PIN;
    GPIO_Init ( SRAM_A17_PORT, & GPIO_InitStructure );
    GPIO_InitStructure.GPIO_Pin = SRAM_A18_PIN;
    GPIO_Init ( SRAM_A18_PORT, & GPIO_InitStructure );
    GPIO_InitStructure.GPIO_Pin = SRAM_A19_PIN;
    GPIO_Init ( SRAM_A19_PORT, & GPIO_InitStructure );
    /* 配置FSMC相对应的控制线
     * FSMC_NOE   :LCD-RD
     * FSMC_NWE   :LCD-WR
     * FSMC_NE3   :LCD-CS
     * FSMC_NBL0
     * FSMC_NBL1
     */
    //GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Pin = SRAM_RD_PIN;
    GPIO_Init (SRAM_RD_PORT, & GPIO_InitStructure );
    GPIO_InitStructure.GPIO_Pin = SRAM_WR_PIN;
    GPIO_Init (SRAM_WR_PORT, & GPIO_InitStructure );
    GPIO_InitStructure.GPIO_Pin = SRAM_CS_PIN;
    GPIO_Init ( SRAM_CS_PORT, & GPIO_InitStructure );
    GPIO_InitStructure.GPIO_Pin = SRAM_NBL0_PIN;
    GPIO_Init ( SRAM_NBL0_PORT, & GPIO_InitStructure );
    GPIO_InitStructure.GPIO_Pin = SRAM_NBL1_PIN;
    GPIO_Init ( SRAM_NBL1_PORT, & GPIO_InitStructure );
    /*-- FSMC Configuration ------------------------------------------------------*/
    p.FSMC_AddressSetupTime = 0;
    p.FSMC_AddressHoldTime = 0;
    p.FSMC_DataSetupTime = 2;
    p.FSMC_BusTurnAroundDuration = 0;
    p.FSMC_CLKDivision = 1;
    p.FSMC_DataLatency = 2;
    p.FSMC_AccessMode = FSMC_AccessMode_A;
    FSMC_NORSRAMInitStructure.FSMC_Bank = FSMC_Bank1_NORSRAM3;
    FSMC_NORSRAMInitStructure.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable;
    FSMC_NORSRAMInitStructure.FSMC_MemoryType = FSMC_MemoryType_SRAM;
    FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b;
    FSMC_NORSRAMInitStructure.FSMC_BurstAccessMode = FSMC_BurstAccessMode_Disable;
    FSMC_NORSRAMInitStructure.FSMC_AsynchronousWait = FSMC_AsynchronousWait_Disable;
    FSMC_NORSRAMInitStructure.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low;
    FSMC_NORSRAMInitStructure.FSMC_WrapMode = FSMC_WrapMode_Disable;
    FSMC_NORSRAMInitStructure.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState;
    FSMC_NORSRAMInitStructure.FSMC_WriteOperation = FSMC_WriteOperation_Enable;
    FSMC_NORSRAMInitStructure.FSMC_WaitSignal = FSMC_WaitSignal_Disable;
    FSMC_NORSRAMInitStructure.FSMC_ExtendedMode = FSMC_ExtendedMode_Disable;
    FSMC_NORSRAMInitStructure.FSMC_WriteBurst = FSMC_WriteBurst_Disable;
    FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct = &p;
    FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct = &p;
    FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure);
    /*!< Enable FSMC Bank1_SRAM Bank */
    FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM3, ENABLE);
}

/**
  * @brief  Writes a Half-word buffer to the FSMC SRAM memory.
  * @param  pBuffer : pointer to buffer.
  * @param  WriteAddr : SRAM memory internal address from which the data will be
  *         written.
  * @param  NumHalfwordToWrite : number of half-words to write.
  * @retval None
  */
void SRAM_WriteBuffer(uint16_t* pBuffer, uint32_t WriteAddr, uint32_t NumHalfwordToWrite)
{
    /*!< while there is data to write */
	for (; NumHalfwordToWrite != 0; NumHalfwordToWrite--) 
    {
        /*!< Transfer data to the memory */
        *(uint16_t *) (Bank1_SRAM3_ADDR + WriteAddr) = *pBuffer++;
        /*!< Increment the address*/
        WriteAddr += 2;
    }
}

/**
  * @brief  Reads a block of data from the FSMC SRAM memory.
  * @param  pBuffer : pointer to the buffer that receives the data read from the
  *         SRAM memory.
  * @param  ReadAddr : SRAM memory internal address to read from.
  * @param  NumHalfwordToRead : number of half-words to read.
  * @retval None
  */
void SRAM_ReadBuffer(uint16_t* pBuffer, uint32_t ReadAddr, uint32_t NumHalfwordToRead)
{
    /*!< while there is data to read */
	for (; NumHalfwordToRead != 0; NumHalfwordToRead--) 
    {
        /*!< Read a half-word from the memory */
        *pBuffer++ = *(__IO uint16_t*) (Bank1_SRAM3_ADDR + ReadAddr);
        /*!< Increment the address*/
        ReadAddr += 2;
    }
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

/**
  * @}
  */

/**
  * @}
  */

