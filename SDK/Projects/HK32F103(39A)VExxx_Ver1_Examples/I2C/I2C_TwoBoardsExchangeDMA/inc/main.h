/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  main.h
* @brief:     Header for main.c file.
* @author:    AE Team
*******************************************************************************/


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif
 
/* Includes ------------------------------------------------------------------*/
#include "hk32f103xxxxa_conf.h"
#include "hk32f103xxxxa_eval.h"

/* Exported types ------------------------------------------------------------*/
extern __IO uint8_t sDataNum;
extern uint8_t RxFlagM; 

#define MASTER_MODE                    (0)
#define SLAVE_MODE                     (1)

#define s_I2C                          I2C1
#define s_I2C_CLK                      RCC_APB1Periph_I2C1
#define s_I2C_SCL_PIN                  GPIO_Pin_6                
#define s_I2C_SCL_GPIO_PORT            GPIOB                      
#define s_I2C_SCL_GPIO_CLK             RCC_APB2Periph_GPIOB
#define s_I2C_SDA_PIN                  GPIO_Pin_7                
#define s_I2C_SDA_GPIO_PORT            GPIOB                      
#define s_I2C_SDA_GPIO_CLK             RCC_APB2Periph_GPIOB

#define s_I2C_DMA                      DMA1
#define s_I2C_DMA_CHANNEL_TX           DMA1_Channel6
#define s_I2C_DMA_CHANNEL_RX           DMA1_Channel7
#define s_I2C_DMA_FLAG_TX_TC           DMA1_IT_TC6
#define s_I2C_DMA_FLAG_TX_GL           DMA1_IT_GL6
#define s_I2C_DMA_FLAG_RX_TC           DMA1_IT_TC7
#define s_I2C_DMA_FLAG_RX_GL           DMA1_IT_GL7
#define s_I2C_DMA_CLK                  RCC_AHBPeriph_DMA1
#define s_I2C_DR_Address               ((uint32_t)0x40005410)

#define s_I2C_DMA_TX_IRQn              DMA1_Channel6_IRQn
#define s_I2C_DMA_RX_IRQn              DMA1_Channel7_IRQn
#define s_I2C_DMA_TX_IRQHandler        DMA1_Channel6_IRQHandler
#define s_I2C_DMA_RX_IRQHandler        DMA1_Channel7_IRQHandler
#define s_I2C_DMA_PREPRIO              (0)
#define s_I2C_DMA_SUBPRIO              (0)

#define CLOCK_SPEED                    (400000)
                                       
#define MASTER_ADDRESS                 (0x30)
#define SLAVE_ADDRESS                  (0x28)
                                       
#define s_FLAG_TIMEOUT                 ((uint32_t)0x1000)
#define s_LONG_TIMEOUT                 ((uint32_t)(10 * s_FLAG_TIMEOUT))
                                       
#define BUFFER_SIZE                    (20)
#define BUFFER_SIZE_R                  (100)

#define s_DIRECTION_TX                 (0)
#define s_DIRECTION_RX                 (1)

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

void s_LowLevel_DMAConfig(uint32_t pBuffer, uint32_t BufferSize, uint32_t Direction);
  
#ifdef __cplusplus
}
#endif

#endif /*__MAIN_H */

