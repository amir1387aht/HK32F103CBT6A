/*******************************************************************************
* @copyright:  Shenzhen Hangshun Chip Technology R&D Co., Ltd 
* @filename:   hk32f103xxxxa_conf.h
* @brief:      Library configuration file. 
* @author:     AE Team 
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HK32F103xxxxA_CONF_H
#define __HK32F103xxxxA_CONF_H

#ifdef __cplusplus
extern "C" {
#endif


/* ########################## Oscillator Values adaptation ####################*/
/* In the following line adjust the value of External High Speed oscillator (HSE)
   used in your application range 4M-32M*/
#define HSE_VALUE    	        ((uint32_t)8000000) /*!< Value of the External oscillator in Hz */
#define SAI_EXT_CLK		        ((uint32_t)49152000)

/* In the following line adjust the External High Speed oscillator (HSE) Startup Timeout value*/
#define HSE_STARTUP_TIMEOUT     ((uint16_t)0xFFFF) /*!< Time out for HSE start up */
#define HSI_STARTUP_TIMEOUT     ((uint16_t)0xFFFF) /*!< Time out for HSI start up */

#define HSI_VALUE    	        ((uint32_t)8000000) /*!< Value of the Internal oscillator in Hz*/
#define HSI8M_VALUE    	        ((uint32_t)8000000) /*!< Value of the Internal oscillator in Hz*/
#define HSI28M_VALUE            ((uint32_t)28000000) /*!< Value of the Internal oscillator in Hz*/
#define HSI56M_VALUE            ((uint32_t)56000000) /*!< Value of the Internal oscillator in Hz*/

#define LSE_VALUE    	        ((uint32_t)32768) /*!< Value of the LSE in Hz*/
#define LSI_VALUE    	        ((uint32_t)40000) /*!< Value of the LSI in Hz*/

#define EXTCLK_VALUE	        ((uint32_t)56000000) /*!< Value of the Internal oscillator in Hz*/

#define FLASH_BASE              ((uint32_t)0x08000000) /*!< FLASH base address in the alias region */
#define SRAM_BASE               ((uint32_t)0x20000000) /*!< SRAM base address in the alias region */
#define PERIPH_BASE             ((uint32_t)0x40000000) /*!< Peripheral base address in the alias region */

#define SRAM_BB_BASE            ((uint32_t)0x22000000) /*!< SRAM base address in the bit-band region */
#define PERIPH_BB_BASE          ((uint32_t)0x42000000) /*!< Peripheral base address in the bit-band region */

/*!< Peripheral memory map */
#define APB1PERIPH_BASE         PERIPH_BASE
#define APB2PERIPH_BASE         (PERIPH_BASE + 0x10000)
#define AHBPERIPH_BASE          (PERIPH_BASE + 0x20000)


/**
  * @}
  */

#include "stdint.h"
/** @addtogroup Device_Included
  * @{
  */

#include "hk32f103xxxxa.h"



/* Exported constants --------------------------------------------------------*/

/* ########################## Module Selection ############################## */
/**
  * @brief This is the list of modules to be used in the driver with hk32f103xxxxa
  */

/* Exported macro ------------------------------------------------------------*/
#include "hk32f103xxxxa_bkp.h"
#include "hk32f103xxxxa_cache.h"
#include "hk32f103xxxxa_can.h"
#include "hk32f103xxxxa_crc.h"
#include "hk32f103xxxxa_dac.h"
#include "hk32f103xxxxa_dbgmcu.h"
#include "hk32f103xxxxa_dma.h"
#include "hk32f103xxxxa_misc.h"
#include "hk32f103xxxxa_exti.h"
#include "hk32f103xxxxa_flash.h"
#include "hk32f103xxxxa_fsmc.h"
#include "hk32f103xxxxa_gpio.h"
#include "hk32f103xxxxa_i2c.h"
#include "hk32f103xxxxa_iwdg.h"
#include "hk32f103xxxxa_pwr.h"
#include "hk32f103xxxxa_rtc.h"
#include "hk32f103xxxxa_sdio.h"
#include "hk32f103xxxxa_spi.h"
#include "hk32f103xxxxa_tim.h"
#include "hk32f103xxxxa_usart.h"
#include "hk32f103xxxxa_wwdg.h"
#include "hk32f103xxxxa_adc.h"
#include "hk32f103xxxxa_rcc.h"



/**
 * @brief HK32F0xx Standard Peripheral Library version number V1.0.0
   */
#define __HK32F103xxxxA_STDPERIPH_VERSION_MAIN   (0x01) /*!< [31:24] main version */
#define __HK32F103xxxxA_STDPERIPH_VERSION_SUB1   (0x00) /*!< [23:16] sub1 version */
#define __HK32F103xxxxA_STDPERIPH_VERSION_SUB2   (0x00) /*!< [15:8]  sub2 version */
#define __HK32F103xxxxA_STDPERIPH_VERSION_RC     (0x00) /*!< [7:0]  release candidate */
#define __HK32F103xxxxA_STDPERIPH_VERSION        ((__HK32F103xxxxA_STDPERIPH_VERSION_MAIN << 24)\
                                             |(__HK32F103xxxxA_STDPERIPH_VERSION_SUB1 << 16)\
                                             |(__HK32F103xxxxA_STDPERIPH_VERSION_SUB2 << 8)\
                                             |(__HK32F103xxxxA_STDPERIPH_VERSION_RC))

/* ########################### System Configuration ######################### */
/**
  * @brief This is the system configuration section
  */
#define  VDD_VALUE                    3300U /*!< Value of VDD in mv */
#define  TICK_INT_PRIORITY            0x0FU /*!< tick interrupt priority */
#define  PREFETCH_ENABLE              1U

/* ########################## Assert Selection ############################## */
/**
  * @brief Uncomment the line below to expanse the "assert_param" macro in the
  *        HAL drivers code
  */
/* #define USE_FULL_ASSERT    1U */
#ifdef  USE_FULL_ASSERT

/**
  * @brief  The assert_param macro is used for function's parameters check.
  * @param  expr: If expr is false, it calls assert_failed function which reports
  *         the name of the source file and the source line number of the call
  *         that failed. If expr is true, it returns no value.
  * @retval None
  */
  #define assert_param(expr) ((expr) ? (void)0 : assert_failed((uint8_t *)__FILE__, __LINE__))
/* Exported functions ------------------------------------------------------- */
  void assert_failed(uint8_t* file, uint32_t line);
#else
  #define assert_param(expr) ((void)0)
#endif /* USE_FULL_ASSERT */

#ifdef __cplusplus
}
#endif

#endif
