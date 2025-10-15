/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd 
* @filename:  hk32f103xxxxa_gpio.h
* @brief:     API file of gpio module 
* @author:    AE Team 
*******************************************************************************/


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HK32F103XXXXA_GPIO_H
#define __HK32F103XXXXA_GPIO_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "hk32f103xxxxa_conf.h"

/** @addtogroup GPIO GPIO
  * @{
  */
	
/** @defgroup GPIO_Exported_Types GPIO_Exported_Types
  * @{
  */		

/** @defgroup GPIO_Speed GPIO_Speed
  * @{
  */
typedef enum
{ 
    GPIO_Speed_10MHz = 1,
    GPIO_Speed_2MHz, 
    GPIO_Speed_50MHz,
    GPIO_Speed_ultraHigh
}GPIOSpeed_TypeDef;

#define IS_GPIO_SPEED(SPEED) (((SPEED) == GPIO_Speed_10MHz) || ((SPEED) == GPIO_Speed_2MHz) || \
                              ((SPEED) == GPIO_Speed_50MHz)|| ((SPEED) == GPIO_Speed_ultraHigh))
/**
  * @}
  */	

/** @defgroup Configuration_Mode_enumeration Configuration_Mode_enumeration
  * @{
  */
typedef enum
{ 
    GPIO_Mode_AIN = 0x0,
    GPIO_Mode_IN_FLOATING = 0x04,
    GPIO_Mode_IPD = 0x28,
    GPIO_Mode_IPU = 0x48,
    GPIO_Mode_Out_OD = 0x14,
    GPIO_Mode_Out_PP = 0x10,
    GPIO_Mode_AF_OD = 0x1C,
    GPIO_Mode_AF_PP = 0x18
}GPIOMode_TypeDef;
/**
  * @}
  */

/** @defgroup Configuration_Schmit Configuration_Schmit
  * @{
  */
typedef enum
{ 
    GPIO_Schmit_Disable = 0x0,
    GPIO_Schmit_Enable = 0x1,
}GPIOSchmit_TypeDef;

#define IS_GPIO_MODE(MODE) (((MODE) == GPIO_Mode_AIN) || ((MODE) == GPIO_Mode_IN_FLOATING) || \
                            ((MODE) == GPIO_Mode_IPD) || ((MODE) == GPIO_Mode_IPU) || \
                            ((MODE) == GPIO_Mode_Out_OD) || ((MODE) == GPIO_Mode_Out_PP) || \
                            ((MODE) == GPIO_Mode_AF_OD) || ((MODE) == GPIO_Mode_AF_PP))
/**
  * @}
  */

/** @defgroup GPIO_Init_structure_definition GPIO_Init_structure_definition
  * @{
  */
typedef struct
{
  	uint16_t GPIO_Pin;             /*!< Specifies the GPIO pins to be configured.
                                      This parameter can be any value of @ref GPIO_pins_define */

  	GPIOSpeed_TypeDef GPIO_Speed;  /*!< Specifies the speed for the selected pins.
                                      This parameter can be a value of @ref GPIOSpeed_TypeDef */

  	GPIOMode_TypeDef GPIO_Mode;    /*!< Specifies the operating mode for the selected pins.
                                      This parameter can be a value of @ref GPIOMode_TypeDef */

	GPIOSchmit_TypeDef GPIO_Schmit;

}GPIO_InitTypeDef;
/**
  * @}
  */


/** @defgroup Bit_SET Bit_SET 
  * @{
  */
typedef enum
{ 
    Bit_RESET = 0,
    Bit_SET
}BitAction;

#define IS_GPIO_BIT_ACTION(ACTION) (((ACTION) == Bit_RESET) || ((ACTION) == Bit_SET))
/**
  * @}
  */


/**
  * @}
  */


/** @defgroup GPIO_Exported_Constants GPIO_Exported_Constants
  * @{
  */
	
/** @defgroup AFIO_OffSet AFIO_OffSet
  * @{
  */
#define AFIO_OFFSET                 (AFIO_BASE - PERIPH_BASE)
/**
  * @}
  */

/** @defgroup EVENTCR_Register EVENTCR_Register
  * @{
  */
#define EVCR_OFFSET                 (AFIO_OFFSET + 0x00)
#define EVOE_BitNumber              ((uint8_t)0x07)
#define EVCR_EVOE_BB                (PERIPH_BB_BASE + (EVCR_OFFSET * 32) + (EVOE_BitNumber * 4))
/**
  * @}
  */

/** @defgroup MAPR_Register_MAPR_Register MAPR_Register_MAPR_Register
  * @{
  */
#define MAPR_OFFSET                 (AFIO_OFFSET + 0x04) 
#define MII_RMII_SEL_BitNumber      ((u8)0x17) 
#define MAPR_MII_RMII_SEL_BB        (PERIPH_BB_BASE + (MAPR_OFFSET * 32) + (MII_RMII_SEL_BitNumber * 4))
#define EVCR_PORTPINCONFIG_MASK     ((uint16_t)0xFF80)
#define LSB_MASK                    ((uint16_t)0xFFFF)
#define DBGAFR_POSITION_MASK        ((uint32_t)0x000F0000)
#define DBGAFR_SWJCFG_MASK          ((uint32_t)0xF0FFFFFF)
#define DBGAFR_CAN2_MASK            ((uint32_t)0x9FFFFFFF)
#define DBGAFR_LOCATION_MASK        ((uint32_t)0x00200000)
#define DBGAFR_NUMBITS_MASK         ((uint32_t)0x00100000)	
/**
  * @}
  */	

/** @defgroup GPIO_Configuration_GPIO_PERIPH GPIO_Configuration_GPIO_PERIPH
  * @{
  */
#define IS_GPIO_ALL_PERIPH(PERIPH) (((PERIPH) == GPIOA) || \
																		((PERIPH) == GPIOB) || \
																		((PERIPH) == GPIOC) || \
																		((PERIPH) == GPIOD) || \
                                    ((PERIPH) == GPIOE))
/**
  * @}
  */	                                     
	




/** @defgroup GPIO_pins_define GPIO_pins_define
  * @{
  */
#define GPIO_Pin_0                 ((uint16_t)0x0001)  /*!< Pin 0 selected */
#define GPIO_Pin_1                 ((uint16_t)0x0002)  /*!< Pin 1 selected */
#define GPIO_Pin_2                 ((uint16_t)0x0004)  /*!< Pin 2 selected */
#define GPIO_Pin_3                 ((uint16_t)0x0008)  /*!< Pin 3 selected */
#define GPIO_Pin_4                 ((uint16_t)0x0010)  /*!< Pin 4 selected */
#define GPIO_Pin_5                 ((uint16_t)0x0020)  /*!< Pin 5 selected */
#define GPIO_Pin_6                 ((uint16_t)0x0040)  /*!< Pin 6 selected */
#define GPIO_Pin_7                 ((uint16_t)0x0080)  /*!< Pin 7 selected */
#define GPIO_Pin_8                 ((uint16_t)0x0100)  /*!< Pin 8 selected */
#define GPIO_Pin_9                 ((uint16_t)0x0200)  /*!< Pin 9 selected */
#define GPIO_Pin_10                ((uint16_t)0x0400)  /*!< Pin 10 selected */
#define GPIO_Pin_11                ((uint16_t)0x0800)  /*!< Pin 11 selected */
#define GPIO_Pin_12                ((uint16_t)0x1000)  /*!< Pin 12 selected */
#define GPIO_Pin_13                ((uint16_t)0x2000)  /*!< Pin 13 selected */
#define GPIO_Pin_14                ((uint16_t)0x4000)  /*!< Pin 14 selected */
#define GPIO_Pin_15                ((uint16_t)0x8000)  /*!< Pin 15 selected */
#define GPIO_Pin_All               ((uint16_t)0xFFFF)  /*!< All pins selected */

#define IS_GPIO_PIN(PIN) ((((PIN) & (uint16_t)0x00) == 0x00) && ((PIN) != (uint16_t)0x00))

#define IS_GET_GPIO_PIN(PIN) (((PIN) == GPIO_Pin_0) || \
                              ((PIN) == GPIO_Pin_1) || \
                              ((PIN) == GPIO_Pin_2) || \
                              ((PIN) == GPIO_Pin_3) || \
                              ((PIN) == GPIO_Pin_4) || \
                              ((PIN) == GPIO_Pin_5) || \
                              ((PIN) == GPIO_Pin_6) || \
                              ((PIN) == GPIO_Pin_7) || \
                              ((PIN) == GPIO_Pin_8) || \
                              ((PIN) == GPIO_Pin_9) || \
                              ((PIN) == GPIO_Pin_10) || \
                              ((PIN) == GPIO_Pin_11) || \
                              ((PIN) == GPIO_Pin_12) || \
                              ((PIN) == GPIO_Pin_13) || \
                              ((PIN) == GPIO_Pin_14) || \
                              ((PIN) == GPIO_Pin_15))
/**
  * @}
  */

/** @defgroup GPIO_Remap_define GPIO_Remap_define
  * @{
  */
#define GPIO_Remap_SPI1             ((uint32_t)0x00000001)  /*!< SPI1 Alternate Function mapping */
#define GPIO_Remap_I2C1             ((uint32_t)0x00000002)  /*!< I2C1 Alternate Function mapping */
#define GPIO_Remap_USART1           ((uint32_t)0x00000004)  /*!< USART1 Alternate Function mapping */
#define GPIO_Remap1_USART2          ((uint32_t)0x00000008)  /*!< USART2 Alternate Function mapping */
#define GPIO_PartialRemap_USART3    ((uint32_t)0x00140010)  /*!< USART3 Partial Alternate Function mapping */
#define GPIO_FullRemap_USART3       ((uint32_t)0x00140030)  /*!< USART3 Full Alternate Function mapping */
#define GPIO_PartialRemap_TIM1      ((uint32_t)0x00160040)  /*!< TIM1 Partial Alternate Function mapping */
#define GPIO_FullRemap_TIM1         ((uint32_t)0x001600C0)  /*!< TIM1 Full Alternate Function mapping */
#define GPIO_PartialRemap1_TIM2     ((uint32_t)0x00180100)  /*!< TIM2 Partial1 Alternate Function mapping */
#define GPIO_PartialRemap2_TIM2     ((uint32_t)0x00180200)  /*!< TIM2 Partial2 Alternate Function mapping */
#define GPIO_FullRemap_TIM2         ((uint32_t)0x00180300)  /*!< TIM2 Full Alternate Function mapping */
#define GPIO_PartialRemap_TIM3      ((uint32_t)0x001A0800)  /*!< TIM3 Partial Alternate Function mapping */
#define GPIO_FullRemap_TIM3         ((uint32_t)0x001A0C00)  /*!< TIM3 Full Alternate Function mapping */
#define GPIO_Remap_TIM4             ((uint32_t)0x00001000)  /*!< TIM4 Alternate Function mapping */
#define GPIO_Remap1_CAN1            ((uint32_t)0x001D4000)  /*!< CAN1 Alternate Function mapping */
#define GPIO_Remap2_CAN1            ((uint32_t)0x001D6000)  /*!< CAN1 Alternate Function mapping */
#define GPIO_Remap_PD01             ((uint32_t)0x00008000)  /*!< PD01 Alternate Function mapping */

#define GPIO_Remap_ADC1_ETRGINJ     ((uint32_t)0x00200002)  /*!< ADC1 External Trigger Injected Conversion remapping */
#define GPIO_Remap_ADC1_ETRGREG     ((uint32_t)0x00200004)  /*!< ADC1 External Trigger Regular Conversion remapping */
#define GPIO_Remap_ADC2_ETRGINJ     ((uint32_t)0x00200008)  /*!< ADC2 External Trigger Injected Conversion remapping */
#define GPIO_Remap_ADC2_ETRGREG     ((uint32_t)0x00200010)  /*!< ADC2 External Trigger Regular Conversion remapping */
#define GPIO_Remap_SWJ_NoJTRST      ((uint32_t)0x00300100)  /*!< Full SWJ Enabled (JTAG-DP + SW-DP) but without JTRST */
#define GPIO_Remap_SWJ_JTAGDisable  ((uint32_t)0x00300200)  /*!< JTAG-DP Disabled and SW-DP Enabled */
#define GPIO_Remap_SWJ_Disable      ((uint32_t)0x00300400)  /*!< Full SWJ Disabled (JTAG-DP + SW-DP) */

#define GPIO_Remap_FSMC_NADV        ((uint32_t)0x80000400)  /*!< FSMC_NADV Alternate Function mapping (only for High density Value line and XL-density devices) */
#define GPIO_Remap_USART1_CTSRTS    ((uint32_t)0x80200200)  /*!< USART1_CTSRTS Alternate Function mapping */
#define GPIO_Remap_FMSC_100PIN      ((uint32_t)0x80208000)


#define GPIO_Remap_TIM5CH4_Mask     ((uint32_t)0x00010000)
#define GPIO_E_Remap2_TIM5CH4_Mask  ((uint32_t)0x00300000)


#define GPIO_E_Remap_TIM5CH4_LSI    ((uint32_t)0x00010000)  /*!< LSI connected to TIM5 Channel4 input capture for calibration */  
#define GPIO_E_Remap_TIM5CH4_HSI	((uint32_t)0x00200000)  /*!< HSI connected to TIM5 Channel4 input capture for calibration */
#define GPIO_E_Remap_TIM5CH4_LSE    ((uint32_t)0x00200001)  /*!< LSE connected to TIM5 Channel4 input capture for calibration */
#define GPIO_E_Remap_TIM5CH4_USB  	((uint32_t)0x00100000)  /*!< The SOF signal of USB2.0 is connected to channel 4 of TIM5 */
                                             

#define IS_GPIO_REMAP(REMAP) (((REMAP) == GPIO_Remap_SPI1) || ((REMAP) == GPIO_Remap_I2C1) || \
                              ((REMAP) == GPIO_Remap_USART1) || ((REMAP) == GPIO_Remap1_USART2) || \
                              ((REMAP) == GPIO_PartialRemap_USART3) || ((REMAP) == GPIO_FullRemap_USART3) || \
                              ((REMAP) == GPIO_PartialRemap_TIM1) || ((REMAP) == GPIO_FullRemap_TIM1) || \
                              ((REMAP) == GPIO_PartialRemap1_TIM2) || ((REMAP) == GPIO_PartialRemap2_TIM2) || \
                              ((REMAP) == GPIO_FullRemap_TIM2) || ((REMAP) == GPIO_PartialRemap_TIM3) || \
                              ((REMAP) == GPIO_FullRemap_TIM3) || ((REMAP) == GPIO_Remap_TIM4) || \
                              ((REMAP) == GPIO_Remap1_CAN1) || ((REMAP) == GPIO_Remap2_CAN1) || \
                              ((REMAP) == GPIO_Remap_PD01) || ((REMAP) == GPIO_Remap_FSMC_NADV) || \
                              ((REMAP) == GPIO_Remap_ADC1_ETRGINJ) ||((REMAP) == GPIO_Remap_ADC1_ETRGREG) || \
                              ((REMAP) == GPIO_Remap_ADC2_ETRGINJ) ||((REMAP) == GPIO_Remap_ADC2_ETRGREG) || \
                              ((REMAP) == GPIO_Remap_SWJ_Disable) ||((REMAP) == GPIO_Remap_SWJ_Disable) || \
                              ((REMAP) == GPIO_Remap_SWJ_NoJTRST) || ((REMAP) == GPIO_Remap_SWJ_JTAGDisable) || \
                               ((REMAP) == GPIO_Remap_USART1_CTSRTS) || ((REMAP) == GPIO_Remap_FMSC_100PIN))

#define IS_GPIO_E_REMAP(REMAP) (((REMAP) == GPIO_E_Remap_TIM5CH4_LSI) || ((REMAP) == GPIO_E_Remap_TIM5CH4_USB) || \
                              ((REMAP) == GPIO_E_Remap_TIM5CH4_HSI) || ((REMAP) == GPIO_E_Remap_TIM5CH4_LSE))
/**
  * @}
  */

/** @defgroup GPIO_Port_Sources GPIO_Port_Sources
  * @{
  */
#define GPIO_PortSourceGPIOA       ((uint8_t)0x00)
#define GPIO_PortSourceGPIOB       ((uint8_t)0x01)
#define GPIO_PortSourceGPIOC       ((uint8_t)0x02)
#define GPIO_PortSourceGPIOD       ((uint8_t)0x03)
#define GPIO_PortSourceGPIOE       ((uint8_t)0x04)
#define GPIO_PortSourceGPIOF       ((uint8_t)0x05)
#define GPIO_PortSourceGPIOG       ((uint8_t)0x06)
#define IS_GPIO_EVENTOUT_PORT_SOURCE(PORTSOURCE) (((PORTSOURCE) == GPIO_PortSourceGPIOA) || \
                                                  ((PORTSOURCE) == GPIO_PortSourceGPIOB) || \
                                                  ((PORTSOURCE) == GPIO_PortSourceGPIOC) || \
                                                  ((PORTSOURCE) == GPIO_PortSourceGPIOD) || \
                                                  ((PORTSOURCE) == GPIO_PortSourceGPIOE))

#define IS_GPIO_EXTI_PORT_SOURCE(PORTSOURCE) (((PORTSOURCE) == GPIO_PortSourceGPIOA) || \
                                              ((PORTSOURCE) == GPIO_PortSourceGPIOB) || \
                                              ((PORTSOURCE) == GPIO_PortSourceGPIOC) || \
                                              ((PORTSOURCE) == GPIO_PortSourceGPIOD) || \
                                              ((PORTSOURCE) == GPIO_PortSourceGPIOE) || \
                                              ((PORTSOURCE) == GPIO_PortSourceGPIOF) || \
                                              ((PORTSOURCE) == GPIO_PortSourceGPIOG))
/**
  * @}
  */

/** @defgroup GPIO_Pin_sources GPIO_Pin_sources
  * @{
  */
#define GPIO_PinSource0            ((uint8_t)0x00)
#define GPIO_PinSource1            ((uint8_t)0x01)
#define GPIO_PinSource2            ((uint8_t)0x02)
#define GPIO_PinSource3            ((uint8_t)0x03)
#define GPIO_PinSource4            ((uint8_t)0x04)
#define GPIO_PinSource5            ((uint8_t)0x05)
#define GPIO_PinSource6            ((uint8_t)0x06)
#define GPIO_PinSource7            ((uint8_t)0x07)
#define GPIO_PinSource8            ((uint8_t)0x08)
#define GPIO_PinSource9            ((uint8_t)0x09)
#define GPIO_PinSource10           ((uint8_t)0x0A)
#define GPIO_PinSource11           ((uint8_t)0x0B)
#define GPIO_PinSource12           ((uint8_t)0x0C)
#define GPIO_PinSource13           ((uint8_t)0x0D)
#define GPIO_PinSource14           ((uint8_t)0x0E)
#define GPIO_PinSource15           ((uint8_t)0x0F)

#define IS_GPIO_PIN_SOURCE(PINSOURCE) (((PINSOURCE) == GPIO_PinSource0) || \
                                       ((PINSOURCE) == GPIO_PinSource1) || \
                                       ((PINSOURCE) == GPIO_PinSource2) || \
                                       ((PINSOURCE) == GPIO_PinSource3) || \
                                       ((PINSOURCE) == GPIO_PinSource4) || \
                                       ((PINSOURCE) == GPIO_PinSource5) || \
                                       ((PINSOURCE) == GPIO_PinSource6) || \
                                       ((PINSOURCE) == GPIO_PinSource7) || \
                                       ((PINSOURCE) == GPIO_PinSource8) || \
                                       ((PINSOURCE) == GPIO_PinSource9) || \
                                       ((PINSOURCE) == GPIO_PinSource10) || \
                                       ((PINSOURCE) == GPIO_PinSource11) || \
                                       ((PINSOURCE) == GPIO_PinSource12) || \
                                       ((PINSOURCE) == GPIO_PinSource13) || \
                                       ((PINSOURCE) == GPIO_PinSource14) || \
                                       ((PINSOURCE) == GPIO_PinSource15))
/**
  * @}
  */



/** @defgroup GPIO_AF_Sel GPIO_AF_Sel
  * @{
  */


#define IS_GPIO_AF_SEL(AFSEL) 				(((AFSEL) == AFIO_SELENA) || \
                                       ((AFSEL) == AFIO_SELENB) || \
                                       ((AFSEL) == AFIO_SELENC) || \
                                       ((AFSEL) == AFIO_SELEND) || \
                                       ((AFSEL) == AFIO_SELENE))
																			 
/**
  * @}
  */


/** @defgroup GPIO_Alternate_Function GPIO_Alternate_Function
  * @{
  */

/** 
  * @brief  AF 0 selection
  * MCO
  */
 
#define GPIO_AF_0            ((uint8_t)0x00)
/** 
  * @brief  AF 1 selection
  * TIM2_CH1_ETR, TIM2_CH2, TIM2_CH3, TIM2_CH4, TIM1_BKIN, TIM1_CH1N, TIM1_CH2N, TIM1_CH3N, TIM1_ETR,TIM1_CH1, TIM1_CH2, TIM1_CH3, TIM1_CH4
  */
#define GPIO_AF_1            ((uint8_t)0x01)
/** 
  * @brief  AF 2 selection
  * TIM5_CH1, TIM5_CH2, TIM5_CH3, TIM5_CH4, TIM5_ETR, TIM3_CH1, TIM3_CH2, TIM3_CH3, TIM3_CH4, TIM4_CH1, TIM4_CH2, TIM4_CH3, TIM4_CH4,
	* TIM3_ETR, TIM4_ETR 
  */
#define GPIO_AF_2            ((uint8_t)0x02) 
/** 
  * @brief  AF 3 selection
  * TIM8_ETR, TIM8_BKIN, TIM8_CH1N, TIM8_CH2N, TIM8_CH3N, TIM8_CH1, TIM8_CH2, TIM8_CH3, TIM8_CH4,
	*/ 
#define GPIO_AF_3            ((uint8_t)0x03) 

/** 
  * @brief  AF 4 selection
  * I2C2_SCL, I2C2_SDA, I2C2_SMBA, I2C1_SMBA, SPI3_NSS/I2S3_WS, SPI3_SCK/I2S3_CK, SPI3_MISO, I2C1_SCL, I2C1_SDA 
  */
#define GPIO_AF_4            ((uint8_t)0x04)

/** 
  * @brief  AF 5 selection
  * SPI1_NSS/I2S1_WS, SPI1_SCK/I2S1_CK, SPI1_MISO, SPI1_MOSI/I2S1_SD, SPI2_NSS/I2S2_WS, SPI2_SCK/I2S2_CK, SPI2_MISO, 
	* SPI2_MOSI, I2S2_MCK, I2S3_MCK, SPI3_NSS/I2S3_WS, SPI3_SCK/I2S3_CK, SPI3_MISO, SPI3_MOSI/I2S3_SD, I2S1_MCK, 
  */
#define GPIO_AF_5            ((uint8_t)0x05)

/** 
  * @brief  AF 6 selection
  * USART2_CTS, USART2_RTS, USART2_TX, USART2_RX, USART2_CK, USART1_CTS, USART1_RTS, USART1_CK, USART1_TX, USART1_RX, SPI3_MOSI/I2S3_SD
  */
#define GPIO_AF_6            ((uint8_t)0x06) 
/** 
  * @brief  AF 7 selection
  * USART3_RX, USART3_TX, USART3_CK, USART3_CTS, USART3_RTS 
  */
#define GPIO_AF_7            ((uint8_t)0x07)
/** 
  * @brief  AF 8 selection
  * USART5_RX, USART5_TX, USART6_RX, USART6_TX, USART6_CK, USART4_CK, USART4_CTS, USART4_RTS, USART6_CTS, USART5_CK, USART6_RTS, USART4_TX, 
	* USART4_RX, USART5_CTS, USART5_RTS
	*/
#define GPIO_AF_8            ((uint8_t)0x08)
/** 
  * @brief  AF 9 selection
  * CAN1_CANRX, CAN1_CANTX, CAN2_CANRX, CAN2_CANTX
  */
#define GPIO_AF_9            ((uint8_t)0x09) 
/** 
  * @brief  AF 10 selection
  * QSPI_CKO, QSPI_BK1_IO0, QSPI_BK1_IO1, QSPI_BK1_IO2, QSPI_BK1_IO3, QSPI_BK1_NCS, QSPI_BK2_NCS, QSPI_BK2_IO0, 
	* QSPI_BK2_IO1, QSPI_BK2_IO2, QSPI_BK2_IO3
  */
#define GPIO_AF_10           ((uint8_t)0x0a)
/** 
  * @brief  AF 11 selection
  * SDIO_D7, SDIO_D6, SDIO_D5, SDIO_D4, SDIO_D3, SDIO_D2, SDIO_D1, SDIO_D0, SDIO_CMD,
  */
#define GPIO_AF_11           ((uint8_t)0x0b)
/** 
  * @brief  AF 12 selection
  * FSMC_A23, FSMC_A19, FSMC_A20, FSMC_A21, FSMC_A22, FSMC_D2, FSMC_D3, FSMC_A13, TFT_DEN1, TFT_VSYNC1, TFT_HSYNC1, FSMC_NE4, FSMC_A14, TFT_DCLK, FSMC_A15, TFT_DEN2, TFT_VSYNC2, TFT_HSYNC2, FSMC_A0
	* FSMC_A1, FSMC_A2, FSMC_A3, FSMC_A4, FSMC_A5, FSMC_D4, FSMC_D5, FSMC_D6, FSMC_D7, FSMC_D8, FSMC_D9, FSMC_D10, FSMC_D11, FSMC_D12, FSMC_INT2, FSMC_INT3, TFT_DEN3, TFT_VSYNC3, TFT_HSYNC3, FSMC_INTR,
	* FSMC_D13, FSMC_D14, FSMC_D15, FSMC_A16_CLE, FSMC_A17_ALE, FSMC_A18, FSMC_D0, FSMC_D1, FSMC_A6, FSMC_A7, FSMC_A8, FSMC_A9, FSMC_A10, FSMC_A11, FSMC_A12, FSMC_NIORD, FSMC_NIOWR, FSMC_NREG, FSMC_A24,
	* FSMC_A25, FSMC_NE2_NCE3, FSMC_NE3_NCE4_1, FSMC_CLK, FSMC_NOE, FSMC_NWE, FSMC_NWAIT, FSMC_NE1_NCE2, TFT_DEN4, TFT_VSYNC4, TFT_HSYNC4, FSMC_NCE4_2, FSMC_NADV, FSMC_CD, FSMC_NBL0, FSMC_NBL1
  */
#define GPIO_AF_12           ((uint8_t)0x0c)
/** 
  * @brief  AF 13 selection
  * DCMI_PIXDI6, DCMI_PIXDI5, DCMI_PIXDI4, DCMI_PIXDI3, DCMI_PIXDI2, DCMI_PIXCLK, DCMI_PIXDI13, DCMI_PIXDI12, DCMI_PIXDI11, DCMI_PIXDI10, DCMI_PIXDI9, DCMI_PIXDI8, DCMI_VYSNC, DCMI_HYSNC, DCMI_PIXDI7,
	* DCMI_PIXDI1, DCMI_PIXDI0
  */
#define GPIO_AF_13           ((uint8_t)0x0d)
/** 
  * @brief  AF 14 selection
  * None
  */
#define GPIO_AF_14           ((uint8_t)0x0e)

/** 
  * @brief  AF 15 selection
  * CM3_TXEV
  */
#define GPIO_AF_15           ((uint8_t)0x0f)

#define IS_GPIO_AF(AF)     (((AF) == GPIO_AF_0) || ((AF) == GPIO_AF_1)  || \
													 ((AF) == GPIO_AF_2)  || ((AF) == GPIO_AF_3)  || \
													 ((AF) == GPIO_AF_4)  || ((AF) == GPIO_AF_5)  || \
													 ((AF) == GPIO_AF_6)  || ((AF) == GPIO_AF_7)  || \
													 ((AF) == GPIO_AF_8)  || ((AF) == GPIO_AF_9)  || \
													 ((AF) == GPIO_AF_10) || ((AF) == GPIO_AF_11) || \
													 ((AF) == GPIO_AF_12) || ((AF) == GPIO_AF_13) || \
													 ((AF) == GPIO_AF_14)	|| ((AF) == GPIO_AF_15))
/**
  * @}
  */                                   

/** @defgroup AFIO_EXTEND_PERIPH AFIO_EXTEND_PERIPH
  * @{
  */
#define IS_AFIO_EXTEND_ALL_PERIPH(PERIPH) (((PERIPH) == AFIO_EXTENDA) || \
																		((PERIPH) == AFIO_EXTENDB) || \
																		((PERIPH) == AFIO_EXTENDC) || \
																		((PERIPH) == AFIO_EXTENDD) || \
                                    ((PERIPH) == AFIO_EXTENDE))
/**
  * @}
  */

/**
  * @}
  */
	
/**
  * @}
  */

/* GPIO_Exported_Functions  */
void GPIO_DeInit(GPIO_TypeDef* GPIOx);
void GPIO_AFIODeInit(void);
void GPIO_Init(GPIO_TypeDef* GPIOx, GPIO_InitTypeDef* GPIO_InitStruct);
void GPIO_StructInit(GPIO_InitTypeDef* GPIO_InitStruct);
void GPIO_PinLockConfig(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
uint8_t GPIO_ReadInputDataBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
uint16_t GPIO_ReadInputData(GPIO_TypeDef* GPIOx);
uint8_t GPIO_ReadOutputDataBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
uint16_t GPIO_ReadOutputData(GPIO_TypeDef* GPIOx);
void GPIO_SetBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void GPIO_ResetBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void GPIO_WriteBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, BitAction BitVal);
void GPIO_Write(GPIO_TypeDef* GPIOx, uint16_t PortVal);
void GPIO_EventOutputConfig(uint8_t GPIO_PortSource, uint8_t GPIO_PinSource);
void GPIO_EventOutputCmd(FunctionalState NewState);
void GPIO_PinRemapConfig(uint32_t GPIO_Remap, FunctionalState NewState);
void GPIO_ExtendPinRemapConfig(uint32_t GPIO_Remap, FunctionalState NewState);
void GPIO_EXTILineConfig(uint8_t GPIO_PortSource, uint8_t GPIO_PinSource);

#ifdef __cplusplus
}
#endif

#endif /*__HK32F103XXXXA_GPIO_H */
 
