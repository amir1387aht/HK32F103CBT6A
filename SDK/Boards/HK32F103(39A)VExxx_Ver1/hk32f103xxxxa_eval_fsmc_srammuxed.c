/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  hk3239a_eval_fsmc_srammuxed.c
* @brief:     This file provides a set of functions needed to drive the
*             EM681FV16BU-55LF SRAM memory mounted on HK32F103xxxxA-EVAL board.
*             this file used in the case of address line and data line multiplexed
* @author:    AE Team
* @version:   V1.0.0/2023-11-14
*             1.Initial version
* @log:
*******************************************************************************/ 

#include "hk32f103xxxxa.h"
#include "hk32f103xxxxa_eval_fsmc_srammuxed.h"


//uint32_t sram[0x40000] __attribute__((at(0X60000000)));

/**
 * @brief  配置SRAM GPIO
 * @param  无
 * @retval 无
 */
void SRAMMUXED_FSMC_GPIO_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    /* 使能FSMC对应相应管脚时钟*/
    RCC_APB2PeriphClockCmd (SRAM_CS_CLK | SRAM_WR_CLK | SRAM_RD_CLK | SRAM_NBL0_CLK | SRAM_NBL1_CLK | SRAM_NADV_CLK |
                            SRAM_D0_CLK | SRAM_D1_CLK |  SRAM_D2_CLK |
                            SRAM_D3_CLK | SRAM_D4_CLK | SRAM_D5_CLK |
                            SRAM_D6_CLK | SRAM_D7_CLK | SRAM_D8_CLK |
                            SRAM_D9_CLK | SRAM_D10_CLK | SRAM_D11_CLK |
                            SRAM_D12_CLK | SRAM_D13_CLK | SRAM_D14_CLK | SRAM_D15_CLK |
                            SRAM_A16_CLK | SRAM_A17_CLK | SRAM_A18_CLK, ENABLE );
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
    GPIO_InitStructure.GPIO_Pin = SRAM_A16_PIN;
    GPIO_Init ( SRAM_A16_PORT, & GPIO_InitStructure );
    GPIO_InitStructure.GPIO_Pin = SRAM_A17_PIN;
    GPIO_Init ( SRAM_A17_PORT, & GPIO_InitStructure );
    GPIO_InitStructure.GPIO_Pin = SRAM_A18_PIN;
    GPIO_Init ( SRAM_A18_PORT, & GPIO_InitStructure );
    /* 配置FSMC相对应的控制线
     * FSMC_NOE   :LCD-RD
     * FSMC_NWE   :LCD-WR
     * FSMC_NE1   :LCD-CS
     * FSMC_NBL0
     * FSMC_NBL1
     */
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
    GPIO_InitStructure.GPIO_Pin = SRAM_NADV_PIN;
    GPIO_Init ( SRAM_NADV_PORT, & GPIO_InitStructure );
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6;
    GPIO_Init ( GPIOE, & GPIO_InitStructure );
}
/**
* @brief  初始化SRAM模块
* @param  无
* @retval 无
*/
void SRAMMUXED_FSMC_Init(void)
{
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FSMC, ENABLE);
    FSMC_NORSRAMInitTypeDef FSMC_NORSRAMInitStruct;
    FSMC_NORSRAMTimingInitTypeDef FSMC_ReadWriteTimingStruct;
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FSMC, ENABLE);
    /* FSMC_NADV_POLARITY_LOW-->电路中需要加反相器
       FSMC_NADV_POLARITY_HIGH --> NADV直接和MC74HC573ADT连接
	   MC74HC573ADT的LE为低表示锁存，FSMC的异步模式B\C\D当NADV为低时传输地址，为高时传输数据*/
    FSMC_NORSRAMInitStruct.NadvPol = FSMC_NADV_POLARITY_HIGH;
    FSMC_NORSRAMInitStruct.FSMC_AsynchronousWait = FSMC_AsynchronousWait_Disable;
    FSMC_NORSRAMInitStruct.FSMC_Bank = FSMC_Bank1_NORSRAM1;
    FSMC_NORSRAMInitStruct.FSMC_BurstAccessMode = FSMC_BurstAccessMode_Disable;
    FSMC_NORSRAMInitStruct.FSMC_DataAddressMux = FSMC_DataAddressMux_Enable;
    FSMC_NORSRAMInitStruct.FSMC_ExtendedMode = FSMC_ExtendedMode_Disable;
    FSMC_NORSRAMInitStruct.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b;
    FSMC_NORSRAMInitStruct.FSMC_MemoryType = FSMC_MemoryType_PSRAM;
    FSMC_NORSRAMInitStruct.FSMC_ReadWriteTimingStruct = &FSMC_ReadWriteTimingStruct;
    FSMC_NORSRAMInitStruct.FSMC_WaitSignal = FSMC_WaitSignal_Disable;
    FSMC_NORSRAMInitStruct.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState;
    FSMC_NORSRAMInitStruct.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low;
    FSMC_NORSRAMInitStruct.FSMC_WrapMode = FSMC_WrapMode_Disable;
    FSMC_NORSRAMInitStruct.FSMC_WriteBurst = FSMC_WriteBurst_Disable;
    FSMC_NORSRAMInitStruct.FSMC_WriteOperation = FSMC_WriteOperation_Enable;
    FSMC_NORSRAMInitStruct.FSMC_WriteTimingStruct = NULL;
    FSMC_ReadWriteTimingStruct.FSMC_AccessMode = FSMC_AccessMode_A;
    FSMC_ReadWriteTimingStruct.FSMC_AddressHoldTime = 3;
    FSMC_ReadWriteTimingStruct.FSMC_AddressSetupTime = 2;
    FSMC_ReadWriteTimingStruct.FSMC_BusTurnAroundDuration = 2;
    FSMC_ReadWriteTimingStruct.FSMC_CLKDivision = 1;
    FSMC_ReadWriteTimingStruct.FSMC_DataLatency = 15;
    FSMC_ReadWriteTimingStruct.FSMC_DataSetupTime = 2;
    FSMC_NORSRAMInit(&FSMC_NORSRAMInitStruct);
    FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM1, ENABLE);
}
