/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  hk32f103xxxxa_eval_fsmc_sram.h
* @brief:     hk32f103xxxxa_dma configuration file.
*             The file is the unique include file that the application programmer
*             is using in the C source code, it is a patch file.
* @author:    AE Team
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HK32F103xxxxA_EVAL_FSMC_SRAM_H
#define __HK32F103xxxxA_EVAL_FSMC_SRAM_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "hk32f103xxxxa_conf.h"

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
  * @{
  */  

/** @defgroup HK32F103xxxxA_EVAL_FSMC_SRAM_Exported_Types
  * @{
  */
/**
  * @}
  */
  
/** @defgroup HK32F103xxxxA_EVAL_FSMC_SRAM_Exported_Constants
  * @{
  */ 
/**
  * @}
  */ 
  
/** @defgroup HK32F103xxxxA_EVAL_FSMC_SRAM_Exported_Macros
  * @{
  */ 
//NCE3
#define      SRAM_CS_CLK                RCC_APB2Periph_GPIOD   
#define      SRAM_CS_PORT               GPIOD
#define      SRAM_CS_PIN                GPIO_Pin_2
	
//NWE
#define      SRAM_WR_CLK                RCC_APB2Periph_GPIOD   
#define      SRAM_WR_PORT               GPIOD
#define      SRAM_WR_PIN                GPIO_Pin_5
	
//NOE
#define      SRAM_RD_CLK                RCC_APB2Periph_GPIOD   
#define      SRAM_RD_PORT               GPIOD
#define      SRAM_RD_PIN                GPIO_Pin_4
	
//NBL0
#define      SRAM_NBL0_CLK              RCC_APB2Periph_GPIOE   
#define      SRAM_NBL0_PORT             GPIOE
#define      SRAM_NBL0_PIN              GPIO_Pin_0

//NBL1
#define      SRAM_NBL1_CLK              RCC_APB2Periph_GPIOE   
#define      SRAM_NBL1_PORT             GPIOE
#define      SRAM_NBL1_PIN              GPIO_Pin_1

//data
#define      SRAM_D0_CLK                RCC_APB2Periph_GPIOD   
#define      SRAM_D0_PORT               GPIOD
#define      SRAM_D0_PIN                GPIO_Pin_14
	
#define      SRAM_D1_CLK                RCC_APB2Periph_GPIOD   
#define      SRAM_D1_PORT               GPIOD
#define      SRAM_D1_PIN                GPIO_Pin_15
	
#define      SRAM_D2_CLK                RCC_APB2Periph_GPIOD   
#define      SRAM_D2_PORT               GPIOD
#define      SRAM_D2_PIN                GPIO_Pin_0
	
#define      SRAM_D3_CLK                RCC_APB2Periph_GPIOD  
#define      SRAM_D3_PORT               GPIOD
#define      SRAM_D3_PIN                GPIO_Pin_1
	
#define      SRAM_D4_CLK                RCC_APB2Periph_GPIOE   
#define      SRAM_D4_PORT               GPIOE
#define      SRAM_D4_PIN                GPIO_Pin_7
	
#define      SRAM_D5_CLK                RCC_APB2Periph_GPIOE   
#define      SRAM_D5_PORT               GPIOE
#define      SRAM_D5_PIN                GPIO_Pin_8
	
#define      SRAM_D6_CLK                RCC_APB2Periph_GPIOE   
#define      SRAM_D6_PORT               GPIOE
#define      SRAM_D6_PIN                GPIO_Pin_9
	
#define      SRAM_D7_CLK                RCC_APB2Periph_GPIOE  
#define      SRAM_D7_PORT               GPIOE
#define      SRAM_D7_PIN                GPIO_Pin_10
	
#define      SRAM_D8_CLK                RCC_APB2Periph_GPIOE   
#define      SRAM_D8_PORT               GPIOE
#define      SRAM_D8_PIN                GPIO_Pin_11
	
#define      SRAM_D9_CLK                RCC_APB2Periph_GPIOE   
#define      SRAM_D9_PORT               GPIOE
#define      SRAM_D9_PIN                GPIO_Pin_12
	
#define      SRAM_D10_CLK                RCC_APB2Periph_GPIOE   
#define      SRAM_D10_PORT               GPIOE
#define      SRAM_D10_PIN                GPIO_Pin_13
	
#define      SRAM_D11_CLK                RCC_APB2Periph_GPIOE   
#define      SRAM_D11_PORT               GPIOE
#define      SRAM_D11_PIN                GPIO_Pin_14
	
#define      SRAM_D12_CLK                RCC_APB2Periph_GPIOE   
#define      SRAM_D12_PORT               GPIOE
#define      SRAM_D12_PIN                GPIO_Pin_15
	
#define      SRAM_D13_CLK                RCC_APB2Periph_GPIOD   
#define      SRAM_D13_PORT               GPIOD
#define      SRAM_D13_PIN                GPIO_Pin_8
	
#define      SRAM_D14_CLK                RCC_APB2Periph_GPIOD   
#define      SRAM_D14_PORT               GPIOD
#define      SRAM_D14_PIN                GPIO_Pin_9
	
#define      SRAM_D15_CLK                RCC_APB2Periph_GPIOD   
#define      SRAM_D15_PORT               GPIOD
#define      SRAM_D15_PIN                GPIO_Pin_10

//address
#define      SRAM_A0_CLK                RCC_APB2Periph_GPIOA   
#define      SRAM_A0_PORT               GPIOA
#define      SRAM_A0_PIN                GPIO_Pin_7

#define      SRAM_A1_CLK                RCC_APB2Periph_GPIOC   
#define      SRAM_A1_PORT               GPIOC
#define      SRAM_A1_PIN                GPIO_Pin_4

#define      SRAM_A2_CLK                RCC_APB2Periph_GPIOC   
#define      SRAM_A2_PORT               GPIOC
#define      SRAM_A2_PIN                GPIO_Pin_5

#define      SRAM_A3_CLK                RCC_APB2Periph_GPIOB   
#define      SRAM_A3_PORT               GPIOB
#define      SRAM_A3_PIN                GPIO_Pin_0
	
#define      SRAM_A4_CLK                RCC_APB2Periph_GPIOB   
#define      SRAM_A4_PORT               GPIOB
#define      SRAM_A4_PIN                GPIO_Pin_1
		
#define      SRAM_A5_CLK                RCC_APB2Periph_GPIOB   
#define      SRAM_A5_PORT               GPIOB
#define      SRAM_A5_PIN                GPIO_Pin_2
			
#define      SRAM_A6_CLK                RCC_APB2Periph_GPIOC   
#define      SRAM_A6_PORT               GPIOC
#define      SRAM_A6_PIN                GPIO_Pin_6
				
#define      SRAM_A7_CLK                RCC_APB2Periph_GPIOC   
#define      SRAM_A7_PORT               GPIOC
#define      SRAM_A7_PIN                GPIO_Pin_7
					
#define      SRAM_A8_CLK                RCC_APB2Periph_GPIOC   
#define      SRAM_A8_PORT               GPIOC
#define      SRAM_A8_PIN                GPIO_Pin_8

#define      SRAM_A9_CLK                RCC_APB2Periph_GPIOC   
#define      SRAM_A9_PORT               GPIOC
#define      SRAM_A9_PIN                GPIO_Pin_9

#define      SRAM_A10_CLK                RCC_APB2Periph_GPIOA   
#define      SRAM_A10_PORT               GPIOA
#define      SRAM_A10_PIN                GPIO_Pin_8
	
#define      SRAM_A11_CLK                RCC_APB2Periph_GPIOA   
#define      SRAM_A11_PORT               GPIOA
#define      SRAM_A11_PIN                GPIO_Pin_9
		
#define      SRAM_A12_CLK                RCC_APB2Periph_GPIOA   
#define      SRAM_A12_PORT               GPIOA
#define      SRAM_A12_PIN                GPIO_Pin_10
			
#define      SRAM_A13_CLK                RCC_APB2Periph_GPIOC   
#define      SRAM_A13_PORT               GPIOC
#define      SRAM_A13_PIN                GPIO_Pin_0
				
#define      SRAM_A14_CLK                RCC_APB2Periph_GPIOA   
#define      SRAM_A14_PORT               GPIOA
#define      SRAM_A14_PIN                GPIO_Pin_1
					
#define      SRAM_A15_CLK                RCC_APB2Periph_GPIOA   
#define      SRAM_A15_PORT               GPIOA
#define      SRAM_A15_PIN                GPIO_Pin_3
						
#define      SRAM_A16_CLK                RCC_APB2Periph_GPIOD   
#define      SRAM_A16_PORT               GPIOD
#define      SRAM_A16_PIN                GPIO_Pin_11

#define      SRAM_A17_CLK                RCC_APB2Periph_GPIOD   
#define      SRAM_A17_PORT               GPIOD
#define      SRAM_A17_PIN                GPIO_Pin_12
	
#define      SRAM_A18_CLK                RCC_APB2Periph_GPIOD   
#define      SRAM_A18_PORT               GPIOD
#define      SRAM_A18_PIN                GPIO_Pin_13

#define      SRAM_A19_CLK                RCC_APB2Periph_GPIOE   
#define      SRAM_A19_PORT               GPIOE
#define      SRAM_A19_PIN                GPIO_Pin_3  
 
/**
  * @}
  */ 

/** @defgroup HK32F103xxxxA_EVAL_FSMC_SRAM_Exported_Functions
  * @{
  */      

void SRAM_Init(void);
void SRAM_WriteBuffer(uint16_t* pBuffer, uint32_t WriteAddr, uint32_t NumHalfwordToWrite);
void SRAM_ReadBuffer(uint16_t* pBuffer, uint32_t ReadAddr, uint32_t NumHalfwordToRead);

#ifdef __cplusplus
}
#endif

#endif /* __HK32F103xxxxA_EVAL_FSMC_SRAM_H */
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

