/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  hk32f103xxxxa_eval.h
* @brief:     This file contains definitions for hk32f103xxxxa Leds, push-buttons
*             COM ports.
* @author:    AE Team
*******************************************************************************/


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HK32F103xxxxA_EVAL_H
#define __HK32F103xxxxA_EVAL_H

#ifdef __cplusplus
extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/
#include "hk32f103xxxxa_conf.h"

/** @defgroup HK32F103xxxxA_EVAL
  * @{
  */ 

/** @defgroup HK32F103xxxxA_EVAL_Exported_Types
  * @{
  */
typedef enum 
{
    LED1 = 0,
    LED2,
    LED3
} Led_TypeDef;

typedef enum 
{
    BUTTON_KEY1 = 0,
    BUTTON_KEY2,
    BUTTON_KEY3
} Button_TypeDef;

typedef enum 
{  
    BUTTON_MODE_GPIO = 0,
    BUTTON_MODE_EXTI = 1
} ButtonMode_TypeDef;

typedef enum 
{
    COM1 = 0
} COM_TypeDef;   
/**
  * @}
  */  
/** @defgroup HK32F103xxxxA_EVAL_LOW_LEVEL_Exported_Constants
  * @{
  */ 
/** @defgroup HK32F103xxxxA_EVAL_LOW_LEVEL_LED
  * @{
  */
#define LEDn                             3

#define LED1_PIN                         GPIO_Pin_1
#define LED1_GPIO_PORT                   GPIOB
#define LED1_GPIO_CLK                    RCC_APB2Periph_GPIOB  
  
#define LED2_PIN                         GPIO_Pin_0
#define LED2_GPIO_PORT                   GPIOB
#define LED2_GPIO_CLK                    RCC_APB2Periph_GPIOB  

#define LED3_PIN                         GPIO_Pin_5  
#define LED3_GPIO_PORT                   GPIOB
#define LED3_GPIO_CLK                    RCC_APB2Periph_GPIOB  

/**
  * @}
  */
  
/** @defgroup HK32F103xxxxA_EVAL_LOW_LEVEL_BUTTON
  * @{
  */   
#define BUTTONn                          3
/**
 * @brief Key push-button
 */
#define KEY1_BUTTON_PIN                   GPIO_Pin_0
#define KEY1_BUTTON_GPIO_PORT             GPIOA
#define KEY1_BUTTON_GPIO_CLK              RCC_APB2Periph_GPIOA
#define KEY1_BUTTON_EXTI_LINE             EXTI_Line0
#define KEY1_BUTTON_EXTI_PORT_SOURCE      GPIO_PortSourceGPIOA
#define KEY1_BUTTON_EXTI_PIN_SOURCE       GPIO_PinSource0
#define KEY1_BUTTON_EXTI_IRQn             EXTI0_IRQn

#define KEY2_BUTTON_PIN                   GPIO_Pin_1
#define KEY2_BUTTON_GPIO_PORT             GPIOA
#define KEY2_BUTTON_GPIO_CLK              RCC_APB2Periph_GPIOA
#define KEY2_BUTTON_EXTI_LINE             EXTI_Line1
#define KEY2_BUTTON_EXTI_PORT_SOURCE      GPIO_PortSourceGPIOA
#define KEY2_BUTTON_EXTI_PIN_SOURCE       GPIO_PinSource1
#define KEY2_BUTTON_EXTI_IRQn             EXTI1_IRQn

#define KEY3_BUTTON_PIN                   GPIO_Pin_13
#define KEY3_BUTTON_GPIO_PORT             GPIOC
#define KEY3_BUTTON_GPIO_CLK              RCC_APB2Periph_GPIOC
#define KEY3_BUTTON_EXTI_LINE             EXTI_Line13
#define KEY3_BUTTON_EXTI_PORT_SOURCE      GPIO_PortSourceGPIOC
#define KEY3_BUTTON_EXTI_PIN_SOURCE       GPIO_PinSource13
#define KEY3_BUTTON_EXTI_IRQn             EXTI15_10_IRQn
/**
  * @}
  */ 

/** @defgroup HK32F103xxxxA_EVAL_LOW_LEVEL_COM
  * @{
  */
#define COMn                             1

/**
 * @brief Definition for COM port1, connected to USART1
 */ 
#define EVAL_COM1                        USART1
#define EVAL_COM1_CLK                    RCC_APB2Periph_USART1
#define EVAL_COM1_TX_PIN                 GPIO_Pin_9
#define EVAL_COM1_TX_GPIO_PORT           GPIOA
#define EVAL_COM1_TX_GPIO_CLK            RCC_APB2Periph_GPIOA
#define EVAL_COM1_RX_PIN                 GPIO_Pin_10
#define EVAL_COM1_RX_GPIO_PORT           GPIOA
#define EVAL_COM1_RX_GPIO_CLK            RCC_APB2Periph_GPIOA
#define EVAL_COM1_IRQn                   USART1_IRQn

/**
  * @}
  */ 

/** @defgroup HK32F103xxxxA_EVAL_LOW_LEVEL_SD_FLASH
  * @{
  */
/**
  * @brief  SD SDIO Interface
  */ 
#define SDIO_FIFO_ADDRESS                ((uint32_t)0x40018080)
/** 
  * @brief  SDIO Intialization Frequency (400KHz max)
  */
#define SDIO_INIT_CLK_DIV                ((uint8_t)0xB2)
/** 
  * @brief  SDIO Data Transfer Frequency (25MHz max) 
  */
#define SDIO_TRANSFER_CLK_DIV            ((uint8_t)0x01) 

/**
  * @}
  */ 
  
/** @addtogroup HK32F103xxxxA_EVAL_LOW_LEVEL_HK25Q_FLASH_SPI
  * @{
  */
/**
  * @brief  HK25Q FLASH SPI Interface pins
  */  
#define sFLASH_SPI                       SPI1
#define sFLASH_SPI_CLK                   RCC_APB2Periph_SPI1
#define sFLASH_SPI_SCK_PIN               GPIO_Pin_5                  /* PA.05 */
#define sFLASH_SPI_SCK_GPIO_PORT         GPIOA                       /* GPIOA */
#define sFLASH_SPI_SCK_GPIO_CLK          RCC_APB2Periph_GPIOA
#define sFLASH_SPI_MISO_PIN              GPIO_Pin_6                  /* PA.06 */
#define sFLASH_SPI_MISO_GPIO_PORT        GPIOA                       /* GPIOA */
#define sFLASH_SPI_MISO_GPIO_CLK         RCC_APB2Periph_GPIOA
#define sFLASH_SPI_MOSI_PIN              GPIO_Pin_7                  /* PA.07 */
#define sFLASH_SPI_MOSI_GPIO_PORT        GPIOA                       /* GPIOA */
#define sFLASH_SPI_MOSI_GPIO_CLK         RCC_APB2Periph_GPIOA
#define sFLASH_CS_PIN                    GPIO_Pin_4                  /* PA.04 */
#define sFLASH_CS_GPIO_PORT              GPIOA                       /* GPIOA */
#define sFLASH_CS_GPIO_CLK               RCC_APB2Periph_GPIOA

/**
  * @}
  */

/** @addtogroup HK32F103xxxxA_EVAL_LOW_LEVEL_EEPROM_I2C
  * @{
  */
/**
  * @brief  HK24c EEPROM I2C Interface pins
  */  

#define sEE_I2C                          I2C1
#define sEE_I2C_CLK                      RCC_APB1Periph_I2C1
#define sEE_I2C_SCL_PIN                  GPIO_Pin_6                 
#define sEE_I2C_SCL_GPIO_PORT            GPIOB                      
#define sEE_I2C_SCL_GPIO_CLK             RCC_APB2Periph_GPIOB
#define sEE_I2C_SDA_PIN                  GPIO_Pin_7                 
#define sEE_I2C_SDA_GPIO_PORT            GPIOB                      
#define sEE_I2C_SDA_GPIO_CLK             RCC_APB2Periph_GPIOB

#define sEE_I2C_DMA                      DMA1
#define sEE_I2C_DMA_CHANNEL_TX           DMA1_Channel6
#define sEE_I2C_DMA_CHANNEL_RX           DMA1_Channel7
#define sEE_I2C_DMA_FLAG_TX_TC           DMA1_IT_TC6
#define sEE_I2C_DMA_FLAG_TX_GL           DMA1_IT_GL6
#define sEE_I2C_DMA_FLAG_RX_TC           DMA1_IT_TC7
#define sEE_I2C_DMA_FLAG_RX_GL           DMA1_IT_GL7
#define sEE_I2C_DMA_CLK                  RCC_AHBPeriph_DMA1
#define sEE_I2C_DR_Address               ((uint32_t)0x40005410)

#define sEE_I2C_DMA_TX_IRQn              DMA1_Channel6_IRQn
#define sEE_I2C_DMA_RX_IRQn              DMA1_Channel7_IRQn
#define sEE_I2C_DMA_TX_IRQHandler        DMA1_Channel6_IRQHandler
#define sEE_I2C_DMA_RX_IRQHandler        DMA1_Channel7_IRQHandler
#define sEE_I2C_DMA_PREPRIO              0
#define sEE_I2C_DMA_SUBPRIO              0

#define sEE_DIRECTION_TX                 0
#define sEE_DIRECTION_RX                 1

/**
  * @}
  */
  
/** @addtogroup HK32F103xxxxA_EVAL_LOW_LEVEL_TSENSOR_I2C
  * @{
  */
/**
  * @brief  LM75 Temperature Sensor I2C Interface pins
  */  
#define LM75_I2C                         I2C2
#define LM75_I2C_CLK                     RCC_APB1Periph_I2C2
#define LM75_I2C_SCL_PIN                 GPIO_Pin_10                
#define LM75_I2C_SCL_GPIO_PORT           GPIOB                      
#define LM75_I2C_SCL_GPIO_CLK            RCC_APB2Periph_GPIOB
#define LM75_I2C_SDA_PIN                 GPIO_Pin_11                
#define LM75_I2C_SDA_GPIO_PORT           GPIOB                      
#define LM75_I2C_SDA_GPIO_CLK            RCC_APB2Periph_GPIOB
#define LM75_I2C_SMBUSALERT_PIN          GPIO_Pin_12                
#define LM75_I2C_SMBUSALERT_GPIO_PORT    GPIOB                      
#define LM75_I2C_SMBUSALERT_GPIO_CLK     RCC_APB2Periph_GPIOB
#define LM75_I2C_DR                      ((uint32_t)0x40005810)

#define LM75_DMA_CLK                     RCC_AHBPeriph_DMA1
#define LM75_DMA_TX_CHANNEL              DMA1_Channel4
#define LM75_DMA_RX_CHANNEL              DMA1_Channel5
#define LM75_DMA_TX_TCFLAG               DMA1_FLAG_TC4
#define LM75_DMA_RX_TCFLAG               DMA1_FLAG_TC5
   
/**
  * @}
  */
  
/**
  * @}
  */
   
/**
  * @}
  */
  
/** @defgroup HK32F103xxxxA_EVAL_LOW_LEVEL_Exported_Macros
  * @{
  */ 
/**
  * @}
  */ 

/** @defgroup HK32F103xxxxA_EVAL_LOW_LEVEL_Exported_Functions
  * @{
  */ 
void HK_EVAL_LEDInit(Led_TypeDef Led);
void HK_EVAL_LEDOn(Led_TypeDef Led);
void HK_EVAL_LEDOff(Led_TypeDef Led);
void HK_EVAL_LEDToggle(Led_TypeDef Led);
void HK_EVAL_PBInit(Button_TypeDef Button, ButtonMode_TypeDef Button_Mode);
uint32_t HK_EVAL_PBGetState(Button_TypeDef Button);
void HK_EVAL_COMInit(COM_TypeDef COM, USART_InitTypeDef* USART_InitStruct);
void SD_LowLevel_DeInit(void);
void SD_LowLevel_Init(void); 
void SD_LowLevel_DMA_TxConfig(uint32_t *BufferSRC, uint32_t BufferSize);
void SD_LowLevel_DMA_RxConfig(uint32_t *BufferDST, uint32_t BufferSize);
uint32_t SD_DMAEndOfTransferStatus(void);
void sFLASH_LowLevel_DeInit(void);
void sFLASH_LowLevel_Init(void); 
void sEE_LowLevel_DeInit(void);
void sEE_LowLevel_Init(void);
void sEE_LowLevel_DMAConfig(uint32_t pBuffer, uint32_t BufferSize, uint32_t Direction); 
void LM75_LowLevel_Init(void);
/**
  * @}
  */
  
#ifdef __cplusplus
}
#endif
  
#endif /*__HK32F103xxxxA_EVAL_H */
/**
  * @}
  */ 

/**
  * @}
  */

