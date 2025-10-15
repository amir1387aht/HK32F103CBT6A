/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  hk32f103xxxxa_eval_fsmc_srammuxed.h
* @brief:     hk32f103xxxxa_dma configuration file.
*             The file is the unique include file that the application programmer
*             is using in the C source code, it is a patch file.
* @author:    AE Team
*******************************************************************************/

/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HK32F103xxxxA_EVAL_SRAMMUXED_H
#define __HK32F103xxxxA_EVAL_SRAMMUXED_H

#ifdef __cplusplus
extern "C" {
#endif
#define 		SRAMMUXED_ADDR             	0x60000000

//NE1
#define      SRAM_CS_CLK                RCC_APB2Periph_GPIOD   
#define      SRAM_CS_PORT               GPIOD
#define      SRAM_CS_PIN                GPIO_Pin_7
	
//NWE
#define      SRAM_WR_CLK                RCC_APB2Periph_GPIOD   
#define      SRAM_WR_PORT               GPIOD
#define      SRAM_WR_PIN                GPIO_Pin_5
	
//NOE
#define      SRAM_RD_CLK                RCC_APB2Periph_GPIOD   
#define      SRAM_RD_PORT               GPIOD
#define      SRAM_RD_PIN                GPIO_Pin_4
	
//NBL0
#define      SRAM_NBL0_CLK                RCC_APB2Periph_GPIOE   
#define      SRAM_NBL0_PORT               GPIOE
#define      SRAM_NBL0_PIN                GPIO_Pin_0

//NBL1
#define      SRAM_NBL1_CLK                RCC_APB2Periph_GPIOE   
#define      SRAM_NBL1_PORT               GPIOE
#define      SRAM_NBL1_PIN                GPIO_Pin_1

//NADV
#define      SRAM_NADV_CLK                RCC_APB2Periph_GPIOB   
#define      SRAM_NADV_PORT               GPIOB
#define      SRAM_NADV_PIN                GPIO_Pin_7

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

						
#define      SRAM_A16_CLK                RCC_APB2Periph_GPIOD   
#define      SRAM_A16_PORT               GPIOD
#define      SRAM_A16_PIN                GPIO_Pin_11

#define      SRAM_A17_CLK                RCC_APB2Periph_GPIOD   
#define      SRAM_A17_PORT               GPIOD
#define      SRAM_A17_PIN                GPIO_Pin_12
	
#define      SRAM_A18_CLK                RCC_APB2Periph_GPIOD   
#define      SRAM_A18_PORT               GPIOD
#define      SRAM_A18_PIN                GPIO_Pin_13

void SRAMMUXED_FSMC_GPIO_Config(void);
void SRAMMUXED_FSMC_Init(void);

#ifdef __cplusplus
}
#endif

#endif /* __HK32F103xxxxA_EVAL_SRAMMUXED_H */
