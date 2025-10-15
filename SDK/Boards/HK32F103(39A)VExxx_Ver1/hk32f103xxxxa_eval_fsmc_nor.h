/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  hk32f103xxxxa_eval_fsmc_nor.h
* @brief:     hk32f103xxxxa_dma configuration file.
*             The file is the unique include file that the application programmer
*             is using in the C source code, it is a patch file.
* @author:    AE Team
*******************************************************************************/
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HK32F103xxxxA_EVAL_FSMC_NOR_H
#define __HK32F103xxxxA_EVAL_FSMC_NOR_H

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
  
/** @addtogroup HK32F103xxxxA_EVAL_FSMC_NOR
  * @{
  */  

/** @defgroup HK32F103xxxxA_EVAL_FSMC_NOR_Exported_Types
  * @{
  */
typedef struct
{
  uint16_t Manufacturer_Code;
  uint16_t Device_Code1;
  uint16_t Device_Code2;
  uint16_t Device_Code3;
}NOR_IDTypeDef;

/* NOR Status */
typedef enum
{
  NOR_SUCCESS = 0,
  NOR_ONGOING,
  NOR_ERROR,
  NOR_TIMEOUT
}NOR_Status;  
/**
  * @}
  */
  
/** @defgroup HK32F103xxxxA_EVAL_FSMC_NOR_Exported_Constants
  * @{
  */ 
/**
  * @}
  */ 
  
/** @defgroup HK32F103xxxxA_EVAL_FSMC_NOR_Exported_Macros
  * @{
  */ 

//NCE2
#define      NOR_CS_CLK                RCC_APB2Periph_GPIOC   
#define      NOR_CS_PORT               GPIOC
#define      NOR_CS_PIN                GPIO_Pin_12
	
//NWE
#define      NOR_WR_CLK                RCC_APB2Periph_GPIOD   
#define      NOR_WR_PORT               GPIOD
#define      NOR_WR_PIN                GPIO_Pin_5
	
//NOE
#define      NOR_RD_CLK                RCC_APB2Periph_GPIOD   
#define      NOR_RD_PORT               GPIOD
#define      NOR_RD_PIN                GPIO_Pin_4
	
//NWAIT
#define      NOR_NWAIT_CLK             RCC_APB2Periph_GPIOD   
#define      NOR_NWAIT_PORT            GPIOD
#define      NOR_NWAIT_PIN             GPIO_Pin_6

//data
#define      NOR_D0_CLK                RCC_APB2Periph_GPIOD   
#define      NOR_D0_PORT               GPIOD
#define      NOR_D0_PIN                GPIO_Pin_14
	
#define      NOR_D1_CLK                RCC_APB2Periph_GPIOD   
#define      NOR_D1_PORT               GPIOD
#define      NOR_D1_PIN                GPIO_Pin_15
	
#define      NOR_D2_CLK                RCC_APB2Periph_GPIOD   
#define      NOR_D2_PORT               GPIOD
#define      NOR_D2_PIN                GPIO_Pin_0
	
#define      NOR_D3_CLK                RCC_APB2Periph_GPIOD  
#define      NOR_D3_PORT               GPIOD
#define      NOR_D3_PIN                GPIO_Pin_1
	
#define      NOR_D4_CLK                RCC_APB2Periph_GPIOE   
#define      NOR_D4_PORT               GPIOE
#define      NOR_D4_PIN                GPIO_Pin_7
	
#define      NOR_D5_CLK                RCC_APB2Periph_GPIOE   
#define      NOR_D5_PORT               GPIOE
#define      NOR_D5_PIN                GPIO_Pin_8
	
#define      NOR_D6_CLK                RCC_APB2Periph_GPIOE   
#define      NOR_D6_PORT               GPIOE
#define      NOR_D6_PIN                GPIO_Pin_9
	
#define      NOR_D7_CLK                RCC_APB2Periph_GPIOE  
#define      NOR_D7_PORT               GPIOE
#define      NOR_D7_PIN                GPIO_Pin_10
	
#define      NOR_D8_CLK                RCC_APB2Periph_GPIOE   
#define      NOR_D8_PORT               GPIOE
#define      NOR_D8_PIN                GPIO_Pin_11
	
#define      NOR_D9_CLK                RCC_APB2Periph_GPIOE   
#define      NOR_D9_PORT               GPIOE
#define      NOR_D9_PIN                GPIO_Pin_12
	
#define      NOR_D10_CLK                RCC_APB2Periph_GPIOE   
#define      NOR_D10_PORT               GPIOE
#define      NOR_D10_PIN                GPIO_Pin_13
	
#define      NOR_D11_CLK                RCC_APB2Periph_GPIOE   
#define      NOR_D11_PORT               GPIOE
#define      NOR_D11_PIN                GPIO_Pin_14
	
#define      NOR_D12_CLK                RCC_APB2Periph_GPIOE   
#define      NOR_D12_PORT               GPIOE
#define      NOR_D12_PIN                GPIO_Pin_15
	
#define      NOR_D13_CLK                RCC_APB2Periph_GPIOD   
#define      NOR_D13_PORT               GPIOD
#define      NOR_D13_PIN                GPIO_Pin_8
	
#define      NOR_D14_CLK                RCC_APB2Periph_GPIOD   
#define      NOR_D14_PORT               GPIOD
#define      NOR_D14_PIN                GPIO_Pin_9
	
#define      NOR_D15_CLK                RCC_APB2Periph_GPIOD   
#define      NOR_D15_PORT               GPIOD
#define      NOR_D15_PIN                GPIO_Pin_10

//address
#define      NOR_A0_CLK                RCC_APB2Periph_GPIOA   
#define      NOR_A0_PORT               GPIOA
#define      NOR_A0_PIN                GPIO_Pin_7

#define      NOR_A1_CLK                RCC_APB2Periph_GPIOC   
#define      NOR_A1_PORT               GPIOC
#define      NOR_A1_PIN                GPIO_Pin_4

#define      NOR_A2_CLK                RCC_APB2Periph_GPIOC   
#define      NOR_A2_PORT               GPIOC
#define      NOR_A2_PIN                GPIO_Pin_5

#define      NOR_A3_CLK                RCC_APB2Periph_GPIOB   
#define      NOR_A3_PORT               GPIOB
#define      NOR_A3_PIN                GPIO_Pin_0
	
#define      NOR_A4_CLK                RCC_APB2Periph_GPIOB   
#define      NOR_A4_PORT               GPIOB
#define      NOR_A4_PIN                GPIO_Pin_1
		
#define      NOR_A5_CLK                RCC_APB2Periph_GPIOB   
#define      NOR_A5_PORT               GPIOB
#define      NOR_A5_PIN                GPIO_Pin_2
			
#define      NOR_A6_CLK                RCC_APB2Periph_GPIOC   
#define      NOR_A6_PORT               GPIOC
#define      NOR_A6_PIN                GPIO_Pin_6
				
#define      NOR_A7_CLK                RCC_APB2Periph_GPIOC   
#define      NOR_A7_PORT               GPIOC
#define      NOR_A7_PIN                GPIO_Pin_7
					
#define      NOR_A8_CLK                RCC_APB2Periph_GPIOC   
#define      NOR_A8_PORT               GPIOC
#define      NOR_A8_PIN                GPIO_Pin_8

#define      NOR_A9_CLK                RCC_APB2Periph_GPIOC   
#define      NOR_A9_PORT               GPIOC
#define      NOR_A9_PIN                GPIO_Pin_9

#define      NOR_A10_CLK                RCC_APB2Periph_GPIOA   
#define      NOR_A10_PORT               GPIOA
#define      NOR_A10_PIN                GPIO_Pin_8
	
#define      NOR_A11_CLK                RCC_APB2Periph_GPIOA   
#define      NOR_A11_PORT               GPIOA
#define      NOR_A11_PIN                GPIO_Pin_9
		
#define      NOR_A12_CLK                RCC_APB2Periph_GPIOA   
#define      NOR_A12_PORT               GPIOA
#define      NOR_A12_PIN                GPIO_Pin_10
			
#define      NOR_A13_CLK                RCC_APB2Periph_GPIOC   
#define      NOR_A13_PORT               GPIOC
#define      NOR_A13_PIN                GPIO_Pin_0
				
#define      NOR_A14_CLK                RCC_APB2Periph_GPIOA   
#define      NOR_A14_PORT               GPIOA
#define      NOR_A14_PIN                GPIO_Pin_1
					
#define      NOR_A15_CLK                RCC_APB2Periph_GPIOA   
#define      NOR_A15_PORT               GPIOA
#define      NOR_A15_PIN                GPIO_Pin_3
						
#define      NOR_A16_CLK                RCC_APB2Periph_GPIOD   
#define      NOR_A16_PORT               GPIOD
#define      NOR_A16_PIN                GPIO_Pin_11

#define      NOR_A17_CLK                RCC_APB2Periph_GPIOD   
#define      NOR_A17_PORT               GPIOD
#define      NOR_A17_PIN                GPIO_Pin_12
	
#define      NOR_A18_CLK                RCC_APB2Periph_GPIOD   
#define      NOR_A18_PORT               GPIOD
#define      NOR_A18_PIN                GPIO_Pin_13

#define      NOR_A19_CLK                RCC_APB2Periph_GPIOE   
#define      NOR_A19_PORT               GPIOE
#define      NOR_A19_PIN                GPIO_Pin_3

#define      NOR_A20_CLK                RCC_APB2Periph_GPIOE   
#define      NOR_A20_PORT               GPIOE
#define      NOR_A20_PIN                GPIO_Pin_4
	
#define      NOR_A21_CLK                RCC_APB2Periph_GPIOE   
#define      NOR_A21_PORT               GPIOE
#define      NOR_A21_PIN                GPIO_Pin_5

#define      NOR_A22_CLK                RCC_APB2Periph_GPIOE   
#define      NOR_A22_PORT               GPIOE
#define      NOR_A22_PIN                GPIO_Pin_6

/**
  * @}
  */ 

/** @defgroup HK32F103xxxxA_EVAL_FSMC_NOR_Exported_Functions
  * @{
  */ 
void NOR_Init(void);
void NOR_ReadID(NOR_IDTypeDef* NOR_ID);
NOR_Status NOR_EraseBlock(uint32_t BlockAddr);
NOR_Status NOR_EraseChip(void);
NOR_Status NOR_WriteHalfWord(uint32_t WriteAddr, uint16_t Data);
NOR_Status NOR_WriteBuffer(uint16_t* pBuffer, uint32_t WriteAddr, uint32_t NumHalfwordToWrite);
NOR_Status NOR_ProgramBuffer(uint16_t* pBuffer, uint32_t WriteAddr, uint32_t NumHalfwordToWrite);
uint16_t NOR_ReadHalfWord(uint32_t ReadAddr);
void NOR_ReadBuffer(uint16_t* pBuffer, uint32_t ReadAddr, uint32_t NumHalfwordToRead);
NOR_Status NOR_ReturnToReadMode(void);
NOR_Status NOR_Reset(void);
NOR_Status NOR_GetStatus(uint32_t Timeout);

#ifdef __cplusplus
}
#endif

#endif /* __HK32F103xxxxA_EVAL_FSMC_NOR_H */
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

