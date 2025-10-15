/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  hk32f103xxxxa_rcc.h
* @brief:     RCC initialization and configuration
* @author:    AE Team
*******************************************************************************/


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HK32F103XXXXA_RCC_H
#define __HK32F103XXXXA_RCC_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "hk32f103xxxxa_conf.h"

/** @addtogroup RCC RCC
  * @{
  */


/** @defgroup RCC_Exported_Types RCC_Exported_Types
  * @{
  */

/**
  * @brief  RCC Init structure definition
  */
typedef struct
{
	uint32_t SYSCLK_Frequency;  /*!< returns SYSCLK clock frequency expressed in Hz */
	uint32_t HCLK_Frequency;    /*!< returns HCLK clock frequency expressed in Hz */
	uint32_t PCLK1_Frequency;   /*!< returns PCLK1 clock frequency expressed in Hz */
	uint32_t PCLK2_Frequency;   /*!< returns PCLK2 clock frequency expressed in Hz */
	uint32_t ADC3CLK_Frequency;  /*!< returns ADC3CLK clock frequency expressed in Hz */
	uint32_t ADC2CLK_Frequency;   /*!< returns ADC2CLK clock frequency expressed in Hz */
	uint32_t ADC1CLK_Frequency ;  /*!< returns ADC1CLK clock frequency expressed in Hz */
	uint32_t USBIF_Frequency;   /*!< returns USBIF clock frequency expressed in Hz */
	uint32_t I2C1_Frequency ;  /*!< returns I2C1 clock frequency expressed in Hz */
	uint32_t I2C2_Frequency;   /*!< returns I2C2 clock frequency expressed in Hz */
}RCC_ClocksTypeDef;

/**
  * @}
  */

/** @defgroup RCC_Macro_Define RCC_Macro_Define
  * @{
  */

/**
  * @brief  HSE_configuration
 */

#define RCC_HSE_OFF                      ((uint32_t)0x00000000)
#define RCC_HSE_ON                       ((uint32_t)0x00010000)
#define RCC_HSE_Bypass                   ((uint32_t)0x00050000)
#define IS_RCC_HSE(HSE) (((HSE) == RCC_HSE_OFF) || ((HSE) == RCC_HSE_ON) || \
                         ((HSE) == RCC_HSE_Bypass))

/**
  * @brief LSE_configuration
  */

#define RCC_LSE_OFF                      ((uint8_t)0x00)
#define RCC_LSE_ON                       ((uint8_t)0x01)
#define RCC_LSE_Bypass                   ((uint8_t)0x04)
#define IS_RCC_LSE(LSE) (((LSE) == RCC_LSE_OFF) || ((LSE) == RCC_LSE_ON) || \
                         ((LSE) == RCC_LSE_Bypass))

/**
  * @brief PLL_entry_clock_source
 */

#define RCC_PLLSource_HSI8M_Div2           ((uint8_t)0x00)
#define RCC_PLLSource_HSI56M		       ((uint8_t)0x11)
#define RCC_PLLSource_HSE		           ((uint8_t)0x10)

#define IS_RCC_PLL_SOURCE(SOURCE) (((SOURCE) == RCC_PLLSource_HSI8M_Div2) || \
                                   ((SOURCE) == RCC_PLLSource_HSI56M) || \
                                   ((SOURCE) == RCC_PLLSource_HSE))

/**
  * @brief PLL_Predivision_factor
 */

#define RCC_PLLPREDIV_1                    ((uint32_t)0x00000000)
#define RCC_PLLPREDIV_2                    ((uint32_t)0x00000001)
#define RCC_PLLPREDIV_3                    ((uint32_t)0x00000002)
#define RCC_PLLPREDIV_4                    ((uint32_t)0x00000003)
#define RCC_PLLPREDIV_5                    ((uint32_t)0x00000004)
#define RCC_PLLPREDIV_6                    ((uint32_t)0x00000005)
#define RCC_PLLPREDIV_7                    ((uint32_t)0x00000006)
#define RCC_PLLPREDIV_8                    ((uint32_t)0x00000007)
#define RCC_PLLPREDIV_9                    ((uint32_t)0x00000008)
#define RCC_PLLPREDIV_10                   ((uint32_t)0x00000009)
#define RCC_PLLPREDIV_11                   ((uint32_t)0x0000000a)
#define RCC_PLLPREDIV_12                   ((uint32_t)0x0000000b)
#define RCC_PLLPREDIV_13                   ((uint32_t)0x0000000c)
#define RCC_PLLPREDIV_14                   ((uint32_t)0x0000000d)
#define RCC_PLLPREDIV_15                   ((uint32_t)0x0000000e)
#define RCC_PLLPREDIV_16                   ((uint32_t)0x0000000f)
#define IS_RCC_PLL_PREDIV(PREDIV) (((PREDIV) == RCC_PLLPREDIV_1) || ((PREDIV) == RCC_PLLPREDIV_2)   || \
                              ((PREDIV) == RCC_PLLPREDIV_3) || ((PREDIV) == RCC_PLLPREDIV_4)   || \
                              ((PREDIV) == RCC_PLLPREDIV_5) || ((PREDIV) == RCC_PLLPREDIV_6)   || \
                              ((PREDIV) == RCC_PLLPREDIV_7) || ((PREDIV) == RCC_PLLPREDIV_8)   || \
                              ((PREDIV) == RCC_PLLPREDIV_9) || ((PREDIV) == RCC_PLLPREDIV_10) || \
                              ((PREDIV) == RCC_PLLPREDIV_11) || ((PREDIV) == RCC_PLLPREDIV_12) || \
                              ((PREDIV) == RCC_PLLPREDIV_13) || ((PREDIV) == RCC_PLLPREDIV_14) || \
                              ((PREDIV) == RCC_PLLPREDIV_15) || ((PREDIV) == RCC_PLLPREDIV_16))

/**
  * @brief RCC_Trimming_Value
  */
#define IS_RCC_CALIBRATION_VALUE(VALUE)       ((VALUE) <= 0x1F)
#define IS_RCC_LSI_TRIM_VALUE(VALUE)          ((VALUE) <= 0xFF)
#define IS_CSS_THRESHOLD_Value(VALUE)         ((VALUE) <= 0x7F)

/**
  * @brief PLL_multiplication_factor
 */

#define IS_RCC_PLL_MUL(MUL) (((MUL) <= 0x7F )&& ((MUL) >=2))

/**
  * @brief System_clock_source_selection
 */


#define RCC_SYSCLKSource_HSI             ((uint32_t)0x00)
#define RCC_SYSCLKSource_HSE  	         ((uint32_t)0x01)
#define RCC_SYSCLKSource_PLLCLK          ((uint32_t)0x02)
#define RCC_SYSCLKSource_LSE        	 ((uint32_t)0x10)
#define RCC_SYSCLKSource_LSI     	     ((uint32_t)0x11)
#define RCC_SYSCLKSource_HSI56           ((uint32_t)0x12)
#define RCC_SYSCLKSource_HSI28           ((uint32_t)0x13)
#define RCC_SYSCLKSource_EXTCLK          ((uint32_t)0x14)

#define IS_RCC_SYSCLK_SOURCE(SOURCE) (((SOURCE) == RCC_SYSCLKSource_HSI) || \
                                      ((SOURCE) == RCC_SYSCLKSource_HSE) || \
                                      ((SOURCE) == RCC_SYSCLKSource_PLLCLK) || \
                                      ((SOURCE) == RCC_SYSCLKSource_LSE) || \
									                    ((SOURCE) == RCC_SYSCLKSource_LSI) || \
									                    ((SOURCE) == RCC_SYSCLKSource_HSI56) || \
									                    ((SOURCE) == RCC_SYSCLKSource_HSI28) || \
                                      ((SOURCE) == RCC_SYSCLKSource_EXTCLK))
/**
  * @brief  AHB_clock_source
 */

#define RCC_SYSCLK_Div1                  ((uint32_t)0x00000000)
#define RCC_SYSCLK_Div2                  ((uint32_t)0x00000080)
#define RCC_SYSCLK_Div4                  ((uint32_t)0x00000090)
#define RCC_SYSCLK_Div8                  ((uint32_t)0x000000A0)
#define RCC_SYSCLK_Div16                 ((uint32_t)0x000000B0)
#define RCC_SYSCLK_Div64                 ((uint32_t)0x000000C0)
#define RCC_SYSCLK_Div128                ((uint32_t)0x000000D0)
#define RCC_SYSCLK_Div256                ((uint32_t)0x000000E0)
#define RCC_SYSCLK_Div512                ((uint32_t)0x000000F0)
#define IS_RCC_HCLK(HCLK) (((HCLK) == RCC_SYSCLK_Div1) || ((HCLK) == RCC_SYSCLK_Div2) || \
                           ((HCLK) == RCC_SYSCLK_Div4) || ((HCLK) == RCC_SYSCLK_Div8) || \
                           ((HCLK) == RCC_SYSCLK_Div16) || ((HCLK) == RCC_SYSCLK_Div64) || \
                           ((HCLK) == RCC_SYSCLK_Div128) || ((HCLK) == RCC_SYSCLK_Div256) || \
                           ((HCLK) == RCC_SYSCLK_Div512))

/**
  * @brief  APB1_APB2_clock_source
 */


#define RCC_HCLK_Div1                    ((uint32_t)0x00000000)
#define RCC_HCLK_Div2                    ((uint32_t)0x00000400)
#define RCC_HCLK_Div4                    ((uint32_t)0x00000500)
#define RCC_HCLK_Div8                    ((uint32_t)0x00000600)
#define RCC_HCLK_Div16                   ((uint32_t)0x00000700)
#define IS_RCC_PCLK(PCLK) (((PCLK) == RCC_HCLK_Div1) || ((PCLK) == RCC_HCLK_Div2) || \
                           ((PCLK) == RCC_HCLK_Div4) || ((PCLK) == RCC_HCLK_Div8) || \
                           ((PCLK) == RCC_HCLK_Div16))

/**
  * @brief  RCC_Interrupt_clear
 */

#define RCC_IT_LSIRDY                    ((uint32_t)0x01)
#define RCC_IT_LSERDY                    ((uint32_t)0x02)
#define RCC_IT_HSIRDY                    ((uint32_t)0x04)
#define RCC_IT_HSERDY                    ((uint32_t)0x08)
#define RCC_IT_PLLRDY                    ((uint32_t)0x10)
#define RCC_IT_CSS                       ((uint32_t)0x80)

#define IS_RCC_IT(IT) ((((IT) & (uint8_t)0x80) == 0x00) && ((IT) != 0x00))
#define IS_RCC_GET_IT(IT) (((IT) == RCC_IT_LSIRDY) || ((IT) == RCC_IT_LSERDY) || \
                            ((IT) == RCC_IT_HSIRDY) || ((IT) == RCC_IT_HSERDY) || \
                           ((IT) == RCC_IT_PLLRDY) || ((IT) == RCC_IT_CSS) )
													 

#define IS_RCC_CLEAR_IT(IT) ((IT) != 0x00)

/**
  * @brief  USB_Device_clock_source
 */

#define RCC_USBCLKSource_PLLCLK_1Div5   ((uint8_t)0x00)
#define RCC_USBCLKSource_PLLCLK_1Div    ((uint8_t)0x01)
#define RCC_USBCLKSource_PLLCLK_2Div	((uint8_t)0x11)
#define RCC_USBCLKSource_PLLCLK_2Div5	((uint8_t)0x12)
#define RCC_USBCLKSource_PLLCLK_3Div 	((uint8_t)0x13)
#define RCC_USBCLKSource_PLLCLK_3Div5 	((uint8_t)0x14)
#define RCC_USBCLKSource_PLLCLK_4Div 	((uint8_t)0x15)



#define IS_RCC_USBCLK_SOURCE(SOURCE) (((SOURCE) == RCC_USBCLKSource_PLLCLK_1Div) || \
									 	((SOURCE) == RCC_USBCLKSource_PLLCLK_1Div5) || \
									 	((SOURCE) == RCC_USBCLKSource_PLLCLK_2Div) || \
									 	((SOURCE) == RCC_USBCLKSource_PLLCLK_2Div5) || \
									 	((SOURCE) == RCC_USBCLKSource_PLLCLK_3Div) || \
									 	((SOURCE) == RCC_USBCLKSource_PLLCLK_3Div5) || \
                                      	((SOURCE) == RCC_USBCLKSource_PLLCLK_4Div))

/**
  * @brief  USBIF_clock_source
 */

#define RCC_USBIFCLKSRC_PCLK1          (((uint32_t)0x00) << RCC_CFGR3_USBIFSW_Pos)
#define RCC_USBIFCLKSRC_PCLK1_DIV2     (((uint32_t)0x01) << RCC_CFGR3_USBIFSW_Pos)
#define RCC_USBIFCLKSRC_PCLK1_DIV3     (((uint32_t)0x02) << RCC_CFGR3_USBIFSW_Pos)
#define RCC_USBIFCLKSRC_PCLK1_DIV4     (((uint32_t)0x03) << RCC_CFGR3_USBIFSW_Pos)

#define IS_RCC_USBIFCLK_SOURCE(SOURCE) (((SOURCE) == RCC_USBIFCLKSRC_PCLK1) || \
										((SOURCE) == RCC_USBIFCLKSRC_PCLK1_DIV2) || \
										((SOURCE) == RCC_USBIFCLKSRC_PCLK1_DIV3) || \
										((SOURCE) == RCC_USBIFCLKSRC_PCLK1_DIV4))

/**
  * @brief  ADC_clock_source
 */

#define RCC_PCLK2_Div2                   ((uint8_t)0x00)
#define RCC_PCLK2_Div4                   ((uint8_t)0x01)
#define RCC_PCLK2_Div6                   ((uint8_t)0x02)
#define RCC_PCLK2_Div8                   ((uint8_t)0x03)
#define RCC_PCLK2_Div10                  ((uint8_t)0x11)
#define RCC_PCLK2_Div12                  ((uint8_t)0x12)
#define RCC_PCLK2_Div14                  ((uint8_t)0x13)
#define RCC_PCLK2_Div16                  ((uint8_t)0x14)
#define RCC_PCLK2_Div20                  ((uint8_t)0x15)

#define IS_RCC_ADCPRE(ADCPRE) (((ADCPRE) == RCC_PCLK2_Div2) || ((ADCPRE) == RCC_PCLK2_Div4) || \
                               ((ADCPRE) == RCC_PCLK2_Div6) || ((ADCPRE) == RCC_PCLK2_Div8)|| \
                               ((ADCPRE) == RCC_PCLK2_Div10) || ((ADCPRE) == RCC_PCLK2_Div12) || \
                               ((ADCPRE) == RCC_PCLK2_Div14) || ((ADCPRE) == RCC_PCLK2_Div16) || \
                               ((ADCPRE) == RCC_PCLK2_Div20))


/**
  * @brief RTC_clock_source
  */

#define RCC_RTCCLKSource_LSE             ((uint32_t)0x00000100)
#define RCC_RTCCLKSource_LSI             ((uint32_t)0x00000200)
#define RCC_RTCCLKSource_HSE_Div128      ((uint32_t)0x00000300)
#define IS_RCC_RTCCLK_SOURCE(SOURCE) (((SOURCE) == RCC_RTCCLKSource_LSE) || \
                                      ((SOURCE) == RCC_RTCCLKSource_LSI) || \
                                      ((SOURCE) == RCC_RTCCLKSource_HSE_Div128))


/**
  * @brief AHB_peripheral
  */

#define RCC_AHBPeriph_DMA1               ((uint32_t)0x00000001)
#define RCC_AHBPeriph_DMA2               ((uint32_t)0x00000002)
#define RCC_AHBPeriph_SRAM               ((uint32_t)0x00000004)
#define RCC_AHBPeriph_FLITF              ((uint32_t)0x00000010)
#define RCC_AHBPeriph_CRC                ((uint32_t)0x00000040)
#define RCC_AHBPeriph_FSMC               ((uint32_t)0x00000100)
#define RCC_AHBPeriph_SDIO               ((uint32_t)0x00000400)

#define IS_RCC_AHB_PERIPH(PERIPH) ((((PERIPH) & 0xFFFFFAA8) == 0x00) && ((PERIPH) != 0x00))

/**
  * @brief AHB_peripheral2
  */
#define RCC_AHBPeriph2_CACHE                ((uint32_t)0x00000100)
#define IS_RCC_AHB_PERIPH2(PERIPH) ((((PERIPH) & 0xFFFFFEFF) == 0x00) && ((PERIPH) != 0x00))

/**
  * @brief APB2_peripheral
  */

#define RCC_APB2Periph_AFIO              ((uint32_t)0x00000001)
#define RCC_APB2Periph_GPIOA             ((uint32_t)0x00000004)
#define RCC_APB2Periph_GPIOB             ((uint32_t)0x00000008)
#define RCC_APB2Periph_GPIOC             ((uint32_t)0x00000010)
#define RCC_APB2Periph_GPIOD             ((uint32_t)0x00000020)
#define RCC_APB2Periph_GPIOE             ((uint32_t)0x00000040)
#define RCC_APB2Periph_ADC1              ((uint32_t)0x00000200)
#define RCC_APB2Periph_ADC2              ((uint32_t)0x00000400)
#define RCC_APB2Periph_TIM1              ((uint32_t)0x00000800)
#define RCC_APB2Periph_SPI1              ((uint32_t)0x00001000)
#define RCC_APB2Periph_TIM8              ((uint32_t)0x00002000)
#define RCC_APB2Periph_USART1            ((uint32_t)0x00004000)
#define RCC_APB2Periph_ADC3              ((uint32_t)0x00008000)

#define IS_RCC_APB2_PERIPH(PERIPH) ((((PERIPH) & 0xFFFF0182) == 0x00) && ((PERIPH) != 0x00))


/**
  * @brief APB1_peripheral
  */

#define RCC_APB1Periph_TIM2              ((uint32_t)0x00000001)
#define RCC_APB1Periph_TIM3              ((uint32_t)0x00000002)
#define RCC_APB1Periph_TIM4              ((uint32_t)0x00000004)
#define RCC_APB1Periph_TIM5              ((uint32_t)0x00000008)
#define RCC_APB1Periph_TIM6              ((uint32_t)0x00000010)
#define RCC_APB1Periph_TIM7              ((uint32_t)0x00000020)
#define RCC_APB1Periph_WWDG              ((uint32_t)0x00000800)
#define RCC_APB1Periph_SPI2              ((uint32_t)0x00004000)
#define RCC_APB1Periph_SPI3              ((uint32_t)0x00008000)
#define RCC_APB1Periph_USART2            ((uint32_t)0x00020000)
#define RCC_APB1Periph_USART3            ((uint32_t)0x00040000)
#define RCC_APB1Periph_UART4             ((uint32_t)0x00080000)
#define RCC_APB1Periph_UART5             ((uint32_t)0x00100000)
#define RCC_APB1Periph_I2C1              ((uint32_t)0x00200000)
#define RCC_APB1Periph_I2C2              ((uint32_t)0x00400000)
#define RCC_APB1Periph_USB               ((uint32_t)0x00800000)
#define RCC_APB1Periph_CAN1              ((uint32_t)0x02000000)
#define RCC_APB1Periph_BKP               ((uint32_t)0x08000000)
#define RCC_APB1Periph_PWR               ((uint32_t)0x10000000)
#define RCC_APB1Periph_DAC               ((uint32_t)0x20000000)
#define IS_RCC_APB1_PERIPH(PERIPH) ((((PERIPH) & 0xC10137C0) == 0x00) && ((PERIPH) != 0x00))


/**
  * @brief Clock_source_to_output_on_MCO_pin
  */

#define RCC_MCO_NoClock                  ((uint32_t)0x00)
#define RCC_MCO_SYSCLK                   ((uint32_t)0x04)
#define RCC_MCO_HSI8M                    ((uint32_t)0x05)
#define RCC_MCO_HSE                      ((uint32_t)0x06)
#define RCC_MCO_PLLCLK_Div2              ((uint32_t)0x07)
#define RCC_MCO_LSI			                 ((uint32_t)0x0C)
#define RCC_MCO_LSE		                   ((uint32_t)0x0D)
#define RCC_MCO_HSI28              	     ((uint32_t)0x0E)

#define IS_RCC_MCO(MCO) (((MCO) == RCC_MCO_NoClock) || ((MCO) == RCC_MCO_HSI8M) || \
                          ((MCO) == RCC_MCO_SYSCLK)  || ((MCO) == RCC_MCO_HSE) || \
                          ((MCO) == RCC_MCO_LSI)  || ((MCO) == RCC_MCO_LSE) || \
                          ((MCO) == RCC_MCO_PLLCLK_Div2)|| ((MCO) == RCC_MCO_HSI28))

/**
  * @brief MCO_PRE define
  */
#define RCC_MCOPrescaler_1                (((uint32_t)0x00) <<RCC_CFGR5_MCOPRE_Pos)
#define RCC_MCOPrescaler_2                (((uint32_t)0x01) <<RCC_CFGR5_MCOPRE_Pos)
#define RCC_MCOPrescaler_4                (((uint32_t)0x02) <<RCC_CFGR5_MCOPRE_Pos)
#define RCC_MCOPrescaler_8                (((uint32_t)0x03) <<RCC_CFGR5_MCOPRE_Pos)
#define RCC_MCOPrescaler_16               (((uint32_t)0x04) <<RCC_CFGR5_MCOPRE_Pos)
#define RCC_MCOPrescaler_32               (((uint32_t)0x05) <<RCC_CFGR5_MCOPRE_Pos)
#define RCC_MCOPrescaler_64               (((uint32_t)0x06) <<RCC_CFGR5_MCOPRE_Pos)
#define RCC_MCOPrescaler_128              (((uint32_t)0x07) <<RCC_CFGR5_MCOPRE_Pos)

#define IS_RCC_MCO_PRESCALER(PRESCALER) (((PRESCALER) == RCC_MCOPrescaler_1)  || \
                                         ((PRESCALER) == RCC_MCOPrescaler_2)  || \
                                         ((PRESCALER) == RCC_MCOPrescaler_4)  || \
                                         ((PRESCALER) == RCC_MCOPrescaler_8)  || \
                                         ((PRESCALER) == RCC_MCOPrescaler_16) || \
                                         ((PRESCALER) == RCC_MCOPrescaler_32) || \
                                         ((PRESCALER) == RCC_MCOPrescaler_64) || \
                                         ((PRESCALER) == RCC_MCOPrescaler_128))

/**
  * @brief RCC_Flag
  */


#define RCC_FLAG_HSIRDY                  ((uint8_t)0x21)
#define RCC_FLAG_HSERDY                  ((uint8_t)0x31)
#define RCC_FLAG_PLLRDY                  ((uint8_t)0x39)
#define RCC_FLAG_LSERDY                  ((uint8_t)0x41)
#define RCC_FLAG_LSIRDY                  ((uint8_t)0x61)
#define RCC_FLAG_PINRST                  ((uint8_t)0x7A)
#define RCC_FLAG_PORRST                  ((uint8_t)0x7B)
#define RCC_FLAG_SFTRST                  ((uint8_t)0x7C)
#define RCC_FLAG_IWDGRST                 ((uint8_t)0x7D)
#define RCC_FLAG_WWDGRST                 ((uint8_t)0x7E)
#define RCC_FLAG_LPWRRST                 ((uint8_t)0x7F)
#define RCC_FLAG_HSI28RDY                ((uint8_t)0x93)
#define RCC_FLAG_HSI56RDY                ((uint8_t)0x91)
#define IS_RCC_FLAG(FLAG) (((FLAG) == RCC_FLAG_HSIRDY) || ((FLAG) == RCC_FLAG_HSERDY) || \
                            ((FLAG) == RCC_FLAG_PLLRDY) || ((FLAG) == RCC_FLAG_LSERDY) || \
                            ((FLAG) == RCC_FLAG_LSIRDY) || ((FLAG) == RCC_FLAG_PINRST) || \
                            ((FLAG) == RCC_FLAG_PORRST) || ((FLAG) == RCC_FLAG_SFTRST) || \
                            ((FLAG) == RCC_FLAG_IWDGRST)|| ((FLAG) == RCC_FLAG_WWDGRST)|| \
                            ((FLAG) == RCC_FLAG_HSI28RDY)|| ((FLAG) == RCC_FLAG_HSI56RDY)|| \
                            ((FLAG) == RCC_FLAG_LPWRRST)) 

/**
  * @}
  */

/** @defgroup RCC_Exported_Functions RCC_Exported_Functions
  * @{
  */


/** @defgroup RCC_Group3 RCC initialization function
	* @{
  */
void RCC_DeInit(void);
/**
  * @}
  */

/** @defgroup RCC_Group4 Internal/external clocks, PLL, CSS and MCO configuration functions
	* @{
  */
void RCC_HSEConfig(uint32_t RCC_HSE);
ErrorStatus RCC_WaitForHSEStartUp(void);
ErrorStatus RCC_WaitForStartUp(uint8_t RDYFlag);
void RCC_HSITrimValue(uint8_t HSITrimValue);
void RCC_HSICalValue(uint8_t HSICalValue);
void RCC_LSITRIM(uint16_t LSITRIMValue);
void RCC_HSICmd(FunctionalState NewState);
void RCC_HSI28Cmd(FunctionalState NewState);
void RCC_HSI56Cmd(FunctionalState NewState);
void RCC_PLLConfig(uint32_t RCC_PLLSource, uint32_t RCC_PLLMul);
void RCC_PREDIVConfig(uint32_t RCC_PREDIV_Div);
void RCC_PLLCmd(FunctionalState NewState);
void RCC_MCOConfig(uint32_t RCC_MCO, uint32_t RCC_MCOPRE);
void RCC_LSEConfig(uint8_t RCC_LSE);
void RCC_LSICmd(FunctionalState NewState);
/**
  * @}
  */

/** @defgroup RCC_Group5 Peripheral clocks configuration functions
	* @{
  */
void RCC_SYSCLKConfig(uint32_t RCC_SYSCLKSource);
uint8_t RCC_GetSYSCLKSource(void);
void RCC_HCLKConfig(uint32_t RCC_SYSCLK);
void RCC_PCLK1Config(uint32_t RCC_HCLK);
void RCC_PCLK2Config(uint32_t RCC_HCLK);
void RCC_ITConfig(uint32_t RCC_IT, FunctionalState NewState);
void RCC_USBCLKConfig(uint32_t RCC_USBCLKSource);
void RCC_USBIFCLKConfig(uint32_t RCC_USBIFCLKSource);

void RCC_ADC1CLKConfig(uint32_t RCC_ADCCLK);
void RCC_ADC2CLKConfig(uint32_t RCC_ADCCLK);
void RCC_ADC3CLKConfig(uint32_t RCC_ADCCLK);
void RCC_TSCLKConfig(uint8_t RCC_TSPRE);

void RCC_RTCCLKConfig(uint32_t RCC_RTCCLKSource);
void RCC_RTCCLKCmd(FunctionalState NewState);
void RCC_GetClocksFreq(RCC_ClocksTypeDef* RCC_Clocks);
/**
  * @}
  */

/** @defgroup RCC_Group6 System, AHB and APB busses clocks configuration functions
	* @{
  */
void RCC_AHBPeriphClockCmd(uint32_t RCC_AHBPeriph, FunctionalState NewState);
void RCC_AHBPeriph2ClockCmd(uint32_t RCC_AHBPeriph, FunctionalState NewState);
void RCC_APB2PeriphClockCmd(uint32_t RCC_APB2Periph, FunctionalState NewState);
void RCC_APB2Periph2ClockCmd(uint32_t RCC_APB2Periph, FunctionalState NewState);
void RCC_APB1PeriphClockCmd(uint32_t RCC_APB1Periph, FunctionalState NewState);

void RCC_APB2PeriphResetCmd(uint32_t RCC_APB2Periph, FunctionalState NewState);
void RCC_APB2Periph2ResetCmd(uint32_t RCC_APB2Periph, FunctionalState NewState);
void RCC_AHBPeriphResetCmd(uint32_t RCC_AHBPeriph, FunctionalState NewState);
void RCC_AHBPeriph2ResetCmd(uint32_t RCC_AHBPeriph2, FunctionalState NewState);
void RCC_APB1PeriphResetCmd(uint32_t RCC_APB1Periph, FunctionalState NewState);
/**
  * @}
  */

/** @defgroup RCC_Group7 Interrupts and flags management functions
	* @{
  */
void RCC_BackupResetCmd(FunctionalState NewState);
void RCC_ClockSecuritySystemCmd(FunctionalState NewState);
FlagStatus RCC_GetFlagStatus(uint8_t RCC_FLAG);
void RCC_ClearFlag(void);
ITStatus RCC_GetITStatus(uint32_t RCC_IT);
void RCC_ClearITPendingBit(uint32_t RCC_IT);
void RCC_CSSThresholdConfig(uint8_t CSS_THRESHOLD_Value);
/**
  * @}
  */
#ifdef __cplusplus
}
#endif

#endif /*__HK32F103XXXXA_RCC_H */

/**
  * @}
  */
/**
  * @}
  */
